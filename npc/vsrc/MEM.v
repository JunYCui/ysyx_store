`timescale 1ns / 1ps
//****************************************VSCODE PLUG-IN**********************************//
//----------------------------------------------------------------------------------------
// IDE :                   VSCODE     
// VSCODE plug-in version: Verilog-Hdl-Format-2.8.20240817
// VSCODE plug-in author : Jiang Percy
//----------------------------------------------------------------------------------------
//****************************************Copyright (c)***********************************//
// Copyright(C)            Please Write Company name
// All rights reserved     
// File name:              
// Last modified Date:     2024/11/24 10:25:51
// Last Version:           V1.0
// Descriptions:           
//----------------------------------------------------------------------------------------
// Created by:             Please Write You Name 
// Created date:           2024/11/24 10:25:51
// mail      :             Please Write mail 
// Version:                V1.0
// TEXT NAME:              MEM.v
// PATH:                   ~/ysyx-workbench/npc/vsrc/MEM.v
// Descriptions:           
//                         
//----------------------------------------------------------------------------------------
//****************************************************************************************//
import "DPI-C" function int npc_pmem_read(input int raddr);
import "DPI-C" function void npc_pmem_write(
  input int waddr, input int wdata, input byte wmask);


module MEM(
    input                        valid                      ,
    input              [  31: 0] raddr                      ,
    input              [  31: 0] wdata                      ,
    input              [   7: 0] wmask                      ,
    input              [  31: 0] waddr                      ,
    input                        wen                        ,
    output reg         [  31: 0] rdata                       
);

always @(*) begin
  if (valid) begin                                                  // 有读写请求时
    rdata = npc_pmem_read(raddr);
    if (wen) begin                                                  // 有写请求时
      npc_pmem_write(waddr, wdata, wmask);
    end
  end
  else begin
    rdata = 0;
  end
end

endmodule

