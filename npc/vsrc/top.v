module top
(
    input                                  ps2_clk                    ,
    input                                  ps2_dat                    ,
    input                                  clk                        ,
    input                                  rst                        ,

    output reg         [   7: 0]           seg1                       ,
    output reg         [   7: 0]           seg2                       ,
    output reg         [   7: 0]           seg3                       ,
    output reg         [   7: 0]           seg4                       ,
    output reg         [   7: 0]           seg5                       ,
    output reg         [   7: 0]           seg6                        

);

    wire                                ready                       ;
    wire               [   7: 0]        dat                         ;
    reg                [   7: 0]        keyvalue                    ;
    reg                                 clrn                        ;
    reg                                 nextdat_n                   ;
    reg                [   2: 0]        state,next_state            ;
    reg                                 overflow                    ;
    reg                                 clear                       ;
    reg                                 flag                        ;
    reg                [   6: 0]        count                       ;
    wire               [   7: 0]        ascill_value                ;

always@(posedge clk)
    if(rst == 1'b0)
        clrn <= 1'b0;
    else
        clrn <= 1'b1;


always @(posedge clk)
    if(rst == 1'b0)
        nextdat_n <= 1'b1;
    else if(flag == 1'b1)
        nextdat_n <= 1'b0;
    else
        nextdat_n <= 1'b1;

always @(posedge clk)
    if(rst == 1'b0)
        state <= 3'd0;
    else
        state <= next_state;

always @(posedge clk)
    if(rst == 1'b0)
        next_state <= 3'd0;
    else
        begin
            case (state)
            3'd0:if(ready&&(overflow == 1'd0)) next_state <= 3'd1; else next_state<=3'b0;
            3'd1:
                begin
                if(dat == 8'hF0)
                next_state <= 3'd3;                                 //松手
                else
                next_state <= 3'd2;
                end
            3'd2:                                                   //未松手
                if(nextdat_n == 1'b0)
                next_state<=3'b0;
                else
                next_state<=next_state;
            3'd3:                                                   //F0H
                if(nextdat_n == 1'b0)
                next_state<=3'd4;
                else
                next_state<=next_state;
            3'd4:                                                   // 松手的键值
                if(ready&&(overflow == 1'd0))
                next_state<=3'd5;
                else
                next_state<=next_state;
            3'd5:
                if(nextdat_n == 1'b0)
                next_state <=3'd0;
                else
                next_state<=next_state;
            default: next_state <= 3'd0;
            endcase
        end


always@(posedge clk)
    if(rst == 1'b0)
        flag <= 1'b0;
    else if(state == 3'd2 || state == 3'd3 || state == 3'd5)
        flag <= 1'b1;
    else
        flag <= 1'b0;
always @(posedge clk)
    if(rst == 1'b0)
        keyvalue <= 8'd0;
    else if(state == 3'd2 && nextdat_n!= 1'd0)
        keyvalue <= dat;
    else
        keyvalue <= keyvalue;

always@(posedge clk)
    if(rst == 1'b0)
        clear <= 1'b1;
    else if(state == 3'd2)
        clear <= 1'b0;
    else if(state == 3'd5)
        clear <= 1'b1;
    else
        clear <= clear;
always@(posedge clk)
    if(rst == 1'b0)
        count <= 7'b0;
    else if(count == 7'd100)
        count <= 7'd0;
    else if(state == 3'd5 && next_state == 3'd0)
        count <= count + 7'd1 ;
    else
        count <= count;

/* verilator lint_off WIDTHTRUNC */
seg7 seg7_inst1(
    .num                                (keyvalue%16               ),
    .clear                              (clear                     ),
    .seg_out                            (seg1                      ) 
);

seg7 seg7_inst2(
    .num                                (keyvalue/16               ),
    .clear                              (clear                     ),
    .seg_out                            (seg2                      ) 
);

seg7 seg7_inst3(
    .num                                (ascill_value%10           ),
    .clear                              (clear                     ),
    .seg_out                            (seg3                      ) 
);

seg7 seg7_inst4(
    .num                                (ascill_value/10           ),
    .clear                              (clear                     ),
    .seg_out                            (seg4                      ) 
);

seg7 seg7_inst5(
    .num                                (count%10                  ),
    .clear                              (1'b0                      ),
    .seg_out                            (seg5                      ) 
);

seg7 seg7_inst6(
    .num                                (count/10                  ),
    .clear                              (1'b0                      ),
    .seg_out                            (seg6                      ) 
);



ROM ROM_Inst
(
    .clk                                (clk                       ),
    .addr                               (keyvalue                  ),
    .data                               (ascill_value              ) 
);



ps2_keyboard ps2_keyboard_inst
(
    .clk                                (clk                       ),
    .clrn                               (clrn                      ),
    .ps2_clk                            (ps2_clk                   ),
    .ps2_data                           (ps2_dat                   ),
    .data                               (dat                       ),
    .ready                              (ready                     ),
    .nextdata_n                         (nextdat_n                 ),
    .overflow                           (overflow                  ) 
);



endmodule

