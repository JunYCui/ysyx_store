`include "vsrc/para.v"
/* verilator lint_off UNUSEDSIGNAL */
module EXU (
    input                        clk                        ,
    input                        rst                        ,
    input              [  31: 0] pc                         ,

    input              [  31: 0] imm                        ,
    input              [   1: 0] imm_opcode                 ,
    input              [   3: 0] alu_opcode                 ,
    input                        inv_flag                   ,
    
    input              [   1: 0] rs1_flag                   ,
    input              [   1: 0] rs2_flag                   ,

    input              [  31: 0] rs1_value                  ,
    input              [  31: 0] rs2_value                  ,
    input              [  31: 0] csr_value                  ,

    output             [  31: 0] EX_result                   
);

    localparam                   NR_KEY_add1               = 3     ;
    localparam                   KEY_LEN_add1              = 2     ;
    localparam                   DATA_LEN_add1             = 32    ;

    localparam                   NR_KEY_add2               = 4     ;
    localparam                   KEY_LEN_add2              = 2     ;
    localparam                   DATA_LEN_add2             = 32    ;


    wire               [  31: 0] add_1                      ;
    wire               [  31: 0] add_2                      ;


    wire               [  31: 0] imm_12i                    ;
    wire               [  31: 0] imm_20i                    ;
 
    wire                         overflow                   ;
    wire               [  31: 0] alu_res                    ;

    reg                [  31: 0] imm_add                    ;
    
    assign                       EX_result                 = alu_res ^{31'd0,inv_flag};


    always@(*)begin
        case(imm_opcode)
        `imm_12i_ysyx_24100029: imm_add = imm_12i;
        `imm_20u_ysyx_24100029: imm_add = {imm[19:0] , 12'd0} ;
        `imm_20i_ysyx_24100029: imm_add = imm_20i << 1;
        `imm_5u_ysyx_24100029:  imm_add = {27'd0,imm[4:0]};
        default: imm_add = 32'd0;
        endcase
    end




/* verilator lint_off IMPLICIT */

MuxKeyInternal #(NR_KEY_add2, KEY_LEN_add2, DATA_LEN_add2, 0) i1 (add_2, rs2_flag, {DATA_LEN_add2{1'b0}},
{
2'd0, imm_add   ,
2'd1, rs2_value ,
2'd2, csr_value ,
2'd3, 32'd0
}
);

MuxKeyInternal #(NR_KEY_add1, KEY_LEN_add1, DATA_LEN_add1, 0) i2 (add_1, rs1_flag, {DATA_LEN_add1{1'b0}},
{
`rs1_dist_reg_ysyx_24100029,    rs1_value,
`rs1_dist_pc_ysyx_24100029,     pc,
`rs1_dist_para_ysyx_24100029,   32'd0
}
);

/* verilator lint_off PINMISSING */
ALU #(
    .BW                          (6'd32                     ) 
) ALU_i0
(
    .d1                          (add_1                     ),
    .d2                          (add_2                     ),
    .choice                      (alu_opcode                ),
    .res                         (alu_res                   ),
    .overflow                    (overflow                  ) 

);

sext #(
    .DATA_WIDTH                  (12                        ),
    .OUT_WIDTH                   (32                        ) 
) sext_i12
(
    .data                        (imm[11:0]                 ),
    .sext_data                   (imm_12i                   ) 
);

sext #(
    .DATA_WIDTH                  (20                        ),
    .OUT_WIDTH                   (32                        ) 
) sext_i20
(
    .data                        (imm[19:0]                 ),
    .sext_data                   (imm_20i                   ) 
);



endmodule


