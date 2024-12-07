`timescale 1ns/1ps
module LSFR (
    input                        clk                        ,
    input                        load                       ,
    output reg         [   7: 0] dat                        ,
    output             [   7: 0] seg0                       ,
    output             [   7: 0] seg1                       ,
    output             [   7: 0] seg2                        
);

/* verilator lint_off WIDTHTRUNC */
    
    reg                [  31: 0] clk_count                  ;
    reg                          data_move                  ;
    reg                          clk_fen                    ;
    wire               [   3: 0] unit,ten,hundred           ;


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
    /* verilator lint_off BLKSEQ */
    always @(posedge clk_fen)
    begin
        if(load)
        begin
            dat = 8'b0000_0001;
            data_move = 1'b1;
        end
        else
        begin
            dat = {data_move,dat[7:1]};
            data_move = dat[4]^dat[3]^dat[2]^dat[0];
        end
    
    end

    assign                       unit                      = dat%10;
    assign                       ten                       = dat/10%10;
    assign                       hundred                   = dat/100;


seg7 seg1_inst
(
    .num                         (unit                      ),
    .clear                       (1'b0                      ),
    .seg_out                     (seg0                      ) 
);

seg7 seg2_inst
(
    .num                         (ten                       ),
    .clear                       (1'b0                      ),
    .seg_out                     (seg1                      ) 
);

seg7 seg3_inst
(
    .num                         (hundred                   ),
    .clear                       (1'b0                      ),
    .seg_out                     (seg2                      ) 
);


endmodule
