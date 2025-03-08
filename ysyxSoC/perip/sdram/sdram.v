// MT48LC64M4A2 – 16 Meg x 4 x 4 banks
// row address A0-A12
// bank address BA0 BA1
// column address A0-A9 A11
module sdram(
    input                               clk                        ,
    input                               cke                        ,// clk enable 
    input                               cs                         ,// chip select
    input                               ras                        ,// command input
    input                               cas                        ,// command input
    input                               we                         ,// command input
    input              [  12: 0]        a                          ,// address input
    input              [   1: 0]        ba                         ,// bank address
    input              [   1: 0]        dqm                        ,// mask signal
    inout              [  15: 0]        dq                          // data bus
);
    reg                [   2: 0]        cas_latency                 ;
    reg                [   2: 0]        burst_lenth                 ;
    reg                [   1: 0]        state                       ;
    reg                [   1: 0]        next_state                  ;
    reg                [  12: 0]        row_addr   [3:0]  ;
    reg                [   1: 0]        bank_addr                   ;
    reg                [  10: 0]        col_addr                    ;
    reg                [   2: 0]        counter                     ;
    reg                [   1: 0]        dqm_reg                     ;

    reg                [  15: 0]       ram[2**BankWidth-1:0][2**RowWidth-1:0][2**ColWidth-1:0]        ;
    
    wire                                active_cmd                  ;
    wire                                write_cmd                   ;
    wire                                read_cmd                    ;
    wire                                loadm_cmd                   ;

    reg                                 ctrl                        ;
    wire               [  15: 0]        data_in                     ;
    wire               [  15: 0]        data_out                    ;
    wire                                full,empty,pop      ;
    wire               [  10: 0]        col_fifo                    ;
    wire               [   1: 0]        ba_fifo                     ;
/******************state*************/
    localparam                          idle                       = 2'b00 ;
    localparam                          work_r                     = 2'b01 ;
    localparam                          work_w                     = 2'b10 ;
    localparam                          data_o                     = 2'b11 ;
/***************** ram *****************/
    localparam                          BankWidth                  = 2     ;
    localparam                          RowWidth                   = 13    ;
    localparam                          ColWidth                   = 11    ;

/* first step bank/row activation */
    assign                              active_cmd                  = ~cs & ~ras & cas & we;
    assign                              read_cmd                    = ~cs & ras & ~cas & we;
    assign                              write_cmd                   = ~cs & ras & ~cas & ~we;
    assign                              loadm_cmd                   = ~cs & ~ras & ~cas & ~we;
    assign                              dq                          = (~ctrl)? data_out : 16'bz;
    assign                              data_in                     = dq;

    always @(posedge clk or negedge cke) begin
        if (!cke)
          cas_latency <= 2;
        else if(loadm_cmd)
          cas_latency <= a[6:4] - 1;
        else
          cas_latency <= cas_latency;
    end
    always @(posedge clk or negedge cke) begin
        if(!cke)
          burst_lenth <= 0;
        else if(loadm_cmd)
          burst_lenth <= 2**a[2:0];
        else
          burst_lenth <= burst_lenth ;
    end
    always @(posedge clk or negedge cke) begin
        if(!cke)
          state <= idle;
        else
          state <= next_state;
    end
    always @(posedge clk or negedge cke) begin
        if(active_cmd)
          row_addr[ba] <= a;
    end
    always @(posedge clk or negedge cke) begin
        if(!cke)
          bank_addr <= 0;
        else if((counter == cas_latency + burst_lenth - 1))begin
            if(~empty)
              bank_addr <= ba_fifo;
            else if(read_cmd)
              bank_addr <= ba;
            else 
              bank_addr <= bank_addr; 
        end
        else if((state == idle)& (read_cmd | write_cmd))
          bank_addr <= ba;
    end
    always @(posedge clk or negedge cke) begin
        if(!cke)
          ctrl <= 1;
        else if(state == data_o & counter == cas_latency + burst_lenth - 1)
          ctrl <= 1;
        else if(state == work_r & counter == cas_latency - 1)
          ctrl <= 0;
    end
    always @(posedge clk or negedge cke ) begin
          if(!cke)
            counter <= 0;
          else if(counter == cas_latency + burst_lenth - 1)
            counter <= counter;
          else if( state == work_r | state == work_w | state == data_o )
            counter <= counter + 1;
          else
            counter <= 0;
    end
    always @(posedge clk or negedge cke ) begin
        if(!cke)
          state <= idle;
        else
          state <= next_state;
    end
    always @(*) begin
        case(state)
        idle:if(read_cmd)
                  next_state = work_r;
              else if(write_cmd & burst_lenth>1)
                  next_state = work_w;
              else
                  next_state = idle;
        work_r:if(counter == cas_latency-1)
                  next_state = data_o;
                else
                  next_state = work_r;
        work_w:if(counter == burst_lenth - 2)
                  next_state = idle;
                else
                  next_state = work_w;
        data_o:if(counter == cas_latency + burst_lenth - 1)
                  if(read_cmd)
                    next_state = data_o;
                  else if(empty)
                    next_state = idle;
                  else
                    next_state = data_o;
                else
                  next_state = state ;
        default:
                next_state = idle;
    endcase
    end

    always @(posedge clk) begin
        if(!cke)
          col_addr <= 0;
        else begin
          case(state)
          idle: if(read_cmd)
                  col_addr <= {a[11],a[9:0]};
                else if(write_cmd)
                  col_addr <= {a[11],a[9:0]};
                else 
                  col_addr <= col_addr;
          work_w:col_addr <= col_addr + 1;
          data_o:if((counter == cas_latency + burst_lenth - 1))begin
                      if(~empty)
                        col_addr <= col_fifo;
                      else if(read_cmd)
                        col_addr <= {a[11],a[9:0]};
                      else 
                        col_addr <= col_addr;
                  end
                 else
                    col_addr <= col_addr + 1;
          default: 
            col_addr <= col_addr;
          endcase
        end
    end
    always @(posedge clk) begin
        if(write_cmd& ~dqm[0])
          ram[ba][row_addr[ba]][{a[11],a[9:0]}][7:0] <= data_in[7:0];
        else if(state == work_w & ~dqm[0])
          ram[bank_addr][row_addr[bank_addr]][col_addr][7:0] <= data_in[7:0] ;
    end
    always @(posedge clk) begin
        if(write_cmd & ~dqm[1])
          ram[ba][row_addr[ba]][{a[11],a[9:0]}][15:8] <= data_in[15:8];
        else if(state == work_w & ~dqm[1])
          ram[bank_addr][row_addr[bank_addr]][col_addr][15:8] <= data_in[15:8] ;
    end


    assign                              data_out                    = ram[bank_addr][row_addr[bank_addr]][col_addr];
    assign                              pop                         = (state == data_o) && (counter == cas_latency + burst_lenth - 1);


fifo_r #(
    .Data_width                         (1                         ) 
)
cmd_fifo_r(
    .clock                              (clk                       ),
    .clr                                (cke                       ),
    .data_in                            (1'b1                      ),
    .push                               (read_cmd & (state!=idle) &~full),
    .pop                                (pop & ~empty              ),
    .data_out                           (                   ),
    .full                               (full                      ),
    .empty                              (empty                     ) 
);

fifo_r #(
    .Data_width                         (2                         ) 
)
ba_fifo_r(
    .clock                              (clk                       ),
    .clr                                (cke                       ),
    .data_in                            (ba                        ),
    .push                               (read_cmd & (state!=idle) &~full),
    .pop                                (pop & ~empty              ),
    .data_out                           (ba_fifo                   ),
    .full                               (                          ),
    .empty                              (                          ) 
);

fifo_r #(
    .Data_width                         (11                        ) 
)
col_fifo_r(
    .clock                              (clk                       ),
    .clr                                (cke                       ),
    .data_in                            ({a[11],a[9:0]}                        ),
    .push                               (read_cmd & (state!=idle) &~full),
    .pop                                (pop & ~empty              ),
    .data_out                           (col_fifo                  ),
    .full                               (                          ),
    .empty                              (                          ) 
);


endmodule


module fifo_r
#(
    parameter                           Data_width                 = 32    
)
(
    input                               clock                      ,
    input                               clr                        ,
    input              [Data_width-1: 0]        data_in                    ,
    input                               push                       ,
    input                               pop                        ,
    output             [Data_width-1: 0]        data_out                   ,
    output                              full                       ,
    output                              empty                       
);
    parameter                           Depth_Width                = 2     ;
    reg                [Depth_Width: 0]        r_ptr                       ;
    reg                [Depth_Width: 0]        w_ptr                       ;
    reg                [Data_width-1: 0]        fifo[2**Depth_Width-1:0]    ;

    always @(posedge clock or negedge clr) begin
        if(!clr)begin
          w_ptr <= 0;
        end
        else if(push)
          w_ptr <= w_ptr + 1;
    end
    always @(posedge clock or negedge clr) begin
        if(!clr)
          r_ptr <= 0;
        else if(pop)
          r_ptr <= r_ptr + 1;
    end
    always @(posedge clock) begin
        if(pop)
          fifo[w_ptr[Depth_Width-1:0]] <= data_in;
    end




    assign                              empty                       = r_ptr == w_ptr;
    assign                              full                        = (r_ptr[Depth_Width]!= w_ptr[Depth_Width]) & (r_ptr[Depth_Width-1:0] == w_ptr[Depth_Width-1:0]);
    assign                              data_out                    = fifo[r_ptr[Depth_Width-1:0]];
endmodule

