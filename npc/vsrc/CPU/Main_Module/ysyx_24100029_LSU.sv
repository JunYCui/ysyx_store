/* verilator lint_off UNUSEDSIGNAL */
`include "../define/interface.sv"

`timescale 1ns / 1ps

module ysyx_24100029_LSU (
    input clock,
    input reset,

    input        mem_ren,
    input        mem_wen,
    input        R_wen,
    input [ 3:0] csr_wen,
    input [31:0] Ex_result,
    input [ 4:0] rd,
    input [ 2:0] funct3,
    input [31:0] rs2_value,
    input        jump_flag,
    input [31:0] rd_value,

    output     [31:0] rd_value_next,
    output            R_wen_next,
    output reg [31:0] LSU_Rdata,
    output     [ 3:0] csr_wen_next,
    output     [31:0] Ex_result_next,
    output     [ 4:0] rd_next,
    output            mem_ren_next,
    output            jump_flag_next,

    axi4_if.master lsu_axi,

    output reg req,

`ifdef Performance_Count
    input      [31:0] pc,
    output     [31:0] pc_next,
    output            mem_wflag,
    output reg [31:0] lsu_cycle,
    input      [31:0] inst,
    output reg [31:0] inst_next,
`endif

    input  valid_last,
    output ready_last,

    input  ready_next,
    output valid_next


);
  /*
always @(*) begin
    if(awaddr >= 32'ha0086fc0 && awaddr < 32'ha0086fc8  && mem_wen_reg)
        $display("0x%x[pc]:\t 0x%x is written at addr 0x%x ",pc_reg,wdata,awaddr);
    else if(araddr >= 32'ha0086fc0 && awaddr < 32'ha0086fc8 && mem_ren_reg)
        $display("0x%x[pc]:\t 0x%x is read at addr 0x%x  ",pc_reg,rdata_ex,araddr);
end
*/

  localparam INVALID = 2'b00;
  localparam VALID = 2'b01;
  localparam WORK = 2'b10;


  reg   [ 1:0] LSU_state;
  reg   [31:0] rdata;
  wire  [31:0] rdata_8i;
  wire  [31:0] rdata_16i;
  wire  [31:0] rdata_8u;
  wire  [31:0] rdata_16u;

  // output declaration of module dcache
  logic [31:0] mem_rdata;
  logic        mem_resp;
  logic [31:0] mem_addr;
  logic [ 1:0] mem_opcode;
  logic [31:0] mem_wdata;
  logic [ 3:0] mem_wstrb;
  logic [ 2:0] mem_size;

  logic [31:0] cpu_rdata;
  logic        cpu_resp;
  logic [31:0] cpu_addr;
  logic [ 1:0] cpu_opcode;
  logic [31:0] cpu_wdata;
  logic [ 3:0] cpu_wstrb;
  logic [ 2:0] cpu_size;


  logic [31:0] clint_rdata;
  logic        clint_resp;
  logic [31:0] clint_addr;
  logic [ 1:0] clint_opcode;
  logic [31:0] clint_wdata;
  logic [ 3:0] clint_wstrb;
  logic [ 2:0] clint_size;

  reg   [31:0] rdata_ex;
  reg          mem_ren_reg;
  reg          mem_wen_reg;
  reg          R_wen_reg;
  reg   [ 3:0] csr_wen_reg;
  reg   [31:0] Ex_result_reg;
  reg   [31:0] rd_value_reg;
  reg   [ 4:0] rd_reg;
  reg   [ 2:0] funct3_reg;
  reg   [31:0] rs2_value_reg;
  reg          jump_flag_reg;
  reg          valid_last_reg;

`ifdef Performance_Count
  typedef enum logic {
    IDLE_PER,
    WORK_PER
  } state;
  state        state_p;
  reg   [31:0] pc_reg;
  assign mem_wflag = mem_wen_reg;
  always @(posedge clock or posedge reset) begin
    if (reset) state_p <= IDLE_PER;
    else begin
      case (state_p)
        IDLE_PER: if ((mem_ren | mem_wen) & valid_last & ready_last) state_p <= WORK_PER;
        WORK_PER: if (lsu_axi.rvalid | lsu_axi.bvalid) state_p <= IDLE_PER;
      endcase
    end
  end
  always @(posedge clock or posedge reset) begin
    if (reset) lsu_cycle <= 0;
    else if (state_p == IDLE_PER & (mem_ren | mem_wen) & valid_last & ready_last)
      lsu_cycle <= lsu_cycle + 1;
    else if (state_p == WORK_PER) lsu_cycle <= lsu_cycle + 1;
  end

  always @(posedge clock) begin
    if (reset) begin
      pc_reg    <= 0;
      inst_next <= 0;
    end else if (valid_last & ready_last) begin
      inst_next <= inst;
      pc_reg <= pc;
    end
  end

  assign pc_next = pc_reg;

`endif

  always @(posedge clock) begin
    if (reset) LSU_state <= INVALID;
    else begin
      case (LSU_state)
        INVALID: LSU_state <= valid_last & ready_last ? mem_wen || mem_ren ? WORK : VALID : INVALID;
        VALID: LSU_state <= valid_last & ready_last ? mem_wen || mem_ren ? WORK : VALID : INVALID;
        WORK:
        LSU_state <= (~mem_resp) ? WORK : INVALID ;
        default: LSU_state <= INVALID;
      endcase
    end
  end



  assign ready_last = LSU_state != WORK ;
  assign valid_next = (LSU_state == WORK) & mem_resp || LSU_state == VALID;


  always @(posedge clock) begin
    if (reset) begin
      mem_ren_reg   <= 0;
      mem_wen_reg   <= 0;
      R_wen_reg     <= 0;
      csr_wen_reg   <= 0;
      Ex_result_reg <= 0;
      rd_value_reg  <= 0;
      rd_reg        <= 0;
      funct3_reg    <= 0;
      rs2_value_reg <= 0;
      jump_flag_reg <= 0;

    end else if (valid_last & ready_last) begin
      mem_ren_reg   <= mem_ren;
      mem_wen_reg   <= mem_wen;
      R_wen_reg     <= R_wen;
      csr_wen_reg   <= csr_wen;
      Ex_result_reg <= Ex_result;
      rd_value_reg  <= rd_value;
      rd_reg        <= rd;
      funct3_reg    <= funct3;
      rs2_value_reg <= rs2_value;
      jump_flag_reg <= jump_flag;
    end
  end


  always @(posedge clock) begin
    if (reset) cpu_opcode <= 0;
    else if (valid_last & ready_last & mem_wen) cpu_opcode <= 2'd2;
    else if (valid_last & ready_last & mem_ren) cpu_opcode <= 2'd1;
    else if (mem_resp) cpu_opcode <= 0;
    else cpu_opcode <= cpu_opcode;
  end




  assign cpu_size = {1'b0,funct3_reg[1:0]};
  assign Ex_result_next = Ex_result_reg;
  assign rd_value_next  = rd_value_reg;
  assign rd_next        = rd_reg;
  assign mem_ren_next   = mem_ren_reg;

  assign R_wen_next     = R_wen_reg;
  assign jump_flag_next = jump_flag_reg;
  assign csr_wen_next   = csr_wen_reg;

  assign req            = lsu_axi.arvalid | lsu_axi.awvalid;

  assign LSU_Rdata      = rdata_ex;

  assign cpu_addr       = Ex_result_reg;
  assign cpu_wdata      = rs2_value_reg << 8 * mem_addr[1:0];


  always @(*) begin
    case (funct3_reg[1:0])
      2'b00:  // lb/lbu
      case (Ex_result_reg[1:0])
        2'b00: rdata = {24'b0, cpu_rdata[7:0]};
        2'b01: rdata = {24'b0, cpu_rdata[15:8]};
        2'b10: rdata = {24'b0, cpu_rdata[23:16]};
        2'b11: rdata = {24'b0, cpu_rdata[31:24]};
      endcase
      2'b01:  // lh/lhu
      case (Ex_result_reg[1])
        1'b0: rdata = {16'b0, cpu_rdata[15:0]};
        1'b1: rdata = {16'b0, cpu_rdata[31:16]};
      endcase
      2'b10: rdata = cpu_rdata;
      default: rdata = 0;
    endcase
  end

  always @(*) begin
    case (funct3_reg[1:0])
      2'b00:  // sb
      case (cpu_addr[1:0])
        2'b00: cpu_wstrb = 4'b0001;
        2'b01: cpu_wstrb = 4'b0010;
        2'b10: cpu_wstrb = 4'b0100;
        2'b11: cpu_wstrb = 4'b1000;
      endcase
      2'b01:  // sh
      case (cpu_addr[1])
        1'b0: cpu_wstrb = 4'b0011;
        1'b1: cpu_wstrb = 4'b1100;
      endcase
      2'b10: cpu_wstrb = 4'b1111;
      default: cpu_wstrb = 4'b0000;
    endcase
  end


  always @(*) begin
    case (funct3_reg)
      3'b000:  rdata_ex = rdata_8i;  // lb
      3'b001:  rdata_ex = rdata_16i;  // lh
      3'b010:  rdata_ex = rdata;  // lw
      3'b100:  rdata_ex = rdata_8u;  // lbu
      3'b101:  rdata_ex = rdata_16u;  // lhu
      default: rdata_ex = 0;
    endcase
  end

  assign rdata_8u  = {24'd0, rdata[7:0]};
  assign rdata_16u = {16'd0, rdata[15:0]};

  /* verilator lint_off PINMISSING */
  ysyx_24100029_sext #(
      .DATA_WIDTH(8),
      .OUT_WIDTH (32)
  ) sext_i8 (
      .data     (rdata[7:0]),
      .sext_data(rdata_8i)
  );

  ysyx_24100029_sext #(
      .DATA_WIDTH(16),
      .OUT_WIDTH (32)
  ) sext_i16 (
      .data     (rdata[15:0]),
      .sext_data(rdata_16i)
  );


  ysyx_24100029_Xbar u_ysyx_24100029_Xbar (
      .cpu_addr  (cpu_addr),
      .cpu_opcode(cpu_opcode),
      .cpu_wdata (cpu_wdata),
      .cpu_wstrb (cpu_wstrb),
      .cpu_rdata (cpu_rdata),
      .cpu_resp  (cpu_resp),
      .cpu_size  (cpu_size),

      .clint_addr  (clint_addr),
      .clint_opcode(clint_opcode),
      .clint_wdata (clint_wdata),
      .clint_wstrb (clint_wstrb),
      .clint_rdata (clint_rdata),
      .clint_resp  (clint_resp),
      .clint_size  (clint_size),

      .mem_addr    (mem_addr),
      .mem_opcode  (mem_opcode),
      .mem_wdata   (mem_wdata),
      .mem_wstrb   (mem_wstrb),
      .mem_rdata   (mem_rdata),
      .mem_resp    (mem_resp),
      .mem_size    (mem_size)
  );



  ysyx_24100029_CLINT u_ysyx_24100029_CLINT (
      .reset (reset),
      .clock (clock),
      .addr  (clint_addr),
      .opcode(clint_opcode),
      .wdata (clint_wdata),
      .wstrb (clint_wstrb),
      .rdata (clint_rdata),
      .resp  (clint_resp)
  );



  ysyx_24100029_dcache u_ysyx_24100029_dcache (
      .clk(clock),
      .rst(reset),

      .mem_addr  (mem_addr),
      .mem_opcode(mem_opcode),
      .mem_wdata (mem_wdata),
      .mem_wstrb (mem_wstrb),
      .mem_rdata (mem_rdata),
      .mem_resp  (mem_resp),

      .dcache_axi(lsu_axi)
  );


endmodule  //MEM

