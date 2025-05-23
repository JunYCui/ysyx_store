module axi4_delayer(
  input         clock,
  input         reset,

  output        in_arready,
  input         in_arvalid,
  input  [3:0]  in_arid,
  input  [31:0] in_araddr,
  input  [7:0]  in_arlen,
  input  [2:0]  in_arsize,
  input  [1:0]  in_arburst,
  input         in_rready,
  output        in_rvalid,
  output [3:0]  in_rid,
  output [31:0] in_rdata,
  output [1:0]  in_rresp,
  output        in_rlast,
  output        in_awready,
  input         in_awvalid,
  input  [3:0]  in_awid,
  input  [31:0] in_awaddr,
  input  [7:0]  in_awlen,
  input  [2:0]  in_awsize,
  input  [1:0]  in_awburst,
  output        in_wready,
  input         in_wvalid,
  input  [31:0] in_wdata,
  input  [3:0]  in_wstrb,
  input         in_wlast,
                in_bready,
  output        in_bvalid,
  output [3:0]  in_bid,
  output [1:0]  in_bresp,

  input         out_arready,
  output        out_arvalid,
  output [3:0]  out_arid,
  output [31:0] out_araddr,
  output [7:0]  out_arlen,
  output [2:0]  out_arsize,
  output [1:0]  out_arburst,
  output        out_rready,
  input         out_rvalid,
  input  [3:0]  out_rid,
  input  [31:0] out_rdata,
  input  [1:0]  out_rresp,
  input         out_rlast,
  input         out_awready,
  output        out_awvalid,
  output [3:0]  out_awid,
  output [31:0] out_awaddr,
  output [7:0]  out_awlen,
  output [2:0]  out_awsize,
  output [1:0]  out_awburst,
  input         out_wready,
  output        out_wvalid,
  output [31:0] out_wdata,
  output [3:0]  out_wstrb,
  output        out_wlast,
                out_bready,
  input         out_bvalid,
  input  [3:0]  out_bid,
  input  [1:0]  out_bresp
);

    parameter                           r                          = 4     ; // main frequency vs slave frequency
    parameter                           s                          = 8     ; //  ratio


  localparam IDLE = 2'b00;
  localparam REQ = 2'b01;
  localparam READ = 2'b10;
  localparam WRITE = 2'b11;

  reg [1:0] state;
  reg [9:0] count;
  reg [9:0] burst_count;
  reg [31:0] ram [7:0];
  reg [3:0] bid;
  reg [3:0] rid;

  assign in_arready = out_arready;
  assign out_arvalid = in_arvalid;
  assign out_arid = in_arid;
  assign out_araddr = in_araddr;
  assign out_arlen = in_arlen;
  assign out_arsize = in_arsize;
  assign out_arburst = in_arburst;

  assign in_awready = out_awready;
  assign out_awvalid = in_awvalid;
  assign out_awid = in_awid;
  assign out_awaddr = in_awaddr;
  assign out_awlen = in_awlen;
  assign out_awsize = in_awsize;
  assign out_awburst = in_awburst;

  assign in_wready = out_wready;
  assign out_wvalid = in_wvalid;
  assign out_wdata = in_wdata;
  assign out_wstrb = in_wstrb;
  assign out_wlast = in_wlast;


  always @(posedge clock or posedge reset) begin
      if(reset)
        state <= IDLE;
      else 
        case(state)
        IDLE: if(((in_arready & out_arvalid) | (in_awready & out_awvalid))& ((in_araddr[31:28]>=4'ha & in_araddr[31:28] < 4'hc) | (in_awaddr[31:28]>=4'ha & in_awaddr[31:28] < 4'hc)))
                      state <= REQ;
              else 
                      state <= IDLE;
        REQ:  if((out_rvalid & out_rlast & in_rready))
                      state <= READ;
              else if((out_bvalid & in_bready))
                      state <= WRITE;
              else
                      state <= REQ;
        READ:if(count == 1)
                      state <= IDLE;
              else 
                      state <= READ;
        WRITE:if(count == 1)
                      state <= IDLE;
              else 
                      state <= WRITE;
        endcase
  end

  always @(posedge clock or posedge reset) begin
      if(reset)
        burst_count <= 0;
      else if(state == IDLE)
        burst_count <= 0;
      else if(out_rvalid & out_rready)
        burst_count <= burst_count + 1;
  end

    always @(posedge clock or posedge reset) begin
        if(reset | state == IDLE)begin
          count <= 0;
        end
        else if(state == READ || state == WRITE) begin
          count <= count - 1;
        end
        else if(state == REQ & ((out_rvalid & out_rlast & out_rready) | (out_bvalid & out_bready)))begin
          count <= ((count + (r<<$clog2(s))) >> $clog2(s)) - 1 ;
        end
        else if(state == REQ)begin
          count <= count + (r<<$clog2(s)) ;
        end
    end

    always @(posedge clock) begin
        if(state == REQ & out_rvalid & out_rready)
            ram[burst_count[2:0]] <= out_rdata;
    end

  always @(posedge clock) begin
      if((state == REQ) & (out_bvalid & out_bready) )
          bid <= out_bid;
  end

  always @(posedge clock) begin
      if((state == REQ) & (out_rvalid & in_rready & out_rlast) )
          rid <= out_bid;
  end

  assign out_bready = (state == IDLE)? in_bready : (state == REQ)? 1'b1:1'b0;

  assign in_bvalid = (state == IDLE)? out_bvalid :(state == WRITE && count == 1)? 1'b1:1'b0 ;
  assign in_bid = (state == WRITE && count == 1)? bid:out_bid ;
  assign in_bresp = out_bresp;

  assign out_rready = (state == IDLE)? in_rready : 1'b1;
  assign in_rvalid =(state == IDLE)? out_rvalid : (state == READ && (burst_count >= count))? 1'b1:1'b0;
  assign in_rid = (state == READ && (burst_count >= count))? rid:out_rid;
  assign in_rdata = (state == READ && (burst_count >= count))? ram[burst_count[2:0]-count[2:0]] : out_rdata ;
  assign in_rresp = out_rresp;
  assign in_rlast = (state == IDLE)? out_rlast :(state == READ && count == 1)? 1'b1:1'b0 ;;


endmodule
