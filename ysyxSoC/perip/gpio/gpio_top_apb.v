module gpio_top_apb(
    input                                  clock                      ,
    input                                  reset                      ,
    input              [  31: 0]           in_paddr                   ,
    input                                  in_psel                    ,
    input                                  in_penable                 ,
    input              [   2: 0]           in_pprot                   ,
    input                                  in_pwrite                  ,
    input              [  31: 0]           in_pwdata                  ,
    input              [   3: 0]           in_pstrb                   ,
    output                                 in_pready                  ,
    output             [  31: 0]           in_prdata                  ,
    output                                 in_pslverr                 ,

    output reg         [  15: 0]           gpio_out                   ,
    input              [  15: 0]           gpio_in                    ,
    output             [   7: 0]           gpio_seg_0                 ,
    output             [   7: 0]           gpio_seg_1                 ,
    output             [   7: 0]           gpio_seg_2                 ,
    output             [   7: 0]           gpio_seg_3                 ,
    output             [   7: 0]           gpio_seg_4                 ,
    output             [   7: 0]           gpio_seg_5                 ,
    output             [   7: 0]           gpio_seg_6                 ,
    output             [   7: 0]           gpio_seg_7                  
);
    wire               [   7: 0]        data_byte[3:0]              ;// byte data
    wire               [   7: 0]        seg_w[7:0]                  ;
    reg                [  31: 0]        rdata                       ;
    reg                [   7: 0]        seg[7:0]                    ;

    assign                              in_pready                   = in_psel & in_penable;
    assign                              data_byte[0]                = in_pwdata[7:0];
    assign                              data_byte[1]                = in_pwdata[15:8];
    assign                              data_byte[2]                = in_pwdata[23:16];
    assign                              data_byte[3]                = in_pwdata[31:24];
    assign                              in_prdata                   = rdata;

    always @(posedge clock or posedge reset) begin
        if(reset)begin
            seg[0] <= 8'b1111_1111;
            seg[1] <= 8'b1111_1111;
            seg[2] <= 8'b1111_1111;
            seg[3] <= 8'b1111_1111;
            seg[4] <= 8'b1111_1111;
            seg[5] <= 8'b1111_1111;
            seg[6] <= 8'b1111_1111;
            seg[7] <= 8'b1111_1111;
        end
        else if(in_pready&in_pwrite&in_paddr[3:0] == 4'd8)begin
            seg[0] <= (in_pstrb[0])? seg_w[0]:seg[0];
            seg[1] <= (in_pstrb[0])? seg_w[1]:seg[1];
            seg[2] <= (in_pstrb[1])? seg_w[2]:seg[2];
            seg[3] <= (in_pstrb[1])? seg_w[3]:seg[3];
            seg[4] <= (in_pstrb[2])? seg_w[4]:seg[4];
            seg[5] <= (in_pstrb[2])? seg_w[5]:seg[5];
            seg[6] <= (in_pstrb[3])? seg_w[6]:seg[6];
            seg[7] <= (in_pstrb[3])? seg_w[7]:seg[7];
        end
    end


    always @(posedge clock or posedge reset) begin
      if(reset)
        gpio_out <= 0;
      else if(in_pready&in_pwrite&in_paddr[3:0] == 0)begin
        gpio_out[7:0] <= (in_pstrb[0])? data_byte[0]:gpio_out[7:0];
        gpio_out[15:8] <= (in_pstrb[1])? data_byte[1]:gpio_out[15:8];
      end
  end
  always @(posedge clock or posedge reset) begin
      if(reset)
        rdata <= 0;
      else if(in_pready&~in_pwrite&in_paddr[3:0] == 4'd4)
        rdata[7:0] <= (in_pstrb[0])? gpio_in[7:0]: rdata[7:0];
        rdata[15:8] <= (in_pstrb[1])? gpio_in[15:8]: rdata[15:8];
        rdata[23:16] <= 0;
        rdata[31:24] <= 0;
  end

// it means no error
    assign                              in_pslverr                  = 0;

    assign                              gpio_seg_0                  = seg[0];
    assign                              gpio_seg_1                  = seg[1];
    assign                              gpio_seg_2                  = seg[2];
    assign                              gpio_seg_3                  = seg[3];
    assign                              gpio_seg_4                  = seg[4];
    assign                              gpio_seg_5                  = seg[5];
    assign                              gpio_seg_6                  = seg[6];
    assign                              gpio_seg_7                  = seg[7];

seg7 seg7_inst0(
    .num                                (data_byte[0][3:0]         ),
    .seg_out                            (seg_w[0]                  ) 
);
seg7 seg7_inst1(
    .num                                (data_byte[0][7:4]         ),
    .seg_out                            (seg_w[1]                  ) 
);
seg7 seg7_inst2(
    .num                                (data_byte[1][3:0]         ),
    .seg_out                            (seg_w[2]                  ) 
);
seg7 seg7_inst3(
    .num                                (data_byte[1][7:4]         ),
    .seg_out                            (seg_w[3]                  ) 
);
seg7 seg7_inst4(
    .num                                (data_byte[2][3:0]         ),
    .seg_out                            (seg_w[4]                  ) 
);
seg7 seg7_inst5(
    .num                                (data_byte[2][7:4]         ),
    .seg_out                            (seg_w[5]                  ) 
);

seg7 seg7_inst6(
    .num                                (data_byte[3][3:0]         ),
    .seg_out                            (seg[6]                    ) 
);
seg7 seg7_inst7(
    .num                                (data_byte[3][7:4]         ),
    .seg_out                            (seg[7]                    ) 
);

endmodule


module seg7(num,seg_out);

    input              [   3: 0]           num                        ;
    output reg         [   7: 0]           seg_out                    ;
always @(*) begin
    case (num)
    4'd0:seg_out = 8'b00000011;
    4'd1:seg_out = 8'b10011111;
    4'd2:seg_out = 8'b00100101;
    4'd3:seg_out = 8'b00001101;
    4'd4:seg_out = 8'b10011001;
    4'd5:seg_out = 8'b01001001;
    4'd6:seg_out = 8'b01000001;
    4'd7:seg_out = 8'b00011111;
    4'd8:seg_out = 8'b00000001;
    4'd9:seg_out = 8'b00001001;
    4'd10:seg_out = 8'b00010001;
    4'd11:seg_out = 8'b11000001;
    4'd12:seg_out = 8'b01100011;
    4'd13:seg_out = 8'b10000101;
    4'd14:seg_out = 8'b01100001;
    4'd15:seg_out = 8'b01110001;
    default: seg_out = 8'b1111_1111;
    endcase
end

endmodule
