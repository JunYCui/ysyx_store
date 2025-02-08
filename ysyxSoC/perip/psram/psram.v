module psram(
    input                                  sck                        ,
    input                                  ce_n                       ,
    inout              [   3: 0]           dio                         
);
    typedef enum [2:0] {cmd_t,addr_t,wait_t,wdata_t,rdata_t,err_t} state_t;

    localparam                          spi_mode                   = 1'b0,
                                        qpi_mode                   = 1'b1;
    localparam  spi_qual_read  = 8'heb,
                spi_qual_write = 8'h38,
                qpi_qual_enter = 8'h35,
                qpi_qual_exit  = 8'hf5,
                qpi_qual_write = 8'h0b,
                qpi_qual_read  = 8'heb;
    wire                                reset                       ;
    reg                                 mode                        ;
    reg                [   5: 0]        count                       ;
    reg                [   7: 0]        psr     [2**24-1:0]  ;
    reg                [   2: 0]        state                       ;
    reg                [   2: 0]        next_state                  ;
    reg                [   7: 0]        cmd                         ;
    reg                [  23: 0]        addr                        ;
    reg                                 ctrl                        ;// 三态门的选择 
    wire               [   3: 0]        data_in                     ;
    wire               [   3: 0]        data_out                    ;
    reg                [   3: 0]        wdata                       ;

    assign                              data_in                     = dio;
    assign                              dio                         = ctrl? data_out:4'bz;
    assign                              data_out                    = ~count[0]? psr[addr][3:0]:psr[addr][7:4];
    assign                              reset                       = ce_n;
// 0xeb read 
// 0x38 write

    always @(posedge sck) begin
        if(count == 7 & state == cmd_t & cmd == qpi_qual_enter)
          mode <= qpi_mode;
        else if(count == 1 & mode == qpi_mode & cmd == qpi_qual_exit)
          mode <= spi_mode;
        else 
          mode <= mode;
    end
    always @(posedge sck or posedge reset) begin
          if(reset)
            state <= cmd_t;
          else
            state <= next_state ;
    end
    always @(*) begin
        if(reset)
          next_state = cmd_t;
        else begin
          case(state)
            cmd_t:
              if(mode == spi_mode)
                if(count == 7 & cmd != qpi_qual_enter)  
                  next_state = addr_t;
                else
                  next_state = cmd_t;
              else 
                if(count == 1 & cmd != qpi_qual_exit)
                  next_state = addr_t;
                else 
                  next_state = cmd_t;
            addr_t:
              if(mode == spi_mode)
                if(count == 13)
                  if(cmd == spi_qual_write)
                    next_state = wdata_t;
                  else if(cmd == spi_qual_read)
                    next_state = wait_t;
                  else
                    next_state = err_t;
                else
                  next_state = addr_t;
              else 
                if(count == 7)
                  if(cmd == qpi_qual_write || cmd ==qpi_qual_read)
                    next_state = wait_t;
                  else 
                    next_state = err_t;
                else 
                  next_state = state;
            wdata_t:
                next_state = state;
            wait_t:
                if(mode == spi_mode)
                  if(count == 20)
                    next_state = rdata_t;
                  else
                    next_state = wait_t;
                else 
                  if(cmd == qpi_qual_write & count ==11)
                      next_state = wdata_t;
                  else if(cmd == qpi_qual_read & count ==13)
                      next_state = rdata_t;
                  else 
                      next_state = state;
            rdata_t:
                next_state = state;
            err_t:begin
              next_state = state;
              $fatal();
            end
            default:
              next_state =state;
          endcase
        end
    end


    always @(posedge sck or posedge reset) begin
        if(reset)
          count <= 0;
        else
          count <= count + 1;
    end

    always @(posedge sck or posedge reset) begin
        if(reset)
          cmd <= 0;
        else if(state == cmd_t)
          if(mode == spi_mode)
            cmd <= {cmd[6:0],data_in[0]};
          else 
            cmd <= {cmd[3:0],data_in};
    end
    always @(posedge sck or posedge reset) begin
        if(reset)
          ctrl <= 0;
        else if(state == wait_t & count == 19)
          ctrl <= 1;
    end

    always @(posedge sck or posedge reset) begin
        if(reset)
          addr <= 0;
        else if(state == addr_t)
          addr <= {addr[19:0],data_in};
        else if(state == wdata_t & count[0])
          addr <= addr + 1;
        else if(state == rdata_t & ~count[0]) // addr + 1 per 2 counts
          addr <= addr + 1;
    end
    always @(posedge sck) begin
        if(state == wdata_t & ~count[0])begin
            wdata <= data_in;
        end
    end
    always @(posedge sck) begin
        if(state == wdata_t & count[0])
          psr[addr] <= {wdata,data_in};
    end






endmodule
