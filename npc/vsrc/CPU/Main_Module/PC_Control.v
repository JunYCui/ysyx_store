module PC_Control (
    input                        clk                        ,
    input                        rst_n                      ,

    input              [  31: 0] rs1_value                  ,
    input              [  31: 0] imm                        ,
    input              [  31: 0] mtvec_out                  ,
    input              [  31: 0] mepc_out                   ,
    input              [  31: 0] Ex_result                  ,

    input              [  31: 0] pc                         ,
    input                        branch_flag                ,
    input                        branch_res                 ,
    input                        jump_flag                  ,
    input                        jump_choice                ,
    input                        mret_flag                  ,
    input                        mecall_flag                ,

    output             [  31: 0] dnpc                       ,
    output             [  31: 0] snpc                       ,
    output             [  31: 0] npc                        ,
    output reg                   valid                       
);


    assign                       snpc                      = pc + 4;
    assign                       npc                       = (mret_flag ||ecall_flag ||jump_flag || branch_flag)? dnpc:snpc;
 
    assign                       dnpc                      = (jump_flag)                                                 ? 
                                                            ((jump_choice)? IDU_rs1_value + imm                              :
                                                            (IDU_pc + imm)):(branch_flag == 1'b1 )                       ?
                                                            pc+imm:(mret_flag)                                           ?
                                                            mepc_out:(ecall_flag)                                        ?
                                                            mtvec_out:pc+4;

always @(*)begin
    if(!rst_n)    
        valid <= 1'b1;
    else if(branch_flag)
        valid <= ~valid;
    else 
        valid <= valid;
end


endmodule                                                           //PC_Control


