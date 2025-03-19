module ysyx_24100029_Control (
    input              [  31: 0]        mtvec_out                  ,
    input              [  31: 0]        mepc_out                   ,

    input              [  31: 0]        EXU_imm                    ,
    input              [  31: 0]        EXU_pc                     ,
    input              [  31: 0]        Ex_result                  ,
    input              [  31: 0]        MEM_Ex_result              ,

    input              [  31: 0]        MEM_Rdata                  ,
    input              [  31: 0]        WBU_rd_value               ,
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
    input                               WBU_valid                  ,

    input              [   4: 0]        EXU_rd                     ,
    input              [   4: 0]        MEM_rd                     ,
    input              [   4: 0]        WBU_rd                     ,

    input                               EXU_R_Wen                  ,
    input                               MEM_R_Wen                  ,
    input                               WBU_R_Wen                  ,

    output             [  31: 0]        EXU_rs1_in                 ,
    output             [  31: 0]        EXU_rs2_in                 ,

    output                              icache_clr                 ,
    output                              IDU_inst_clear             ,
    output             [  31: 0]        dnpc                       ,
    output                              dnpc_flag                   
);


    wire               [   2: 0]        IDU_rs1_choice              ;
    wire               [   2: 0]        IDU_rs2_choice              ;

    assign                              dnpc_flag                   = EXU_valid? jump_flag|fence_i_flag|(branch_flag&Ex_result[0]) : IDU_valid? mret_flag|ecall_flag : 0 ;
    //((mret_flag&IDU_valid) || (ecall_flag&IDU_valid) || (jump_flag&EXU_valid) || (branch_flag&EXU_valid&Ex_result[0]) || (fence_i_flag&EXU_valid) );

    assign                              IDU_inst_clear              = EXU_valid? jump_flag|fence_i_flag|(branch_flag&Ex_result[0]) : IDU_valid? mret_flag|ecall_flag : 0 ;
    assign                              icache_clr                  = fence_i_flag&EXU_valid;


    assign                       dnpc                      = EXU_valid?  (jump_flag? Ex_result : branch_flag?  EXU_pc+EXU_imm: EXU_pc+4)
                                                            : mret_flag? mepc_out:mtvec_out;
    /*(jump_flag&EXU_valid)                                                  ?                                                                         
                                                            Ex_result:(branch_flag&EXU_valid&(Ex_result[0]))                   ?
                                                             EXU_pc+EXU_imm:(mret_flag&IDU_valid)                                   ?
                                                            mepc_out:(ecall_flag&IDU_valid)                                         ?
                                                            mtvec_out:(fence_i_flag&EXU_valid)?
                                                            EXU_pc+4:0 ;

*/
    assign EXU_rs1_in = (IDU_rs1_choice == 3'b001)? Ex_result:
                        (IDU_rs1_choice == 3'b010)? WBU_rd_value:
                        (IDU_rs1_choice == 3'b011)? MEM_Rdata:
                        (IDU_rs1_choice == 3'b100)? MEM_Ex_result:
                        IDU_rs1_value;

    assign EXU_rs2_in = (IDU_rs2_choice == 3'b001)? Ex_result:
                        (IDU_rs2_choice == 3'b010)? WBU_rd_value:
                        (IDU_rs2_choice == 3'b011)? MEM_Rdata:
                        (IDU_rs2_choice == 3'b100)? MEM_Ex_result:
                        IDU_rs2_value;


ysyx_24100029_Data_hazard Data_hazard_inst(
    .IDU_rs1                            (IDU_rs1                   ),
    .IDU_rs2                            (IDU_rs2                   ),

    .EXU_rd                             (EXU_rd                    ),
    .MEM_rd                             (MEM_rd                    ),
    .WBU_rd                             (WBU_rd                    ),

    .MEM_valid                          (MEM_valid                 ),
    .EXU_valid                          (EXU_valid                 ),
    .WBU_valid                          (WBU_valid                 ),
    .IDU_valid                          (IDU_valid                 ),

    .MEM_mem_ren                        (MEM_mem_ren               ),
    .EXU_R_Wen                          (EXU_R_Wen                 ),
    .WBU_R_Wen                          (WBU_R_Wen                 ),
    .MEM_R_Wen                          (MEM_R_Wen                 ),

    .IDU_rs1_choice                     (IDU_rs1_choice            ),
    .IDU_rs2_choice                     (IDU_rs2_choice            ) 
);

endmodule                                                           //PC_Control



