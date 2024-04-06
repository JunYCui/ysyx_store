module translation(x,en,led);

input [7:0]x;
input en;
output [2:0]led;
always @(x or en) 
begin
    casex (x)   
    {
    8'b1xxxxxxx : led = 3'b111; 
    8'bx1xxxxxx : led = 3'b110;    
    8'bxx1xxxxx : led = 3'b101;
    8'bxxx1xxxx : led = 3'b100;
    8'bxxxx1xxx : led = 3'b011;
    8'bxxxxx1xx : led = 3'b010;
    8'bxxxxxx1x : led = 3'b001;
    8'bxxxxxxx1 : led = 3'b000;
    default: led =3'b000;
    }
    endcase

end



endmodule

