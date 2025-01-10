// 触发器模板
module ysyx_24100029_Reg #(WIDTH = 1, RESET_VAL = 0) (
    input                        clock                      ,
    input                        reset                      ,
    input              [WIDTH-1: 0]din                      ,
    output reg         [WIDTH-1: 0]dout                     ,
    input                        wen                         
);
  always @(posedge clock) begin
    if (reset) dout <= RESET_VAL;
    else if (wen) dout <= din;
  end
endmodule

