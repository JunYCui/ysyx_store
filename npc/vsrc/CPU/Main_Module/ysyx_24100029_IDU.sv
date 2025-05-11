`include "../define/para.v"
`include "../define/interface.sv"
`include "../define/struct.sv"
module ysyx_24100029_IDU (
    input clock,
    input reset,

    input  logic slave_valid,
    output logic slave_ready,

    input logic [31:0] inst,
    input logic [31:0] pc,
    input logic        pred_res,
    input logic        inst_kill,

    output logic [31:0] br_npc,
    output logic [31:0] br_pc,
    output logic [1:0] br_type,
    output logic br_commit,
    output logic br_error,


    output logic master_valid,
    input  logic master_ready,
    output rv_decode_pkt_t dec_pkt

);

  logic   [ 4:0] rs1;
  logic   [ 4:0] rs2;
  logic   [ 4:0] rd;
  logic   [ 3:0] alu_op;
  rv_op_e        inst_op;
  logic   [ 2:0] funct3;
  logic   [ 6:0] oprand;

  logic   [ 6:0] opcode;

  logic   [31:0] imm_I;
  logic   [31:0] imm_U;
  logic   [31:0] imm_R;
  logic   [31:0] imm_S;
  logic   [31:0] imm_B;
  logic   [31:0] imm_J;
  logic   [31:0] imm;

  logic          ecall_flag;
  logic          mret_flag;
  logic          fence_i_flag;
  assign slave_ready = master_ready;

  always @(posedge clock) begin
    if (reset | inst_kill) master_valid <= 0;
    else master_valid <= slave_valid;
  end

  always @(posedge clock) begin
    if (reset | inst_kill) begin
      dec_pkt.imm <= 0;
      dec_pkt.pc <= 0;
      dec_pkt.rs1 <= 0;
      dec_pkt.rs2 <= 0;
      dec_pkt.rd <= 0;
      dec_pkt.alu_op <= 0;
      dec_pkt.inst_op <= OP_NONE;
      dec_pkt.funct3 <= 0;
      dec_pkt.ecall_flag <= 0;
      dec_pkt.mret_flag <= 0;
      dec_pkt.fence_i_flag <= 0;
      dec_pkt.pred_res <= 0;
    end else if (slave_ready & slave_valid) begin
      dec_pkt.imm <= imm;
      dec_pkt.pc <= pc;
      dec_pkt.rs1 <= rs1;
      dec_pkt.rs2 <= rs2;
      dec_pkt.rd <= rd;
      dec_pkt.alu_op <= alu_op;
      dec_pkt.inst_op <= inst_op;
      dec_pkt.funct3 <= funct3;
      dec_pkt.ecall_flag <= ecall_flag;
      dec_pkt.mret_flag <= mret_flag;
      dec_pkt.fence_i_flag <= fence_i_flag;
      dec_pkt.pred_res <= pred_res;
    end
  end


  assign oprand = inst[31:25];
  assign opcode = inst[6:0];
  assign rs1 = inst[19:15];
  assign rs2 = inst[24:20];
  assign funct3 = inst[14:12];
  assign rd = inst[11:7];

  assign ecall_flag = (inst == 32'b00000000000000000000000001110011);  //ecall
  assign mret_flag = (inst == 32'b00110000001000000000000001110011);  // mret
  assign fence_i_flag = (inst == 32'b00000000000000000001000000001111);

  assign br_commit = (opcode == `J_opcode_ysyx_24100029);
  assign br_pc = pc;
  assign br_npc = pc + imm;
  assign br_type = BR_TYPE_JAL;
  assign br_error = br_commit & ~pred_res; 


  assign alu_op =     (opcode == `I_opcode_ysyx_24100029 && funct3 == 3'b010)     ||
           (opcode == `R_opcode_ysyx_24100029 && funct3 == 3'b010)                                                     ||
           (opcode == `B_opcode_ysyx_24100029 && (funct3 == 3'b101 || funct3 == 3'b100))                               ?
           `alu_signed_comparator_ysyx_24100029:
           (opcode == `B_opcode_ysyx_24100029 && (funct3 == 3'b110 || funct3 == 3'b111))                               ||
           (opcode == `I_opcode_ysyx_24100029 && (funct3 == 3'b011))                                                  ||
           (opcode == `R_opcode_ysyx_24100029 && (funct3 ==  3'b011))                                                  ?
           `alu_unsigned_comparator_ysyx_24100029:
           (opcode == `I_opcode_ysyx_24100029 && funct3 == 3'b100 )                                                   ||
           (opcode == `R_opcode_ysyx_24100029 && funct3 == 3'b100 )                                                    ?
           `alu_xor_ysyx_24100029 :(opcode == `I_opcode_ysyx_24100029 && funct3 == 3'b110 )                           ||
           (opcode == `R_opcode_ysyx_24100029 && funct3 == 3'b110 )                                                    ||
           (opcode == `M_opcode_ysyx_24100029 && funct3 == 3'b010 )                                                    ?
           `alu_or_ysyx_24100029  : (opcode == `I_opcode_ysyx_24100029 && funct3 == 3'b111 )                          ||
           (opcode == `R_opcode_ysyx_24100029 && funct3 == 3'b111 )                                                    ?
           `alu_and_ysyx_24100029 :(opcode == `I_opcode_ysyx_24100029 && funct3 == 3'b001  )                          ||
           (opcode == `R_opcode_ysyx_24100029 && funct3 == 3'b001 )                                                    ?
           `alu_sll_ysyx_24100029 :(opcode == `I_opcode_ysyx_24100029 && funct3 == 3'b101 && oprand == 7'b0000000)    ||
           (opcode == `R_opcode_ysyx_24100029 && funct3 == 3'b101 && oprand == 7'b0000000)                             ?
           `alu_srl_ysyx_24100029 :(opcode == `I_opcode_ysyx_24100029 && funct3 == 3'b101 && oprand == 7'b0100000)    ||
           (opcode == `R_opcode_ysyx_24100029 && funct3 == 3'b101 && oprand == 7'b0100000)                             ?
           `alu_sra_ysyx_24100029 : (opcode == `R_opcode_ysyx_24100029 && funct3 == 3'b000 && oprand == 7'b0100000)    ?
           `alu_sub_ysyx_24100029 : (opcode == `B_opcode_ysyx_24100029 && funct3[2:1] == 2'b00)                     ?
           `alu_equal_ysyx_24100029: (opcode == `R_opcode_ysyx_24100029 && oprand == 7'b0000001 && ~funct3[2])?
           `alu_mul_ysyx_24100029:(opcode == `R_opcode_ysyx_24100029 && oprand == 7'b0000001 && funct3[2])?
           `alu_div_ysyx_24100029:`alu_add_ysyx_24100029;


  assign inst_op = (opcode == `R_opcode_ysyx_24100029)? OP_REG:
           (opcode == `LOAD_opcode_ysyx_24100029)? OP_LOAD:
           (opcode == `I_opcode_ysyx_24100029)? OP_IMM:
           (opcode == `JALR_opcode_ysyx_24100029)? OP_JALR:
           (opcode == `S_opcode_ysyx_24100029)? OP_STORE:
           (opcode == `B_opcode_ysyx_24100029)? OP_BRANCH:
           (opcode == `LUI_opcode_ysyx_24100029)? OP_LUI:
           (opcode == `M_opcode_ysyx_24100029)? OP_CSR:
           (opcode == `J_opcode_ysyx_24100029)? OP_JAL:
           (opcode == `AUIPC_opcode_ysyx_24100029)? OP_AUIPC:OP_NONE;



  assign imm_I = {{20{inst[31]}}, inst[31:20]};
  assign imm_U = {inst[31:12], 12'd0};
  assign imm_R = {25'd0, inst[31:25]};
  assign imm_S = {{20{inst[31]}}, inst[31:25], inst[11:7]};
  assign imm_B = {imm_S[31:11], imm_S[0], imm_S[10:1]} << 1;
  assign imm_J = {{11{inst[31]}}, inst[31], inst[19:12], inst[20], inst[30:21]} << 1;
  /* verilator lint_off IMPLICIT */
  assign imm = (opcode == `I_opcode_ysyx_24100029 || opcode == `LOAD_opcode_ysyx_24100029 || opcode == `JALR_opcode_ysyx_24100029 || opcode == `M_opcode_ysyx_24100029)? imm_I:
           (opcode == `AUIPC_opcode_ysyx_24100029 || opcode == `LUI_opcode_ysyx_24100029)? imm_U:
           (opcode == `J_opcode_ysyx_24100029)? imm_J:
           (opcode == `B_opcode_ysyx_24100029)? imm_B:
           (opcode == `S_opcode_ysyx_24100029)? imm_S:
           (opcode == `R_opcode_ysyx_24100029)? imm_R :
           0;


endmodule

