import "DPI-C" function void fi();


module cpu_ysyx_24100029
(
    input                        clk                        ,
    input                        rst_n                      ,
    output reg         [  31: 0] pc                         ,
    output             [  31: 0] snpc                       ,
    output             [  31: 0] dnpc                        
);

    wire               [  31: 0] npc                        ;
    wire               [  31: 0] IFU_pc                     ;
    wire               [  31: 0] IFU_inst                   ;

    wire               [  31: 0] WBU_rd_value               ;
    wire               [  31: 0] WBU_csrd                   ;
    wire               [   4: 0] WBU_rd                     ;
    wire                         WBU_R_wen                  ;
    wire               [   3: 0] WBU_csr_wen                ;

    wire               [  31: 0] IDU_pc                     ;
    wire               [   4: 0] IDU_rd                     ;
    wire               [  31: 0] IDU_imm                    ;
    wire               [   2: 0] IDU_funct3                 ;
    wire                         IDU_mret_flag              ;
    wire                         IDU_ecall_flag             ;
    wire               [  31: 0] IDU_rs1_value              ;
    wire               [  31: 0] IDU_rs2_value              ;
    wire               [   3: 0] IDU_csr_wen                ;
    wire                         IDU_R_wen                  ;
    wire               [  31: 0] IDU_csrs                   ;
    wire                         IDU_mem_wen                ;
    wire                         IDU_mem_ren                ;
    wire               [   1: 0] IDU_add1_choice            ;
    wire               [   1: 0] IDU_add2_choice            ;
    wire                         IDU_inv_flag               ;
    wire                         IDU_branch_flag            ;
    wire                         IDU_jump_flag              ;
    wire                         IDU_jump_choice            ;
    wire               [   1: 0] IDU_imm_opcode             ;
    wire               [   3: 0] IDU_alu_opcode             ;
    wire               [  31: 0] IDU_a0_value               ;
    wire               [  31: 0] IDU_mepc_out               ;
    wire               [  31: 0] IDU_mtvec_out              ;

    wire                         EXU_jump_flag              ;
    wire               [   2: 0] EXU_funct3                 ;
    wire               [  31: 0] EXU_rs2_value              ;
    wire               [   4: 0] EXU_rd                     ;
    wire               [  31: 0] EXU_csrs                   ;
    wire               [   3: 0] EXU_csr_wen                ;
    wire                         EXU_R_wen                  ;
    wire                         EXU_mem_wen                ;
    wire                         EXU_mem_ren                ;
    wire               [  31: 0] EXU_pc                     ;
    wire               [  31: 0] EXU_result                  ;

    wire                         MEM_jump_flag              ;
    wire                         MEM_R_wen                  ;
    wire               [  31: 0] MEM_Rdata                  ;
    wire               [   3: 0] MEM_csr_wen                ;
    wire               [  31: 0] MEM_Ex_result              ;
    wire               [  31: 0] MEM_csrs                   ;
    wire               [  31: 0] MEM_pc                     ;
    wire               [   4: 0] MEM_rd                     ;
    wire                         MEM_mem_ren                ;



    assign                       snpc                      = pc + 4;
    assign                       npc                       = (IDU_mret_flag ||IDU_ecall_flag ||IDU_jump_flag || IDU_branch_flag)? dnpc:snpc;
    assign                       dnpc                      = (IDU_jump_flag )                                                 ? 
                                                            ((IDU_jump_choice)? IDU_rs1_value + IDU_imm                       :
                                                            (IDU_pc + IDU_imm)):(IDU_branch_flag == 1'b1 && EXU_result != 32'd0)?
                                                            pc+IDU_imm:(IDU_mret_flag)                                        ?
                                                            IDU_mepc_out:(IDU_ecall_flag)                                         ?
                                                            IDU_mtvec_out:pc+4;

    assign                       pc                        = IFU_pc;

    always @(*)begin
        if(IFU_inst == 32'h00100073) begin
            if(IDU_a0_value == 0)
                $display("\033[32;42m Hit The Good TRAP \033[0m");
            else
                $display("\033[31;41m Hit The Bad TRAP \033[0m");
            fi();
        end
    end





task  GetInst;
    output                       bit[31:0]inst_exec         ;
    inst_exec = IFU_inst;
endtask

    export "DPI-C" task GetInst;



IFU IFU_Inst0(
    .clk                         (clk                       ),
    .rst_n                       (rst_n                     ),
    .npc                         (npc                       ),
    .pc                          (IFU_pc                    ),
    .inst                        (IFU_inst                  ) 
);

IDU IDU_Inst0(
    .clk                         (clk                       ),
    .rst_n                       (rst_n                     ),

    .inst                        (IFU_inst                  ),
    .pc                          (IFU_pc                    ),
    .rd_value                    (WBU_rd_value              ),
    .csrd                        (WBU_csrd                  ),
    .rd                          (WBU_rd                    ),
    .R_wen                       (WBU_R_wen                 ),
    .csr_wen                     (WBU_csr_wen               ),

    .pc_next                     (IDU_pc                    ),
    .rd_next                     (IDU_rd                    ),
    .imm                         (IDU_imm                   ),
    .funct3                      (IDU_funct3                ),
    .mret_flag                   (IDU_mret_flag             ),
    .ecall_flag                  (IDU_ecall_flag            ),

    .rs1_value                   (IDU_rs1_value             ),
    .rs2_value                   (IDU_rs2_value             ),
    .csr_wen_next                (IDU_csr_wen               ),
    .R_wen_next                  (IDU_R_wen                 ),
    .csrs                        (IDU_csrs                  ),

    .mem_wen                     (IDU_mem_wen               ),
    .mem_ren                     (IDU_mem_ren               ),
    .add1_choice                 (IDU_add1_choice           ),
    .add2_choice                 (IDU_add2_choice           ),
    .inv_flag                    (IDU_inv_flag              ),
    .branch_flag                 (IDU_branch_flag           ),
    .jump_flag                   (IDU_jump_flag             ),
    .jump_choice                 (IDU_jump_choice           ),
    .imm_opcode                  (IDU_imm_opcode            ),
    .alu_opcode                  (IDU_alu_opcode            ),

    .a0_value                    (IDU_a0_value              ),
    .mepc_out                    (IDU_mepc_out              ),
    .mtvec_out                   (IDU_mtvec_out             ) 

);

EXU EXU_Inst0(
    .clk                         (clk                       ),
    .rst_n                       (rst_n                     ),

    .funct3                      (IDU_funct3                ),
    .pc                          (IDU_pc                    ),
    .csr_wen                     (IDU_csr_wen               ),
    .R_wen                       (IDU_R_wen                 ),
    .mem_wen                     (IDU_mem_wen               ),
    .mem_ren                     (IDU_mem_ren               ),
    .rd                          (IDU_rd                    ),
    .imm                         (IDU_imm                   ),
    .imm_opcode                  (IDU_imm_opcode            ),
    .alu_opcode                  (IDU_alu_opcode            ),
    .inv_flag                    (IDU_inv_flag              ),
    .jump_flag                   (IDU_jump_flag             ),

    .add1_choice                 (IDU_add1_choice           ),
    .add2_choice                 (IDU_add2_choice           ),
    .rs1_value                   (IDU_rs1_value             ),
    .rs2_value                   (IDU_rs2_value             ),
    .csrs                        (IDU_csrs                  ),

    .jump_flag_next              (EXU_jump_flag             ),
    .funct3_next                 (EXU_funct3                ),
    .rs2_value_next              (EXU_rs2_value             ),
    .rd_next                     (EXU_rd                    ),
    .csrs_next                   (EXU_csrs                  ),
    .csr_wen_next                (EXU_csr_wen               ),
    .R_wen_next                  (EXU_R_wen                 ),
    .mem_wen_next                (EXU_mem_wen               ),
    .mem_ren_next                (EXU_mem_ren               ),
    .pc_next                     (EXU_pc                    ),
    .EX_result                   (EXU_result                 ) 
);

MEM MEM_Inst0(
    .clk                         (clk                       ),
    .rst_n                       (rst_n                     ),

    .pc                          (EXU_pc                    ),
    .mem_ren                     (EXU_mem_ren               ),
    .mem_wen                     (EXU_mem_wen               ),
    .R_wen                       (EXU_R_wen                 ),
    .csr_wen                     (EXU_csr_wen               ),
    .Ex_result                   (EXU_result                 ),
    .csrs                        (EXU_csrs                  ),
    .rd                          (EXU_rd                    ),
    .funct3                      (EXU_funct3                ),
    .rs2_value                   (EXU_rs2_value             ),
    .jump_flag                   (EXU_jump_flag             ),

    .jump_flag_next              (MEM_jump_flag             ),
    .R_wen_next                  (MEM_R_wen                 ),
    .MEM_Rdata                   (MEM_Rdata                 ),
    .csr_wen_next                (MEM_csr_wen               ),
    .Ex_result_next              (MEM_Ex_result             ),
    .csrs_next                   (MEM_csrs                  ),
    .pc_next                     (MEM_pc                    ),
    .rd_next                     (MEM_rd                    ),
    .mem_ren_next                (MEM_mem_ren               ) 
);

WBU WBU_inst0(
    .clk                         (clk                       ),
    .rst_n                       (rst_n                     ),

    .MEM_Rdata                   (MEM_Rdata                 ),
    .Ex_result                   (MEM_Ex_result             ),
    .csrs                        (MEM_csrs                  ),
    .pc                          (MEM_pc                    ),
    .rd                          (MEM_rd                    ),
    .csr_wen                     (MEM_csr_wen               ),
    .R_wen                       (MEM_R_wen                 ),
    .mem_ren                     (MEM_mem_ren               ),
    .jump_flag                   (MEM_jump_flag             ),

    .R_wen_next                  (WBU_R_wen                 ),
    .csr_wen_next                (WBU_csr_wen               ),
    .csrd                        (WBU_csrd                  ),
    .rd_value                    (WBU_rd_value              ),
    .rd_next                     (WBU_rd                    ) 

);



endmodule

