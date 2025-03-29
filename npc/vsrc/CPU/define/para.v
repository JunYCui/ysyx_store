/*interface define*/


// __opcode__

`define R_opcode_ysyx_24100029  7'b0110011
`define I0_opcode_ysyx_24100029 7'b0000011                          //lw
`define I1_opcode_ysyx_24100029 7'b0010011                          //addi
`define I2_opcode_ysyx_24100029 7'b1100111                          //jalr
`define S_opcode_ysyx_24100029  7'b0100011
`define B_opcode_ysyx_24100029  7'b1100011
`define U0_opcode_ysyx_24100029 7'b0110111                          //lui
`define U1_opcode_ysyx_24100029 7'b0010111                          //auipc
`define J_opcode_ysyx_24100029  7'b1101111                          //jal
`define M_opcode_ysyx_24100029  7'b1110011

// alu
`define alu_add_ysyx_24100029                   4'b0000
`define alu_sub_ysyx_24100029                   4'b0001
`define alu_or_ysyx_24100029                    4'b0010
`define alu_and_ysyx_24100029                   4'b0011
`define alu_xor_ysyx_24100029                   4'b0100
`define alu_signed_comparator_ysyx_24100029     4'b0101
`define alu_unsigned_comparator_ysyx_24100029   4'b0110
`define alu_equal_ysyx_24100029                 4'b0111
`define alu_sll_ysyx_24100029                   4'b1000
`define alu_srl_ysyx_24100029                   4'b1001
`define alu_sra_ysyx_24100029                   4'b1010

`define Performance_Count

