`include "./vsrc/CPU/define/para.v"
//`include "/home/cjy/ysyx-workbench/npc/vsrc/CPU/define/para.v"

module ysyx_24100029_EXU (
    input                        clock                      ,
    input                        reset                      ,

    /* control signal */
    input                        inst_clear                 ,

    input              [  31: 0] pc                         ,
    input              [   3: 0] csr_wen                    ,
    input                        R_wen                      ,
    input                        mem_wen                    ,
    input                        mem_ren                    ,
    input              [   4: 0] rd                         ,
    input              [   2: 0] funct3                     ,

    input              [  31: 0] imm                        ,
    input              [   1: 0] imm_opcode                 ,
    input              [   3: 0] alu_opcode                 ,
    input                        inv_flag                   ,
    input                        jump_flag                  ,
    input                        branch_flag                ,

    input              [   1: 0] add1_choice                ,
    input              [   1: 0] add2_choice                ,

    input              [  31: 0] rs1_value                  ,
    input              [  31: 0] rs2_value                  ,
    input              [  31: 0] csrs                       ,

    output                       branch_flag_next           ,
    output                       jump_flag_next             ,
    output             [   2: 0] funct3_next                ,
    output             [  31: 0] rs2_value_next             ,
    output             [  31: 0] imm_next                   ,
    output             [   4: 0] rd_next                    ,
    output             [  31: 0] csrs_next                  ,
    output             [   3: 0] csr_wen_next               ,
    output                       R_wen_next                 ,
    output                       mem_wen_next               ,
    output                       mem_ren_next               ,
    output             [  31: 0] pc_next                    ,
    output             [  31: 0] EX_result                  ,

    input                        valid_last                 ,
    output                       ready_last                 ,

    input                        ready_next                 ,
    output reg                   valid_next                 ,

    input              [  31: 0] inst                       ,
    output reg         [  31: 0] inst_next                   
);

    localparam                   NR_KEY_add1               = 3     ;
    localparam                   KEY_LEN_add1              = 2     ;
    localparam                   DATA_LEN_add1             = 32    ;

    localparam                   NR_KEY_add2               = 4     ;
    localparam                   KEY_LEN_add2              = 2     ;
    localparam                   DATA_LEN_add2             = 32    ;

    reg                [  31: 0] pc_reg                     ;
    reg                [   3: 0] csr_wen_reg                ;
    reg                          R_wen_reg                  ;
    reg                          mem_wen_reg                ;
    reg                          mem_ren_reg                ;
    reg                [   4: 0] rd_reg                     ;
    reg                [   2: 0] funct3_reg                 ;

    reg                [  31: 0] imm_reg                    ;
    reg                [   1: 0] imm_opcode_reg             ;
    reg                [   3: 0] alu_opcode_reg             ;
    reg                          inv_flag_reg               ;
    reg                          jump_flag_reg              ;
    reg                          branch_flag_reg            ;

    reg                [   1: 0] add1_choice_reg            ;
    reg                [   1: 0] add2_choice_reg            ;
    reg                [  31: 0] rs1_value_reg              ;
    reg                [  31: 0] rs2_value_reg              ;
    reg                [  31: 0] csrs_reg                   ;


    assign                       ready_last                = ready_next;



    always @(posedge clock) begin
        if(reset)
            valid_next <= 1'b0;
        else if(ready_last & valid_last & inst_clear)
            valid_next <= 1'b0;
        else if(ready_last & valid_last)
            valid_next <= 1'b1;
        else
            valid_next <= 1'b0;
    end



    always @(posedge clock) begin
        if(reset)begin
            pc_reg          <= 0;
            funct3_reg      <= 0;
            rd_reg          <= 0;
            imm_reg         <= 0;
            imm_opcode_reg  <= 0;
            alu_opcode_reg  <= 0;
            inv_flag_reg    <= 0;
            jump_flag_reg   <= 0;
            branch_flag_reg <= 0;

            add1_choice_reg <= 0;
            add2_choice_reg <= 0;
            rs1_value_reg   <= 0;
            rs2_value_reg   <= 0;
            csrs_reg        <= 0;
        end
        else if(valid_last & ready_next)
        begin
            pc_reg          <= pc           ;
            funct3_reg      <= funct3       ;
            rd_reg          <= rd;

            imm_reg         <= imm          ;
            imm_opcode_reg  <= imm_opcode   ;
            alu_opcode_reg  <= alu_opcode   ;
            inv_flag_reg    <= inv_flag     ;

            add1_choice_reg <= add1_choice  ;
            add2_choice_reg <= add2_choice  ;
            rs1_value_reg   <= rs1_value    ;
            rs2_value_reg   <= rs2_value    ;
            csrs_reg        <= csrs         ;

        end
    end

always @(posedge clock) begin
    if(reset)begin
        mem_ren_reg     <= 0;
        csr_wen_reg     <= 0;
        R_wen_reg       <= 0;
        mem_wen_reg     <= 0;
        jump_flag_reg   <= 0;
        branch_flag_reg <= 0;
    end
    else if(inst_clear &valid_last&ready_last)begin
        mem_ren_reg     <= 0;
        csr_wen_reg     <= 0;
        R_wen_reg       <= 0;
        mem_wen_reg     <= 0;
        jump_flag_reg   <= 0;
        branch_flag_reg <= 0;
    end
    else if(valid_last & ready_next) begin
        mem_ren_reg     <= mem_ren;
        csr_wen_reg     <= csr_wen;
        R_wen_reg       <= R_wen;
        mem_wen_reg     <= mem_wen;
        jump_flag_reg   <= jump_flag;
        branch_flag_reg <= branch_flag;
    end
end

always @(posedge clock) begin
    if(reset)
        inst_next <=0;
    else if(inst_clear)
        inst_next <=0;
    else if(valid_last & ready_next)
        inst_next <= inst;
end


    wire               [  31: 0] add_1                      ;
    wire               [  31: 0] add_2                      ;


    wire               [  31: 0] imm_12i                    ;
    wire               [  31: 0] imm_20i                    ;
/* verilator lint_off UNUSEDSIGNAL */
    wire                         overflow                   ;
    wire               [  31: 0] alu_res                    ;

    reg                [  31: 0] imm_add                    ;
    

    assign                       jump_flag_next            = jump_flag_reg;
    assign                       funct3_next               = funct3_reg;
    assign                       pc_next                   = pc_reg;
    assign                       rd_next                   = rd_reg;
    assign                       csrs_next                 = csrs_reg;
    assign                       csr_wen_next              = csr_wen_reg;
    assign                       R_wen_next                = R_wen_reg;
    assign                       mem_wen_next              = mem_wen_reg;
    assign                       mem_ren_next              = mem_ren_reg;
    assign                       EX_result                 = alu_res ^{31'd0,inv_flag_reg};
    assign                       rs2_value_next            = rs2_value_reg;
    assign                       branch_flag_next          = branch_flag_reg;
    assign                       imm_next                  = imm_reg;

    always@(*)begin
        case(imm_opcode_reg)
        `imm_12i_ysyx_24100029: imm_add = imm_12i;
        `imm_20u_ysyx_24100029: imm_add = {imm_reg[19:0] , 12'd0} ;
        `imm_20i_ysyx_24100029: imm_add = imm_20i << 1;
        `imm_5u_ysyx_24100029:  imm_add = {27'd0,imm_reg[4:0]};
        default: imm_add = 32'd0;
        endcase
    end




/* verilator lint_off IMPLICIT */

ysyx_24100029_MuxKeyInternal #(NR_KEY_add2, KEY_LEN_add2, DATA_LEN_add2, 0) i1 (add_2, add2_choice_reg, {DATA_LEN_add2{1'b0}},
{
2'd0, imm_add   ,
2'd1, rs2_value_reg ,
2'd2, csrs_reg      ,
2'd3, 32'd0
}
);

ysyx_24100029_MuxKeyInternal #(NR_KEY_add1, KEY_LEN_add1, DATA_LEN_add1, 0) i2 (add_1, add1_choice_reg, {DATA_LEN_add1{1'b0}},
{
`rs1_dist_reg_ysyx_24100029,    rs1_value_reg,
`rs1_dist_pc_ysyx_24100029,     pc_reg,
`rs1_dist_para_ysyx_24100029,   32'd0
}
);

/* verilator lint_off PINMISSING */
ysyx_24100029_ALU #(
    .BW                          (6'd32                     ) 
) ALU_i0
(
    .d1                          (add_1                     ),
    .d2                          (add_2                     ),
    .choice                      (alu_opcode_reg            ),
    .res                         (alu_res                   ),
    .overflow                    (overflow                  ) 

);

ysyx_24100029_sext #(
    .DATA_WIDTH                  (12                        ),
    .OUT_WIDTH                   (32                        ) 
) sext_i12
(
    .data                        (imm_reg[11:0]             ),
    .sext_data                   (imm_12i                   ) 
);

ysyx_24100029_sext #(
    .DATA_WIDTH                  (20                        ),
    .OUT_WIDTH                   (32                        ) 
) sext_i20
(
    .data                        (imm_reg[19:0]             ),
    .sext_data                   (imm_20i                   ) 
);



endmodule


