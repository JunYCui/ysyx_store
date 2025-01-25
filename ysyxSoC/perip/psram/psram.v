module psram(
    input                                  sck                        ,
    input                                  ce_n                       ,
    inout              [   3: 0]           dio                         
);
    typedef enum [2:0] {cmd_t,addr_t,wait_t,wdata_t,rdata_t,err_t} state_t;
    
    wire                                reset                       ;
    reg                [   5: 0]        count                       ;
    reg                [   7: 0]        psr        [2**24-1:0]  ;
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
    assign                              data_out                    = count[0]? psr[addr][3:0]:psr[addr][7:4];
// 0xeb read 
// 0x38 write
    initial begin
      $monitor("addr =0x%x",addr);
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
              if(count == 7)
                next_state = addr_t;
              else
                next_state = cmd_t;
            addr_t:
              if(count == 13)
                if(cmd == 8'h38)
                  next_state = wdata_t;
                else if(cmd == 8'heb)
                  next_state = wait_t;
                else
                  next_state = err_t;
              else
                next_state = addr_t;
            wdata_t:
                next_state = state;
            wait_t:
                if(count == 19)
                  next_state = rdata_t;
                else
                  next_state = wait_t;
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
          cmd <= {cmd[6:0],data_in[0]};
    end
    always @(posedge sck or posedge reset) begin
        if(reset)
          ctrl <= 0;
        else if(state == rdata_t)
          ctrl <= 1;
    end

    always @(posedge sck or posedge reset) begin
        if(reset)
          addr <= 0;
        else if(state == addr_t)
          addr <= {addr[19:0],data_in};
        else if(state == wdata_t & count[0])
          addr <= addr + 1;
        else if(state == rdata_t & count[0])
          addr <= addr + 1;
    end
    always @(posedge sck) begin
        if(state == wdata_t)begin
          if(count[0] == 0)
            wdata <= data_in;
        end
    end
    always @(posedge sck) begin
        if(state == wdata_t & count[0])
          psr[addr] <= {wdata,data_in};
    end






endmodule
