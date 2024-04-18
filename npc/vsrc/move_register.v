module move_register(
    input in_data,
    input clk,
    input [2:0]ctrl,
    output reg [7:0]out,
    output reg [7:0]par_out
);
    reg [3:0]count;
    reg [31:0]clk_count;
    reg clk_fen;
    always @(posedge clk) begin
        if(clk_count == 31'd50000)
        begin
            clk_count <= 31'd0;
            clk_fen <= ~clk_fen;
        end
        else
        begin
            clk_count <= clk_count + 1'd1;
            clk_fen <= clk_fen;
        end
    end
    initial
    begin
        out = 8'b0000_0000;
    end
    always @(posedge clk_fen) 
    begin
        case(ctrl)
        3'b000: out <= 8'b0000_0000;
        3'b001: out <= 8'b1111_1010;
        3'b010: out <= {in_data,out[7:1]};
        3'b011: out <= {out[6:0],in_data};
        3'b100: out <= {out[7],in_data,out[6:1]};
        3'b101: out <= {in_data,out[7:1]};
        3'b110: out <= {out[0],out[7:1]};
        3'b111: out <= {out[6:0],out[7]};
        endcase 
    end
    always @(posedge clk_fen) 
    begin
        if(ctrl == 3'b101)
        begin
            if(count == 4'd8)
                count <= 4'd0;
            else 
                count <= count + 1'b1;
        end
        else 
            count <= 4'd0;
    end
    always @(posedge clk_fen) begin
        if (ctrl == 3'b101)
        begin
            if(count == 4'd8)
                par_out <= out;
            else
                par_out <= par_out;
        end
        else 
            par_out <= 8'd0;
    end


endmodule

