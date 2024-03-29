module light
(
    input clk,
    input rst,
    output reg [15:0]led 
);
    reg [31:0] count;
    always @(posedge clk) 
    begin
        if(rst) begin count <=1'b0; end    
        else if(count == 32'd5000000)
                count <= 1'b0;
        else 
            begin
                count <= count + 1'b1;
            end
    end
    always@(posedge clk)
    begin
        if(rst) begin led <= 16'd1; end
        else if(count == 32'd5000000)
            led <= {led[14:0],led[15]};
        else 
            led <= led;
    end



endmodule
