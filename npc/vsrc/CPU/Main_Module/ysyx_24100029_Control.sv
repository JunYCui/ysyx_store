
module ysyx_24100029_Control (
    input              [  31: 0]        Ex_result                  ,
    input              [  31: 0]        MEM_rd_value               ,

    input              [  31: 0]        IDU_rs1_value              ,
    input              [  31: 0]        IDU_rs2_value              ,

    input                               EXU_branch_flag            ,
    input                               IDU_jal_flag               ,
    input                               EXU_jalr_flag              ,
    input                               fence_i_flag               ,

    input              [  31: 0]        EXU_pc                     ,
    input              [  31: 0]        IDU_pc                     ,
    input              [   4: 0]        IDU_rs1                    ,
    input              [   4: 0]        IDU_rs2                    ,
    input              [  31: 0]        EXU_branch_pc              ,
    input              [  31: 0]        IDU_jal_pc                 ,
    input              [  31: 0]        EXU_pred_pc                ,

    input                               IDU_valid                  ,
    input                               EXU_valid                  ,
    input                               MEM_valid                  ,
    input                               EXU_ready                  ,
    input                               LSU_ready                  ,

    input              [   4: 0]        EXU_rd                     ,
    input              [   4: 0]        MEM_rd                     ,

    input                               IDU_pred_res               ,
    input                               EXU_pred_res               ,
    input                               EXU_mem_ren                ,
    input                               EXU_R_Wen                  ,
    input                               MEM_R_Wen                  ,

    output                              br_valid                   ,
    output                              br_is_taken                ,
    output             [  31: 0]        br_pc                      ,
    output             [  31: 0]        br_npc                     ,

    output                              stall                      ,
    output             [  31: 0]        EXU_rs1_in                 ,
    output             [  31: 0]        EXU_rs2_in                 ,

    output                              icache_clr                 ,

    output                              IDU_clear                  ,
    output                              EXU_clear                  ,
    output             [  31: 0]        dnpc                       ,
    output                              dnpc_flag                   
);

    wire                                EXU_pred_error              ;
    wire                                IDU_pred_error              ;
    wire               [   1: 0]        IDU_rs1_choice              ;
    wire               [   1: 0]        IDU_rs2_choice              ;



    assign                              IDU_pred_error              = ~IDU_pred_res & IDU_jal_flag;
    assign                              EXU_pred_error              = (EXU_jalr_flag&(~EXU_pred_res || Ex_result != EXU_pred_pc) ) | (EXU_branch_flag & (EXU_pred_res ^ Ex_result[0]) );
    assign                              IDU_clear                   = (IDU_pred_error&IDU_valid&EXU_ready | EXU_pred_error&EXU_valid&LSU_ready);
    assign                              EXU_clear                   = EXU_pred_error&EXU_valid&LSU_ready | stall;

    assign                              dnpc_flag                   = EXU_pred_error&EXU_valid&LSU_ready | IDU_pred_error&IDU_valid&EXU_ready;
    assign                              stall                       = EXU_mem_ren&EXU_valid&LSU_ready&((EXU_rd == IDU_rs1) || (EXU_rd == IDU_rs2)) ;

    assign                              icache_clr                  = fence_i_flag&EXU_valid&LSU_ready;


    assign                              dnpc                        = EXU_pred_error? EXU_branch_flag? Ex_result[0]? EXU_branch_pc:EXU_pc+4 : Ex_result :IDU_jal_pc;

    assign                              br_valid                    = IDU_jal_flag | EXU_branch_flag | EXU_jalr_flag;
    assign                              br_is_taken                 = EXU_branch_flag ?  Ex_result[0]:EXU_jalr_flag? 1'b1:IDU_jal_flag ;
    assign                              br_npc                      = EXU_jalr_flag? Ex_result:
                                                                      EXU_branch_flag? EXU_branch_pc :  IDU_jal_pc  ;
    assign                              br_pc                       = EXU_jalr_flag | EXU_branch_flag ? EXU_pc : IDU_pc;







ysyx_24100029_dmux4to1 #(
    .DATA_WIDTH                         (32                        ),
    .Is_One_Hot                         (0   )                     ) 
u_ysyx_24100029_dmux4to1(
    .data_i0                            (IDU_rs2_value             ),
    .data_i1                            (Ex_result                 ),
    .data_i2                            (MEM_rd_value              ),
    .data_i3                            (IDU_rs2_value             ),

    .sel                                (IDU_rs2_choice            ),
    .data_o                             (EXU_rs2_in                ) 
);

ysyx_24100029_dmux4to1 #(
    .DATA_WIDTH                         (32                        ),
    .Is_One_Hot                         (0   )                     ) 
u1_ysyx_24100029_dmux4to1(
    .data_i0                            (IDU_rs1_value             ),
    .data_i1                            (Ex_result                 ),
    .data_i2                            (MEM_rd_value              ),
    .data_i3                            (IDU_rs1_value             ),

    .sel                                (IDU_rs1_choice            ),
    .data_o                             (EXU_rs1_in                ) 
);


ysyx_24100029_Data_hazard Data_hazard_inst(
    .IDU_rs1                            (IDU_rs1                   ),
    .IDU_rs2                            (IDU_rs2                   ),

    .EXU_rd                             (EXU_rd                    ),
    .MEM_rd                             (MEM_rd                    ),

    .IDU_valid                          (IDU_valid                 ),
    .EXU_valid                          (EXU_valid                 ),
    .MEM_valid                          (MEM_valid                 ),

    .EXU_R_Wen                          (EXU_R_Wen                 ),
    .MEM_R_Wen                          (MEM_R_Wen                 ),

    .IDU_rs1_choice                     (IDU_rs1_choice            ),
    .IDU_rs2_choice                     (IDU_rs2_choice            ) 
);

endmodule                                                           //PC_Control



