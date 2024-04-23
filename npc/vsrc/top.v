module top
(
input ps2_clk,
input ps2_dat,
input clk,
input rst,

output reg [7:0] seg1,
output reg [7:0] seg2


);

wire ready;
wire [7:0]dat;
reg [7:0]keyvalue;
reg flag;
reg clrn;
reg nextdat_n;
reg [2:0]state,next_state;
reg overflow;
reg [9:0]count;
reg clear;

always@(posedge clk)
    if(rst == 1'b0)
        count <= 10'b0;
    else if (count == 10'd1023)
        count <= 10'b0;
    else if(state == 3'd1)
        count <= count + 10'd1; 

always@(posedge clk)
    if(rst == 1'b0)
        clrn <= 1'b0;
    else if (count == 10'd1023&&state == 3'd0)
        clrn <= 1'b0;
    else 
        clrn <= 1'b1;


always @(posedge clk)
    if(rst == 1'b0)
        nextdat_n <= 1'b1;
    else if(state == 3'd1)
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
                next_state <= 3'd3;
                else 
                next_state <= 3'd2;
                end
            3'd2:
                if(nextdat_n == 1'b0)
                next_state<=3'b0;
                else 
                next_state<=next_state;
            3'd3:
                if(nextdat_n == 1'b0)
                next_state<=3'd0;
                else 
                next_state<=next_state;
            default: next_state <= 3'd0;
            endcase    
        end

always @(posedge clk)
    if(rst == 1'b0)
        flag <= 1'b0;
    else if(state == 3'd3)
        flag <= 1'b1;
    else if(state == 3'd2)
        flag <= 1'b0;
    else 
        flag <= flag;

always @(posedge clk)
    if(rst == 1'b0)
        keyvalue <= 8'd0;
    else if(state == 3'd2)
        keyvalue <= dat;
    else if(flag == 1'b1 &&state == 3'd1)
        keyvalue <= 8'h00;
    else 
        keyvalue <= keyvalue;

always@(posedge clk)
    if(rst == 1'b0)
        clear <= 1'b1; 
    else if(keyvalue == 8'h00) 
        clear <= 1'b1;
    else 
        clear <= 1'b0;
/* verilator lint_off WIDTHTRUNC */
seg7 seg7_inst1(
    .num(keyvalue%16),
    .clear(clear),
    .seg_out(seg1)
);

seg7 seg7_inst2(
    .num(keyvalue/16),
    .clear(clear),
    .seg_out(seg2)
);


ps2_keyboard ps2_keyboard_inst
(   
    .clk(clk),
    .clrn(clrn),
    .ps2_clk(ps2_clk),
    .ps2_data(ps2_dat),
    .data(dat),
    .ready(ready),
    .nextdata_n(nextdat_n),
    .overflow(overflow)
);



endmodule

