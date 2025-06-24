/*
 * Data Cache Module (2-Way Set-Associative, Write-Back)
 *
 * Features:
 * - 2-way set-associative cache (LRU replacement)
 * - Write-back policy with dirty bit
 * - Byte-level write mask support (mem_wstrb)
 * - Synchronous read/write with peripheral interface
 */
`include "../define/interface.sv"
module ysyx_24100029_dcache(
    // System Signals
    input                               clk                        ,// Clock
    input                               rst                        ,// Active-high reset
    // CPU Interface
    input              [   2: 0]        mem_size                   ,
    input              [  31: 0]        mem_addr                   ,// Memory access address
    input              [   1: 0]        mem_opcode                 ,// 0-none, 1-read, 2-write
    input              [  31: 0]        mem_wdata                  ,// Write data from CPU
    input              [   3: 0]        mem_wstrb                  ,// Byte write enable (1 bit per byte)
    output             [  31: 0]        mem_rdata                  ,// Read data to CPU
    output                              mem_resp                   ,// 1 = operation complete

    axi4_if.master    dcache_axi

);

// --------------------------------
// Cache Configuration Parameters
// --------------------------------
    localparam                          ADDR_WIDTH                 = 32    ;          // Full address width
    localparam                          BLOCK_WIDTH                = 64    ;         // Cache line size (bits) = 8 bytes
    localparam                          INDEX_WIDTH                = 3     ;          // Number of index bits (8 sets)
    localparam                          STATE_WIDTH                = 2     ;          // 2 bits for line state (INVALID/VALID/DIRTY)
    localparam                          OFFSET_WIDTH               = $clog2(BLOCK_WIDTH / 8);  // log2(8) = 3 (byte offset within block)
    localparam                          TAG_WIDTH                  = ADDR_WIDTH - INDEX_WIDTH - OFFSET_WIDTH;  // Tag bits = 32-3-3=26
    localparam                          CACHE_WIDTH                = BLOCK_WIDTH + TAG_WIDTH + STATE_WIDTH + 1;  // 64(data) + 26(tag) + 2(state) + 1(age)
    localparam                          GROUP_WIDTH                = 1     ;          // 2-way set-associative (group_choice = 0 or 1)
    localparam                          AGE_WIDTH                  = 1     ;

    /* State Parameter */
    localparam                          IDLE                       = 3'b000 ;            // Idle or cache hit
    localparam                          ADDR_DEC                   = 3'b001 ;
    localparam                          DATA                       = 3'b010 ;            // Load data from peripheral (cache miss)
    localparam                          WB                         = 3'b011 ;            // Write-back dirty line to peripheral
    localparam                          UNCACHE_AR                 = 3'b100;
    localparam                          UNCACHE_WR                 = 3'b101;
    localparam                          UNCACHE_RD                 = 3'b110;
    localparam                          DEVICE_ADR                 = 4'ha  ;

    /* Block State Parameter */
    localparam                          INVALID                    = 2'b00 ;         // Line invalid
    localparam                          VALID                      = 2'b01 ;         // Line valid (clean)
    localparam                          DIRTY                      = 2'b10 ;         // Line dirty (needs write-back)


// --------------------------------
// Registers & Wires
// --------------------------------
    // Cache Memory (2-way set-associative)
    reg                [CACHE_WIDTH-1: 0] ram[2**INDEX_WIDTH-1:0][2**GROUP_WIDTH-1:0]        ;
    // Format: [0:0]=AGE, [1:2]=STATE, [3:28]=TAG, [29:92]=DATA (64 bits)
    // FSM Control
    reg                [   2: 0]        state                       ;// Current state (IDLE/DATA/WB)
    reg                [   1: 0]        counter                     ;// Cycle counter for multi-cycle ops
    reg                [   1: 0]        opcode_r                    ;// Registered mem_opcode
    reg                [   3: 0]        mem_wstrb_r                 ;// Registered mem_wstrb
    reg                [INDEX_WIDTH-1: 0]        index_r                     ;// Registered index
    reg                [  31: 0]        mem_wdata_r                 ;// Registered write data
    reg                                 mem_addr_r                  ;// Registered LSB of offset (selects upper/lower 32-bit word)
    reg                [TAG_WIDTH-1: 0]        tag_r                       ;// Registered tag
    reg [2:0]size_r;

    // Combinational Signals
    wire               [INDEX_WIDTH-1: 0]        index                       ;// Current index from address
    wire               [TAG_WIDTH-1: 0]        tag                         ;// Current tag from address
    wire                                group_choice                ;// Selected way (LRU or hit way)
    wire                                is_hit                      ;// 1 = cache hit
    wire                                is_dirty                    ;// 1 = selected line is dirty


// --------------------------------
// Finite State Machine (FSM)
// --------------------------------
    always @(posedge clk) begin
        if (rst) state <= IDLE;
        else begin
            case (state)
                IDLE:                                               // Wait for request
                    state <= (mem_opcode == 0) ? IDLE :(mem_addr[31:28] == DEVICE_ADR)? UNCACHE_AR :  ADDR_DEC;
                ADDR_DEC :
                    state <= is_hit? IDLE: is_dirty? WB:DATA;       // Transition to WB if dirty, else DATA on miss
                DATA:                                               // Fetch data from peripheral
                    state <= (dcache_axi.rready & dcache_axi.rvalid & dcache_axi.rlast ) ? IDLE : DATA;// Takes 2 cycles
                WB:                                                 // Write-back dirty line
                    state <= ( dcache_axi.bready & dcache_axi.bvalid ) ? DATA : WB;// Takes 2 cycles
                UNCACHE_AR:
                    state <= (dcache_axi.arvalid & dcache_axi.arready) ? UNCACHE_RD : (dcache_axi.awvalid & dcache_axi.awready)? UNCACHE_WR : UNCACHE_AR;
                UNCACHE_RD:
                    state <= (dcache_axi.rvalid & dcache_axi.rready&dcache_axi.rlast)? IDLE:UNCACHE_RD;
                UNCACHE_WR:
                    state <= ( dcache_axi.bready & dcache_axi.bvalid ) ? IDLE : UNCACHE_WR;
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
             mem_addr_r, tag_r} <= 0;
        end
        else if (state == IDLE && (mem_opcode != 0)) begin
            // Latch inputs when miss occurs
            opcode_r    <= mem_opcode;
            mem_wstrb_r <= mem_wstrb;
            index_r     <= index;
            mem_wdata_r <= mem_wdata;
            mem_addr_r  <= mem_addr[OFFSET_WIDTH-1];                // Selects 32-bit word within block
            tag_r       <= tag;
            size_r <= mem_size;
        end
    end

// --------------------------------
// Cycle Counter for Multi-Cycle Ops
// --------------------------------
    always @(posedge clk) begin
        if (rst) counter <= 0;
        else if (dcache_axi.bready & dcache_axi.bvalid || dcache_axi.rready & dcache_axi.rvalid & dcache_axi.rlast ) counter <= 0;
        else if (state == DATA || state == WB) counter <= (dcache_axi.rready & dcache_axi.rvalid || dcache_axi.wvalid & dcache_axi.wready)? counter + 1 : counter;
    end

// --------------------------------
// Cache Data Update Logic
// --------------------------------
    always @(posedge clk) begin
        case (state)
        ADDR_DEC: if(is_hit)begin
            // update data
                 // --------------------------------------------------------
                // Byte-wise write with mask (Lower 32-bit word in cache line)
                // --------------------------------------------------------
                // 字节0 (bits 7:0)
                ram[index_r][group_choice][AGE_WIDTH + STATE_WIDTH + TAG_WIDTH +:8] <=
                    (opcode_r == 2'd2 & ~mem_addr_r & mem_wstrb_r[0]) ?
                    mem_wdata_r[7:0] : ram[index_r][group_choice][AGE_WIDTH + STATE_WIDTH + TAG_WIDTH +:8];
                // 字节1 (bits 15:8)
                ram[index_r][group_choice][AGE_WIDTH + STATE_WIDTH + TAG_WIDTH + 8 +:8] <=
                    (opcode_r == 2'd2 & ~mem_addr_r & mem_wstrb_r[1]) ?
                    mem_wdata_r[15:8] : ram[index_r][group_choice][AGE_WIDTH + STATE_WIDTH + TAG_WIDTH + 8 +:8];
                // 字节2 (bits 23:16)
                ram[index_r][group_choice][AGE_WIDTH + STATE_WIDTH + TAG_WIDTH + 16 +:8] <=
                    (opcode_r == 2'd2 & ~mem_addr_r & mem_wstrb_r[2]) ?
                    mem_wdata_r[23:16] : ram[index_r][group_choice][AGE_WIDTH + STATE_WIDTH + TAG_WIDTH + 16 +:8];
                // 字节3 (bits 31:24)
                ram[index_r][group_choice][AGE_WIDTH + STATE_WIDTH + TAG_WIDTH + 24 +:8] <=
                    (opcode_r == 2'd2 & ~mem_addr_r & mem_wstrb_r[3]) ?
                    mem_wdata_r[31:24] : ram[index_r][group_choice][AGE_WIDTH + STATE_WIDTH + TAG_WIDTH + 24 +:8];
                // --------------------------------------------------------
                // Byte-wise write with mask (Upper 32-bit word in cache line)
                // --------------------------------------------------------
                // 字节4 (bits 39:32)
                ram[index_r][group_choice][AGE_WIDTH + STATE_WIDTH + TAG_WIDTH + 32 +:8] <=
                    (opcode_r == 2'd2 & mem_addr_r & mem_wstrb_r[0]) ?
                    mem_wdata_r[7:0] : ram[index_r][group_choice][AGE_WIDTH + STATE_WIDTH + TAG_WIDTH + 32 +:8];
                // 字节5 (bits 47:40)
                ram[index_r][group_choice][AGE_WIDTH + STATE_WIDTH + TAG_WIDTH + 32 + 8 +:8] <=
                    (opcode_r == 2'd2 & mem_addr_r & mem_wstrb_r[1]) ?
                    mem_wdata_r[15:8] : ram[index_r][group_choice][AGE_WIDTH + STATE_WIDTH + TAG_WIDTH + 32 + 8 +:8];
                // 字节6 (bits 55:48)
                ram[index_r][group_choice][AGE_WIDTH + STATE_WIDTH + TAG_WIDTH + 32 + 16 +:8] <=
                    (opcode_r == 2'd2 & mem_addr_r & mem_wstrb_r[2]) ?
                    mem_wdata_r[23:16] : ram[index_r][group_choice][AGE_WIDTH + STATE_WIDTH + TAG_WIDTH + 32 + 16 +:8];
                // 字节7 (bits 63:56)
                ram[index_r][group_choice][AGE_WIDTH + STATE_WIDTH + TAG_WIDTH + 32 + 24 +:8] <=
                    (opcode_r == 2'd2 & mem_addr_r & mem_wstrb_r[3]) ?
                    mem_wdata_r[31:24] : ram[index_r][group_choice][AGE_WIDTH + STATE_WIDTH + TAG_WIDTH + 32 + 24 +:8];

            ram[index_r][group_choice][AGE_WIDTH +:STATE_WIDTH] <= (opcode_r == 2'd2 || ram[index_r][group_choice][AGE_WIDTH +:STATE_WIDTH] == DIRTY)? DIRTY:  VALID;
            //update age
            ram[index_r][group_choice][0 +:AGE_WIDTH] <= (opcode_r != 2'd0)? 1'b1 : ram[index_r][group_choice][0 +:AGE_WIDTH];// least Recent Used
            ram[index_r][~group_choice][0 +:AGE_WIDTH] <= (opcode_r != 2'd0)? 1'b0 : ram[index_r][~group_choice][0 +:AGE_WIDTH];
        end
        DATA:if(dcache_axi.rready & dcache_axi.rvalid)begin
            // upadate state
            ram[index_r][group_choice][AGE_WIDTH +:STATE_WIDTH] <= (opcode_r == 2'd2)? DIRTY : VALID;
            // update tag
            ram[index_r][group_choice][AGE_WIDTH+STATE_WIDTH +:TAG_WIDTH] <= tag_r;
            // update data
            // --------------------------------------------------------
            // Byte-wise write with mask (Lower 32-bit word in cache line)
            // --------------------------------------------------------
            ram[index_r][group_choice][AGE_WIDTH + STATE_WIDTH + TAG_WIDTH +:8] <= (opcode_r == 2'd2 & ~mem_addr_r & mem_wstrb_r[0] )? mem_wdata_r[7:0]:(counter == 0)? dcache_axi.rdata[7:0] :ram[index_r][group_choice][AGE_WIDTH + STATE_WIDTH + TAG_WIDTH +:8] ;
            ram[index_r][group_choice][AGE_WIDTH + STATE_WIDTH + TAG_WIDTH + 8 +:8] <= (opcode_r == 2'd2 & ~mem_addr_r & mem_wstrb_r[1] )? mem_wdata_r[15:8]:(counter == 0)? dcache_axi.rdata[15:8]: ram[index_r][group_choice][AGE_WIDTH + STATE_WIDTH + TAG_WIDTH + 8 +:8] ;
            ram[index_r][group_choice][AGE_WIDTH + STATE_WIDTH + TAG_WIDTH + 16 +:8] <= (opcode_r == 2'd2 & ~mem_addr_r & mem_wstrb_r[2] )? mem_wdata_r[23:16]:(counter == 0)? dcache_axi.rdata[23:16]: ram[index_r][group_choice][AGE_WIDTH + STATE_WIDTH + TAG_WIDTH + 16 +:8] ;
            ram[index_r][group_choice][AGE_WIDTH + STATE_WIDTH + TAG_WIDTH + 24 +:8] <= (opcode_r == 2'd2 & ~mem_addr_r & mem_wstrb_r[3] )? mem_wdata_r[31:24]:(counter == 0)? dcache_axi.rdata[31:24]: ram[index_r][group_choice][AGE_WIDTH + STATE_WIDTH + TAG_WIDTH + 24 +:8] ;
            // --------------------------------------------------------
            // Byte-wise write with mask (Upper 32-bit word in cache line)
            // --------------------------------------------------------
            ram[index_r][group_choice][AGE_WIDTH + STATE_WIDTH + TAG_WIDTH + 32 +:8] <= (opcode_r == 2'd2 & mem_addr_r & mem_wstrb_r[0] )? mem_wdata_r[7:0]:(counter == 1)? dcache_axi.rdata[7:0] : ram[index_r][group_choice][AGE_WIDTH + STATE_WIDTH + TAG_WIDTH + 32 +:8] ;
            ram[index_r][group_choice][AGE_WIDTH + STATE_WIDTH + TAG_WIDTH + 32 + 8 +:8] <= (opcode_r == 2'd2 &mem_addr_r & mem_wstrb_r[1] )? mem_wdata_r[15:8]:(counter == 1)? dcache_axi.rdata[15:8] :ram[index_r][group_choice][AGE_WIDTH + STATE_WIDTH + TAG_WIDTH + 32 + 8 +:8] ;
            ram[index_r][group_choice][AGE_WIDTH + STATE_WIDTH + TAG_WIDTH + 32 + 16 +:8] <= (opcode_r == 2'd2 &mem_addr_r & mem_wstrb_r[2] )? mem_wdata_r[23:16]:(counter == 1)? dcache_axi.rdata[23:16] :ram[index_r][group_choice][AGE_WIDTH + STATE_WIDTH + TAG_WIDTH + 32 + 16 +:8] ;
            ram[index_r][group_choice][AGE_WIDTH + STATE_WIDTH + TAG_WIDTH + 32 + 24 +:8] <= (opcode_r == 2'd2 &mem_addr_r & mem_wstrb_r[3] )? mem_wdata_r[31:24]:(counter == 1)? dcache_axi.rdata[31:24] :ram[index_r][group_choice][AGE_WIDTH + STATE_WIDTH + TAG_WIDTH  + 32 + 24 +:8] ;
            // update age
            ram[index_r][group_choice][0 +:AGE_WIDTH] <= (counter == 1)? 1'b1 : ram[index_r][group_choice][0 +:AGE_WIDTH];
            ram[index_r][~group_choice][0 +:AGE_WIDTH]  <= (counter == 1)? 1'b0 : ram[index_r][~group_choice][0 +:AGE_WIDTH];
        end
        default:  ram[index_r][group_choice] <=  ram[index_r][group_choice];
        endcase;
    end

// --------------------------------
// Combinational Logic
// --------------------------------
// Cache hit/dirty check

    // Cache hit/dirty check
    assign                              is_dirty                    = (ram[index_r][group_choice][AGE_WIDTH +:STATE_WIDTH] == DIRTY);
    assign                              tag                         = mem_addr[OFFSET_WIDTH + INDEX_WIDTH +:TAG_WIDTH];// Extract tag
    assign                              index                       = mem_addr[OFFSET_WIDTH +:INDEX_WIDTH];// Extract index

    // Hit detection (compare tag and check valid)
    assign is_hit = 
        ((tag_r == ram[index_r][0][AGE_WIDTH + STATE_WIDTH +:TAG_WIDTH]) &&
         (ram[index_r][0][AGE_WIDTH +:STATE_WIDTH] != INVALID)) ||
        ((tag_r == ram[index_r][1][AGE_WIDTH + STATE_WIDTH +:TAG_WIDTH]) &&
         (ram[index_r][1][AGE_WIDTH +:STATE_WIDTH] != INVALID));

    // Way selection: on hit -> choose hit way; on miss -> LRU way
    assign group_choice = 
        ((state == ADDR_DEC) && is_hit) ?
            (tag_r == ram[index_r][1][AGE_WIDTH + STATE_WIDTH +:TAG_WIDTH]) :
            ram[index_r][0][0 +:AGE_WIDTH];                         // LRU bit (0=way0 is MRU)

    // Response to CPU (hit in IDLE or DATA completion)
    assign mem_resp = ((state == ADDR_DEC) && is_hit) || 
                      (state == DATA & counter == 1 & dcache_axi.rlast & dcache_axi.rvalid) || (state == UNCACHE_RD&dcache_axi.rvalid & dcache_axi.rready&dcache_axi.rlast ) || (state == UNCACHE_WR & dcache_axi.wvalid & dcache_axi.wready & dcache_axi.wlast);
    // Read data selection (hit: from cache; miss: from peripheral)
    assign mem_rdata = 
        (state == ADDR_DEC) ?
            // Hit: select word based on offset bit
            mem_addr[OFFSET_WIDTH-1] ?
                ram[index_r][group_choice][AGE_WIDTH + STATE_WIDTH + TAG_WIDTH + 32 +:32] :
                ram[index_r][group_choice][AGE_WIDTH + STATE_WIDTH + TAG_WIDTH +:32] :
        // Miss: peripheral data or partially filled cache line
        (state == UNCACHE_RD || mem_addr_r) ? dcache_axi.rdata : ram[index_r][group_choice][AGE_WIDTH + STATE_WIDTH + TAG_WIDTH +:32];

    // Peripheral interface control


    always@(posedge clk)begin
        if(rst)
            dcache_axi.arvalid <= 1'b0;
        else if(dcache_axi.arvalid & dcache_axi.arready)
            dcache_axi.arvalid <= 1'b0;
        else if ((state == ADDR_DEC &~is_hit&~is_dirty) || (state == WB & dcache_axi.bready & dcache_axi.bvalid)|| (state == IDLE & mem_opcode == 2'd1 & mem_addr[31:28] == 4'ha))
            dcache_axi.arvalid <= 1'b1;
    end


    always @(posedge clk) begin
        if(rst)
            dcache_axi.awvalid <= 1'b0;
        else if(dcache_axi.awvalid & dcache_axi.awready)
            dcache_axi.awvalid <= 1'b0;
        else if((state == ADDR_DEC &~is_hit&is_dirty) || (state == IDLE & mem_opcode == 2'd2 & mem_addr[31:28] == 4'ha))
            dcache_axi.awvalid <= 1'b1;
    end

    assign                              dcache_axi.araddr  = (state == UNCACHE_AR)? {tag_r,index_r,mem_addr_r,{OFFSET_WIDTH-1{1'b0}}}:  {tag_r, index_r, {OFFSET_WIDTH{1'b0}}} ;         
    assign                              dcache_axi.arburst          = 2'b01;// INCR
    assign                              dcache_axi.arlen            = state ==  UNCACHE_AR? 0: 1;
    assign                              dcache_axi.arid             = 0;
    assign                              dcache_axi.arsize           = state ==UNCACHE_AR? size_r: 3'b010;
    assign                              dcache_axi.rready           = state == DATA || state == UNCACHE_RD;

    assign                              dcache_axi.bready           = state == WB || state == UNCACHE_WR;

    assign                              dcache_axi.wstrb            = state ==UNCACHE_AR? mem_wstrb_r: 4'b1111;
    assign                              dcache_axi.wlast            = (state == WB & (counter == 1)) || state == UNCACHE_WR;
    assign                              dcache_axi.wvalid           = state == WB || state == UNCACHE_WR;
    assign                              dcache_axi.awid             = 0;
    assign                              dcache_axi.awlen            = state ==UNCACHE_AR? 0: 1;
    assign                              dcache_axi.awburst          = 2'b01;
    assign                              dcache_axi.wdata            =state == UNCACHE_WR?  mem_wdata_r: (counter == 0) ?                 
        ram[index_r][group_choice][AGE_WIDTH + STATE_WIDTH + TAG_WIDTH +:32] :
        ram[index_r][group_choice][AGE_WIDTH + STATE_WIDTH + TAG_WIDTH + 32 +:32];// Upper word;
    assign                              dcache_axi.awsize           = state == UNCACHE_AR? size_r : 3'b010;
    assign                              dcache_axi.awaddr           = (state == UNCACHE_AR)?  {tag_r,index_r,mem_addr_r,{OFFSET_WIDTH-1{1'b0}}}:                
        {ram[index_r][group_choice][AGE_WIDTH + STATE_WIDTH +:TAG_WIDTH], index_r, {OFFSET_WIDTH{1'b0}}} ;



endmodule

