module cpu_v1
(
    input  [31:0] inst,
    output [31:0] pc   

);


assign pc = 32'h80000000;



endmodule

