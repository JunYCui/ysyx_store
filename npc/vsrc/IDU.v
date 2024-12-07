`include "./vsrc/para.v"
/* verilator lint_off UNUSEDPARAM */

    localparam                   i1_NR_KEY                 = 9     ;
    localparam                   i1_KEY_LEN                = 7     ;
    localparam                   i1_DATA_LEN               = 32    ;


module IDU(
    input              [  31: 0] inst                       ,
    output             [   4: 0] rs1                        ,
    output             [   4: 0] rs2                        ,
    output             [   4: 0] rd                         ,
    output             [  31: 0] imm                        ,
    output             [   2: 0] funct3                     ,
    output             [   6: 0] oprand                     ,
    output             [   6: 0] opcode                      
);


    assign                       oprand                    = inst[31:25];
    assign                       opcode                    = inst[6:0];
    assign                       rs1                       = inst[19:15];
    assign                       rs2                       = inst[24:20];
    assign                       funct3                    = inst[14:12];
    assign                       rd                        = inst[11:7];

/* verilator lint_off IMPLICIT */

/* imm 处理*/
MuxKeyInternal #(i1_NR_KEY, i1_KEY_LEN, i1_DATA_LEN, 0) i1 (imm, opcode, {i1_DATA_LEN{1'b0}},
{`R_opcode_ysyx_24100029,     {25'd0,inst[31:25]},
 `I0_opcode_ysyx_24100029,    {20'd0,inst[31:20]},
 `I1_opcode_ysyx_24100029,    {20'd0,inst[31:20]},
 `I2_opcode_ysyx_24100029,    {20'd0,inst[31:20]},
 `U0_opcode_ysyx_24100029,    {12'd0,inst[31:12]},
 `U1_opcode_ysyx_24100029,    {12'd0,inst[31:12]},
 `J_opcode_ysyx_24100029,     {12'd0,inst[31],inst[19:12],inst[20],inst[30:21]},
 `B_opcode_ysyx_24100029,     {20'd0,inst[31],inst[7],inst[30:25],inst[11:8]},
 `S_opcode_ysyx_24100029,     {20'd0,inst[31:25],inst[11:7]}
 });





endmodule

