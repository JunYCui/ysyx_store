<<<<<<< HEAD
// __Type__
`define R_Type 3'd1
`define I_Type 3'd2
`define S_Type 3'd3
`define B_Type 3'd4
`define U_Type 3'd5
`define J_Type 3'd6

// __opcode__

`define R_opcode  7'b0110011
`define I0_opcode 7'b0000011
`define I1_opcode 7'b0010011
`define S_opcode  7'b0100011
`define B_opcode  7'b1100011
`define U0_opcode 7'b0110111
`define U1_opcode 7'b0010111
`define J0_opcode 7'b1101111
`define J1_opcode 7'b1100111
=======
// __opcode__

`define R_opcode_ysyx_24100029  7'b0110011
`define I0_opcode_ysyx_24100029 7'b0000011
`define I1_opcode_ysyx_24100029 7'b0010011
`define I2_opcode_ysyx_24100029 7'b1100111
`define S_opcode_ysyx_24100029  7'b0100011
`define B_opcode_ysyx_24100029  7'b1100011
`define U0_opcode_ysyx_24100029 7'b0110111
`define U1_opcode_ysyx_24100029 7'b0010111
`define J_opcode_ysyx_24100029 7'b1101111

// alu
`define alu_add_ysyx_24100029           4'b0000
`define alu_sub_ysyx_24100029           4'b0001
`define alu_not_ysyx_24100029           4'b0010
`define alu_or_ysyx_24100029            4'b0011
`define alu_and_ysyx_24100029           4'b0100
`define alu_xor_ysyx_24100029           4'b0101
`define alu_comparator_ysyx_24100029    4'b0110
`define alu_equal_ysyx_24100029         4'b0111
`define alu_sll_ysyx_24100029           4'b1000
`define alu_srl_ysyx_24100029           4'b1001
`define alu_sra_ysyx_24100029           4'b1010

// rs1_dist
`define rs1_dist_reg_ysyx_24100029       2'b00
`define rs1_dist_pc_ysyx_24100029        2'b01
`define rs1_dist_para_ysyx_24100029      2'b10

// imm_opcode 

`define imm_12i_ysyx_24100029            2'b00
`define imm_20u_ysyx_24100029            2'b01
`define imm_20i_ysyx_24100029            2'b10
`define imm_5u_ysyx_24100029             2'b11

>>>>>>> 3e8efcc
