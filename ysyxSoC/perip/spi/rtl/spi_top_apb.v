// define this macro to enable fast behavior simulation
// for flash by skipping SPI transfers
//`define FAST_FLASH

module spi_top_apb #(
    parameter                           flash_addr_start           = 32'h30000000,
    parameter                           flash_addr_end             = 32'h3fffffff,
    parameter                           spi_ss_num                 = 8     
) (
    input                                  clock                      ,
    input                                  reset                      ,
    input              [  31: 0]           in_paddr                   ,// addr
    input                                  in_psel                    ,// sel completer
    input                                  in_penable                 ,// APB transfer enable
    input              [   2: 0]           in_pprot                   ,// PPROT indicates the normal, privileged, or secure protection level of the transaction
    input                                  in_pwrite                  ,// pwrite indicates access direction
    input              [  31: 0]           in_pwdata                  ,
    input              [   3: 0]           in_pstrb                   ,// write strb
    output                                 in_pready                  ,
    output             [  31: 0]           in_prdata                  ,
    output                                 in_pslverr                 ,// assert 1 when transfer error

    output                                 spi_sck                    ,
    output             [spi_ss_num-1: 0]           spi_ss                     ,
    output                                 spi_mosi                   ,
    input                                  spi_miso                   ,
    output                                 spi_irq_out                 
);

/*`ifdef FAST_FLASH

    wire               [  31: 0]        data                        ;
    parameter                           invalid_cmd                = 8'h0  ;
flash_cmd flash_cmd_i(
    .clock                              (clock                     ),
    .valid                              (in_psel && !in_penable    ),
    .cmd                                (in_pwrite ? invalid_cmd : 8'h03),// 
    .addr                               ({8'b0, in_paddr[23:2], 2'b0}),
    .data                               (data                      ) 
);
    assign                              spi_sck                     = 1'b0;
    assign                              spi_ss                      = 8'b0;
    assign                              spi_mosi                    = 1'b1;
    assign                              spi_irq_out                 = 1'b0;
    assign                              in_pslverr                  = 1'b0;
    assign                              in_pready                   = in_penable && in_psel && !in_pwrite;
    assign                              in_prdata                   = data[31:0];

`else
*/
// 000 001 010 011 100
typedef enum [2:0] {IDLE, DIVIR,CTRL,TXR,SSR,WAIT,RDATA,CLEAR} state_t;

    reg                [   2: 0]        state                       ;
    reg                [   2: 0]        next_state                  ;
    reg                [   4: 0]        wb_adr_i                    ;
    reg                [  31: 0]        wb_dat_i                    ;
    reg                [  31: 0]        wb_dat_o                    ;
    reg                [   3: 0]        wb_sel_i                    ;
    reg                                 wb_we_i                     ;
    reg                                 wb_stb_i                    ;
    reg                                 wb_cyc_i                    ;
    reg                                 wb_ack_o                    ;
    reg                                 wb_err_o                    ;
    reg                                 wb_int_o                    ;
always @(posedge clock) begin
    if(reset)begin
        state <= IDLE;
    end
    else
        state <= next_state;
end
always @(*) begin
    case(state)
    IDLE:if(in_paddr[31:28] == 4'd3 & in_penable & in_psel)begin
        next_state = DIVIR;
    end
    else
        next_state = IDLE;
    DIVIR:if(wb_ack_o)begin
        next_state = TXR;
    end
    else
        next_state = DIVIR;
    TXR:if(wb_ack_o)
        next_state = SSR;
    else
        next_state = TXR;
    SSR:if(wb_ack_o)
        next_state = CTRL;
    else
        next_state = SSR;
    CTRL:if(wb_ack_o)begin
        next_state = WAIT;
    end
    else
        next_state = CTRL;
    WAIT:if(wb_ack_o & ~wb_dat_o[8])
        next_state = RDATA;
    else
        next_state = WAIT;
    RDATA:if(wb_ack_o)
        next_state = CLEAR;
    else
        next_state = RDATA;
    CLEAR:if(wb_ack_o)
        next_state = IDLE;
    else 
        next_state = CLEAR;
    default:
        next_state = IDLE;
    endcase
end
always @(posedge clock) begin
    if(reset)begin
        wb_adr_i <= 0;
        wb_dat_i <= 0;
        wb_sel_i <= 0;
        wb_we_i <= 0;
        wb_stb_i <= 0;
        wb_cyc_i <= 0;
    end
    else if(state == IDLE && in_paddr[31:28] == 4'd3)begin
        wb_adr_i <= 5'h14;
        wb_dat_i <= 32'h2;
        wb_sel_i <= 4'b1111;
        wb_we_i <= 1'b1;
        wb_stb_i <= 1'b1;
        wb_cyc_i <= 1'b1;
    end
    else if(state == DIVIR && wb_ack_o)begin
        wb_adr_i <= 5'h04;
        wb_dat_i <= {8'h03,in_paddr[23:2],2'b00};
        wb_sel_i <= 4'b1111;
        wb_we_i <= 1'b1;
        wb_stb_i <= 1'b1;
        wb_cyc_i <= 1'b1;
    end
    else if(state == TXR && wb_ack_o)begin
        wb_adr_i <= 5'h18;
        wb_dat_i <= 32'h01;
        wb_sel_i <= 4'b1111;
        wb_we_i <= 1'b1;
        wb_stb_i <= 1'b1;
        wb_cyc_i <= 1'b1;
    end
    else if(state == SSR && wb_ack_o)begin
        wb_adr_i <= 5'h10;
        wb_dat_i <= 32'h0140;                                       // 64bits msb first
        wb_sel_i <= 4'b1111;
        wb_we_i <= 1'b1;
        wb_stb_i <= 1'b1;
        wb_cyc_i <= 1'b1;
    end
    else if(state == CTRL && wb_ack_o)begin
        wb_adr_i <= 5'h10;
        wb_dat_i <= 32'h00;
        wb_sel_i <= 4'b1111;
        wb_we_i <= 1'b0;
        wb_stb_i <= 1'b1;
        wb_cyc_i <= 1'b1;
    end
    else if(state == WAIT & wb_ack_o & ~wb_dat_o[8])begin
        wb_adr_i <= 5'h00;
        wb_dat_i <= 32'h00;
        wb_sel_i <= 4'b1111;
        wb_we_i <= 1'b0;
        wb_stb_i <= 1'b1;
        wb_cyc_i <= 1'b1;
    end
    else if(state == RDATA && wb_ack_o)begin
        wb_adr_i <= 5'h18;
        wb_dat_i <= 32'h00;
        wb_sel_i <= 4'b1111;
        wb_we_i <= 1'b1;
        wb_stb_i <= 1'b1;
        wb_cyc_i <= 1'b1;
    end
    else if(state == CLEAR && wb_ack_o)begin
        wb_adr_i <= 0;
        wb_dat_i <= 0;
        wb_sel_i <= 0;
        wb_we_i <= 0;
        wb_stb_i <= 0;
        wb_cyc_i <= 0;
    end
end

    assign                              in_pready                   = (state == RDATA) & wb_ack_o;
    assign                              in_prdata                   = ((state == RDATA) & wb_ack_o) ? {wb_dat_o[7:0],wb_dat_o[15:8],wb_dat_o[23:16],wb_dat_o[31:24]}:32'd0;
    assign                              in_pslverr                  = wb_err_o;

spi_top u0_spi_top (
    .wb_clk_i                           (clock                     ),
    .wb_rst_i                           (reset                     ),
    .wb_adr_i                           (wb_adr_i                  ),//in_paddr[4:0] 
    .wb_dat_i                           (wb_dat_i                  ),//in_pwdata     
    .wb_dat_o                           (wb_dat_o                  ),//in_prdata     
    .wb_sel_i                           (wb_sel_i                  ),//in_pstrb      
    .wb_we_i                            (wb_we_i                   ),//in_pwrite     
    .wb_stb_i                           (wb_stb_i                  ),//in_psel       
    .wb_cyc_i                           (wb_cyc_i                  ),//in_penable    
    .wb_ack_o                           (wb_ack_o                  ),//in_pready     
    .wb_err_o                           (wb_err_o                  ),//in_pslverr    
    .wb_int_o                           (wb_int_o                  ),

    .ss_pad_o                           (spi_ss                    ),
    .sclk_pad_o                         (spi_sck                   ),
    .mosi_pad_o                         (spi_mosi                  ),
    .miso_pad_i                         (spi_miso                  ) 
);

//`endif // FAST_FLASH

endmodule
