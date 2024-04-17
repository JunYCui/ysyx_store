module ALU(
    input [3:0] d1,
    input [3:0] d2,
    input [2:0] choice,
    output reg [3:0] res,
    output reg overflow,
    output reg compare
);
    reg [3:0]res_compare; 
    reg [3:0]d2_n;
    always@(*)
    begin
    case(choice)
    3'b000: begin 
            res = d1 + d2;
            overflow = ((d1[3] == d2[3])&(d1[3]!= res[3]));
            compare  = 1'b0;
            res_compare= 4'b0;
            d2_n =4'b0;
            end
    3'b001: begin
                /* verilator lint_off WIDTHEXPAND */
                d2_n = ~d2 + 4'b0001;
                res  = d1 + d2_n ;
                overflow = ((d1[3] == d2_n[3])&(d1[3]!= res[3]));
                 /* verilator lint_on WIDTHEXPAND */
                compare  = 1'b0;
                res_compare= 4'b0;
            end
    3'b010: begin 
        /* verilator lint_off WIDTHEXPAND */
            res = ~d1;
        /* verilator lint_on WIDTHEXPAND */
            overflow = 1'b0;
            compare  = 1'b0;
            res_compare= 4'b0;
            d2_n =4'b0;      
            end
    3'b011: begin 
            res = d1 & d2;
            overflow = 1'b0;
            compare  = 1'b0; 
            res_compare= 4'b0;
            d2_n =4'b0;
            end
    3'b100: begin 
            res = d1 | d2;
            overflow = 1'b0;
            compare  = 1'b0;    
            res_compare= 4'b0; 
            d2_n =4'b0;         
            end
    3'b101: begin
            res = d1 ^ d2;
            overflow = 1'b0;
            compare  = 1'b0;  
            res_compare= 4'b0;
            d2_n =4'b0;             
            end
    3'b110:begin 
            d2_n = ~d2 + 4'b0001;
            if(d2_n == 4'b1000)
                d2_n = 4'b0000;
            res_compare = d1 + d2_n;
            if((d1[3] == d2_n[3])&&(d1[3]!= res_compare[3]))
            begin
                if(res_compare[3]==1'b1)
                  compare = 1'b0; 
                else 
                  compare = 1'b1; 
            end
            else 
            begin
                if(res_compare[3]==1'b0)
                 compare = 1'b0; 
                else 
                 compare = 1'b1;
            end
            res = 4'b0;
            overflow = 1'b0;
            end
    3'b111:begin 
            res_compare = d1 + (~d2) + 1'b1;
            if(res_compare[2:0] == 3'b000)
                compare  = 1'b1;
            else 
                compare = 1'b0;
            res = 4'b0;
            overflow = 1'b0;
            d2_n =4'b0;
            end
    endcase
    
    end


endmodule

