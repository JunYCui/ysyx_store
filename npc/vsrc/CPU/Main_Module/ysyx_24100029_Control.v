module ysyx_24100029_Control (
    input              [  31: 0]        mtvec_out                  ,
    input              [  31: 0]        mepc_out                   ,

    input              [  31: 0]        EXU_imm                    ,
    input              [  31: 0]        EXU_pc                     ,
    input              [  31: 0]        Ex_result                  ,
    input              [  31: 0]        MEM_Ex_result              ,

    input              [  31: 0]        MEM_Rdata                  ,
    input              [  31: 0]        IDU_rs1_value              ,
    input              [  31: 0]        IDU_rs2_value              ,

    input                               branch_flag                ,
    input                               jump_flag                  ,
    input                               mret_flag                  ,
    input                               ecall_flag                 ,
    input                               EXU_mem_ren                ,
    input                               MEM_mem_ren                ,
    input                               fence_i_flag               ,

    input              [   4: 0]        IDU_rs1                    ,
    input              [   4: 0]        IDU_rs2                    ,

    input                               IDU_valid                  ,
    input                               EXU_valid                  ,
    input                               MEM_valid                  ,

    input              [   4: 0]        EXU_rd                     ,
    input              [   4: 0]        MEM_rd                     ,

    input                               EXU_R_Wen                  ,
    input                               MEM_R_Wen                  ,

    output             [  31: 0]        EXU_rs1_in                 ,
    output             [  31: 0]        EXU_rs2_in                 ,

    output                              icache_clr                 ,
    output                              IDU_inst_clear             ,
    output             [  31: 0]        dnpc                       ,
    output                              dnpc_flag                   
);


    wire               [   1: 0]        IDU_rs1_choice              ;
    wire               [   1: 0]        IDU_rs2_choice              ;
    wire                                exu_clear_cond            =jump_flag | fence_i_flag | (branch_flag & Ex_result[0]);
    wire                                idu_clear_cond            =mret_flag | ecall_flag;
    wire [31:0] exu_pc_plus_imm;
    assign                              IDU_inst_clear              = (EXU_valid & exu_clear_cond) | (IDU_valid & idu_clear_cond);


    assign                              dnpc_flag                   = IDU_inst_clear;
    assign                              icache_clr                  = fence_i_flag&EXU_valid;

    assign exu_pc_plus_imm = EXU_pc + EXU_imm;  // 独立计算
    assign dnpc = (~EXU_valid) ? (mret_flag ? mepc_out : mtvec_out) :
                    jump_flag   ? Ex_result :
                    branch_flag ? exu_pc_plus_imm : 32'b0;



    assign EXU_rs1_in = (IDU_rs1_choice == 2'b01)? Ex_result:
                        (IDU_rs1_choice == 2'b11)? MEM_Rdata:
                        (IDU_rs1_choice == 2'b10)? MEM_Ex_result:
                        IDU_rs1_value;

    assign EXU_rs2_in = (IDU_rs2_choice == 2'b01)? Ex_result:
                        (IDU_rs2_choice == 2'b11)? MEM_Rdata:
                        (IDU_rs2_choice == 2'b10)? MEM_Ex_result:
                        IDU_rs2_value;


ysyx_24100029_Data_hazard Data_hazard_inst(
    .IDU_rs1                            (IDU_rs1                   ),
    .IDU_rs2                            (IDU_rs2                   ),

    .EXU_rd                             (EXU_rd                    ),
    .MEM_rd                             (MEM_rd                    ),

    .MEM_valid                          (MEM_valid                 ),
    .EXU_valid                          (EXU_valid                 ),
    .IDU_valid                          (IDU_valid                 ),

    .MEM_mem_ren                        (MEM_mem_ren               ),
    .EXU_R_Wen                          (EXU_R_Wen                 ),
    .MEM_R_Wen                          (MEM_R_Wen                 ),

    .IDU_rs1_choice                     (IDU_rs1_choice            ),
    .IDU_rs2_choice                     (IDU_rs2_choice            ) 
);

endmodule                                                           //PC_Control



