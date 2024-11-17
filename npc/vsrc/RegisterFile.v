module RegisterFile #(ADDR_WIDTH = 1, DATA_WIDTH = 1) (
  input clk,
  input [DATA_WIDTH-1:0] wdata,
  input [ADDR_WIDTH-1:0] waddr,
  input wen,
  input rst,
  input [ADDR_WIDTH-1:0]  rs1_addr,
  input [ADDR_WIDTH-1:0]  rs2_addr,

  output [DATA_WIDTH-1:0] rs1_value,  
  output [DATA_WIDTH-1:0] rs2_value,
  output [DATA_WIDTH-1:0] a0_value

);
  reg [DATA_WIDTH-1:0] rf [2**ADDR_WIDTH-1:0];
  always @(posedge clk) begin
    if (wen) rf[waddr] <= wdata;
  end

  always @(posedge clk)begin
      if(!rst)
      rf[0] <= 32'd0;
  end

assign rs1_value = rf[rs1_addr];
assign rs2_value = rf[rs2_addr];
assign a0_value = rf[10];

endmodule

