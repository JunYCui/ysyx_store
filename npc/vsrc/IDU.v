`include "./vsrc/para.v"
/* verilator lint_off UNUSEDPARAM */

    localparam                   i1_NR_KEY                 = 10    ;
    localparam                   i1_KEY_LEN                = 7     ;
    localparam                   i1_DATA_LEN               = 32    ;


module IDU(
    input                        clk                        ,
    input                        rst_n                      ,
    input              [  31: 0] inst                       ,
    input              [  31: 0] pc                         ,
    input              [  31: 0] rd_value                   ,
    input              [  31: 0] csrd                       ,
    input              [   4: 0] rd                         ,
    input                        R_wen                      ,
    input              [   3: 0] csr_wen                    ,

    output             [  31: 0] pc_next                    ,
    output             [   4: 0] rd_next                    ,
    output             [  31: 0] imm                        ,
    output             [   2: 0] funct3                     ,
    output                       mret_flag                  ,
    output                       ecall_flag                 ,

    output             [  31: 0] rs1_value                  ,
    output             [  31: 0] rs2_value                  ,
    output             [   3: 0] csr_wen_next               ,
    output                       R_wen_next                 ,
    output             [  31: 0] csrs                       ,

    output                       mem_wen                    ,
    output                       mem_ren                    ,
    output             [   1: 0] add1_choice                ,
    output             [   1: 0] add2_choice                ,
    output                       inv_flag                   ,
    output                       branch_flag                ,
    output                       jump_flag                  ,
    output                       jump_choice                ,
    output             [   1: 0] imm_opcode                 ,
    output             [   3: 0] alu_opcode                 ,

    output             [  31: 0] a0_value                   ,
    output             [  31: 0] mepc_out                   ,
    output             [  31: 0] mtvec_out                   

);


    wire               [  31: 0] csr_addr                   ;
    wire               [   6: 0] oprand                     ;
    wire               [   6: 0] opcode                     ;
    wire               [   4: 0] rs1                        ;
    wire               [   4: 0] rs2                        ;
 
    assign                       oprand                    = inst[31:25];
    assign                       opcode                    = inst[6:0];
    assign                       rs1                       = inst[19:15];
    assign                       rs2                       = inst[24:20];
    assign                       funct3                    = inst[14:12];
    assign                       rd_next                   = inst[11:7];
    assign                       pc_next                   = pc;

    assign                       ecall_flag                = (inst == 32'b00000000000000000000000001110011);//ecall
    assign                       mret_flag                 = (inst == 32'b00110000001000000000000001110011);// mret

    assign                       csr_wen_next[0]           = (opcode == `M_opcode_ysyx_24100029 && imm == 32'h341) || ecall_flag;
    assign                       csr_wen_next[1]           = (opcode == `M_opcode_ysyx_24100029 && imm == 32'h342) || ecall_flag;
    assign                       csr_wen_next[2]           = (opcode == `M_opcode_ysyx_24100029 && imm == 32'h300);
    assign                       csr_wen_next[3]           = (opcode == `M_opcode_ysyx_24100029 && imm == 32'h305);

    assign                       R_wen_next                = (opcode == `S_opcode_ysyx_24100029 || opcode == `B_opcode_ysyx_24100029)? 1'b0:1'b1;
    assign                       mem_wen                   = (opcode == `S_opcode_ysyx_24100029);
    assign                       mem_ren                   = (opcode == `I0_opcode_ysyx_24100029);

    assign                       jump_flag                 = (opcode == `I2_opcode_ysyx_24100029 || opcode == `J_opcode_ysyx_24100029)? 1'b1:1'b0;
    assign                       jump_choice               = (opcode == `I2_opcode_ysyx_24100029);
    assign                       add2_choice               = (opcode == `R_opcode_ysyx_24100029 || opcode == `B_opcode_ysyx_24100029)? 2'd1:
                                                             (opcode == `M_opcode_ysyx_24100029 && funct3 == 3'b010)? 2'd2:
                                                             (opcode == `M_opcode_ysyx_24100029 && funct3 == 3'b001)? 2'd3:2'd0;
    assign                       inv_flag                  = (opcode == `B_opcode_ysyx_24100029 && (funct3 == 3'b101 || funct3 == 3'b111 || funct3 == 3'b000 ))? 1'b1:1'b0;
    assign                       branch_flag               = (opcode == `B_opcode_ysyx_24100029)? 1'b1:1'b0;
    assign                       csr_addr                  = imm;



    assign imm_opcode = (opcode == `U0_opcode_ysyx_24100029 || opcode == `U1_opcode_ysyx_24100029 )                            ?
                        `imm_20u_ysyx_24100029:(opcode == `J_opcode_ysyx_24100029)                                             ?
                        `imm_20i_ysyx_24100029:(opcode == `I1_opcode_ysyx_24100029 && (funct3 == 3'b001 || funct3 == 3'b101))  ?
                        `imm_5u_ysyx_24100029 : `imm_12i_ysyx_24100029                                                         ;
    assign add1_choice  =  (opcode == `U0_opcode_ysyx_24100029)                                                                   ?
                        `rs1_dist_para_ysyx_24100029:(opcode == `J_opcode_ysyx_24100029 || opcode == `U1_opcode_ysyx_24100029 )?
                        `rs1_dist_pc_ysyx_24100029   : `rs1_dist_reg_ysyx_24100029                                             ;

    assign alu_opcode = (opcode == `S_opcode_ysyx_24100029 ||  opcode == `I0_opcode_ysyx_24100029 
                        || opcode == `U0_opcode_ysyx_24100029 || opcode == `U1_opcode_ysyx_24100029
                        || opcode == `J_opcode_ysyx_24100029 || opcode == `I2_opcode_ysyx_24100029
                        || (opcode ==`I1_opcode_ysyx_24100029  &&  funct3 == 3'b000)  || (opcode == `R_opcode_ysyx_24100029         &&
                        funct3 == 3'b000 && oprand == 7'b0000000) || (opcode == `B_opcode_ysyx_24100029                             &&
                        funct3[2:1] == 2'b01                 ))                                                                     ?
                        `alu_add_ysyx_24100029 :(opcode == `I1_opcode_ysyx_24100029 && funct3 == 3'b010)                            ||
                        (opcode == `R_opcode_ysyx_24100029 && funct3 == 3'b010)                                                     ||
                        (opcode == `B_opcode_ysyx_24100029 && (funct3 == 3'b101 || funct3 == 3'b100))                               ?
                        `alu_signed_comparator_ysyx_24100029:
                        (opcode == `B_opcode_ysyx_24100029 && (funct3 == 3'b110 || funct3 == 3'b111))                               ||
                        (opcode == `I1_opcode_ysyx_24100029 && (funct3 == 3'b011))                                                  ||
                        (opcode == `R_opcode_ysyx_24100029 && (funct3 ==  3'b011))                                                  ?
                        `alu_unsigned_comparator_ysyx_24100029:
                        (opcode == `I1_opcode_ysyx_24100029 && funct3 == 3'b100 )                                                   ||
                        (opcode == `R_opcode_ysyx_24100029 && funct3 == 3'b100 )                                                    ?
                        `alu_xor_ysyx_24100029 :(opcode == `I1_opcode_ysyx_24100029 && funct3 == 3'b110 )                           ||
                        (opcode == `R_opcode_ysyx_24100029 && funct3 == 3'b110 )                                                    ||
                        (opcode == `M_opcode_ysyx_24100029 && funct3 == 3'b010 )                                                    ?
                        `alu_or_ysyx_24100029  : (opcode == `I1_opcode_ysyx_24100029 && funct3 == 3'b111 )                          ||
                        (opcode == `R_opcode_ysyx_24100029 && funct3 == 3'b111 )                                                    ?
                        `alu_and_ysyx_24100029 :(opcode == `I1_opcode_ysyx_24100029 && funct3 == 3'b001  )                          ||
                        (opcode == `R_opcode_ysyx_24100029 && funct3 == 3'b001 )                                                    ?
                        `alu_sll_ysyx_24100029 :(opcode == `I1_opcode_ysyx_24100029 && funct3 == 3'b101 && oprand == 7'b0000000)    ||
                        (opcode == `R_opcode_ysyx_24100029 && funct3 == 3'b101 && oprand == 7'b0000000)                             ?
                        `alu_srl_ysyx_24100029 :(opcode == `I1_opcode_ysyx_24100029 && funct3 == 3'b101 && oprand != 7'b0000000)    ||
                        (opcode == `R_opcode_ysyx_24100029 && funct3 == 3'b101 && oprand != 7'b0000000)                             ?
                        `alu_sra_ysyx_24100029 : (opcode == `R_opcode_ysyx_24100029 && funct3 == 3'b000 && oprand != 7'b0000000)    ?
                        `alu_sub_ysyx_24100029 : (opcode == `B_opcode_ysyx_24100029 && funct3[2:1] == 2'b00)                        ?
                        `alu_equal_ysyx_24100029:`alu_add_ysyx_24100029;







/* verilator lint_off IMPLICIT */

/* imm 处理*/
MuxKeyInternal #(i1_NR_KEY, i1_KEY_LEN, i1_DATA_LEN, 0) i1 (imm, opcode, {i1_DATA_LEN{1'b0}},
{`R_opcode_ysyx_24100029 ,    {25'd0,inst[31:25]},
 `I0_opcode_ysyx_24100029,    {20'd0,inst[31:20]},
 `I1_opcode_ysyx_24100029,    {20'd0,inst[31:20]},
 `I2_opcode_ysyx_24100029,    {{20{inst[31]}},inst[31:20]},
 `U0_opcode_ysyx_24100029,    {12'd0,inst[31:12]},
 `U1_opcode_ysyx_24100029,    {12'd0,inst[31:12]},
 `J_opcode_ysyx_24100029 ,    {{12{inst[31]}},inst[31],inst[19:12],inst[20],inst[30:21]}<<1,
 `B_opcode_ysyx_24100029 ,    {{20{inst[31]}},inst[31],inst[7],inst[30:25],inst[11:8]}<<1,
 `S_opcode_ysyx_24100029 ,    {20'd0,inst[31:25],inst[11:7]},
 `M_opcode_ysyx_24100029 ,    {20'd0,inst[31:20]}
 });

Reg_Stack Reg_Stack_inst0(
    .rst_n                       (rst_n                     ),
    .clk                         (clk                       ),
    .pc                          (pc                        ),
    .ecall_flag                  (ecall_flag                ),

    .rs1                         (rs1                       ),
    .rs2                         (rs2                       ),
    .rd                          (rd                        ),
    .rd_value                    (rd_value                  ),

    .csr_addr                    (csr_addr                  ),
    .R_wen                       (R_wen                     ),
    .csr_wen                     (csr_wen                   ),
    .csrd                        (csrd                      ),

    .rs1_value                   (rs1_value                 ),
    .rs2_value                   (rs2_value                 ),
    .a0_value                    (a0_value                  ),
    .csrs                        (csrs                      ),
    .mepc_out                    (mepc_out                  ),
    .mtvec_out                   (mtvec_out                 ) 
);





endmodule

