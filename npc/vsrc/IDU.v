`include "vsrc/para.v"
/* verilator lint_off UNUSEDPARAM */
localparam i0_NR_KEY  = 4'd9;
localparam i0_KEY_LEN = 4'd7;
localparam i0_DATA_LEN= 4'd4;

module IDU(
    input [31:0]PC  ,
    output[4 :0]rs1 ,
    output[4 :0]rs2 ,
    output[4 :0]rd  ,
    output[20:0]imm ,
    output[3: 0]Type,
    output[6:0]opcode
);



assign opcode = PC[6:0];

// choose type
MuxKeyInternal #(i0_NR_KEY, i0_KEY_LEN, i0_DATA_LEN, 0) i0 (out, key, {i0_DATA_LEN{1'b0}}, 
{R_opcode,R_Type,
 B_opcode,B_Type,
 S_opcode,S_Type,
 I0_opcode,I_Type,
 I1_opcode,I_Type,
 J0_opcode,J_Type,
 J1_opcode,J_Type,
 U0_opcode,U_Type,
 U1_opcode,U_Type
 });



endmodule

