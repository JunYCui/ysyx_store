/*
 * Data Cache Module (2-Way Set-Associative, Write-Back)
 * 
 * Features:
 * - 2-way set-associative cache (LRU replacement)
 * - Write-back policy with dirty bit
 * - Byte-level write mask support (mem_wstrb)
 * - Synchronous read/write with peripheral interface
 */

module ysyx_24100029_dcache(
    // System Signals
    input                               clk,             // Clock
    input                               rst,             // Active-high reset
    // CPU Interface
    input              [  31: 0]        mem_addr,        // Memory access address
    input              [   1: 0]        mem_opcode,      // 0-none, 1-read, 2-write
    input              [  31: 0]        mem_wdata,       // Write data from CPU
    input              [   3: 0]        mem_wstrb,       // Byte write enable (1 bit per byte)
    output             [  31: 0]        mem_rdata,       // Read data to CPU
    output                              mem_resp,        // 1 = operation complete
    // Peripheral Interface (for cache miss handling)
    output             [  31: 0]        perip_addr,      // Physical address to memory
    output                              perip_wen,       // Peripheral write enable (WB state)
    output wire        [   1: 0]        perip_mask,      // Transfer size mask (always word)
    output             [  31: 0]        perip_wdata,     // Write data to memory (WB state)
    input              [  31: 0]        perip_rdata      // Read data from memory (DATA state)

);

// --------------------------------
// Cache Configuration Parameters
// --------------------------------
    localparam ADDR_WIDTH = 32;          // Full address width
    localparam BLOCK_WIDTH = 64;         // Cache line size (bits) = 8 bytes
    localparam INDEX_WIDTH = 3;          // Number of index bits (8 sets)
    localparam STATE_WIDTH = 2;          // 2 bits for line state (INVALID/VALID/DIRTY)
    localparam OFFSET_WIDTH = $clog2(BLOCK_WIDTH / 8);  // log2(8) = 3 (byte offset within block)
    localparam TAG_WIDTH = ADDR_WIDTH - INDEX_WIDTH - OFFSET_WIDTH;  // Tag bits = 32-3-3=26
    localparam CACHE_WIDTH = BLOCK_WIDTH + TAG_WIDTH + STATE_WIDTH + 1;  // 64(data) + 26(tag) + 2(state) + 1(age)
    localparam GROUP_WIDTH = 1;          // 2-way set-associative (group_choice = 0 or 1)
    localparam AGE_WIDTH = 1;

    /* State Parameter */
    localparam IDLE = 2'b00;            // Idle or cache hit
    localparam DATA = 2'b01;            // Load data from peripheral (cache miss)
    localparam WB   = 2'b10;            // Write-back dirty line to peripheral
    /* Block State Parameter */
    localparam INVALID = 2'b00;         // Line invalid
    localparam VALID   = 2'b01;         // Line valid (clean)
    localparam DIRTY   = 2'b10;         // Line dirty (needs write-back)


// --------------------------------
// Registers & Wires
// --------------------------------
    // Cache Memory (2-way set-associative)
    reg [CACHE_WIDTH-1:0] ram [2**INDEX_WIDTH-1:0][2**GROUP_WIDTH-1:0]; 
    // Format: [0:0]=AGE, [1:2]=STATE, [3:28]=TAG, [29:92]=DATA (64 bits)
    // FSM Control
    reg [1:0] state;                    // Current state (IDLE/DATA/WB)
    reg [1:0] counter;                  // Cycle counter for multi-cycle ops
    reg [1:0] opcode_r;                 // Registered mem_opcode
    reg [3:0] mem_wstrb_r;              // Registered mem_wstrb
    reg [INDEX_WIDTH-1:0] index_r;      // Registered index
    reg [31:0] mem_wdata_r;             // Registered write data
    reg group_choice_r;                 // Selected way (during miss)
    reg mem_addr_r;                     // Registered LSB of offset (selects upper/lower 32-bit word)
    reg [TAG_WIDTH-1:0] tag_r;          // Registered tag


    // Combinational Signals
    wire [INDEX_WIDTH-1:0] index;       // Current index from address
    wire [TAG_WIDTH-1:0] tag;           // Current tag from address
    wire group_choice;                  // Selected way (LRU or hit way)
    wire is_hit;                        // 1 = cache hit
    wire is_dirty;                      // 1 = selected line is dirty
    wire [31:0] perip_addr_r;           // Peripheral read address
    wire [31:0] perip_addr_w;           // Peripheral write address (WB)

// --------------------------------
// Finite State Machine (FSM)
// --------------------------------
    always @(posedge clk) begin
        if (rst) state <= IDLE;
        else begin
            case (state)
                IDLE: // Wait for request
                    // Transition to WB if dirty, else DATA on miss
                    state <= (is_hit || mem_opcode == 0) ? IDLE : 
                             is_dirty ? WB : DATA;
                DATA: // Fetch data from peripheral
                    state <= (counter == 1) ? IDLE : DATA;  // Takes 2 cycles
                WB:   // Write-back dirty line
                    state <= (counter == 1) ? DATA : WB;    // Takes 2 cycles
                default: state <= IDLE;
            endcase
        end
    end

// --------------------------------
// Register Inputs on Cache Miss
// --------------------------------
    always @(posedge clk) begin
        if (rst) begin
            {mem_wdata_r, mem_wstrb_r, opcode_r, index_r, 
             group_choice_r, mem_addr_r, tag_r} <= 0;
        end
        else if (state == IDLE && ~(is_hit || mem_opcode == 0)) begin
            // Latch inputs when miss occurs
            opcode_r    <= mem_opcode;
            mem_wstrb_r <= mem_wstrb;
            index_r     <= index;
            mem_wdata_r <= mem_wdata;
            group_choice_r <= group_choice;
            mem_addr_r  <= mem_addr[OFFSET_WIDTH-1];  // Selects 32-bit word within block
            tag_r       <= tag;
        end
    end

// --------------------------------
// Cycle Counter for Multi-Cycle Ops
// --------------------------------
    always @(posedge clk) begin
        if (rst) counter <= 0;
        else if (counter == 1) counter <= 0;
        else if (state == DATA || state == WB) counter <= counter + 1;
    end

// --------------------------------
// Cache Data Update Logic
// --------------------------------
    always @(posedge clk) begin
        case (state)
        IDLE: if(is_hit)begin
            // update data
                 // --------------------------------------------------------
                // Byte-wise write with mask (Lower 32-bit word in cache line)
                // --------------------------------------------------------
                // 字节0 (bits 7:0)
                ram[index][group_choice][AGE_WIDTH + STATE_WIDTH + TAG_WIDTH +:8] <= 
                    (mem_opcode == 2'd2 & ~mem_addr[OFFSET_WIDTH-1] & mem_wstrb[0]) ? 
                    mem_wdata[7:0] : ram[index][group_choice][AGE_WIDTH + STATE_WIDTH + TAG_WIDTH +:8];
                // 字节1 (bits 15:8)
                ram[index][group_choice][AGE_WIDTH + STATE_WIDTH + TAG_WIDTH + 8 +:8] <= 
                    (mem_opcode == 2'd2 & ~mem_addr[OFFSET_WIDTH-1] & mem_wstrb[1]) ? 
                    mem_wdata[15:8] : ram[index][group_choice][AGE_WIDTH + STATE_WIDTH + TAG_WIDTH + 8 +:8];
                // 字节2 (bits 23:16)
                ram[index][group_choice][AGE_WIDTH + STATE_WIDTH + TAG_WIDTH + 16 +:8] <= 
                    (mem_opcode == 2'd2 & ~mem_addr[OFFSET_WIDTH-1] & mem_wstrb[2]) ? 
                    mem_wdata[23:16] : ram[index][group_choice][AGE_WIDTH + STATE_WIDTH + TAG_WIDTH + 16 +:8];
                // 字节3 (bits 31:24)
                ram[index][group_choice][AGE_WIDTH + STATE_WIDTH + TAG_WIDTH + 24 +:8] <= 
                    (mem_opcode == 2'd2 & ~mem_addr[OFFSET_WIDTH-1] & mem_wstrb[3]) ? 
                    mem_wdata[31:24] : ram[index][group_choice][AGE_WIDTH + STATE_WIDTH + TAG_WIDTH + 24 +:8];
                // --------------------------------------------------------
                // Byte-wise write with mask (Upper 32-bit word in cache line)
                // --------------------------------------------------------
                // 字节4 (bits 39:32)
                ram[index][group_choice][AGE_WIDTH + STATE_WIDTH + TAG_WIDTH + 32 +:8] <= 
                    (mem_opcode == 2'd2 & mem_addr[OFFSET_WIDTH-1] & mem_wstrb[0]) ? 
                    mem_wdata[7:0] : ram[index][group_choice][AGE_WIDTH + STATE_WIDTH + TAG_WIDTH + 32 +:8];
                // 字节5 (bits 47:40)
                ram[index][group_choice][AGE_WIDTH + STATE_WIDTH + TAG_WIDTH + 32 + 8 +:8] <= 
                    (mem_opcode == 2'd2 & mem_addr[OFFSET_WIDTH-1] & mem_wstrb[1]) ? 
                    mem_wdata[15:8] : ram[index][group_choice][AGE_WIDTH + STATE_WIDTH + TAG_WIDTH + 32 + 8 +:8];
                // 字节6 (bits 55:48)
                ram[index][group_choice][AGE_WIDTH + STATE_WIDTH + TAG_WIDTH + 32 + 16 +:8] <= 
                    (mem_opcode == 2'd2 & mem_addr[OFFSET_WIDTH-1] & mem_wstrb[2]) ? 
                    mem_wdata[23:16] : ram[index][group_choice][AGE_WIDTH + STATE_WIDTH + TAG_WIDTH + 32 + 16 +:8];
                // 字节7 (bits 63:56)
                ram[index][group_choice][AGE_WIDTH + STATE_WIDTH + TAG_WIDTH + 32 + 24 +:8] <= 
                    (mem_opcode == 2'd2 & mem_addr[OFFSET_WIDTH-1] & mem_wstrb[3]) ? 
                    mem_wdata[31:24] : ram[index][group_choice][AGE_WIDTH + STATE_WIDTH + TAG_WIDTH + 32 + 24 +:8];

            ram[index][group_choice][AGE_WIDTH +:STATE_WIDTH] <= (mem_opcode == 2'd2 || ram[index][group_choice][AGE_WIDTH +:STATE_WIDTH] == DIRTY)? DIRTY:  VALID;
            //update age
            ram[index][group_choice][0 +:AGE_WIDTH] <= (mem_opcode != 2'd0)? 1'b1 : ram[index][group_choice][0 +:AGE_WIDTH]; // least Recent Used
            ram[index][~group_choice][0 +:AGE_WIDTH] <= (mem_opcode != 2'd0)? 1'b0 : ram[index][~group_choice][0 +:AGE_WIDTH];
        end
        DATA:begin
            // upadate state
            ram[index_r][group_choice_r][AGE_WIDTH +:STATE_WIDTH] <= (opcode_r == 2'd2)? DIRTY : VALID;
            // update tag
            ram[index_r][group_choice_r][AGE_WIDTH+STATE_WIDTH +:TAG_WIDTH] <= tag_r;
            // update data
            // --------------------------------------------------------
            // Byte-wise write with mask (Lower 32-bit word in cache line)
            // --------------------------------------------------------
            ram[index_r][group_choice_r][AGE_WIDTH + STATE_WIDTH + TAG_WIDTH +:8] <= (opcode_r == 2'd2 & ~mem_addr_r & mem_wstrb_r[0] )? mem_wdata_r[7:0]:(counter == 0)? perip_rdata[7:0] :ram[index_r][group_choice_r][AGE_WIDTH + STATE_WIDTH + TAG_WIDTH +:8] ;
            ram[index_r][group_choice_r][AGE_WIDTH + STATE_WIDTH + TAG_WIDTH + 8 +:8] <= (opcode_r == 2'd2 & ~mem_addr_r & mem_wstrb_r[1] )? mem_wdata_r[15:8]:(counter == 0)? perip_rdata[15:8]: ram[index_r][group_choice_r][AGE_WIDTH + STATE_WIDTH + TAG_WIDTH + 8 +:8] ;
            ram[index_r][group_choice_r][AGE_WIDTH + STATE_WIDTH + TAG_WIDTH + 16 +:8] <= (opcode_r == 2'd2 & ~mem_addr_r & mem_wstrb_r[2] )? mem_wdata_r[23:16]:(counter == 0)? perip_rdata[23:16]: ram[index_r][group_choice_r][AGE_WIDTH + STATE_WIDTH + TAG_WIDTH + 16 +:8] ;
            ram[index_r][group_choice_r][AGE_WIDTH + STATE_WIDTH + TAG_WIDTH + 24 +:8] <= (opcode_r == 2'd2 & ~mem_addr_r & mem_wstrb_r[3] )? mem_wdata_r[31:24]:(counter == 0)? perip_rdata[31:24]: ram[index_r][group_choice_r][AGE_WIDTH + STATE_WIDTH + TAG_WIDTH + 24 +:8] ;    
            // --------------------------------------------------------
            // Byte-wise write with mask (Upper 32-bit word in cache line)
            // --------------------------------------------------------
            ram[index_r][group_choice_r][AGE_WIDTH + STATE_WIDTH + TAG_WIDTH + 32 +:8] <= (opcode_r == 2'd2 & mem_addr_r & mem_wstrb_r[0] )? mem_wdata_r[7:0]:(counter == 1)? perip_rdata[7:0] : ram[index_r][group_choice_r][AGE_WIDTH + STATE_WIDTH + TAG_WIDTH + 32 +:8] ;
            ram[index_r][group_choice_r][AGE_WIDTH + STATE_WIDTH + TAG_WIDTH + 32 + 8 +:8] <= (opcode_r == 2'd2 &mem_addr_r & mem_wstrb_r[1] )? mem_wdata_r[15:8]:(counter == 1)? perip_rdata[15:8] :ram[index_r][group_choice_r][AGE_WIDTH + STATE_WIDTH + TAG_WIDTH + 32 + 8 +:8] ;
            ram[index_r][group_choice_r][AGE_WIDTH + STATE_WIDTH + TAG_WIDTH + 32 + 16 +:8] <= (opcode_r == 2'd2 &mem_addr_r & mem_wstrb_r[2] )? mem_wdata_r[23:16]:(counter == 1)? perip_rdata[23:16] :ram[index_r][group_choice_r][AGE_WIDTH + STATE_WIDTH + TAG_WIDTH + 32 + 16 +:8] ;
            ram[index_r][group_choice_r][AGE_WIDTH + STATE_WIDTH + TAG_WIDTH + 32 + 24 +:8] <= (opcode_r == 2'd2 &mem_addr_r & mem_wstrb_r[3] )? mem_wdata_r[31:24]:(counter == 1)? perip_rdata[31:24] :ram[index_r][group_choice_r][AGE_WIDTH + STATE_WIDTH + TAG_WIDTH  + 32 + 24 +:8] ;
            // update age
            ram[index_r][group_choice_r][0 +:AGE_WIDTH] <= 1'b1;
            ram[index_r][~group_choice_r][0 +:AGE_WIDTH]  <= 1'b0;
        end
        default:  ram[index][group_choice] <=  ram[index][group_choice];
        endcase;
    end

// --------------------------------
// Combinational Logic
// --------------------------------
// Cache hit/dirty check

    // Cache hit/dirty check
    assign is_dirty = (ram[index][group_choice][AGE_WIDTH +:STATE_WIDTH] == DIRTY);
    assign tag = mem_addr[OFFSET_WIDTH + INDEX_WIDTH +:TAG_WIDTH];  // Extract tag
    assign index = mem_addr[OFFSET_WIDTH +:INDEX_WIDTH];            // Extract index

    // Hit detection (compare tag and check valid)
    assign is_hit = 
        ((tag == ram[index][0][AGE_WIDTH + STATE_WIDTH +:TAG_WIDTH]) && 
         (ram[index][0][AGE_WIDTH +:STATE_WIDTH] != INVALID)) || 
        ((tag == ram[index][1][AGE_WIDTH + STATE_WIDTH +:TAG_WIDTH]) && 
         (ram[index][1][AGE_WIDTH +:STATE_WIDTH] != INVALID));

    // Way selection: on hit -> choose hit way; on miss -> LRU way
    assign group_choice = 
        ((state == IDLE) && is_hit) ? 
            (tag == ram[index][1][AGE_WIDTH + STATE_WIDTH +:TAG_WIDTH]) : 
            ram[index][0][0 +:AGE_WIDTH];  // LRU bit (0=way0 is MRU)

    // Response to CPU (hit in IDLE or DATA completion)
    assign mem_resp = ((state == IDLE) && is_hit && (mem_opcode != 0)) || 
                      (state == DATA && counter == 1);
    // Read data selection (hit: from cache; miss: from peripheral)
    assign mem_rdata = 
        (state == IDLE) ? 
            // Hit: select word based on offset bit
            mem_addr[OFFSET_WIDTH-1] ? 
                ram[index][group_choice][AGE_WIDTH + STATE_WIDTH + TAG_WIDTH + 32 +:32] : 
                ram[index][group_choice][AGE_WIDTH + STATE_WIDTH + TAG_WIDTH +:32] :
        // Miss: peripheral data or partially filled cache line
        mem_addr_r ? perip_rdata : ram[index_r][group_choice_r][AGE_WIDTH + STATE_WIDTH + TAG_WIDTH +:32];

    // Peripheral interface control
    assign perip_wen = (state == WB);                     // Write-back enable
    assign perip_addr_w = (counter == 0) ?                // WB address (lower word)
        {ram[index_r][group_choice_r][AGE_WIDTH + STATE_WIDTH +:TAG_WIDTH], index_r, {OFFSET_WIDTH{1'b0}}} : 
        {ram[index_r][group_choice_r][AGE_WIDTH + STATE_WIDTH +:TAG_WIDTH], index_r, 1'b1, {OFFSET_WIDTH-1{1'b0}}};  // Upper word
    assign perip_wdata = (counter == 0) ?                 // WB data (lower word)
        ram[index_r][group_choice_r][AGE_WIDTH + STATE_WIDTH + TAG_WIDTH +:32] : 
        ram[index_r][group_choice_r][AGE_WIDTH + STATE_WIDTH + TAG_WIDTH + 32 +:32];  // Upper word
    // Peripheral read address (during DATA state)
    assign perip_addr_r = (counter == 0) ? 
        {tag_r, index_r, {OFFSET_WIDTH{1'b0}}} :          // Lower word
        {tag_r, index_r, 1'b1, {(OFFSET_WIDTH-1){1'b0}}}; // Upper word
    assign perip_mask = 2'b10;                            // Always word-aligned (32-bit)
    assign perip_addr = (state == WB) ? perip_addr_w : perip_addr_r;  // Mux between read/write address


endmodule

