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
// Last modified Date:     2025/05/02 21:11:54
// Last Version:           V1.0
// Descriptions:           
//----------------------------------------------------------------------------------------
// Created by:             Please Write You Name 
// Created date:           2025/05/02 21:11:54
// mail      :             Please Write mail 
// Version:                V1.0
// TEXT NAME:              ysyx_24100029_IFU_tb.v
// PATH:                   ~/ysyx-workbench/npc/vsrc/testbench/vsrc/ysyx_24100029_IFU_tb.v
// Descriptions:           
//                         
//----------------------------------------------------------------------------------------
//****************************************************************************************//

module ysyx_24100029_IFU_tb();

    localparam                          ADDR_WIDTH                 = 32    ;

    reg                                 clock,reset                 ;

    wire                                awready                     ;
    wire                                awvalid                     ;
    wire               [ADDR_WIDTH-1: 0]        awaddr                      ;
    wire               [   3: 0]        awid                        ;
    wire               [   7: 0]        awlen                       ;
    wire               [   2: 0]        awsize                      ;
    wire               [   1: 0]        awburst                     ;
    wire                                wready                      ;
    wire                                wvalid                      ;
    wire               [  31: 0]        wdata                       ;
    wire               [   3: 0]        wstrb                       ;
    wire                                wlast                       ;
    wire                                bready                      ;
    wire                                bvalid                      ;
    wire               [   1: 0]        bresp                       ;
    wire               [   3: 0]        bid                         ;
    wire                                arready                     ;
    wire                                arvalid                     ;
    wire               [ADDR_WIDTH-1: 0]        araddr                      ;
    wire               [   3: 0]        arid                        ;
    wire               [   7: 0]        arlen                       ;
    wire               [   2: 0]        arsize                      ;
    wire               [   1: 0]        arburst                     ;
    wire                                rready                      ;
    wire                                rvalid                      ;
    wire               [   1: 0]        rresp                       ;
    wire               [  31: 0]        rdata                       ;
    wire                                rlast                       ;
    wire               [   3: 0]        rid                         ;

    reg                [ADDR_WIDTH-1: 0]        dnpc                        ;
    reg                                 dnpc_valid                  ;
    reg                                 icache_clr                  ;
    reg                [   3: 0]        inst_ren                    ;
    reg                                 clr                         ;

    wire               [   3: 0]        inst_count                  ;
    wire               [  31: 0]        inst1_o,pc1_o               ;
    wire               [  31: 0]        inst2_o,pc2_o               ;
    wire               [  31: 0]        inst3_o,pc3_o               ;
    wire               [  31: 0]        inst4_o,pc4_o               ;
    wire req;
    initial begin
        clock = 0;
        reset = 1;
        icache_clr = 0;
        clr = 0;
        dnpc = 0;
        dnpc_valid = 0;
        #10
        reset = 0;
        #10
        repeat(5)begin
            @(inst_count > 4)
            inst_ren = 4'b1111;
            $display("inst1_o = %x pc = %x ",inst1_o,pc1_o);
            $display("inst2_o = %x pc = %x ",inst2_o,pc2_o);
            $display("inst3_o = %x pc = %x ",inst3_o,pc3_o);
            $display("inst4_o = %x pc = %x ",inst4_o,pc4_o);
            #11
            inst_ren = 4'b0000;
            ;
        end
        $finish();
    end


always #5 clock <= ~clock;





mem #(
    .MEM_SIZE                           (1024                      ),
    .DATA_WIDTH                         (32                        ) 
)
u_mem(
    .clk                                (clock                     ),
    .reset                              (reset                     ),
    .slave_awready                      (awready                   ),
    .slave_awvalid                      (awvalid                   ),
    .slave_awaddr                       (awaddr                    ),
    .slave_awid                         (awid                      ),
    .slave_awlen                        (awlen                     ),
    .slave_awsize                       (awsize                    ),
    .slave_awburst                      (awburst                   ),
    .salve_wready                       (wready                    ),
    .salve_wvalid                       (wvalid                    ),
    .salve_wdata                        (wdata                     ),
    .salve_wstrb                        (wstrb                     ),
    .salve_wlast                        (wlast                     ),
    .slave_bready                       (bready                    ),
    .slave_bvalid                       (bvalid                    ),
    .slave_bresp                        (bresp                     ),
    .slave_bid                          (bid                       ),
    .slave_arready                      (arready                   ),
    .slave_arvalid                      (arvalid                   ),
    .slave_araddr                       (araddr                    ),
    .slave_arid                         (arid                      ),
    .slave_arlen                        (arlen                     ),
    .slave_arsize                       (arsize                    ),
    .slave_arburst                      (arburst                   ),
    .slave_rready                       (rready                    ),
    .slave_rvalid                       (rvalid                    ),
    .slave_rresp                        (rresp                     ),
    .slave_rdata                        (rdata                     ),
    .slave_rlast                        (rlast                     ),
    .slave_rid                          (rid                       ) 
);





ysyx_24100029_IFU #(
    .ResetValue                         (32'h8000_0000             ),
    .Issue_Num                          (4                         ),
    .ADDR_WIDTH                         (32        )               ) 
u_ysyx_24100029_IFU(
    .clock                              (clock                     ),
    .reset                              (reset                     ),

    .dnpc                               (dnpc                      ),
    .dnpc_valid                         (dnpc_valid                ),
    .icache_clr                         (icache_clr                ),
    .clr                                (clr                       ),

    .inst_ren                           (inst_ren                  ),
    .inst1_o                            (inst1_o                   ),
    .inst2_o                            (inst2_o                   ),
    .inst3_o                            (inst3_o                   ),
    .inst4_o                            (inst4_o                   ),
    .pc1_o                              (pc1_o                     ),
    .pc2_o                              (pc2_o                     ),
    .pc3_o                              (pc3_o                     ),
    .pc4_o                              (pc4_o                     ),
    .inst_count                         (inst_count                ),

    .awready                            (awready                   ),
    .awvalid                            (awvalid                   ),
    .awaddr                             (awaddr                    ),
    .awid                               (awid                      ),
    .awlen                              (awlen                     ),
    .awsize                             (awsize                    ),
    .awburst                            (awburst                   ),
    .wready                             (wready                    ),
    .wvalid                             (wvalid                    ),
    .wdata                              (wdata                     ),
    .wstrb                              (wstrb                     ),
    .wlast                              (wlast                     ),
    .bready                             (bready                    ),
    .bvalid                             (bvalid                    ),
    .bresp                              (bresp                     ),
    .bid                                (bid                       ),
    .arready                            (arready                   ),
    .arvalid                            (arvalid                   ),
    .araddr                             (araddr                    ),
    .arid                               (arid                      ),
    .arlen                              (arlen                     ),
    .arsize                             (arsize                    ),
    .arburst                            (arburst                   ),
    .rready                             (rready                    ),
    .rvalid                             (rvalid                    ),
    .rresp                              (rresp                     ),
    .rdata                              (rdata                     ),
    .rlast                              (rlast                     ),
    .rid                                (rid                       ),
    .req                                (req                       ) 
);

                                                                   
                                                                   




endmodule
