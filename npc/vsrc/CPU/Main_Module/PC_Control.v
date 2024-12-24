module PC_Control (
    input                        clk                        ,
    input                        rst_n                      ,

    input              [  31: 0] rs1_value                  ,
    input              [  31: 0] imm                        ,
    input              [  31: 0] mtvec_out                  ,
    input              [  31: 0] mepc_out                   ,
    input              [  31: 0] Ex_result                  ,

    input              [  31: 0] IDU_pc                     ,
    input                        IDU_branch_flag            ,
    input              [  31: 0] WBU_pc                     ,
    input                        WBU_branch_flag            ,
    input                        jump_flag                  ,
    input                        jump_choice                ,
    input                        mret_flag                  ,
    input                        mecall_flag                ,

    output             [  31: 0] dnpc                       ,
    output                       dnpc_flag                  ,
    output reg                   valid                       
);

    reg                [  31: 0] branch_imm                 ;

    assign                       dnpc_flag                 = (mret_flag ||mecall_flag ||jump_flag || WBU_branch_flag);
 
    assign                       dnpc                      = (jump_flag)                                                          ? 
                                                            ((jump_choice)? rs1_value + imm                                       :
                                                            (IDU_pc + imm)):(WBU_branch_flag)                                     ?
                                                            ((Ex_result != 32'd0)? WBU_pc+branch_imm:WBU_pc+4):(mret_flag)        ?
                                                            mepc_out:(mecall_flag)                                                ?
                                                            mtvec_out:0;
    always @(posedge clk) begin
        if(!rst_n)
            branch_imm <= 0 ;
        else if(IDU_branch_flag)
            branch_imm <= imm;
        else if(WBU_branch_flag)
            branch_imm <= 0;
        else
            branch_imm <= branch_imm;
    end
                                                    

always @(posedge clk)begin
    if(!rst_n)
        valid <= 1'b1;
    else if(IDU_branch_flag)
        valid <= 1'b0;
    else if(WBU_branch_flag)
        valid <= 1'b1;
    else
        valid <= valid;

end


endmodule                                                           //PC_Control



