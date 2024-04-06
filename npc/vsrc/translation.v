module translation(x,en,led,seg0);

input [7:0]x;
input en;
output reg [2:0]led;
output reg [6:0]seg0;
always @(x or en) 
/* verilator lint_off CASEX */
begin
    if(en)
   begin
    casex (x)   
    8'b1xxxxxxx :led = 3'b111; 
    8'b01xxxxxx :led = 3'b110;    
    8'b001xxxxx :led = 3'b101;
    8'b0001xxxx :led = 3'b100;
    8'b00001xxx :led = 3'b011;
    8'b000001xx :led = 3'b010;
    8'b0000001x :led = 3'b001;
    8'b00000001 :led = 3'b000;
    default: led =3'b000;
    endcase 
   end
end
/* verilator lint_on CASEX */
seg7 inst1(
    .num(led),
    .seg_out(seg0)
);

endmodule

