module ROM 
(
  input  clk,
  input  [7:0]addr,
  output reg [7:0]data
);

always@(posedge clk)
    begin
    case(addr)
    8'h16:data <= 8'd33;
    8'h1e:data <= 8'd34;
    8'h26:data <= 8'd35;
    8'h25:data <= 8'd36;
    8'h2e:data <= 8'd37;
    8'h36:data <= 8'd38;
    8'h3d:data <= 8'd39;
    8'h3e:data <= 8'd40;
    8'h46:data <= 8'd41;
    8'h45:data <= 8'd32;
    8'h1c:data <= 8'd65;
    8'h32:data <= 8'd66;
    8'h21:data <= 8'd67;
    8'h23:data <= 8'd68;
    8'h24:data <= 8'd69;
    8'h2b:data <= 8'd70;
    8'h34:data <= 8'd71;
    8'h33:data <= 8'd72;
    8'h43:data <= 8'd73; 
    8'h3b:data <= 8'd74;
    8'h42:data <= 8'd75;
    8'h4b:data <= 8'd76;
    8'h3a:data <= 8'd77;
    8'h31:data <= 8'd78;
    8'h44:data <= 8'd79;
    8'h4d:data <= 8'd80;
    8'h15:data <= 8'd81;
    8'h2d:data <= 8'd82;
    8'h1b:data <= 8'd83;
    8'h2c:data <= 8'd84;
    8'h3c:data <= 8'd85;
    8'h2a:data <= 8'd86;
    8'h1d:data <= 8'd87;
    8'h22:data <= 8'd88;
    8'h35:data <= 8'd89;
    8'h1a:data <= 8'd90;
    endcase
    end
    


endmodule