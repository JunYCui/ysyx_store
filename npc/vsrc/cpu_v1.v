module cpu_v1
(
    input  [31:0] inst,
    output [31:0] pc,   
    output [31:0] inst_out
);


assign pc = 32'h80000004;
assign inst_out = inst;


endmodule

