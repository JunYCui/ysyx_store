module LSFR (
    input clk,
    input load,
    output [7:0]seg0,
    output [7:0]seg1,
    output [7:0]seg2
);

/* verilator lint_off WIDTHTRUNC */
/* verilator lint_off BLKSEQ */
    reg [7:0]date1;
    reg [31:0]clk_count;
    reg data_move;
    reg clk_fen;
    wire [2:0] unit,ten,hundred;


    always @(posedge clk) begin
        if(clk_count == 32'd5000000)
        begin
            clk_count <= 32'd0;
            clk_fen <= ~clk_fen;
        end
        else
        begin
            clk_count <= clk_count + 1'd1;
            clk_fen <= clk_fen;
        end
    end
    always @(posedge clk_fen)
    begin
        if(load)
        begin
            date1 <= 8'b0000_0001;
            data_move <= 1'b1;  
        end
        else 
        begin
            
            date1 = {data_move,date1[6:0]};
            data_move = date1[4]^date1[3]^date1[2]^date1[0];
        end 
    
    end

    assign unit = date1%10;
    assign ten = date1/10%10;
    assign hundred = date1/100;


seg7 seg1_inst
(
    .num (unit),
    .seg_out (seg0)
);

seg7 seg2_inst
(
    .num (ten),
    .seg_out (seg1)
);

seg7 seg3_inst
(
    .num (hundred),
    .seg_out (seg2)
);


endmodule
