module add
#(
    parameter BW=4
)
(
   input choose_add_sub,
   input [BW-1:0]add_1,
   input [BW-1:0]add_2,
   output [BW-1:0]result,
   output overflow    
);
// if {choose_add_sub == 1} addd_1 - add_2 else  add_1 + add_2

wire [BW-1:0]add_3;

assign add_3 = (choose_add_sub == 1'b0)? add_2:(~add_2 + 1'b1);

assign result = add_1 + add_3;

assign overflow = (add_1[BW-1] == add_3[BW-1])? ( (result[BW-1] == add_1[BW-1])? 1'b0:1'b1):(1'b0) ;









endmodule


