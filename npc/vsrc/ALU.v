module ALU(
    input [3:0] d1,
    input [3:0] d2,
    input [2:0] choice,
    output reg [3:0] res,
    output reg overflow,
    output reg compare
);
    reg [3:0]res_compare; 
    always@(*)
    begin
    case(choice)
    3'b000: begin 
            res = d1 + d2;
            overflow = ((d1[3] == d2[3])&(d1[3]!= res[3]));
            compare  = 1'b0;
            end
    3'b001: begin
                /* verilator lint_off WIDTHEXPAND */
                res  = d1 + (~d2) + 1'b1 ;
                overflow = ((d1[3] == d2[3])&(d1[3]!= res[3]));
                 /* verilator lint_on WIDTHEXPAND */
                compare  = 1'b0;
            end
    3'b010: begin 
        /* verilator lint_off WIDTHEXPAND */
            res = ~d1+1'b1;
        /* verilator lint_on WIDTHEXPAND */
            overflow = 1'b0;
            compare  = 1'b0;      
            end
    3'b011: begin 
            res = d1 & d2;
            overflow = 1'b0;
            compare  = 1'b0;
            Carry = 1'b0;     
            end
    3'b100: begin 
            res = d1 | d2;
            overflow = 1'b0;
            compare  = 1'b0;
            Carry = 1'b0;                 
            end
    3'b101: begin
            res = d1 ^ d2;
            overflow = 1'b0;
            compare  = 1'b0;
            Carry = 1'b0;                 
            end
    3'b110:begin 
            res_compare = d1 + (~d2) + 1'b1;
            if((d1[3] == d2[3])&&(d1[3]!= res_compare[3]))
            {
                if(res_compare[3]==1'b1)
                {
                  compare = 1'b0; 
                }
                else 
                {
                  compare = 1'b1; 
                }
            }
            else 
            {
                if(res_compare[3]==1'b0)
                {
                 compare = 1'b0; 
                }
                else 
                {
                 compare = 1'b1;
                }
            }
            res = 4'b0;
            overflow = 1'b0;
            end
    3'b111:begin 
            res_compare = d1 + (~d2) + 1'b1;
            if(res_compare[2:0] == 3'b000)
            {
                compare  = 1'b1;
            }
            else 
            {
                compare = 1'b1;
            }
            res = 4'b0;
            overflow = 1'b0;
            end
    endcase
    
    end


endmodule

