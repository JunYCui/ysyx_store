`timescale 1ns / 1ps
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

module IFU(
    input                        clk                        ,
    input                        rst_n                      ,
    input              [  31: 0] dnpc                       ,
    input                        dnpc_flag                  ,
    input                        pipe_stop                  ,

    output reg         [  31: 0] pc                         ,
    output reg         [  31: 0] inst                       ,

    input                        ready                      ,
    output                       valid                       
);

    reg                          dnpc_flag_reg              ;
    reg                          pipe_stop_reg              ;
    reg [31:0] dnpc_reg;

always @(posedge clk) begin
    if(!rst_n)begin
        dnpc_flag_reg <= 0;
        pipe_stop_reg <= 0;
        dnpc_reg <=0;
    end
    else if(~ready | ~valid)begin
        dnpc_flag_reg <= dnpc_flag;
        pipe_stop_reg <= pipe_stop;
        dnpc_reg <= dnpc;
    end
    else if(ready & valid)begin
        dnpc_reg <= 0;
        dnpc_flag_reg <= 0;
        pipe_stop_reg <= 0; 
    end

end


always @(posedge clk) begin
        if(!rst_n)
            pc <= 32'h80000000;
        else if((pipe_stop| pipe_stop_reg) &valid&ready)
            pc <= pc ;
        else if(dnpc_flag_reg & valid &ready)
            pc <= dnpc_reg;
        else if(dnpc_flag&valid&ready)
            pc <= dnpc;
        else if(valid & ready)
            pc <= pc + 4;
end



/* verilator lint_off PINMISSING */
SRAM
#(
    .DATA_WIDTH                  (32                        ),
    .ADDR_WIDTH                  (32                        ) 
) SRAM_inst0
(
    .rst_n                       (rst_n                     ),
    .clk                         (clk                       ),
  
    .araddr                      (pc                        ),
    .arvalid                     (1'b1                      ),

    .rready                      (1'b1                      ),
    .rdata                       (inst                      ),

    .rvalid                      (valid                     ),

    .awaddr                      (0                         ),
    .awvalid                     (0                         ),


    .wdata                       (0                         ),
    .wstrb                       (0                         ),
    .wvalid                      (0                         ),

    .bready                      (0                         ) 
);
                                                                   
endmodule

