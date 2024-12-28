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
import "DPI-C" function void npc_pmem_write(input int waddr, input int wdata, input byte wmask);


    localparam                   i4_NR_KEY                 = 5     ; //键值的个数
    localparam                   i4_KEY_LEN                = 3     ; //键值的长度
    localparam                   i4_DATA_LEN               = 32    ; //数据的长度

    localparam                   i5_NR_KEY                 = 3     ; //键值的个数
    localparam                   i5_KEY_LEN                = 3     ; //键值的长度
    localparam                   i5_DATA_LEN               = 8     ; //数据的长度

/* verilator lint_off UNUSEDSIGNAL */
module AM(
    input                        rst_n                      ,
    input                        clk                        ,
    input                        valid                      ,
    input              [  31: 0] raddr                      ,
    input              [  31: 0] wdata                      ,
    input              [   2: 0] funct3                     ,
    input              [  31: 0] waddr                      ,
    input                        wen                        ,
    output             [  31: 0] rd_data                     
);

    wire               [  31: 0] rdata_8i                   ;
    wire               [  31: 0] rdata_16i                  ;
    wire               [  31: 0] rdata_8u                   ;
    wire               [  31: 0] rdata_16u                  ;


MuxKeyInternal #(i4_NR_KEY, i4_KEY_LEN, i4_DATA_LEN) i4 (rd_data, funct3, {i4_DATA_LEN{1'b0}},{
  3'b000,rdata_8i,                                                  // lb
  3'b001,rdata_16i,                                                 // lh
  3'b010,rdata,                                                     // lw
  3'b100,rdata_8u,                                                  // 1bu
  3'b101,rdata_16u                                                  // 1hu
});
MuxKeyInternal #(i5_NR_KEY, i5_KEY_LEN, i5_DATA_LEN) i5 (wmask, funct3, {i5_DATA_LEN{1'b0}},{
  3'b000,8'd1,
  3'b001,8'd2,
  3'b010,8'd4
});


    wire               [   7: 0] wmask                      ;

    reg                [  31: 0] rdata                      ;

    assign                       rdata_8u                  = {24'd0,rdata[7:0]};
    assign                       rdata_16u                 = {16'd0,rdata[15:0]};
/*
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
*/

    reg                [32-1: 0] rf                 [2**8-1:0]  ;
  always @(posedge clk) begin
    if(!rst_n)
      rf[waddr] <=0;
    else if (wen) rf[waddr[7:0]] <= wdata;
  end


    assign                       rdata                     = rf[raddr[7:0]];

sext #(
    .DATA_WIDTH                  (8                         ),
    .OUT_WIDTH                   (32                        ) 
) sext_i8
(
    .data                        (rdata[7:0]                ),
    .sext_data                   (rdata_8i                  ) 
);

sext #(
    .DATA_WIDTH                  (16                        ),
    .OUT_WIDTH                   (32                        ) 
) sext_i16
(
    .data                        (rdata[15:0]               ),
    .sext_data                   (rdata_16i                 ) 
);


endmodule

