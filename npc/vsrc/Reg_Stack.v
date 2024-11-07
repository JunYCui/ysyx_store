module Reg_Stack(
    input rst               ,
    input clk               ,
    input [4:0]rs1          ,
    input [4:0]rs2          ,
    input [4:0]rd           ,
    input [31:0]rd_value    ,
    input wen               ,

    output [31:0]rs1_value  ,
    output [31:0]rs2_value
);




RegisterFile #(5, 32) io(
     .clk(clk)              ,
     .wdata(rd_value)       ,
     .waddr(rd)             ,
     .wen(wen)              ,
     .rst(rst)              ,
     .rs1_addr(rs1)         ,
     .rs2_addr(rs2)         ,

     .rs1_value(rs1_value)  ,  
     .rs2_value(rs2_value)
);


endmodule

