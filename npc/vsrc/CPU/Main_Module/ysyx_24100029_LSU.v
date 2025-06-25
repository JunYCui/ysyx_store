/* verilator lint_off UNUSEDSIGNAL */

`timescale 1ns / 1ps

module ysyx_24100029_LSU (
    input                               clock                      ,
    input                               reset                      ,

    input                               mem_ren                    ,
    input                               mem_wen                    ,
    input                               R_wen                      ,
    input              [   3: 0]        csr_wen                    ,
    input              [  31: 0]        Ex_result                  ,
    input              [   4: 0]        rd                         ,
    input              [   2: 0]        funct3                     ,
    input              [  31: 0]        rs2_value                  ,
    input                               jump_flag                  ,
    input              [  31: 0]        rd_value                   ,

    output             [  31: 0]        rd_value_next              ,
    output                              R_wen_next                 ,
    output reg         [  31: 0]        LSU_Rdata                  ,
    output             [   3: 0]        csr_wen_next               ,
    output             [  31: 0]        Ex_result_next             ,
    output             [   4: 0]        rd_next                    ,
    output                              mem_ren_next               ,
    output                              jump_flag_next             ,

    input                               awready                    ,
    output                              awvalid                    ,
    output             [  31: 0]        awaddr                     ,
    output             [   3: 0]        awid                       ,
    output             [   7: 0]        awlen                      ,
    output             [   2: 0]        awsize                     ,
    output             [   1: 0]        awburst                    ,

    input                               wready                     ,
    output                              wvalid                     ,
    output             [  31: 0]        wdata                      ,
    output             [   3: 0]        wstrb                      ,
    output                              wlast                      ,
     
    output                              bready                     ,
    input                               bvalid                     ,
    input              [   1: 0]        bresp                      ,
    input              [   3: 0]        bid                        ,
     
    input                               arready                    ,
    output                              arvalid                    ,
    output             [  31: 0]        araddr                     ,
    output             [   3: 0]        arid                       ,
    output             [   7: 0]        arlen                      ,
    output             [   2: 0]        arsize                     ,
    output             [   1: 0]        arburst                    ,
     
    output                              rready                     ,
    input                               rvalid                     ,
    input              [   1: 0]        rresp                      ,
    input              [  31: 0]        rdata                      ,
    input                               rlast                      ,
    input              [   3: 0]        rid                        ,

    output reg                          req                        ,

`ifdef Performance_Count
    input              [  31: 0]        pc                         ,
    output             [  31: 0]        pc_next                    ,
    output                              mem_wflag                  ,
    output reg         [  31: 0]        lsu_cycle                  ,
    input              [  31: 0]        inst                       ,
    output reg         [  31: 0]        inst_next                  ,
`endif

    input                               valid_last                 ,
    output reg                          ready_last                 ,

    input                               ready_next                 ,
    output reg                          valid_next                  


);
/*
always @(*) begin
    if(awaddr >= 32'ha0086fc0 && awaddr < 32'ha0086fc8  && mem_wen_reg)
        $display("0x%x[pc]:\t 0x%x is written at addr 0x%x ",pc_reg,wdata,awaddr);
    else if(araddr >= 32'ha0086fc0 && awaddr < 32'ha0086fc8 && mem_ren_reg)
        $display("0x%x[pc]:\t 0x%x is read at addr 0x%x  ",pc_reg,rdata_ex,araddr);
end
*/
    wire               [  31: 0]        rdata_8i                    ;
    wire               [  31: 0]        rdata_16i                   ;
    wire               [  31: 0]        rdata_8u                    ;
    wire               [  31: 0]        rdata_16u                   ;

    wire               [   4: 0]        rdata_b_choice              ;

    reg                [  31: 0]        rdata_ex                    ;
    reg                                 mem_ren_reg                 ;
    reg                                 mem_wen_reg                 ;
    reg                                 R_wen_reg                   ;
    reg                [   3: 0]        csr_wen_reg                 ;
    reg                [  31: 0]        Ex_result_reg               ;
    reg                [  31: 0]        rd_value_reg                ;
    reg                [   4: 0]        rd_reg                      ;
    reg                [   2: 0]        funct3_reg                  ;
    reg                [  31: 0]        rs2_value_reg               ;
    reg                                 jump_flag_reg               ;
    reg                                 valid_last_reg              ;

`ifdef Performance_Count
    typedef enum logic {IDLE,WORK} state;
    state state_p;
    reg                [  31: 0]        pc_reg                      ;
    assign                              mem_wflag                   = mem_wen_reg;
    always @(posedge clock or posedge reset) begin
        if(reset)
            state_p <= IDLE;
        else begin
            case(state_p)
            IDLE: if((mem_ren | mem_wen) & valid_last & ready_last)
                    state_p <= WORK;
            WORK: if(rvalid | bvalid)
                    state_p <= IDLE;
            endcase
        end
    end
    always @(posedge clock or posedge reset) begin
        if(reset)
            lsu_cycle <= 0;
        else if(state_p == IDLE & (mem_ren | mem_wen) & valid_last & ready_last)
            lsu_cycle <= lsu_cycle + 1;
        else if(state_p == WORK)
            lsu_cycle <= lsu_cycle + 1;
    end

    always @(posedge clock) begin
        if(reset)begin
            pc_reg          <= 0       ;
            inst_next       <= 0       ;
        end
        else if(valid_last & ready_last)begin
            inst_next <= inst;
            pc_reg <= pc;
        end
    end

    assign                              pc_next                     = pc_reg;

`endif

    always @(posedge clock) begin
        if(reset)begin
            mem_ren_reg     <=  0         ;
            mem_wen_reg     <=  0         ;
            R_wen_reg       <=  0         ;
            csr_wen_reg     <=  0         ;
            Ex_result_reg   <=  0         ;
            rd_value_reg    <=  0         ;
            rd_reg          <=  0         ;
            funct3_reg      <=  0         ;
            rs2_value_reg   <=  0         ;
            jump_flag_reg   <=  0         ;

        end
        else if(valid_last & ready_last)
            begin
            mem_ren_reg     <=  mem_ren     ;
            mem_wen_reg     <=  mem_wen     ;
            R_wen_reg       <=  R_wen       ;
            csr_wen_reg     <=  csr_wen     ;
            Ex_result_reg   <=  Ex_result   ;
            rd_value_reg    <=  rd_value        ;
            rd_reg          <=  rd          ;
            funct3_reg      <=  funct3      ;
            rs2_value_reg   <=  rs2_value   ;
            jump_flag_reg   <=  jump_flag   ;
        end
    end

    always @(posedge clock) begin
        if(reset)
            LSU_Rdata <=0;
        else if(rvalid)
            LSU_Rdata <= rdata_ex;
    end


/* **************Axi4 bus**************s */
    always @(posedge clock) begin
        if(reset)
            valid_last_reg <= 0;
        else if(ready_last)
            valid_last_reg <= valid_last;
    end

    always @(posedge clock) begin
        if(reset)begin
            bready <= 1'b0;
        end
        else if(mem_wen & valid_last & ready_last)begin
            bready <= 1'b1;
        end
        else if(bready & bvalid)begin
            bready <= 1'b0;
        end
    end

always @(posedge clock) begin
    if(reset)begin
        wvalid <= 1'b0;
        wlast <= 1'b0;
    end
    else if(mem_wen & valid_last & ready_last)begin
        wvalid <= 1'b1;
        wlast <= 1'b1;
    end
    else if(wvalid & wready)begin
        wvalid <= 1'b0;
        wlast <= 1'b0;
    end
end

always @(posedge clock) begin
    if(reset)begin
        awvalid <= 1'b0;
    end
    else if(mem_wen & valid_last & ready_last)begin
        awvalid <= 1'b1;
    end
    else if(awvalid & awready)
        awvalid <= 1'b0;
end

    always @(posedge clock) begin
        if(reset)begin
            arvalid <= 1'b0;
        end
        else if(mem_ren & valid_last &ready_last)begin
            arvalid <= 1'b1;
        end
        else if(arready&arvalid)begin
            arvalid <= 1'b0;
        end
    end
    always @(posedge clock) begin
        if(reset)
            rready <= 1'b0;
        else if(mem_ren & valid_last &ready_last)
            rready <= 1'b1;
        else if(rready & rvalid)
            rready <= 1'b0;
    end


    assign                              araddr                      = Ex_result_reg;
    

    assign                              awaddr                      = Ex_result_reg;
    assign                              awid                        = 1;
    assign                              awlen                       = 0;
    assign                              awsize                      = funct3;
    assign                              awburst                     = 0;

    assign                       wdata                     = (funct3_reg == 3'b000)?
                                                            rs2_value_reg<<rdata_b_choice:(funct3_reg == 3'b001)?
                                                            rs2_value_reg<<{Ex_result_reg[1],4'b0}:(funct3_reg == 3'b010)?
                                                            rs2_value_reg:0;
    assign                              rdata_b_choice              = {Ex_result_reg[1:0],3'b0};
    
    assign wstrb = (funct3_reg == 3'b000)                           ?
                    4'b0001<<Ex_result_reg[1:0]:(funct3_reg == 3'b001)     ?
                    4'b0011<<{Ex_result_reg[1],1'b0}:(funct3_reg == 3'b010)     ?
                    4'b1111:4'b0000;


    assign                              arid                        = 0;
    assign                              arlen                       = 0;

    assign                          arsize                    = {1'b0,funct3_reg[1:0]};

    assign                              arburst                     = 0;






/*
    assert (rresp == 2'b00)
    else
        $display("LSU Read Fail ");
    assert (bresp == 2'b00)
    else
        $display("LSU Write Fail ");

*/
/* **************Axi4 bus**************s */

    always @(posedge clock) begin
        if(reset)
            ready_last <= 1'b1;
        else if((mem_ren | mem_wen) & valid_last & ready_last)
            ready_last <= 1'b0;
        else if((bready & bvalid) | rvalid)
            ready_last <= 1'b1;
    end


    always @(posedge clock) begin
        if(reset)
            valid_next <= 0;
        else if((mem_ren | mem_wen) & valid_last & ready_last)
            valid_next <= 1'b0;
        else if((bready & bvalid) | rvalid)
            valid_next <= 1'b1;
        else if(ready_last)
            valid_next <= valid_last;
    end



    assign                              Ex_result_next              = Ex_result_reg;
    assign                              rd_value_next               = rd_value_reg;
    assign                              rd_next                     = rd_reg;
    assign                              mem_ren_next                = mem_ren_reg;

    assign                              R_wen_next                  = R_wen_reg;
    assign                              jump_flag_next              = jump_flag_reg;
    assign                              csr_wen_next                = csr_wen_reg;

    assign                              req                         = ~ready_last;




always @(*) begin
    case(funct3_reg)
        3'b000:rdata_ex = rdata_8i;                                 // lb
        3'b001:rdata_ex = rdata_16i;                                // lh
        3'b010:rdata_ex = rdata;                                    // lw
        3'b100:rdata_ex = rdata_8u;                                 // lbu
        3'b101:rdata_ex = rdata_16u;                                // lhu
        default:rdata_ex = 0;
    endcase
end

    assign                              rdata_8u                    = {24'd0,rdata[rdata_b_choice +: 8]};
    assign                              rdata_16u                   = {16'd0,rdata[rdata_b_choice +: 16]};

/* verilator lint_off PINMISSING */
ysyx_24100029_sext #(
    .DATA_WIDTH                         (8                         ),
    .OUT_WIDTH                          (32                        ) 
) sext_i8
(
    .data                               (rdata[rdata_b_choice +:8] ),
    .sext_data                          (rdata_8i                  ) 
);

ysyx_24100029_sext #(
    .DATA_WIDTH                         (16                        ),
    .OUT_WIDTH                          (32                        ) 
) sext_i16
(
    .data                               (rdata[rdata_b_choice+:16] ),
    .sext_data                          (rdata_16i                 ) 
);



endmodule                                                           //MEM

