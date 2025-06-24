`include "../define/para.sv"
`include "../define/interface.sv"

module ysyx_24100029_Aribiter (
    input                               clock,
    input                               reset,
    
    input                               IFU_req,
    input                               LSU_req,

    axi4_if.slave                       ifu_axi,
    axi4_if.slave                       lsu_axi,
    axi4_if.master                      aribiter_axi
);

    localparam IFU  = 2'b10;
    localparam LSU  = 2'b01;
    localparam IDLE = 2'b00;

    wire [1:0] req;
    wire [1:0] choice;
    reg [1:0] state;

    // 状态机
    always @(posedge clock) begin
        if (reset) begin
            state <= IDLE;
        end
        else begin
            case (state)
                IDLE: begin
                    // 当任意通道的地址握手完成时转换状态
                    if ((aribiter_axi.awready && aribiter_axi.awvalid) || 
                        (aribiter_axi.arready && aribiter_axi.arvalid)) begin
                        state <= choice;
                    end
                end
                IFU: begin
                    // IFU读事务完成时返回IDLE
                    if (aribiter_axi.rvalid && aribiter_axi.rlast && aribiter_axi.rready) begin
                        state <= IDLE;
                    end
                end
                LSU: begin
                    // LSU读事务或写响应完成时返回IDLE
                    if ((aribiter_axi.rvalid && aribiter_axi.rlast && aribiter_axi.rready) || 
                        (aribiter_axi.bvalid && aribiter_axi.bready)) begin
                        state <= IDLE;
                    end
                end
                default: state <= IDLE;
            endcase
        end
    end

    // 请求优先级编码
    assign req = {IFU_req, LSU_req};
    assign choice = req & ~(req - 1);  // 找出最低位的1

    // 主仲裁逻辑
    always @(*) begin
        // 默认值
        ifu_axi.awready = 0;
        lsu_axi.awready = 0;
        ifu_axi.wready = 0;
        lsu_axi.wready = 0;
        ifu_axi.bvalid = 0;
        ifu_axi.bresp = 0;
        ifu_axi.bid = 0;
        lsu_axi.bvalid = 0;
        lsu_axi.bresp = 0;
        lsu_axi.bid = 0;
        ifu_axi.arready = 0;
        lsu_axi.arready = 0;
        ifu_axi.rvalid = 0;
        ifu_axi.rresp = 0;
        ifu_axi.rdata = 0;
        ifu_axi.rlast = 0;
        ifu_axi.rid = 0;
        lsu_axi.rvalid = 0;
        lsu_axi.rresp = 0;
        lsu_axi.rdata = 0;
        lsu_axi.rlast = 0;
        lsu_axi.rid = 0;

        aribiter_axi.awvalid = 0;
        aribiter_axi.awaddr = 0;
        aribiter_axi.awid = 0;
        aribiter_axi.awlen = 0;
        aribiter_axi.awsize = 0;
        aribiter_axi.awburst = 0;
        aribiter_axi.wvalid = 0;
        aribiter_axi.wdata = 0;
        aribiter_axi.wstrb = 0;
        aribiter_axi.wlast = 0;
        aribiter_axi.bready = 0;
        aribiter_axi.arvalid = 0;
        aribiter_axi.araddr = 0;
        aribiter_axi.arid = 0;
        aribiter_axi.arlen = 0;
        aribiter_axi.arsize = 0;
        aribiter_axi.arburst = 0;
        aribiter_axi.rready = 0;

        if (state == IDLE) begin
            case (choice)
                LSU: begin  // LSU优先级高
                    // 写地址通道
                    lsu_axi.awready = aribiter_axi.awready;
                    aribiter_axi.awvalid = lsu_axi.awvalid;
                    aribiter_axi.awaddr = lsu_axi.awaddr;
                    aribiter_axi.awid = lsu_axi.awid;
                    aribiter_axi.awlen = lsu_axi.awlen;
                    aribiter_axi.awsize = lsu_axi.awsize;
                    aribiter_axi.awburst = lsu_axi.awburst;

                    // 读地址通道
                    lsu_axi.arready = aribiter_axi.arready;
                    aribiter_axi.arvalid = lsu_axi.arvalid;
                    aribiter_axi.araddr = lsu_axi.araddr;
                    aribiter_axi.arid = lsu_axi.arid;
                    aribiter_axi.arlen = lsu_axi.arlen;
                    aribiter_axi.arsize = lsu_axi.arsize;
                    aribiter_axi.arburst = lsu_axi.arburst;
                    
                end
                IFU: begin  // IFU请求
                    // 写地址通道
                    ifu_axi.awready = aribiter_axi.awready;
                    aribiter_axi.awvalid = ifu_axi.awvalid;
                    aribiter_axi.awaddr = ifu_axi.awaddr;
                    aribiter_axi.awid = ifu_axi.awid;
                    aribiter_axi.awlen = ifu_axi.awlen;
                    aribiter_axi.awsize = ifu_axi.awsize;
                    aribiter_axi.awburst = ifu_axi.awburst;

                    // 读地址通道
                    ifu_axi.arready = aribiter_axi.arready;
                    aribiter_axi.arvalid = ifu_axi.arvalid;
                    aribiter_axi.araddr = ifu_axi.araddr;
                    aribiter_axi.arid = ifu_axi.arid;
                    aribiter_axi.arlen = ifu_axi.arlen;
                    aribiter_axi.arsize = ifu_axi.arsize;
                    aribiter_axi.arburst = ifu_axi.arburst;

                end
                default: begin
                    // IDLE状态下无请求，保持所有接口空闲
                end
            endcase
        end
        else begin  // 非IDLE状态保持当前选择
            case (state)
                LSU: begin
                    // 写地址通道
                    lsu_axi.awready = aribiter_axi.awready;
                    aribiter_axi.awvalid = lsu_axi.awvalid;
                    aribiter_axi.awaddr = lsu_axi.awaddr;
                    aribiter_axi.awid = lsu_axi.awid;
                    aribiter_axi.awlen = lsu_axi.awlen;
                    aribiter_axi.awsize = lsu_axi.awsize;
                    aribiter_axi.awburst = lsu_axi.awburst;

                    // 写数据通道
                    lsu_axi.wready = aribiter_axi.wready;
                    aribiter_axi.wvalid = lsu_axi.wvalid;
                    aribiter_axi.wdata = lsu_axi.wdata;
                    aribiter_axi.wstrb = lsu_axi.wstrb;
                    aribiter_axi.wlast = lsu_axi.wlast;
                    
                    // 写响应通道
                    aribiter_axi.bready = lsu_axi.bready;
                    lsu_axi.bvalid = aribiter_axi.bvalid;
                    lsu_axi.bresp = aribiter_axi.bresp;
                    lsu_axi.bid = aribiter_axi.bid;

                    // 读地址通道
                    lsu_axi.arready = aribiter_axi.arready;
                    aribiter_axi.arvalid = lsu_axi.arvalid;
                    aribiter_axi.araddr = lsu_axi.araddr;
                    aribiter_axi.arid = lsu_axi.arid;
                    aribiter_axi.arlen = lsu_axi.arlen;
                    aribiter_axi.arsize = lsu_axi.arsize;
                    aribiter_axi.arburst = lsu_axi.arburst;
                    
                    // 读数据通道
                    aribiter_axi.rready = lsu_axi.rready;
                    lsu_axi.rvalid = aribiter_axi.rvalid;
                    lsu_axi.rresp = aribiter_axi.rresp;
                    lsu_axi.rdata = aribiter_axi.rdata;
                    lsu_axi.rlast = aribiter_axi.rlast;
                    lsu_axi.rid = aribiter_axi.rid;
                end
                IFU: begin
                    // 写地址通道
                    ifu_axi.awready = aribiter_axi.awready;
                    aribiter_axi.awvalid = ifu_axi.awvalid;
                    aribiter_axi.awaddr = ifu_axi.awaddr;
                    aribiter_axi.awid = ifu_axi.awid;
                    aribiter_axi.awlen = ifu_axi.awlen;
                    aribiter_axi.awsize = ifu_axi.awsize;
                    aribiter_axi.awburst = ifu_axi.awburst;

                    // 写数据通道
                    ifu_axi.wready = aribiter_axi.wready;
                    aribiter_axi.wvalid = ifu_axi.wvalid;
                    aribiter_axi.wdata = ifu_axi.wdata;
                    aribiter_axi.wstrb = ifu_axi.wstrb;
                    aribiter_axi.wlast = ifu_axi.wlast;

                    // 写响应通道
                    aribiter_axi.bready = ifu_axi.bready;
                    ifu_axi.bvalid = aribiter_axi.bvalid;
                    ifu_axi.bresp = aribiter_axi.bresp;
                    ifu_axi.bid = aribiter_axi.bid;

                    // 读地址通道
                    ifu_axi.arready = aribiter_axi.arready;
                    aribiter_axi.arvalid = ifu_axi.arvalid;
                    aribiter_axi.araddr = ifu_axi.araddr;
                    aribiter_axi.arid = ifu_axi.arid;
                    aribiter_axi.arlen = ifu_axi.arlen;
                    aribiter_axi.arsize = ifu_axi.arsize;
                    aribiter_axi.arburst = ifu_axi.arburst;

                    // 读数据通道
                    aribiter_axi.rready = ifu_axi.rready;
                    ifu_axi.rvalid = aribiter_axi.rvalid;
                    ifu_axi.rresp = aribiter_axi.rresp;
                    ifu_axi.rdata = aribiter_axi.rdata;
                    ifu_axi.rlast = aribiter_axi.rlast;
                    ifu_axi.rid = aribiter_axi.rid;
                end
                default: begin
                    // 保持空闲状态
                end
            endcase
        end
    end
    
endmodule  // ysyx_24100029_Aribiter
