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
// Last modified Date:     2024/11/25 15:23:28
// Last Version:           V1.0
// Descriptions:
//----------------------------------------------------------------------------------------
// Created by:             Cui Junyan
// Created date:           2024/11/25 15:23:28
// mail      :             1354315077@qq.com
// Version:                V1.0
// TEXT NAME:              control.v
// PATH:                   ~/ysyx-workbench/npc/vsrc/control.v
// Descriptions:
//
//----------------------------------------------------------------------------------------
//****************************************************************************************//
`include "vsrc/para.v"

module Control(
    input              [   6: 0] opcode                     ,
    input              [   2: 0] funct3                     ,
    input              [   6: 0] oprand                     ,
    output                       re_wen                     ,
    output                       mem_wen                    ,
    output                       mem_ren                    ,
    output                       jump_flag                  ,
    output                       branch_flag                ,

    output reg         [   3: 0] alu_opcode                 ,
    output reg         [   1: 0] imm_opcode                 ,
    output                       rs2_flag                   ,
    output reg         [   1: 0] rs1_flag                   ,
    output reg                   comp_flag                  ,
    output                       inv_flag                    
);

    


    assign                       re_wen                    = (opcode == `S_opcode_ysyx_24100029 || opcode == `B_opcode_ysyx_24100029 )? 1'b0:1'b1;
    assign                       mem_wen                   = (opcode == `S_opcode_ysyx_24100029)? 1'b1:1'b0;
    assign                       mem_ren                   = (opcode == `I0_opcode_ysyx_24100029)? 1'b1:1'b0;

    assign                       jump_flag                 = (opcode == `I2_opcode_ysyx_24100029 || opcode == `J_opcode_ysyx_24100029)? 1'b1:1'b0;
    assign                       rs2_flag                  = (opcode == `R_opcode_ysyx_24100029 || opcode == `B_opcode_ysyx_24100029)? 1'b1:1'b0;
    assign                       inv_flag                  = (opcode == `B_opcode_ysyx_24100029 && (funct3 == 3'b101 || funct3 == 3'b111 || funct3 == 3'b000 ))? 1'b1:1'b0;
    assign                       branch_flag               = (opcode == `B_opcode_ysyx_24100029)? 1'b1:1'b0;


/* comp_flag */
    always@(*)begin
        if(opcode == `B_opcode_ysyx_24100029 && (funct3 == 3'b110 || funct3 == 3'b111) )
            comp_flag = 1'b1;
        else if(opcode == `I1_opcode_ysyx_24100029 && (funct3 == 3'b011))
            comp_flag = 1'b1;
        else if(opcode == `R_opcode_ysyx_24100029 && (funct3 ==  3'b011))
            comp_flag = 1'b1;
        else 
            comp_flag = 1'b0;
    end


/* imm_opcode        */
    always@(*)begin
        if(opcode == `U0_opcode_ysyx_24100029 || opcode == `U1_opcode_ysyx_24100029 )
            imm_opcode = `imm_20u_ysyx_24100029;
        else if( opcode == `J_opcode_ysyx_24100029)
            imm_opcode = `imm_20i_ysyx_24100029;
        else if(opcode == `I1_opcode_ysyx_24100029 && (funct3 == 3'b001 || funct3 == 3'b101) )
            imm_opcode = `imm_5u_ysyx_24100029 ;
        else
            imm_opcode = `imm_12i_ysyx_24100029;
    end

/*   rs1_flag     */
    always@(*)begin
        if(opcode == `U0_opcode_ysyx_24100029)
            rs1_flag = `rs1_dist_para_ysyx_24100029 ;
        else if (opcode == `J_opcode_ysyx_24100029 || opcode == `U1_opcode_ysyx_24100029 )
            rs1_flag = `rs1_dist_pc_ysyx_24100029 ;
        else
            rs1_flag = `rs1_dist_reg_ysyx_24100029 ;
    end

/*   alu_opcode     */
always@(*)begin
    if(opcode == `S_opcode_ysyx_24100029 ||  opcode == `I0_opcode_ysyx_24100029 || opcode == `U0_opcode_ysyx_24100029
    || opcode == `U1_opcode_ysyx_24100029 || opcode == `J_opcode_ysyx_24100029 || opcode == `I2_opcode_ysyx_24100029)
                        alu_opcode = `alu_add_ysyx_24100029;
    else if(opcode == `I1_opcode_ysyx_24100029)
        begin
           case(funct3)
            3'b000:             alu_opcode = `alu_add_ysyx_24100029;
            3'b010,3'b011:      alu_opcode = `alu_comparator_ysyx_24100029;
            3'b100:             alu_opcode = `alu_xor_ysyx_24100029;
            3'b110:             alu_opcode = `alu_or_ysyx_24100029;
            3'b111:             alu_opcode = `alu_and_ysyx_24100029;
            3'b001:             alu_opcode = `alu_sll_ysyx_24100029;
            3'b101:begin
               if(oprand == 7'b0000000)
                    alu_opcode = `alu_srl_ysyx_24100029;
                else
                    alu_opcode = `alu_sra_ysyx_24100029;
            end
           endcase
        end
    else if(opcode == `R_opcode_ysyx_24100029)
        begin
            case(funct3)
                3'b000: begin
                if(oprand == 7'b0000000)
                    alu_opcode = `alu_add_ysyx_24100029;
                else
                    alu_opcode = `alu_sub_ysyx_24100029;
                end
                3'b001:             alu_opcode = `alu_sll_ysyx_24100029;
                3'b010,3'b011:      alu_opcode = `alu_comparator_ysyx_24100029;
                3'b100:             alu_opcode = `alu_xor_ysyx_24100029;
                3'b110:             alu_opcode = `alu_or_ysyx_24100029;
                3'b111:             alu_opcode = `alu_and_ysyx_24100029;
                3'b101:begin
                    if(oprand == 7'b0000000)
                        alu_opcode = `alu_srl_ysyx_24100029;
                    else
                        alu_opcode = `alu_sra_ysyx_24100029;
                end
            endcase
        end
    else if(opcode == `B_opcode_ysyx_24100029)
        begin
             case(funct3)
                3'b000: alu_opcode = `alu_equal_ysyx_24100029;
                3'b001: alu_opcode = `alu_equal_ysyx_24100029;
                3'b100: alu_opcode = `alu_comparator_ysyx_24100029;
                3'b101: alu_opcode = `alu_comparator_ysyx_24100029;
                3'b110: alu_opcode = `alu_comparator_ysyx_24100029;
                3'b111: alu_opcode = `alu_comparator_ysyx_24100029;
                default: alu_opcode = `alu_add_ysyx_24100029;
             endcase
        end
    else 
        alu_opcode = `alu_add_ysyx_24100029;
end



endmodule


