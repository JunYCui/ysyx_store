`include "../define/para.sv"


module ysyx_24100029_IDU(
    input                               clock                      ,
    input                               reset                      ,

    input                               pred_res                   ,
    input              [  31: 0]        pred_pc                    ,
    input              [  31: 0]        inst                       ,
    input              [  31: 0]        pc                         ,

    input              [  31: 0]        rd_value                   ,
    input              [  31: 0]        csrd                       ,
    input              [   4: 0]        rd                         ,
    input                               R_wen                      ,
    input              [   3: 0]        csr_wen                    ,

    input              [  31: 0]        EXU_rs1_in                 ,
    input              [  31: 0]        EXU_rs2_in                 ,
    input                               clear                      ,
    input                               stall                      ,

    output             [   4: 0]        rd_next                    ,
    output             [   2: 0]        funct3                     ,
    output                              fence_i_flag               ,

    output             [  31: 0]        branch_pc                  ,
    output             [  31: 0]        rs1_value                  ,
    output             [  31: 0]        rs2_value                  ,
    
    output             [  31: 0]        add1_value                 ,
    output             [  31: 0]        add2_value                 ,
    output             [   3: 0]        csr_wen_next               ,
    output                              R_wen_next                 ,
    output             [  31: 0]        rd_value_next              ,

    output                              mem_wen                    ,
    output                              mem_ren                    ,
    output                              inv_flag                   ,
    output                              branch_flag                ,
    output                              jal_flag                   ,
    output                              jalr_flag                  ,
    output             [  31: 0]        jal_pc                     ,

    output             [   3: 0]        alu_opcode                 ,
    output                              pred_res_next              ,
    output             [  31: 0]        pred_pc_next               ,

    output             [   4: 0]        rs1                        ,
    output             [   4: 0]        rs2                        ,
    output             [  31: 0]        a0_value                   ,
    output             [  31: 0]        mepc_out                   ,
    output             [  31: 0]        mtvec_out                  ,
    output             [  31: 0]        pc_next                    ,

`ifdef Performance_Count
    output reg         [  31: 0]        InstR_count                ,
    output reg         [  31: 0]        InstI_count                ,
    output reg         [  31: 0]        InstS_count                ,
    output reg         [  31: 0]        InstB_count                ,
    output reg         [  31: 0]        InstU_count                ,
    output reg         [  31: 0]        InstJ_count                ,
    output reg         [  31: 0]        InstM_count                ,
    output             [  31: 0]        inst_next                  ,

`endif
    input                               valid_last                 ,
    output                              ready_last                 ,

    input                               ready_next                 ,
    output  reg                         valid_next                  
);
`ifdef Performance_Count
    always @(posedge clock) begin
        if(reset)begin
            InstR_count <= 0;
            InstI_count <= 0;
            InstS_count <= 0;
            InstB_count <= 0;
            InstU_count <= 0;
            InstJ_count <= 0;
            InstM_count <= 0;
        end
        else if (valid_next & ready_next) begin
            InstR_count <= (opcode == `R_opcode_ysyx_24100029)? InstR_count+1:InstR_count;
            InstI_count <= (opcode == `I0_opcode_ysyx_24100029 || opcode == `I1_opcode_ysyx_24100029 || opcode == `I2_opcode_ysyx_24100029)? InstI_count+1 : InstI_count;
            InstS_count <= (opcode == `S_opcode_ysyx_24100029)? InstS_count+1 : InstS_count;
            InstB_count <= (opcode == `B_opcode_ysyx_24100029)? InstB_count+1 : InstB_count;
            InstU_count <= (opcode == `U0_opcode_ysyx_24100029 || opcode == `U1_opcode_ysyx_24100029)? InstU_count+1 : InstU_count;
            InstJ_count <= (opcode == `J_opcode_ysyx_24100029)? InstJ_count + 1 : InstJ_count;
            InstM_count <= (opcode == `M_opcode_ysyx_24100029)? InstM_count + 1 : InstM_count;
        end
    end
    assign                              inst_next                   = inst;

`endif

  
    wire               [  31: 0]        csr_addr                    ;
    wire               [   6: 0]        oprand                      ;
    wire               [   6: 0]        opcode                      ;

    wire               [  31: 0]        imm_I                       ;
    wire               [  31: 0]        imm_U                       ;
    wire               [  31: 0]        imm_R                       ;
    wire               [  31: 0]        imm_S                       ;
    wire               [  31: 0]        imm_B                       ;
    wire               [  31: 0]        imm_J                       ;
    wire               [  31: 0]        csrs                        ;
    wire               [  31: 0]        imm                         ;
    wire                                mret_flag                   ;
    wire                                ecall_flag                  ;
    wire               [  31: 0]        snpc                        ;

    reg                [  31: 0]        pc_reg,inst_reg,pred_pc_reg    ;
    reg                pred_res_reg;


    always @(posedge clock) begin
        if(reset|clear)
            valid_next <= 1'b0;
        else if(stall)
            valid_next <= valid_next;
        else if(valid_last & ready_last)
            valid_next <= 1'b1;
        else if(valid_next & ready_next)
            valid_next <= 1'b0;
    end


    always @(posedge clock) begin
        if(reset|clear)begin
            pc_reg <= 0;
            inst_reg <=0;
            pred_res_reg <= 0;
            pred_pc_reg <= 0;
        end
        else if(stall)begin
            pc_reg <= pc_reg;
            inst_reg <= inst_reg;
            pred_res_reg <= pred_res_reg;
            pred_pc_reg <= pred_pc_reg;
        end
        else if(ready_last&valid_last)begin
            pc_reg <= pc;
            inst_reg <= inst;
            pred_res_reg <= pred_res;
            pred_pc_reg <= pred_pc;
        end
    end


    assign                              snpc                        = pc_reg + 4;
    assign                              ready_last                  = ready_next;
    assign                              pred_pc_next                = pred_pc_reg;
    assign                              pred_res_next               = pred_res_reg;
    assign                              oprand                      = inst_reg[31:25];
    assign                              opcode                      = inst_reg[6:0];
    assign                              rs1                         = inst_reg[19:15];
    assign                              rs2                         = inst_reg[24:20];
    assign                              funct3                      = inst_reg[14:12];
    assign                              rd_next                     = inst_reg[11:7];

    assign                              ecall_flag                  = (inst_reg == 32'b00000000000000000000000001110011);//ecall
    assign                              mret_flag                   = (inst_reg == 32'b00110000001000000000000001110011);// mret
    assign                              fence_i_flag                = (inst_reg == 32'b00000000000000000001000000001111);

    assign                              csr_wen_next[0]             = (opcode == `M_opcode_ysyx_24100029 && imm == 32'h341);
    assign                              csr_wen_next[1]             = (opcode == `M_opcode_ysyx_24100029 && imm == 32'h342);
    assign                              csr_wen_next[2]             = (opcode == `M_opcode_ysyx_24100029 && imm == 32'h300);
    assign                              csr_wen_next[3]             = (opcode == `M_opcode_ysyx_24100029 && imm == 32'h305);

    assign                              R_wen_next                  = (opcode == `S_opcode_ysyx_24100029 || opcode == `B_opcode_ysyx_24100029 || opcode == 0)? 1'b0:1'b1;
    assign                              mem_wen                     = (opcode == `S_opcode_ysyx_24100029);
    assign                              mem_ren                     = (opcode == `I0_opcode_ysyx_24100029);


    assign                              jalr_flag                   = opcode == `I2_opcode_ysyx_24100029;
    assign                              jal_flag                    = opcode == `J_opcode_ysyx_24100029 | mret_flag | ecall_flag ;

    assign                              inv_flag                    = (opcode == `B_opcode_ysyx_24100029 && (funct3 == 3'b101 || funct3 == 3'b111 || funct3 == 3'b000 ))? 1'b1:1'b0;
    assign                              branch_flag                 = (opcode == `B_opcode_ysyx_24100029)? 1'b1:1'b0;
 
    assign                              csr_addr                    = imm;

    assign                              rd_value_next               = jal_flag|jalr_flag? snpc: 
                                                                    (|csr_wen_next)? csrs:
                                                                    0;

    assign                              jal_pc                      = mret_flag? mepc_out : 
                                                                      ecall_flag? mtvec_out:pc_reg + imm;


    assign                              branch_pc                   = pc_reg + imm;
    assign                              pc_next                     = pc_reg;


    assign add1_value = (opcode == `U0_opcode_ysyx_24100029)? 0 :
                        (opcode == `J_opcode_ysyx_24100029 || opcode == `U1_opcode_ysyx_24100029 )? pc_reg :
                        EXU_rs1_in;

    assign add2_value = (opcode == `R_opcode_ysyx_24100029 || opcode == `B_opcode_ysyx_24100029)?  EXU_rs2_in :
                        (opcode == `M_opcode_ysyx_24100029 && funct3 == 3'b010)? rd_value_next :
                        (opcode == `M_opcode_ysyx_24100029 && funct3 == 3'b001)? 0 : imm;
 

    assign alu_opcode   = (opcode == `I1_opcode_ysyx_24100029 && funct3 == 3'b010)                                                    ||
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
                        `alu_sll_ysyx_24100029 :(opcode == `I1_opcode_ysyx_24100029 && funct3 == 3'b101 && oprand[5] == 1'b0)    ||
                        (opcode == `R_opcode_ysyx_24100029 && funct3 == 3'b101 && oprand[5] == 1'b0)                             ?
                        `alu_srl_ysyx_24100029 :(opcode == `I1_opcode_ysyx_24100029 && funct3 == 3'b101 && oprand[5] == 1'b1)    ||
                        (opcode == `R_opcode_ysyx_24100029 && funct3 == 3'b101 && oprand[5] == 1'b1)                             ?
                        `alu_sra_ysyx_24100029 : (opcode == `R_opcode_ysyx_24100029 && funct3 == 3'b000 && oprand[5] == 1'b1)    ?
                        `alu_sub_ysyx_24100029 : (opcode == `B_opcode_ysyx_24100029 && funct3[2:1] == 2'b00)                        ?
                        `alu_equal_ysyx_24100029:`alu_add_ysyx_24100029;


    assign                              imm_I                       = {{20{inst_reg[31]}},inst_reg[31:20]};
    assign                              imm_U                       = {inst_reg[31:12],12'd0};
    assign                              imm_R                       = {25'd0,inst_reg[31:25]};
    assign                              imm_S                       = {{20{inst_reg[31]}},inst_reg[31:25],inst_reg[11:7]};
    assign                              imm_B                       = {imm_S[31:11],imm_S[0],imm_S[10:1]}<<1;
    assign                              imm_J                       = {{11{inst_reg[31]}},inst_reg[31],inst_reg[19:12],inst_reg[20],inst_reg[30:21]}<<1;
/* verilator lint_off IMPLICIT */

    assign imm = (opcode == `I0_opcode_ysyx_24100029 || opcode == `I1_opcode_ysyx_24100029 || opcode == `I2_opcode_ysyx_24100029 || opcode == `M_opcode_ysyx_24100029)? imm_I:
                 (opcode == `U0_opcode_ysyx_24100029 || opcode == `U1_opcode_ysyx_24100029)? imm_U:
                 (opcode == `J_opcode_ysyx_24100029)? imm_J:
                 (opcode == `B_opcode_ysyx_24100029)? imm_B:
                 (opcode == `S_opcode_ysyx_24100029)? imm_S:
                 (opcode == `S_opcode_ysyx_24100029)? imm_R:
                  0;

ysyx_24100029_Reg_Stack Reg_Stack_inst0(
    .reset                              (reset                     ),
    .clock                              (clock                     ),
    .pc                                 (pc_reg                    ),
    .ecall_flag                         (ecall_flag                ),

    .rs1                                (rs1[4:0]                  ),
    .rs2                                (rs2[4:0]                  ),
    .rd                                 (rd[4:0]                   ),
    .rd_value                           (rd_value                  ),

    .csr_addr                           (csr_addr                  ),
    .R_wen                              (R_wen                     ),
    .csr_wen                            (csr_wen                   ),
    .csrd                               (csrd                      ),

    .rs1_value                          (rs1_value                 ),
    .rs2_value                          (rs2_value                 ),
    .a0_value                           (a0_value                  ),
    .csrs                               (csrs                      ),
    .mepc_out                           (mepc_out                  ),
    .mtvec_out                          (mtvec_out                 ) 
);


endmodule

