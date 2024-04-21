module top
(
input ps2_clk,
input ps2_dat,
input clk,
input clrn,

output reg [15:0] led

);

wire ready;
wire [7:0]dat;
reg nextdat_n;
reg f1_flag;
reg [2:0]state,next_state;
wire overflow;



always @(posedge clk or negedge clrn)
    if(clrn == 1'b0)
        nextdat_n <= 1'b1;
    else if(f1_flag == 1'b1)
        nextdat_n <= 1'b0;
    else 
        nextdat_n <= 1'b1;

always @(posedge clk or negedge clrn)
    if(clrn == 1'b0)
        state <= 3'd0;
    else 
        state <= next_state;

always @(posedge clk or negedge clrn)
    if(clrn == 1'b0)
        next_state <= 3'd0;
    else  
        begin
            case (state)
            3'd0:if(ready) next_state <= 3'd1; else next_state<=3'b0;
            3'd1:if(f1_flag == 1'b1) next_state <= 3'd2;
            3'd2:if(nextdat_n == 1'b0) next_state <= 3'd0; 
            default: next_state <= 3'd0;
            endcase    
        end

always @(posedge clk or negedge clrn)
    if(clrn == 1'b0)
        f1_flag <= 1'd0;
    else if(state == 1'd1)
        f1_flag <= 1'd1;
    else 
        f1_flag <= f1_flag;

always @(posedge clk or negedge clrn)
    if(clrn == 1'b0)
        led <= 16'd0;
    else if(state == 1'd1)
        led <= {8'd0,dat};
    else 
        led <= led;


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

