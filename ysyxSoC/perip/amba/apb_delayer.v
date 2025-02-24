module apb_delayer(
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

    output             [  31: 0]           out_paddr                  ,
    output                                 out_psel                   ,
    output                                 out_penable                ,
    output             [   2: 0]           out_pprot                  ,
    output                                 out_pwrite                 ,
    output             [  31: 0]           out_pwdata                 ,
    output             [   3: 0]           out_pstrb                  ,
    input                                  out_pready                 ,
    input              [  31: 0]           out_prdata                 ,
    input                                  out_pslverr                 
);
    parameter                           r                          = 3     ; // main frequency vs slave frequency
    parameter                           s                          = 4     ; //  ratio


    typedef enum logic [1:0] {
      IDLE = 2'b00,
      REQ  = 2'b01,
      WAIT = 2'b10
    } state_t;
    state_t state;
    reg                [   9: 0]        count                       ;
    reg                [  31: 0]        rdata_r                     ;
    reg                                 pready_r                    ;
    reg                                 pslverr_r                   ;
    wire                                req                         ;

    assign                              out_paddr                   = in_paddr;
    assign                              out_psel                    = in_psel;
    assign                              out_penable                 = in_penable;
    assign                              out_pprot                   = in_pprot;
    assign                              out_pwrite                  = in_pwrite;
    assign                              out_pwdata                  = in_pwdata;
    assign                              out_pstrb                   = in_pstrb;

    always @(posedge clock or posedge reset) begin
        if(reset)
          state <= IDLE;
        else begin
          case(state)
            IDLE:if(in_psel & in_paddr[31:28]>=4'ha & in_paddr[31:28] < 4'hc)
                      state <= REQ;
            REQ:if(out_pready)
                      state <= WAIT;
            WAIT:if(count == 0)
                      state <= IDLE;
            default: state <= IDLE;
        endcase
        end
    end

    always @(posedge clock or posedge reset) begin
        if(reset | state == IDLE)begin
          count <= 0;
        end
        else if(state == WAIT & |count) begin
          count <= count - 1;
        end
        else if(state == REQ & out_pready)begin
          count <= count >> $clog2(s) ;
        end
        else if(state == REQ)begin
          count <= count + (r<<$clog2(s)) ;
        end
    end
    always @(posedge clock or posedge reset) begin
        if(reset)begin
          pready_r <= 0;
          rdata_r  <= 0;
          pslverr_r<= 0;
        end
        else begin
          pready_r  <= (out_pready)? 1 : pready_r ;
          rdata_r   <= (out_pready)? out_prdata : rdata_r ;
          pslverr_r <= (out_pready)? out_pslverr : pslverr_r ;
        end
    end
    

    assign                              req                         = state == WAIT & count == 0;
    assign                              in_pready                   = (req)? pready_r :(state == IDLE)? out_pready :0;
    assign                              in_prdata                   = (req)? rdata_r  :(state == IDLE)? out_prdata :0;
    assign                              in_pslverr                  = (req)? pslverr_r:(state == IDLE)? out_pslverr :0;

endmodule
