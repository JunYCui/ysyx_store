`include "../../CPU/define/interface.sv" 
module mem # (
    parameter                           MEM_SIZE                   = 1024  ,
    parameter                           DATA_WIDTH                 = 32    
)
(
    input                               clk                        ,
    input                               reset                      ,
/* verilator lint_off UNDRIVEN */
    axi4_if.slave          mem_if
);

    localparam                          INCR                       = 2'b01 ;
    localparam                          FIXED                      = 2'b00 ;

    localparam                          IDLE                       = 2'b00 ;
    localparam                          ADDR                       = 2'b01 ;
    localparam                          READ                       = 2'b10 ;

    localparam                          ROM_ADDR                  = 32'h80000000;

    logic                [   1: 0]        state                       ;
    logic                [DATA_WIDTH-1: 0]        rom[MEM_SIZE/4-1:0]         ;
    logic                [   7: 0]        len                         ;
    logic                [   2: 0]        size                        ;
    logic                [  31: 0]        addr                        ;
    logic                [   1: 0]        burst                       ;

initial begin
    $readmemh("data/rom.hex",rom);
end


    always @(posedge clk) begin
        if(reset)
            state <= IDLE;
        else begin
            case(state)
            IDLE: state <= (mem_if.arready & mem_if.arvalid)? ADDR : IDLE;
            ADDR: state <= (mem_if.rready  & mem_if.rvalid)? mem_if.rlast? IDLE:READ  : ADDR;
            READ: state <= (mem_if.rready  & mem_if.rvalid & mem_if.rlast)? IDLE : READ;
            default: state <= IDLE;
            endcase
        end
    end

    always @(posedge clk) begin
        if(reset)begin
            size <= 0;
            len <= 0;
            burst <= 0;
        end
        else if(~(state == IDLE) & mem_if.rvalid & mem_if.rready & ~mem_if.rlast)
            len <= len-1;
        else if((state == IDLE) & mem_if.arready & mem_if.arvalid)begin
            size <= mem_if.arsize;
            len <= mem_if.arlen;
            burst <= mem_if.arburst;
        end
    end

    always @(posedge clk) begin
        if(reset)
            addr <= 0;
        else if(burst == INCR & ~(state == IDLE)& mem_if.rvalid & mem_if.rready)
            addr <= addr + 2**size;
        else if((state == IDLE) & mem_if.arready & mem_if.arvalid)
            addr <= mem_if.araddr;
    end


    assign                              mem_if.rdata                 = (addr[31:28] == 4'h8)? rom[addr[$clog2(MEM_SIZE/4)+1:2]]:0;
    assign                              mem_if.rlast                 = (state == ADDR || state == READ) & (len == 0);
    assign                              mem_if.arready               = state == IDLE;
    assign                              mem_if.rvalid                = (state == ADDR) || (state == READ);

endmodule

