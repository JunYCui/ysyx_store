module ysyx_24100029_PHT #(
    PHT_INDEX_WIDTH = 8
)
(
    input  clock,
    input  reset,

    input  [PHT_INDEX_WIDTH-1:0]pht_index_w,
    input  is_taken,
    input  pht_w_en,
    input  [PHT_INDEX_WIDTH-1:0]pht_index_r,

    output pht_state       
);

  localparam TAKE_W = 2'b11;
  localparam TAKE_S = 2'b10;
  localparam NOT_TAKE_W = 2'b01;
  localparam NOT_TAKE_S = 2'b00;

 logic [1:0] ram[(2**PHT_INDEX_WIDTH)-1:0];

  // 2bit counter
  always @(posedge clock) begin
    if (pht_w_en) begin
      case (ram[pht_index_w])
        NOT_TAKE_S: ram[pht_index_w] <= is_taken ? NOT_TAKE_W : NOT_TAKE_S;
        NOT_TAKE_W: ram[pht_index_w] <= is_taken ? TAKE_W : NOT_TAKE_S;
        TAKE_W: ram[pht_index_w] <= is_taken ? TAKE_S : NOT_TAKE_W;
        TAKE_S: ram[pht_index_w] <= is_taken ? TAKE_S : TAKE_W;
      endcase
    end
  end

    assign pht_state = ram[pht_index_r][1];



endmodule

