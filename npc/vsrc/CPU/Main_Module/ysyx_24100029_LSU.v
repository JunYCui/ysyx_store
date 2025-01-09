/* verilator lint_off UNUSEDSIGNAL */
// signal not use
`timescale 1ns / 1ps
    localparam                   i4_NR_KEY                 = 5     ; //键值的个数
    localparam                   i4_KEY_LEN                = 3     ; //键值的长度
    localparam                   i4_DATA_LEN               = 32    ; //数据的长度

    localparam                   i5_NR_KEY                 = 3     ; 
    localparam                   i5_KEY_LEN                = 3     ; 
    localparam                   i5_DATA_LEN               = 4     ; 

module ysyx_24100029_LSU (
    input                        clock                      ,
    input                        reset                      ,

    input              [  31: 0] pc                         ,
    input                        mem_ren                    ,
    input                        mem_wen                    ,
    input                        R_wen                      ,
    input              [   3: 0] csr_wen                    ,
    input              [  31: 0] Ex_result                  ,
    input              [  31: 0] csrs                       ,
    input              [   4: 0] rd                         ,
    input              [   2: 0] funct3                     ,
    input              [  31: 0] rs2_value                  ,
    input                        jump_flag                  ,
  

    output                       R_wen_next                 ,
    output reg         [  31: 0] LSU_Rdata                  ,
    output             [   3: 0] csr_wen_next               ,
    output             [  31: 0] Ex_result_next             ,
    output             [  31: 0] csrs_next                  ,
    output             [  31: 0] pc_next                    ,
    output             [   4: 0] rd_next                    ,
    output                       mem_ren_next               ,
    output                       jump_flag_next             ,

    input                        awready                    ,
    output                       awvalid                    ,
    output             [  31: 0] awaddr                     ,
    output             [   3: 0] awid                       ,
    output             [   7: 0] awlen                      ,
    output             [   2: 0] awsize                     ,
    output             [   1: 0] awburst                    ,

    input                        wready                     ,
    output                       wvalid                     ,
    output             [  31: 0] wdata                      ,
    output             [   3: 0] wstrb                      ,
    output                       wlast                      ,

    output                       bready                     ,
    input                        bvalid                     ,
    input              [   1: 0] bresp                      ,
    input              [   3: 0] bid                        ,
    
    input                        arready                    ,
    output                       arvalid                    ,
    output             [  31: 0] araddr                     ,
    output             [   3: 0] arid                       ,
    output             [   7: 0] arlen                      ,
    output             [   2: 0] arsize                     ,
    output             [   1: 0] arburst                    ,
    
    output                       rready                     ,
    input                        rvalid                     ,
    input              [   1: 0] rresp                      ,
    input              [  31: 0] rdata                      ,
    input                        rlast                      ,
    input              [   3: 0] rid                        ,

    output reg                   req                        ,

    input                        valid_last                 ,
    output reg                   ready_last                 ,

    input                        ready_next                 ,
    output reg                   valid_next                 ,

    input              [  31: 0] inst                       ,
    output reg         [  31: 0] inst_next                   
);
 
    wire               [  31: 0] rdata_8i                   ;
    wire               [  31: 0] rdata_16i                  ;
    wire               [  31: 0] rdata_8u                   ;
    wire               [  31: 0] rdata_16u                  ;

    wire               [  31: 0] rdata_ex                   ;


    reg                [  31: 0] pc_reg                     ;
    reg                          mem_ren_reg                ;
    reg                          mem_wen_reg                ;
    reg                          R_wen_reg                  ;
    reg                [   3: 0] csr_wen_reg                ;
    reg                [  31: 0] Ex_result_reg              ;
    reg                [  31: 0] csrs_reg                   ;
    reg                [   4: 0] rd_reg                     ;
    reg                [   2: 0] funct3_reg                 ;
    reg                [  31: 0] rs2_value_reg              ;
    reg                          jump_flag_reg              ;
    reg                          valid_last_reg             ;

    always @(posedge clock) begin
        if(reset)begin
            pc_reg          <=  0         ;
            mem_ren_reg     <=  0         ;
            mem_wen_reg     <=  0         ;
            R_wen_reg       <=  0         ;
            csr_wen_reg     <=  0         ;
            Ex_result_reg   <=  0         ;
            csrs_reg        <=  0         ;
            rd_reg          <=  0         ;
            funct3_reg      <=  0         ;
            rs2_value_reg   <=  0         ;
            jump_flag_reg   <=  0         ;

        end
        else if(valid_last & ready_last)
            begin
            pc_reg          <=  pc          ;
            mem_ren_reg     <=  mem_ren     ;
            mem_wen_reg     <=  mem_wen     ;
            R_wen_reg       <=  R_wen       ;
            csr_wen_reg     <=  csr_wen     ;
            Ex_result_reg   <=  Ex_result   ;
            csrs_reg        <=  csrs        ;
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
            awvalid <= 1'b0;
            wvalid <= 1'b0;
            wlast <= 1'b0;
        end
        else if(mem_wen & valid_last & ready_last)begin
            wlast <= 1'b1;
            bready <= 1'b1;
            awvalid <= 1'b1;
            wvalid <= 1'b1;
        end
        else if(bready & bvalid)begin
            wlast <= 1'b0;
            bready <= 1'b0;
            awvalid <= 1'b0;
            wvalid <= 1'b0;
        end
    end


    always @(posedge clock) begin
        if(reset)begin
            arvalid <= 1'b0;
            rready <= 1'b0;
        end
        else if(mem_ren & valid_last &ready_last)begin
            arvalid <= 1'b1;
            rready <= 1'b1;
        end
        else if(rvalid)begin
            arvalid <= 1'b0;
            rready <= 1'b0;
        end
    end


    assign                       araddr                    = Ex_result_reg;
    

    assign                       awaddr                    = Ex_result_reg;
    assign                       awid                      = 0;
    assign                       awlen                     = 0;
    assign                       awsize                    = 4;
    assign                       awburst                   = 0;

    assign                       wdata                     = rs2_value_reg;

ysyx_24100029_MuxKeyInternal #(i5_NR_KEY, i5_KEY_LEN, i5_DATA_LEN) i5 (wstrb, funct3_reg, {i5_DATA_LEN{1'b0}},{
  3'b000,4'b0001,
  3'b001,4'b0011,
  3'b010,4'b1111
});

    assign                       arid                      = 0;
    assign                       arlen                     = 0;
    assign                       arsize                    = 4;
    assign                       arburst                   = 0;

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
        else if(mem_ren & valid_last & ready_last)
            ready_last <= 1'b0;
        else if(mem_wen & valid_last & ready_last)
            ready_last <= 1'b0;
        else if(bready & bvalid)
            ready_last <= 1'b1;
        else if(rvalid)
            ready_last <= 1'b1;
    end


   always @(posedge clock) begin
       if(reset)
            valid_next <= 0;
        else if(mem_ren & valid_last & ready_last)
            valid_next <= 1'b0;
        else if(mem_wen & valid_last & ready_last)
            valid_next <= 1'b0;
        else if(bready & bvalid)
            valid_next <= 1'b1;
        else if(rvalid)
            valid_next <= 1'b1;
        else if(ready_last)
            valid_next <= valid_last;
   end



    assign                       Ex_result_next            = Ex_result_reg;
    assign                       csrs_next                 = csrs_reg;
    assign                       pc_next                   = pc_reg;
    assign                       rd_next                   = rd_reg;
    assign                       mem_ren_next              = mem_ren_reg;

    assign                       R_wen_next                = R_wen_reg;
    assign                       jump_flag_next            = jump_flag_reg;
    assign                       csr_wen_next              = csr_wen_reg;

    assign                       req                       = ~ready_last;

    always @(posedge clock) begin
        if(reset)
            inst_next <=0;
        else if(valid_last & ready_last)
            inst_next <= inst;
    end



ysyx_24100029_MuxKeyInternal #(i4_NR_KEY, i4_KEY_LEN, i4_DATA_LEN) i4 (rdata_ex, funct3_reg, {i4_DATA_LEN{1'b0}},{
  3'b000,rdata_8i,                                                  // lb
  3'b001,rdata_16i,                                                 // lh
  3'b010,rdata,                                                     // lw
  3'b100,rdata_8u,                                                  // 1bu
  3'b101,rdata_16u                                                  // 1hu
});

    assign                       rdata_8u                  = {24'd0,rdata[7:0]};
    assign                       rdata_16u                 = {16'd0,rdata[15:0]};

/* verilator lint_off PINMISSING */
ysyx_24100029_sext #(
    .DATA_WIDTH                  (8                         ),
    .OUT_WIDTH                   (32                        ) 
) sext_i8
(
    .data                        (rdata[7:0]                ),
    .sext_data                   (rdata_8i                  ) 
);

ysyx_24100029_sext #(
    .DATA_WIDTH                  (16                        ),
    .OUT_WIDTH                   (32                        ) 
) sext_i16
(
    .data                        (rdata[15:0]               ),
    .sext_data                   (rdata_16i                 ) 
);



endmodule                                                           //MEM

