module mem # (
    parameter                           MEM_SIZE                   = 1024  ,
    parameter                           DATA_WIDTH                 = 32    
)
(
    input                               clk                        ,
    input                               reset                      ,
/* verilator lint_off UNDRIVEN */
    output                              slave_awready              ,
    input                               slave_awvalid              ,
    input              [  31: 0]        slave_awaddr               ,
    input              [   3: 0]        slave_awid                 ,
    input              [   7: 0]        slave_awlen                ,
    input              [   2: 0]        slave_awsize               ,
    input              [   1: 0]        slave_awburst              ,
        
    output                              salve_wready               ,
    input                               salve_wvalid               ,
    input              [  31: 0]        salve_wdata                ,
    input              [   3: 0]        salve_wstrb                ,
    input                               salve_wlast                ,

    input                               slave_bready               ,
    output                              slave_bvalid               ,
    output             [   1: 0]        slave_bresp                ,
    output             [   3: 0]        slave_bid                  ,
    
    output                              slave_arready              ,
    input                               slave_arvalid              ,
    input              [  31: 0]        slave_araddr               ,
    input              [   3: 0]        slave_arid                 ,
    input              [   7: 0]        slave_arlen                ,
    input              [   2: 0]        slave_arsize               ,
    input              [   1: 0]        slave_arburst              ,
    
    input                               slave_rready               ,
    output                              slave_rvalid               ,
    output             [   1: 0]        slave_rresp                ,
    output             [  31: 0]        slave_rdata                ,
    output                              slave_rlast                ,
    output             [   3: 0]        slave_rid                   
);

    localparam                          INCR                       = 2'b01 ;
    localparam                          FIXED                      = 2'b00 ;

    localparam                          IDLE                       = 2'b00 ;
    localparam                          ADDR                       = 2'b01 ;
    localparam                          READ                       = 2'b10 ;

    localparam                          ROM_ADDR                  = 32'h80000000;

    reg                [   1: 0]        state                       ;
    reg                [DATA_WIDTH-1: 0]        rom[MEM_SIZE/4-1:0]         ;
    reg                [   7: 0]        len                         ;
    reg                [   2: 0]        size                        ;
    reg                [  31: 0]        addr                        ;
    reg                [   1: 0]        burst                       ;

initial begin
    $readmemh("data/rom.hex",rom);
end


    always @(posedge clk) begin
        if(reset)
            state <= IDLE;
        else begin
            case(state)
            IDLE: state <= (slave_arready & slave_arvalid)? ADDR : IDLE;
            ADDR: state <= (slave_rready  & slave_rvalid)? slave_rlast? IDLE:READ  : ADDR;
            READ: state <= (slave_rready  & slave_rvalid & slave_rlast)? IDLE : READ;
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
        else if(~(state == IDLE) & slave_rvalid & slave_rready & ~slave_rlast)
            len <= len-1;
        else if((state == IDLE) & slave_arready & slave_arvalid)begin
            size <= slave_arsize;
            len <= slave_arlen;
            burst <= slave_arburst;
        end
    end

    always @(posedge clk) begin
        if(reset)
            addr <= 0;
        else if(burst == INCR & ~(state == IDLE)& slave_rvalid & slave_rready)
            addr <= addr + 2**size;
        else if((state == IDLE) & slave_arready & slave_arvalid)
            addr <= slave_araddr;
    end


    assign                              slave_rdata                 = (addr[31:28] == 4'h8)? rom[addr[$clog2(MEM_SIZE/4)+1:2]]:0;
    assign                              slave_rlast                 = (state == ADDR || state == READ) & (len == 0);
    assign                              slave_arready               = state == IDLE;
    assign                              slave_rvalid                = (state == ADDR) || (state == READ);

endmodule

