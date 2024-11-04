module cpu_v1
(
    input  clk          ,
    input  rst          ,
    input  [31:0] inst  ,
    output reg [31:0] pc     
);


parameter PC_MAX = 32'h80000004;
 


always @(posedge clk or negedge rst) begin
    if(!rst)
    pc <= 32'h80000000;
    else if(pc == PC_MAX)
    pc <= 32'h80000000;
    else 
    pc <= pc + 1'b1;
end








endmodule

