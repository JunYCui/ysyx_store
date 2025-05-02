`timescale 1ns / 1ps
`include "../define/para.v"
//****************************************VSCODE PLUG-IN**********************************//
//----------------------------------------------------------------------------------------
// IDE :                   VSCODE     
// VSCODE plug-in version: Verilog-Hdl-Format-2.8.20240817
// VSCODE plug-in author : Jiang Percy
//----------------------------------------------------------------------------------------
//****************************************Copyright (c)***********************************//
// Copyright(C)            IMECAS
// All rights reserved     
// File name:              
// Last modified Date:     2024/11/24 14:30:53
// Last Version:           V1.0
// Descriptions:           
//----------------------------------------------------------------------------------------
// Created by:             Cui Junyan
// Created date:           2024/11/24 14:30:53
// mail      :             1354315077@qq.com 
// Version:                V1.0
// TEXT NAME:              IFU.v
// PATH:                   ~/ysyx-workbench/npc/vsrc/IFU.v
// Descriptions:           
//                         
//----------------------------------------------------------------------------------------
//****************************************************************************************//
module ysyx_24100029_IFU #(
    parameter                           ResetValue                 = 32'h30000000,
    parameter                           Issue_Num                  = 4     ,
    parameter                           ADDR_WIDTH                 = 32    
)
(
    input                               clock                      ,
    input                               reset                      ,
    input              [  31: 0]        dnpc                       ,
    input                               dnpc_valid                 ,
    input                               icache_clr                 ,
    input                               clr                        ,

    input              [   3: 0]        inst_ren                   ,

    output             [  31: 0]        inst1_o                    ,
    output             [  31: 0]        inst2_o                    ,
    output             [  31: 0]        inst3_o                    ,
    output             [  31: 0]        inst4_o                    ,
    output             [ADDR_WIDTH-1: 0]        pc1_o                      ,
    output             [ADDR_WIDTH-1: 0]        pc2_o                      ,
    output             [ADDR_WIDTH-1: 0]        pc3_o                      ,
    output             [ADDR_WIDTH-1: 0]        pc4_o                      ,
    output             [   3: 0]        inst_count                 ,



    input                               awready                    ,
    output                              awvalid                    ,
    output             [ADDR_WIDTH-1: 0]        awaddr                     ,
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
    output             [ADDR_WIDTH-1: 0]        araddr                     ,
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

`ifdef Performance_Count
    output             [  31: 0]        fetch_inst                 ,
    output             [  31: 0]        flash_hit,flash_miss,sdram_hit,sdram_miss,
`endif
    output                              req                         
);


/****************icache****************/
    wire               [ADDR_WIDTH-1: 0]        pc                          ;
    wire               [ADDR_WIDTH-1: 0]        pc1_i                       ;
    wire               [ADDR_WIDTH-1: 0]        pc2_i                       ;
    wire               [ADDR_WIDTH-1: 0]        pc3_i                       ;
    wire               [ADDR_WIDTH-1: 0]        pc4_i                       ;
    wire               [  31: 0]        inst1_i                     ;
    wire               [  31: 0]        inst2_i                     ;
    wire               [  31: 0]        inst3_i                     ;
    wire               [  31: 0]        inst4_i                     ;
    wire               [   3: 0]        inst_wen                    ;

    wire               [  31: 0]        icache_addr                 ;
    wire                                icache_arvalid              ;
    wire                                icache_arready              ;
    wire                                icache_rready               ;
    wire               [Issue_Num*32-1: 0]        icache_inst                 ;
    wire                                icache_rvalid               ;

    wire                                pc_update                   ;
    wire               [   2: 0]        inst_issue_count            ;
    wire                                inst_buffer_clr             ;

`ifdef Performance_Count
    reg                [  31: 0]        valid_count                 ;
    always @(posedge clock) begin
        if(reset)
            fetch_inst <= 0;
        else if(ifu_rvalid)
            fetch_inst <= fetch_inst + 1;
    end

    always @(posedge clock or posedge reset) begin
        if(reset)
            valid_count <= 0;
        else if(~valid)begin
            valid_count <= valid_count + 1;
            assert(valid_count < 1000);
        end
        else
            valid_count <= 0;
    end

`endif



    assign                              req                         = arvalid;


    assign                              inst_wen[0]                 = icache_rvalid & icache_rready;
    assign                              inst_wen[1]                 = icache_rvalid & icache_rready & ~(inst_issue_count < 2);
    assign                              inst_wen[2]                 = icache_rvalid & icache_rready & ~(inst_issue_count < 3);
    assign                              inst_wen[3]                 = icache_rvalid & icache_rready & ~(inst_issue_count < 4);
    assign                              pc1_i                       = pc;
    assign                              pc2_i                       = pc + 4;
    assign                              pc3_i                       = pc + 8;
    assign                              pc4_i                       = pc + 12;
    
    
    assign                              inst1_i                     = inst_issue_count < 2 ? icache_inst[127:96] : (inst_issue_count < 3)? icache_inst[95:64] : (inst_issue_count < 4)? icache_inst[63:32]:icache_inst[31:0];
    assign                              inst2_i                     = (inst_issue_count < 3)? icache_inst[127:96] : (inst_issue_count < 4)? icache_inst[95:64]:icache_inst[63:32];
    assign                              inst3_i                     = (inst_issue_count < 4)? icache_inst[127:96] : icache_inst[95:64];
    assign                              inst4_i                     = icache_inst[127:96];

    assign                              icache_rready               = inst_count + inst_issue_count < 17;
    assign                              inst_issue_count            = Issue_Num -  pc[2+:$clog2(Issue_Num)];
    assign                              inst_buffer_clr             = dnpc_valid;

    assign                              pc_update                   = icache_rvalid & icache_rready;
    assign                              icache_arvalid              = 1'b1;
    assign                              icache_addr                 = pc;



npc_generate #(
    .ResetValue                         (ResetValue                ),
    .Issue_Num                          (Issue_Num                 ) 
)
u_npc_generate(
    .clock                              (clock                     ),
    .reset                              (reset                     ),
    .dnpc                               (dnpc                      ),
    .dnpc_valid                         (dnpc_valid                ),
    .pc_update                          (pc_update                 ),
    .pc                                 (pc                        ) 
);




Inst_Buffer #(
    .DATA_WIDTH                         (32                        ),
    .ADDR_WIDTH                         (ADDR_WIDTH                ),
    .Depth                              (16  )                     ) 
u_Inst_Buffer(
    .clk                                (clock                     ),
    .rst                                (reset                     ),
    .clr                                (inst_buffer_clr           ),

    .inst1_i                            (inst1_i                   ),
    .inst2_i                            (inst2_i                   ),
    .inst3_i                            (inst3_i                   ),
    .inst4_i                            (inst4_i                   ),
    .pc1_i                              (pc1_i                     ),
    .pc2_i                              (pc2_i                     ),
    .pc3_i                              (pc3_i                     ),
    .pc4_i                              (pc4_i                     ),
    .inst_wen                           (inst_wen                  ),

    .inst_ren                           (inst_ren                  ),
    .inst1_o                            (inst1_o                   ),
    .inst2_o                            (inst2_o                   ),
    .inst3_o                            (inst3_o                   ),
    .inst4_o                            (inst4_o                   ),
    .pc1_o                              (pc1_o                     ),
    .pc2_o                              (pc2_o                     ),
    .pc3_o                              (pc3_o                     ),
    .pc4_o                              (pc4_o                     ),
    .inst_count                         (inst_count                ) 

);






ysyx_24100029_icache u_ysyx_24100029_icache(
    .clock                              (clock                     ),
    .reset                              (reset                     ),
    .clr                                (clr                       ),

    .addr                               (icache_addr               ),
    .arvalid                            (icache_arvalid            ),
    .arready                            (icache_arready            ),
    .rready                             (icache_rready             ),
    .inst                               (icache_inst               ),
    .rvalid                             (icache_rvalid             ),

`ifdef Performance_Count
    .flash_hit                          (flash_hit                 ),
    .flash_miss                         (flash_miss                ),
    .sdram_hit                          (sdram_hit                 ),
    .sdram_miss                         (sdram_miss                ),
`endif


    .icache_awready                     (awready                   ),
    .icache_awvalid                     (awvalid                   ),
    .icache_awaddr                      (awaddr                    ),
    .icache_awid                        (awid                      ),
    .icache_awlen                       (awlen                     ),
    .icache_awsize                      (awsize                    ),
    .icache_awburst                     (awburst                   ),
    .icache_wready                      (wready                    ),
    .icache_wvalid                      (wvalid                    ),
    .icache_wdata                       (wdata                     ),
    .icache_wstrb                       (wstrb                     ),
    .icache_wlast                       (wlast                     ),
    .icache_bready                      (bready                    ),
    .icache_bvalid                      (bvalid                    ),
    .icache_bresp                       (bresp                     ),
    .icache_bid                         (bid                       ),
    .icache_arready                     (arready                   ),
    .icache_arvalid                     (arvalid                   ),
    .icache_araddr                      (araddr                    ),
    .icache_arid                        (arid                      ),
    .icache_arlen                       (arlen                     ),
    .icache_arsize                      (arsize                    ),
    .icache_arburst                     (arburst                   ),
    .icache_rready                      (rready                    ),
    .icache_rvalid                      (rvalid                    ),
    .icache_rresp                       (rresp                     ),
    .icache_rdata                       (rdata                     ),
    .icache_rlast                       (rlast                     ),
    .icache_rid                         (rid                       ) 
);



endmodule

