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
`include "../../CPU/define/interface.sv"
module ysyx_24100029_icache_tb ();

  localparam ADDR_WIDTH = 32;
  localparam INST_WIDTH = 256;

  axi4_if #(
      .ADDR_WIDTH(32),
      .DATA_WIDTH(32),
      .ID_WIDTH  (1)
  ) bus ();


  logic                   clock;
  logic                   reset;

  logic  [ADDR_WIDTH-1:0] addr;
  logic                   arvalid;
  logic                  arready;

  logic                   rready;
  logic [INST_WIDTH-1:0] inst;
  logic                  rvalid;
  logic                   clr;

  initial begin
    clock = 0;
    reset = 1;
    addr = 0;
    arvalid = 0;
    rready = 0;
    clr = 0;
    #10 reset = 0;
    addr = 32'h8000_0000;
    arvalid = 1;
    #10 arvalid = 0;
    rready = 1;
    @(rvalid)
    @(posedge clock)
    $display(
        "@%-t \n inst0 = %x \n inst1 = %x \n inst2 = %x \n inst3 = %x \n inst4 = %x \n inst5 = %x \n inst6 = %x \n inst7 = %x",
        $time,
        inst[31:0],
        inst[63:32],
        inst[95:64],
        inst[127:96],
        inst[159:128],
        inst[191:160],
        inst[223:192],
        inst[255:224]
    );
    rready = 0;
    #10 addr = 32'h8000_0080;
    arvalid = 1;
    #10 arvalid = 0;
    rready = 1;
    @rvalid
    $display(
        "@%-t \n inst0 = %x \n inst1 = %x \n inst2 = %x \n inst3 = %x \n inst4 = %x \n inst5 = %x \n inst6 = %x \n inst7 = %x",
        $time,
        inst[31:0],
        inst[63:32],
        inst[95:64],
        inst[127:96],
        inst[159:128],
        inst[191:160],
        inst[223:192],
        inst[255:224]
    );
    #10 $finish();
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


  ysyx_24100029_icache u_ysyx_24100029_icache (
      .clock     (clock),
      .reset     (reset),
      .clr       (clr),
      .addr      (addr),
      .arvalid   (arvalid),
      .arready   (arready),
      .rready    (rready),
      .inst      (inst),
      .rvalid    (rvalid),
      .icache_axi(bus.master)
  );




endmodule
