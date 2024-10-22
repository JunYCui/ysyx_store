module add
#(
    parameter BW=4
)
(
   input [BW-1:0]add_1,
   input [BW-1:0]add_2,
   output [BW-1:0]result,
   output overflow    
);

assign result = add_1 + add_2;

assign overflow = (add_1[BW-1] == add_2[BW-1])? ( (result[BW-1] == add_1[BW-1])? 1'b0:1'b1):(1'b0) ;









endmodule


