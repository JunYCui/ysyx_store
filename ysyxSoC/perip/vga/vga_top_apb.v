module vga_top_apb(
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

    output             [   7: 0]           vga_r                      ,
    output             [   7: 0]           vga_g                      ,
    output             [   7: 0]           vga_b                      ,
    output                                 vga_hsync                  ,
    output                                 vga_vsync                  ,
    output                                 vga_valid                   
);
// outports wire
    wire               [   9: 0]        h_addr                      ;
    wire               [   9: 0]        v_addr                      ;
    wire               [  19: 0]        addr                        ;
    wire                                valid                       ;
    reg                                 vga_clk                     ;
    reg                [  31: 0]        ram[2**20-1:0]              ;
    reg                [   1: 0]        count                       ;


    assign                              in_pready                   = in_penable & in_psel;
    assign                              in_pslverr                  = 0;
    assign                              addr                        = {10'd0,h_addr} + 640* {10'd0,v_addr};
    always @(posedge clock) begin
        if(in_penable & in_psel & in_pwrite)
          ram[in_paddr[21:2]] <= in_pwdata;
    end


vga_ctrl u_vga_ctrl(
    .pclk                               (clock                     ),
    .reset                              (reset                     ),
    .vga_data                           (ram[addr][23:0]           ),
    .h_addr                             (h_addr                    ),
    .v_addr                             (v_addr                    ),
    .hsync                              (vga_hsync                 ),
    .vsync                              (vga_vsync                 ),
    .valid                              (vga_valid                 ),
    .vga_r                              (vga_r                     ),
    .vga_g                              (vga_g                     ),
    .vga_b                              (vga_b                     ) 
);



endmodule

module vga_ctrl(
    input                                  pclk                       ,//25MHz时钟
    input                                  reset                      ,//置位
    input              [  23: 0]           vga_data                   ,//上层模块提供的VGA颜色数据
    output             [   9: 0]           h_addr                     ,//提供给上层模块的当前扫描像素点坐标
    output             [   9: 0]           v_addr                     ,
    output                                 hsync                      ,//行同步和列同步信号
    output                                 vsync                      ,
    output                                 valid                      ,//消隐信号
    output             [   7: 0]           vga_r                      ,//红绿蓝颜色信号
    output             [   7: 0]           vga_g                      ,
    output             [   7: 0]           vga_b                       
    );

  //640x480分辨率下的VGA参数设置
    parameter                           h_frontporch               = 96    ;
    parameter                           h_active                   = 144   ;
    parameter                           h_backporch                = 784   ;
    parameter                           h_total                    = 800   ;

    parameter                           v_frontporch               = 2     ;
    parameter                           v_active                   = 35    ;
    parameter                           v_backporch                = 515   ;
    parameter                           v_total                    = 525   ;

  //像素计数值
    reg                [   9: 0]        x_cnt                       ;
    reg                [   9: 0]        y_cnt                       ;
    wire                                h_valid                     ;
    wire                                v_valid                     ;

  always @(posedge pclk or posedge reset)                           //行像素计数
      if (reset == 1'b1)
        x_cnt <= 1;
      else
      begin
        if (x_cnt == h_total)
            x_cnt <= 1;
        else
            x_cnt <= x_cnt + 10'd1;
      end

  always @(posedge pclk or posedge reset)                           //列像素计数
      if (reset == 1'b1)
        y_cnt <= 1;
      else
      begin
        if (y_cnt == v_total & x_cnt == h_total)
            y_cnt <= 1;
        else if (x_cnt == h_total)
            y_cnt <= y_cnt + 10'd1;
      end
  //生成同步信号
    assign                              hsync                       = (x_cnt > h_frontporch);
    assign                              vsync                       = (y_cnt > v_frontporch);
  //生成消隐信号
    assign                              h_valid                     = (x_cnt > h_active) & (x_cnt <= h_backporch);
    assign                              v_valid                     = (y_cnt > v_active) & (y_cnt <= v_backporch);
    assign                              valid                       = h_valid & v_valid;
  //计算当前有效像素坐标
    assign                              h_addr                      = h_valid ? (x_cnt - 10'd145) : {10{1'b0}};
    assign                              v_addr                      = v_valid ? (y_cnt - 10'd36) : {10{1'b0}};
  //设置输出的颜色值
    assign                              vga_r                       = vga_data[23:16];
    assign                              vga_g                       = vga_data[15:8];
    assign                              vga_b                       = vga_data[7:0];
endmodule
