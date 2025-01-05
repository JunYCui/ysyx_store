import "DPI-C" function void fi(int val);


module cpu_ysyx_24100029
(
    input                        clk                        ,
    input                        rst_n                      ,
    output reg         [  31: 0] pc                         ,
    output             [  31: 0] snpc                       ,
    output             [  31: 0] dnpc                       ,
    output             [  31: 0] IFU_pc                     ,
    output             [  31: 0] LSU_pc                     ,
    output                       WBU_valid                   
);


 //   wire               [  31: 0] IFU_pc                     ;
    wire               [  31: 0] IFU_inst                   ;
    wire                         IFU_valid                  ;
    wire                         IFU_rvalid                 ;
    wire               [  31: 0] IFU_rdata                  ;
    wire                         IFU_req                    ;

/************************* IDU ********************/
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
    wire               [   1: 0] IDU_imm_opcode             ;
    wire               [   3: 0] IDU_alu_opcode             ;

    wire               [   4: 0] IDU_rs1                    ;
    wire               [   4: 0] IDU_rs2                    ;
    wire               [  31: 0] IDU_a0_value               ;
    wire               [  31: 0] IDU_mepc_out               ;
    wire               [  31: 0] IDU_mtvec_out              ;

    wire                         IDU_valid                  ;
    wire                         IDU_ready                  ;
    wire               [  31: 0] IDU_inst                   ;//debug
/************************* EXU ********************/
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
    wire               [  31: 0] EXU_Ex_result              ;
    wire                         EXU_branch_flag            ;
    wire               [  31: 0] EXU_rs1_in                 ;
    wire               [  31: 0] EXU_rs2_in                 ;
    wire               [  31: 0] EXU_imm                    ;

    wire                         EXU_valid                  ;
    wire                         EXU_ready                  ;
    wire               [  31: 0] EXU_inst                   ;
/************************* LSU ********************/
    wire                         LSU_jump_flag              ;
    wire                         LSU_R_wen                  ;
    wire               [  31: 0] LSU_Rdata                  ;
    wire               [   3: 0] LSU_csr_wen                ;
    wire               [  31: 0] LSU_Ex_result              ;
    wire               [  31: 0] LSU_csrs                   ;
//    wire               [  31: 0] MEM_pc                     ;
    wire               [   4: 0] LSU_rd                     ;
    wire                         LSU_mem_ren                ;

    wire               [  31: 0] LSU_araddr                 ;
    wire                         LSU_arvalid                ;
    wire                         LSU_rready                 ;
    wire               [  31: 0] LSU_rdata                  ;
    wire                         LSU_rvalid                 ;
    wire               [  31: 0] LSU_awaddr                 ;
    wire                         LSU_awvalid                ;
    wire               [  31: 0] LSU_mem_wdata              ;
    wire               [   7: 0] LSU_wmask                  ;
    wire                         LSU_wvalid                 ;
    wire                         LSU_bresp                  ;
    wire                         LSU_bvalid                 ;
    wire                         LSU_bready                 ;
    wire                         LSU_req                    ;


    wire                         LSU_valid                  ;
    wire                         LSU_ready                  ;
    wire               [  31: 0] LSU_inst                   ;
/************************* WBU ********************/
    wire               [  31: 0] WBU_pc                     ;
    wire               [  31: 0] WBU_inst                   ;
    wire               [  31: 0] WBU_rd_value               ;
    wire               [  31: 0] WBU_csrd                   ;
    wire               [   4: 0] WBU_rd                     ;
    wire                         WBU_R_wen                  ;
    wire               [   3: 0] WBU_csr_wen                ;
    wire                         WBU_ready                  ;
 //   wire                         WBU_valid                  ;

 /************************* SRAM ********************/

    wire               [  31: 0] araddr                     ;
    wire                         arvalid                    ;
    wire                         arready                    ;

    wire                         rready                     ;
    wire               [  31: 0] rdata                      ;
    wire                         rresp                      ;
    wire                         rvalid                     ;
    
    wire               [  31: 0] awaddr                     ;
    wire                         awvalid                    ;
    wire                         awready                    ;
    
    wire               [  31: 0] wdata                      ;
    wire               [   7: 0] wstrb                      ;
    wire                         wvalid                     ;
    wire                         wready                     ;
    
    wire                         bresp                      ;
    wire                         bvalid                     ;
    wire                         bready                     ;


/*            PERSONAL              */

    wire                         dnpc_flag                  ;
    wire                         IDU_pipe_s                 ;
    wire                         IFU_pipe_s                 ;
    wire                         IDU_inst_clear             ;
    wire                         EXU_inst_clear             ;

    assign                       pc                        = WBU_pc;
    assign                       snpc                      = pc + 4;

    always @(*)begin
        if(WBU_inst == 32'h00100073) begin
            if(IDU_a0_value == 0)begin
                $display("\033[32;42m Hit The Good TRAP \033[0m");
                fi(0);
            end
            else begin
                $display("\033[31;41m Hit The Bad TRAP \033[0m");
                fi(1);
            end
        end
    end





task  GetInst;
    output                       bit[31:0]inst_exec         ;
    inst_exec = WBU_inst;
endtask

export "DPI-C" task GetInst;

Control Control_inst0(
    .mtvec_out                   (IDU_mtvec_out             ),
    .mepc_out                    (IDU_mepc_out              ),

    .EXU_imm                     (EXU_imm                   ),
    .EXU_pc                      (EXU_pc                    ),
    .Ex_result                   (EXU_Ex_result             ),
    .MEM_Ex_result               (LSU_Ex_result             ),
    .WBU_rd_value                (WBU_rd_value              ),
    .IDU_rs1_value               (IDU_rs1_value             ),
    .IDU_rs2_value               (IDU_rs2_value             ),
    .MEM_Rdata                   (LSU_Rdata                 ),

    .branch_flag                 (EXU_branch_flag           ),
    .jump_flag                   (EXU_jump_flag             ),
    .mret_flag                   (IDU_mret_flag             ),
    .ecall_flag                  (IDU_ecall_flag            ),
    .EXU_mem_ren                 (EXU_mem_ren               ),
    .MEM_mem_ren                 (LSU_mem_ren               ),

    .IDU_rs1                     (IDU_rs1                   ),
    .IDU_rs2                     (IDU_rs2                   ),

    .IDU_valid                   (IDU_valid                 ),
    .EXU_valid                   (EXU_valid                 ),
    .MEM_valid                   (LSU_valid                 ),
    .WBU_valid                   (WBU_valid                 ),

    .EXU_rd                      (EXU_rd                    ),
    .WBU_rd                      (WBU_rd                    ),
    .MEM_rd                      (LSU_rd                    ),

    .EXU_R_Wen                   (EXU_R_wen                 ),
    .WBU_R_Wen                   (WBU_R_wen                 ),
    .MEM_R_Wen                   (LSU_R_wen                 ),

    .EXU_rs1_in                  (EXU_rs1_in                ),
    .EXU_rs2_in                  (EXU_rs2_in                ),
    .IFU_pipe_s                  (IFU_pipe_s                ),
    .IDU_pipe_s                  (IDU_pipe_s                ),
    .IDU_inst_clear              (IDU_inst_clear            ),
    .EXU_inst_clear              (EXU_inst_clear            ),
    .dnpc                        (dnpc                      ),
    .dnpc_flag                   (dnpc_flag                 ) 
);






IFU IFU_Inst0(
    .clk                         (clk                       ),
    .rst_n                       (rst_n                     ),
    .dnpc                        (dnpc                      ),
    .dnpc_flag                   (dnpc_flag                 ),
    .pipe_stop                   (IFU_pipe_s                ),
    .pc                          (IFU_pc                    ),
    .inst                        (IFU_inst                  ),

    .rvalid                      (IFU_rvalid                ),
    .rdata                       (IFU_rdata                 ),
    .req                         (IFU_req                   ),

    .ready                       (IDU_ready                 ),
    .valid                       (IFU_valid                 ) 
);

IDU IDU_Inst0(
    .clk                         (clk                       ),
    .rst_n                       (rst_n                     ),

    .inst_clear                  (IDU_inst_clear            ),
    .pipe_stop                   (IDU_pipe_s                ),

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
    .imm_opcode                  (IDU_imm_opcode            ),
    .alu_opcode                  (IDU_alu_opcode            ),

    .inst_next                   (IDU_inst                  ),
    .rs1                         (IDU_rs1                   ),
    .rs2                         (IDU_rs2                   ),
    .a0_value                    (IDU_a0_value              ),
    .mepc_out                    (IDU_mepc_out              ),
    .mtvec_out                   (IDU_mtvec_out             ),

    .valid_last                  (IFU_valid                 ),
    .ready_last                  (IDU_ready                 ),

    .ready_next                  (EXU_ready                 ),
    .valid_next                  (IDU_valid                 ) 

);

EXU EXU_Inst0(
    .clk                         (clk                       ),
    .rst_n                       (rst_n                     ),

    .inst_clear                  (EXU_inst_clear            ),

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
    .branch_flag                 (IDU_branch_flag           ),

    .add1_choice                 (IDU_add1_choice           ),
    .add2_choice                 (IDU_add2_choice           ),
    .rs1_value                   (EXU_rs1_in                ),
    .rs2_value                   (EXU_rs2_in                ),
    .csrs                        (IDU_csrs                  ),

    .imm_next                    (EXU_imm                   ),
    .branch_flag_next            (EXU_branch_flag           ),
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
    .EX_result                   (EXU_Ex_result             ),

    .valid_last                  (IDU_valid                 ),
    .ready_last                  (EXU_ready                 ),

    .ready_next                  (LSU_ready                 ),
    .valid_next                  (EXU_valid                 ),


    .inst                        (IDU_inst                  ),
    .inst_next                   (EXU_inst                  ) 
);

LSU LSU_Inst0(
    .clk                         (clk                       ),
    .rst_n                       (rst_n                     ),

    .pc                          (EXU_pc                    ),
    .mem_ren                     (EXU_mem_ren               ),
    .mem_wen                     (EXU_mem_wen               ),
    .R_wen                       (EXU_R_wen                 ),
    .csr_wen                     (EXU_csr_wen               ),
    .Ex_result                   (EXU_Ex_result             ),
    .csrs                        (EXU_csrs                  ),
    .rd                          (EXU_rd                    ),
    .funct3                      (EXU_funct3                ),
    .rs2_value                   (EXU_rs2_value             ),
    .jump_flag                   (EXU_jump_flag             ),

    .R_wen_next                  (LSU_R_wen                 ),
    .MEM_Rdata                   (LSU_Rdata                 ),
    .csr_wen_next                (LSU_csr_wen               ),
    .Ex_result_next              (LSU_Ex_result             ),
    .csrs_next                   (LSU_csrs                  ),
    .pc_next                     (LSU_pc                    ),
    .rd_next                     (LSU_rd                    ),
    .mem_ren_next                (LSU_mem_ren               ),
    .jump_flag_next              (LSU_jump_flag             ),

    .araddr                      (LSU_araddr                ),
    .arvalid                     (LSU_arvalid               ),

    .rready                      (LSU_rready                ),
    .rdata                       (LSU_rdata                 ),
    .rvalid                      (LSU_rvalid                ),

    .awaddr                      (LSU_awaddr                ),
    .awvalid                     (LSU_awvalid               ),

    .mem_wdata                   (LSU_mem_wdata             ),
    .wmask                       (LSU_wmask                 ),
    .wvalid                      (LSU_wvalid                ),

    .bresp                       (LSU_bresp                 ),
    .bvalid                      (LSU_bvalid                ),
    .bready                      (LSU_bready                ),

    .req                         (LSU_req                   ),

    .valid_last                  (EXU_valid                 ),
    .ready_last                  (LSU_ready                 ),

    .ready_next                  (WBU_ready                 ),
    .valid_next                  (LSU_valid                 ),

    .inst                        (EXU_inst                  ),
    .inst_next                   (LSU_inst                  ) 
);

WBU WBU_inst0(
    .clk                         (clk                       ),
    .rst_n                       (rst_n                     ),

    .MEM_Rdata                   (LSU_Rdata                 ),
    .Ex_result                   (LSU_Ex_result             ),
    .csrs                        (LSU_csrs                  ),
    .pc                          (LSU_pc                    ),
    .rd                          (LSU_rd                    ),
    .csr_wen                     (LSU_csr_wen               ),
    .R_wen                       (LSU_R_wen                 ),
    .mem_ren                     (LSU_mem_ren               ),
    .jump_flag                   (LSU_jump_flag             ),
    .inst                        (LSU_inst                  ),

    .pc_next                     (WBU_pc                    ),
    .R_wen_next                  (WBU_R_wen                 ),
    .csr_wen_next                (WBU_csr_wen               ),
    .csrd                        (WBU_csrd                  ),
    .rd_value                    (WBU_rd_value              ),
    .inst_next                   (WBU_inst                  ),

    .valid                       (LSU_valid                 ),
    .ready                       (WBU_ready                 ),

    .rd_next                     (WBU_rd                    ),
    .valid_next                  (WBU_valid                 ) 
);
/* verilator lint_off PINMISSING */
Aribiter #(
    .DATA_WIDTH                  (32                        ),
    .ADDR_WIDTH                  (32                        ) 
)Aribiter_inst(
    .clk                         (clk                       ),
    .rst_n                       (rst_n                     ),

    .IFU_req                     (IFU_req                   ),
    .LSU_req                     (LSU_req                   ),

    .IFU_araddr                  (IFU_pc                    ),
    .IFU_arvalid                 (1'b1                      ),

    .IFU_rready                  (1'b1                      ),
    .IFU_rdata                   (IFU_rdata                 ),
    .IFU_rvalid                  (IFU_rvalid                ),

    .IFU_awaddr                  (0                         ),
    .IFU_awvalid                 (0                         ),


    .IFU_wdata                   (0                         ),
    .IFU_wstrb                   (0                         ),
    .IFU_wvalid                  (0                         ),

    .IFU_bready                  (0                         ),

    .LSU_araddr                  (LSU_araddr                ),
    .LSU_arvalid                 (LSU_arvalid               ),

    .LSU_rready                  (LSU_rready                ),
    .LSU_rdata                   (LSU_rdata                 ),
    .LSU_rvalid                  (LSU_rvalid                ),

    .LSU_awaddr                  (LSU_awaddr                ),
    .LSU_awvalid                 (LSU_awvalid               ),

    .LSU_wdata                   (LSU_mem_wdata             ),
    .LSU_wstrb                   (LSU_wmask                 ),
    .LSU_wvalid                  (LSU_wvalid                ),

    .LSU_bresp                   (LSU_bresp                 ),
    .LSU_bvalid                  (LSU_bvalid                ),
    .LSU_bready                  (LSU_bready                ),

    .araddr                      (araddr                    ),
    .arvalid                     (arvalid                   ),
    .arready                     (arready                   ),

    .rready                      (rready                    ),
    .rdata                       (rdata                     ),
    .rresp                       (rresp                     ),
    .rvalid                      (rvalid                    ),

    .awaddr                      (awaddr                    ),
    .awvalid                     (awvalid                   ),
    .awready                     (awready                   ),

    .wdata                       (wdata                     ),
    .wstrb                       (wstrb                     ),
    .wvalid                      (wvalid                    ),
    .wready                      (wready                    ),

    .bresp                       (bresp                     ),
    .bvalid                      (bvalid                    ),
    .bready                      (bready                    ) 



);
SRAM
#(
    .DATA_WIDTH                  (32                        ),
    .ADDR_WIDTH                  (32                        ) 
)SRAM_inst0
(
    .araddr                      (araddr                    ),
    .arvalid                     (arvalid                   ),
    .arready                     (arready                   ),

    .rready                      (rready                    ),
    .rdata                       (rdata                     ),
    .rresp                       (rresp                     ),
    .rvalid                      (rvalid                    ),
    
    .awaddr                      (awaddr                    ),
    .awvalid                     (awvalid                   ),
    .awready                     (awready                   ),
    
    .wdata                       (wdata                     ),
    .wstrb                       (wstrb                     ),
    .wvalid                      (wvalid                    ),
    .wready                      (wready                    ),
    
    .bresp                       (bresp                     ),
    .bvalid                      (bvalid                    ),
    .bready                      (bready                    ) 
);


endmodule

