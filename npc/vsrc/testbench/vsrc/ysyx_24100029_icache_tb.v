`timescale 1ns / 1ps
//****************************************VSCODE PLUG-IN**********************************//
//----------------------------------------------------------------------------------------
// IDE :                   VSCODE     
// VSCODE plug-in version: Verilog-Hdl-Format-3.5.20250220
// VSCODE plug-in author : Jiang Percy
//----------------------------------------------------------------------------------------
//****************************************Copyright (c)***********************************//
// Copyright(C)            Please Write Company name
// All rights reserved     
// File name:              
// Last modified Date:     2025/05/02 09:03:05
// Last Version:           V1.0
// Descriptions:           
//----------------------------------------------------------------------------------------
// Created by:             Please Write You Name 
// Created date:           2025/05/02 09:03:05
// mail      :             Please Write mail 
// Version:                V1.0
// TEXT NAME:              ysyx_24100029_icache_tb.v
// PATH:                   ~/ysyx-workbench/npc/testbench/ysyx_24100029_icache_tb.v
// Descriptions:           
//                         
//----------------------------------------------------------------------------------------
//****************************************************************************************//

module ysyx_24100029_icache_tb();

    localparam                          ADDR_WIDTH                 = 32    ;
    localparam                          INST_WIDTH                 = 128   ;

    wire                                icache_awready              ;
    wire                                icache_awvalid              ;
    wire               [ADDR_WIDTH-1: 0]        icache_awaddr               ;
    wire               [   3: 0]        icache_awid                 ;
    wire               [   7: 0]        icache_awlen                ;
    wire               [   2: 0]        icache_awsize               ;
    wire               [   1: 0]        icache_awburst              ;
    wire                                icache_wready               ;
    wire                                icache_wvalid               ;
    wire               [  31: 0]        icache_wdata                ;
    wire               [   3: 0]        icache_wstrb                ;
    wire                                icache_wlast                ;
    wire                                icache_bready               ;
    wire                                icache_bvalid               ;
    wire               [   1: 0]        icache_bresp                ;
    wire               [   3: 0]        icache_bid                  ;
    wire                                icache_arready              ;
    wire                                icache_arvalid              ;
    wire               [ADDR_WIDTH-1: 0]        icache_araddr               ;
    wire               [   3: 0]        icache_arid                 ;
    wire               [   7: 0]        icache_arlen                ;
    wire               [   2: 0]        icache_arsize               ;
    wire               [   1: 0]        icache_arburst              ;
    wire                                icache_rready               ;
    wire                                icache_rvalid               ;
    wire               [   1: 0]        icache_rresp                ;
    wire               [  31: 0]        icache_rdata                ;
    wire                                icache_rlast                ;
    wire               [   3: 0]        icache_rid                  ;


    reg                                 clock                       ;
    reg                                 reset                       ;

    reg                [ADDR_WIDTH-1: 0]        addr                        ;
    reg                                 arvalid                     ;
    wire                                arready                     ;
    
    reg                                 rready                      ;
    wire               [INST_WIDTH-1: 0]        inst                        ;
    wire                                rvalid                      ;
    reg                                 clr                         ;

    initial begin
        clock = 0;
        reset = 1;
        addr = 0;
        arvalid = 0;
        rready = 0;
        clr = 0 ;
        #10
        reset = 0;
        addr = 32'h8000_0000;
        arvalid = 1;
        #10
        arvalid = 0;
        rready = 1;
        @(rvalid)
        @(posedge clock) 
        $display("@%-t \n inst0 = %x \n inst1 = %x \n inst2 = %x \n inst3 = %x",$time,inst[31:0],inst[63:32],inst[95:64],inst[127:96]);
        rready = 0;
        #10
        addr = 32'h8000_0040;
        arvalid = 1;
        #10
        arvalid = 0;
        rready = 1;
        @rvalid
        $display("@%-t \n inst0 = %x \n inst1 = %x \n inst2 = %x \n inst3 = %x",$time,inst[31:0],inst[63:32],inst[95:64],inst[127:96]);
        #10
        $finish();
    end


    always #5 clock <= ~ clock ;











mem #(
    .MEM_SIZE                           (1024                      ),
    .DATA_WIDTH                         (32    )                   ) 
u_mem(
    .clk                                (clock                       ),
    .reset                              (reset                     ),
    .slave_awready                      (icache_awready            ),
    .slave_awvalid                      (icache_awvalid            ),
    .slave_awaddr                       (icache_awaddr             ),
    .slave_awid                         (icache_awid               ),
    .slave_awlen                        (icache_awlen              ),
    .slave_awsize                       (icache_awsize             ),
    .slave_awburst                      (icache_awburst            ),
    .salve_wready                       (icache_wready             ),
    .salve_wvalid                       (icache_wvalid             ),
    .salve_wdata                        (icache_wdata              ),
    .salve_wstrb                        (icache_wstrb              ),
    .salve_wlast                        (icache_wlast              ),
    .slave_bready                       (icache_bready             ),
    .slave_bvalid                       (icache_bvalid             ),
    .slave_bresp                        (icache_bresp              ),
    .slave_bid                          (icache_bid                ),
    .slave_arready                      (icache_arready            ),
    .slave_arvalid                      (icache_arvalid            ),
    .slave_araddr                       (icache_araddr             ),
    .slave_arid                         (icache_arid               ),
    .slave_arlen                        (icache_arlen              ),
    .slave_arsize                       (icache_arsize             ),
    .slave_arburst                      (icache_arburst            ),
    .slave_rready                       (icache_rready             ),
    .slave_rvalid                       (icache_rvalid             ),
    .slave_rresp                        (icache_rresp              ),
    .slave_rdata                        (icache_rdata              ),
    .slave_rlast                        (icache_rlast              ),
    .slave_rid                          (icache_rid                ) 
);


ysyx_24100029_icache u_ysyx_24100029_icache(
    .clock                              (clock                     ),
    .reset                              (reset                     ),
    .clr                                (clr                       ),
    .addr                               (addr                      ),
    .arvalid                            (arvalid                   ),
    .arready                            (arready                   ),
    .rready                             (rready                    ),
    .inst                               (inst                      ),
    .rvalid                             (rvalid                    ),
    .icache_awready                     (icache_awready            ),
    .icache_awvalid                     (icache_awvalid            ),
    .icache_awaddr                      (icache_awaddr             ),
    .icache_awid                        (icache_awid               ),
    .icache_awlen                       (icache_awlen              ),
    .icache_awsize                      (icache_awsize             ),
    .icache_awburst                     (icache_awburst            ),
    .icache_wready                      (icache_wready             ),
    .icache_wvalid                      (icache_wvalid             ),
    .icache_wdata                       (icache_wdata              ),
    .icache_wstrb                       (icache_wstrb              ),
    .icache_wlast                       (icache_wlast              ),
    .icache_bready                      (icache_bready             ),
    .icache_bvalid                      (icache_bvalid             ),
    .icache_bresp                       (icache_bresp              ),
    .icache_bid                         (icache_bid                ),
    .icache_arready                     (icache_arready            ),
    .icache_arvalid                     (icache_arvalid            ),
    .icache_araddr                      (icache_araddr             ),
    .icache_arid                        (icache_arid               ),
    .icache_arlen                       (icache_arlen              ),
    .icache_arsize                      (icache_arsize             ),
    .icache_arburst                     (icache_arburst            ),
    .icache_rready                      (icache_rready             ),
    .icache_rvalid                      (icache_rvalid             ),
    .icache_rresp                       (icache_rresp              ),
    .icache_rdata                       (icache_rdata              ),
    .icache_rlast                       (icache_rlast              ),
    .icache_rid                         (icache_rid                ) 
);



                                                                   
endmodule
