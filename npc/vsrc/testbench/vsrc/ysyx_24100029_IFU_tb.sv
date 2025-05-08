`timescale 1ns / 1ns
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

module ysyx_24100029_IFU_tb ();

  localparam ADDR_WIDTH = 32;

  axi4_if #(
      .ADDR_WIDTH(32),
      .DATA_WIDTH(32),
      .ID_WIDTH  (1)
  ) bus ();

  logic clock, reset;

  logic [ADDR_WIDTH-1:0] dnpc;
  logic                  dnpc_valid;
  logic [           3:0] inst_ren;
  logic                  clr;

  logic [           3:0] inst_count;
  logic [31:0] inst1_o, pc1_o;
  logic [31:0] inst2_o, pc2_o;
  logic [31:0] inst3_o, pc3_o;
  logic [31:0] inst4_o, pc4_o;
  logic req;
  logic [3:0]valid;
  logic [3:0]ready;
  logic [7:0]count;
  
  logic commit_valid    ;
  logic commit_is_taken ;
  logic [31:0]commit_pc       ;
  logic [1:0] commit_pc_type  ;
  logic [31:0]commit_npc      ;


  initial begin
    clock = 0;
    reset = 1;
    clr = 0;
    dnpc = 0;
    dnpc_valid = 0;
    ready = 4'b1111;
    count = 1;
    commit_valid = 0   ;
    commit_is_taken = 0 ;
    commit_pc    = 0;    
    commit_pc_type = 0;
    commit_npc  =0 ;    
    #10 reset = 0;
    #10
    repeat (100) begin
      if(&valid)begin
        $display("--------- epoch: %d ---------",count);
        $display("inst1_o = %x pc = %x ", inst1_o, pc1_o);
        $display("inst2_o = %x pc = %x ", inst2_o, pc2_o);
        $display("inst3_o = %x pc = %x ", inst3_o, pc3_o);
        $display("inst4_o = %x pc = %x ", inst4_o, pc4_o);
        count = count + 1;
      end
      #10
      ;
    end
    $finish();
  end


  always #5 clock <= ~clock;





  mem #(
      .MEM_SIZE  (1024),
      .DATA_WIDTH(32)
  ) u_mem (
      .clk   (clock),
      .reset (reset),
      .mem_if(bus.slave)
  );




ysyx_24100029_IFU #(
  .ResetValue 	(32'h80000000  ),
  .Issue_Num  	(4         ),
  .ADDR_WIDTH 	(32        ))
u_ysyx_24100029_IFU(
  .clock           	(clock            ),
  .reset           	(reset            ),
  .dnpc            	(dnpc             ),
  .dnpc_valid      	(dnpc_valid       ),
  .clr             	(clr              ),

  .inst1_o         	(inst1_o          ),
  .inst2_o         	(inst2_o          ),
  .inst3_o         	(inst3_o          ),
  .inst4_o         	(inst4_o          ),
  .pc1_o           	(pc1_o            ),
  .pc2_o           	(pc2_o            ),
  .pc3_o           	(pc3_o            ),
  .pc4_o           	(pc4_o            ),
  .valid           	(valid            ),
  .ready           	(ready            ),
  .ifu_axi         	(bus.master       ),

  .req             	(req              ),

  .commit_valid    	(commit_valid     ),
  .commit_is_taken 	(commit_is_taken  ),
  .commit_pc       	(commit_pc        ),
  .commit_pc_type  	(commit_pc_type   ),
  .commit_npc      	(commit_npc       )
);








endmodule
