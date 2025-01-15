module Control (
    input              [  31: 0] mtvec_out                  ,
    input              [  31: 0] mepc_out                   ,

    input              [  31: 0] EXU_imm                    ,
    input              [  31: 0] EXU_pc                     ,
    input              [  31: 0] Ex_result                  ,
    input              [  31: 0] WBU_rd_value               ,
    input              [  31: 0] IDU_rs1_value              ,
    input              [  31: 0] IDU_rs2_value              ,

    input                        branch_flag                ,
    input                        jump_flag                  ,
    input                        mret_flag                  ,
    input                        ecall_flag                 ,
    input                        EXU_mem_ren                ,

    input              [   4: 0] IDU_rs1                    ,
    input              [   4: 0] IDU_rs2                    ,

    input              [   4: 0] EXU_rd                     ,
    input              [   4: 0] WBU_rd                     ,
    input                        EXU_R_Wen                  ,
    input                        WBU_R_Wen                  ,

    output             [  31: 0] EXU_rs1_in                 ,
    output             [  31: 0] EXU_rs2_in                 ,


    output                       IFU_pipe_s                 ,
    output                       IDU_pipe_s                 ,
    output                       IDU_inst_clear             ,
    output                       EXU_inst_clear             ,
    output             [  31: 0] dnpc                       ,
    output                       dnpc_flag                   
);


    wire                         pipe_stop                  ;
    wire               [   1: 0] IDU_rs1_choice             ;
    wire               [   1: 0] IDU_rs2_choice             ;

    assign                       dnpc_flag                 = (mret_flag ||ecall_flag ||jump_flag || branch_flag);

    assign                       IDU_inst_clear            = (mret_flag || ecall_flag || jump_flag || branch_flag);
    assign                       EXU_inst_clear            = (jump_flag || branch_flag || pipe_stop);


    assign                       dnpc                      = (jump_flag)                                                  ?                                                                         
                                                            Ex_result:(branch_flag)                                       ?
                                                            ((Ex_result != 32'd0)? EXU_pc+EXU_imm:EXU_pc+4):(mret_flag)   ?
                                                            mepc_out:(ecall_flag)                                         ?
                                                            mtvec_out:0;

    // lw 
    assign                       pipe_stop                 = (EXU_mem_ren && (IDU_rs1 == EXU_rd || IDU_rs2 == EXU_rd));
    assign                       IFU_pipe_s                = pipe_stop;
    assign                       IDU_pipe_s                = pipe_stop;


    assign EXU_rs1_in = (IDU_rs1_choice == 2'b01)? Ex_result:
                        (IDU_rs1_choice == 2'b10)? WBU_rd_value:
                        IDU_rs1_value;

    assign EXU_rs2_in = (IDU_rs2_choice == 2'b01)? Ex_result:
                        (IDU_rs2_choice == 2'b10)? WBU_rd_value:
                        IDU_rs2_value;


Aribter Aribter_inst(
    .IDU_rs1                     (IDU_rs1                   ),
    .IDU_rs2                     (IDU_rs2                   ),

    .EXU_rd                      (EXU_rd                    ),
    .WBU_rd                      (WBU_rd                    ),

    .EXU_R_Wen                   (EXU_R_Wen                 ),
    .WBU_R_Wen                   (WBU_R_Wen                 ),

    .IDU_rs1_choice              (IDU_rs1_choice            ),
    .IDU_rs2_choice              (IDU_rs2_choice            ) 
);

endmodule                                                           //PC_Control



