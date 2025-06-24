module ysyx_24100029_dmux4to1 #(
    parameter  DATA_WIDTH = 32,
    parameter  Is_One_Hot = 1'b1,
    localparam SEL_WIDTH  = Is_One_Hot ? 4 : 2,
    localparam type data_t = logic [DATA_WIDTH-1:0],
    localparam type sel_t = logic [SEL_WIDTH-1:0]
) (
    input data_t data_i0,
    input data_t data_i1,
    input data_t data_i2,
    input data_t data_i3,
    input sel_t  sel,
    output data_t data_o
);



  if (Is_One_Hot) begin : One_Hot_Sel
    always_comb begin : demux_comb
      case (sel)
        4'b0001: data_o = data_i0;
        4'b0010: data_o = data_i1;
        4'b0100: data_o = data_i2;
        4'b1000: data_o = data_i3;
        default: data_o = 'd0;
      endcase
    end
  end else begin : bin_sel
    always_comb begin : demux_comb
      case (sel)
        2'b00:   data_o = data_i0;
        2'b01:   data_o = data_i1;
        2'b10:   data_o = data_i2;
        2'b11:   data_o = data_i3;
        default: data_o = 'd0;
      endcase
    end
  end





endmodule

