module ALU(
    input [3:0] d1,
    input [3:0] d2,
    input [2:0] choice,
    output reg [3:0] res,
    output reg Carry,
    output reg overflow,
    output reg compare
)
    
    always@(*)
    begin
    case(choice)
    3'b000:{Carry,res} = d1 + d2;
           overflow = (d1[3] == d2[3])&(d1[3]!= res[3]);
    3'b001:{Carry,res} = d1 + ~d2 + 1'b1;
            overflow = ((d1[3] == d2[3])&(d1[3]!= res[3]));
    3'b010:res = ~d1;

    3'b011:res = d1 & d2;
    3'b100:res = d1 | d2;
    3'b101:res = d1 ^ d2;
    
    3'b110:if(d1>d2)compare <= 1'b1 else compare <= 1'b0 
    3'b111:if(d1==d2)compare = 1'b1 else compare <= 1'b0
    endcase
    
    end


endmodule