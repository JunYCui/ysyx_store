import "DPI-C" function void fi();


module cpu_ysyx_24100029
(
    input                        clk                        ,
    input                        rst_n                      ,
    output reg         [  31: 0] pc                         ,
    output             [  31: 0] snpc                       ,
    output             [  31: 0] dnpc                        
);




    wire               [   4: 0] rs1                        ;
    wire               [   4: 0] rs2                        ;
    wire               [   4: 0] rd                         ;

    wire               [  31: 0] imm                        ;
    wire               [   2: 0] funct3                     ;
    wire               [   6: 0] opcode                     ;
    wire               [   6: 0] oprand                     ;


    wire               [  31: 0] rs1_value                  ;
    wire               [  31: 0] rs2_value                  ;
    wire               [  31: 0] a0_value                   ;
    wire               [  31: 0] rd_value                   ;

    wire               [  31: 0] npc                        ;
    wire               [  31: 0] EX_result                  ;

    wire               [  31: 0] inst                       ;
    wire                         Data_mem_valid             ;
    reg                          valid                      ;

    wire               [  31: 0] mem_wdata                  ;
    wire               [  31: 0] mem_rdata                  ;

    wire               [   3: 0] alu_opcode                 ;
    wire               [   1: 0] imm_opcode                 ;
    wire               [   3: 0] csr_wen                    ;


    wire                         R_wen                      ;
    wire                         mem_wen                    ;
    wire                         mem_ren                    ;
    wire                         jump_flag                  ;
    wire                         comp_flag                  ;
    wire               [   1: 0] rs1_flag                   ;
    wire               [   1: 0] rs2_flag                   ;
    wire                         inv_flag                   ;
    wire                         branch_flag                ;

    wire               [  31: 0] csr_value                  ;
    wire               [  31: 0] mepc_out                   ;
    wire               [  31: 0] mcause_out                 ;
    wire               [  31: 0] mstatus_out                ;
    wire               [  31: 0] mtvec_out                  ;

    wire               [  31: 0] mepc_in                    ;
    wire               [  31: 0] mcause_in                  ;
    wire               [  31: 0] mstatus_in                 ;
    wire               [  31: 0] mtvec_in                   ;
    wire                         ecall_flag                 ;
    wire                         mret_flag                  ;

    assign                       snpc                      = pc + 4;
    assign                       npc                       = (mret_flag) ?   mepc_out:
                                                             (ecall_flag)?  mtvec_out:
                                                             (jump_flag == 1'd1 || branch_flag == 1'd1)? dnpc:snpc;
    assign                       rd_value                  = (jump_flag == 1'd1)? pc+4 : (mem_ren == 1'b1)?  mem_rdata:(opcode == `M_opcode_ysyx_24100029)? csr_value:EX_result;
    assign                       dnpc                      = (jump_flag == 1'd1)? EX_result: (branch_flag == 1'b1 && EX_result != 32'd0)?  pc+({{20{imm[11]}},imm[11:0]}<<1) :pc+4;
    assign                       mem_wdata                 = rs2_value;
    assign                       Data_mem_valid            = mem_ren|mem_wen;
    assign                       csr_value                 = (opcode == `M_opcode_ysyx_24100029 && imm == 32'h341)? mepc_out   :
                                                             (opcode == `M_opcode_ysyx_24100029 && imm == 32'h342)? mcause_out :
                                                             (opcode == `M_opcode_ysyx_24100029 && imm == 32'h300)? mstatus_out:
                                                             (opcode == `M_opcode_ysyx_24100029 && imm == 32'h305)? mtvec_out:32'd0;
    assign                       ecall_flag                = (inst == 32'b00000000000000000000000001110011);//ecall
    assign                       mret_flag                 = (inst == 32'b00110000001000000000000001110011);// mret
    assign                       mcause_in                 = (ecall_flag)? 32'd11:EX_result;// 11 means trigger environment from machine
    assign                       mepc_in                   = (ecall_flag)? snpc:EX_result;// save the trigger pc
    assign                       mstatus_in                = EX_result;
    assign                       mtvec_in                  = EX_result;



    always @(posedge clk) begin
        if(!rst_n)
            begin
                pc <= 32'h80000000;
                valid <= 1'b1;
            end
        else
            begin
                pc <= npc;
                valid <= valid;
            end
    end

    always @(*)begin
        if(inst == 32'h00100073)begin
            if(a0_value == 0)
                $display("\033[32;42m Hit The Good TRAP \033[0m");
            else
                $display("\033[31;41m Hit The Bad TRAP \033[0m");
            fi();
        end
    end





task  GetInst;
    output                       bit[31:0]inst_exec         ;
    inst_exec = inst;
endtask

    export "DPI-C" task GetInst;

Reg #(
    .WIDTH                       (32                        ),
    .RESET_VAL                   (0                         ) 
) CSR_MEPC(
    .clk                         (clk                       ),
    .rst                         (rst_n                     ),
    .din                         (mepc_in                   ),
    .dout                        (mepc_out                  ),
    .wen                         (csr_wen[0]                ) 
);

Reg #(
    .WIDTH                       (32                        ),
    .RESET_VAL                   (0                         ) 
) CSR_MCAUSE(
    .clk                         (clk                       ),
    .rst                         (rst_n                     ),
    .din                         (mcause_in                 ),
    .dout                        (mcause_out                ),
    .wen                         (csr_wen[1]                ) 
);

Reg #(
    .WIDTH                       (32                        ),
    .RESET_VAL                   (32'h1800                  ) 
) CSR_MSTATUS(
    .clk                         (clk                       ),
    .rst                         (rst_n                     ),
    .din                         (mstatus_in                ),
    .dout                        (mstatus_out               ),
    .wen                         (csr_wen[2]                ) 
);

Reg #(
    .WIDTH                       (32                        ),
    .RESET_VAL                   (0                         ) 
) CSR_MTVEC(
    .clk                         (clk                       ),
    .rst                         (rst_n                     ),
    .din                         (mtvec_in                  ),
    .dout                        (mtvec_out                 ),
    .wen                         (csr_wen[3]                ) 
);



IFU IFU_inst0(
    .pc                          (pc                        ),
    .valid                       (valid                     ),
    .inst                        (inst                      ) 
);


EXU EXU_inst0
(
    .clk                         (clk                       ),
    .rst                         (rst_n                     ),
    .pc                          (pc                        ),

    .imm                         (imm                       ),
    .imm_opcode                  (imm_opcode                ),
    .alu_opcode                  (alu_opcode                ),
    .comp_flag                   (comp_flag                 ),
    .rs1_flag                    (rs1_flag                  ),
    .rs2_flag                    (rs2_flag                  ),
    .inv_flag                    (inv_flag                  ),

    .rs1_value                   (rs1_value                 ),
    .rs2_value                   (rs2_value                 ),
    .csr_value                   (csr_value                 ),

    .EX_result                   (EX_result                 ) 
);


Reg_Stack Reg_Stack_inst0(
    .rst                         (rst_n                     ),
    .clk                         (clk                       ),
    .rs1                         (rs1                       ),
    .rs2                         (rs2                       ),
    .rd                          (rd                        ),
    .rd_value                    (rd_value                  ),
    .R_wen                       (R_wen                     ),

    .rs1_value                   (rs1_value                 ),
    .rs2_value                   (rs2_value                 ),
    .a0_value                    (a0_value                  ) 
);


IDU IDU_inst0(
    .inst                        (inst                      ),
    
    .rs1                         (rs1                       ),
    .rs2                         (rs2                       ),
    .rd                          (rd                        ),
    .imm                         (imm                       ),
    .funct3                      (funct3                    ),
    .opcode                      (opcode                    ),
    .oprand                      (oprand                    ) 
);

MEM Data_MEM_inst(
    .valid                       (Data_mem_valid            ),
    .raddr                       (EX_result                 ),
    .wdata                       (mem_wdata                 ),
    .funct3                      (funct3                    ),
    .waddr                       (EX_result                 ),
    .wen                         (mem_wen                   ),
    .rd_data                     (mem_rdata                 ) 
);

Control Control_inst(
    .opcode                      (opcode                    ),
    .funct3                      (funct3                    ),
    .oprand                      (oprand                    ),
    .imm                         (imm                       ),
    .ecall_flag                  (ecall_flag                ),

    .R_wen                       (R_wen                     ),
    .csr_wen                     (csr_wen                   ),
    .mem_wen                     (mem_wen                   ),
    .mem_ren                     (mem_ren                   ),
    .jump_flag                   (jump_flag                 ),
    .branch_flag                 (branch_flag               ),

    .alu_opcode                  (alu_opcode                ),
    .imm_opcode                  (imm_opcode                ),
    .rs1_flag                    (rs1_flag                  ),
    .rs2_flag                    (rs2_flag                  ),
    .comp_flag                   (comp_flag                 ),
    .inv_flag                    (inv_flag                  ) 
);



endmodule

