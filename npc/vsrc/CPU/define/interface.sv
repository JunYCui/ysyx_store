`ifndef INTERFACE_SV
`define INTERFACE_SV

interface axi4_if #(
    parameter ADDR_WIDTH = 32,
    parameter DATA_WIDTH = 32,
    parameter ID_WIDTH  = 1
);

    // 写地址通道 (AW)
    logic [ID_WIDTH-1:0]     awid;
    logic [ADDR_WIDTH-1:0]   awaddr;
    logic [7:0]              awlen;     // 突发长度
    logic [2:0]              awsize;    // 突发大小
    logic [1:0]              awburst;   // 突发类型
    logic                    awvalid;   // 写地址有效
    logic                    awready;   // 写地址准备
    
    // 写数据通道 (W)
    logic [DATA_WIDTH-1:0]   wdata;
    logic [(DATA_WIDTH/8)-1:0] wstrb;   // 字节选通
    logic                    wlast;     // 最后传输指示
    logic                    wvalid;    // 写数据有效
    logic                    wready;    // 写数据准备
    
    // 写响应通道 (B)
    logic [ID_WIDTH-1:0]     bid;
    logic [1:0]              bresp;     // 写响应
    logic                    bvalid;    // 写响应有效
    logic                    bready;    // 写响应准备
    
    // 读地址通道 (AR)
    logic [ID_WIDTH-1:0]     arid;
    logic [ADDR_WIDTH-1:0]   araddr;
    logic [7:0]              arlen;     // 突发长度
    logic [2:0]              arsize;    // 突发大小
    logic [1:0]              arburst;   // 突发类型
    logic                    arvalid;   // 读地址有效
    logic                    arready;   // 读地址准备
    
    // 读数据通道 (R)
    logic [ID_WIDTH-1:0]     rid;
    logic [DATA_WIDTH-1:0]   rdata;
    logic [1:0]              rresp;     // 读响应
    logic                    rlast;     // 最后传输指示
    logic                    rvalid;    // 读数据有效
    logic                    rready;    // 读数据准备
    
    // Modport定义 - 主设备(Master)视图
    modport master (
        
        // 写地址通道
        output awid, awaddr, awlen, awsize, awburst, 
        output awvalid,
        input  awready,
        
        // 写数据通道
        output wdata, wstrb, wlast,
        output wvalid,
        input  wready,
        
        // 写响应通道
        input  bid, bresp,
        input  bvalid,
        output bready,
        
        // 读地址通道
        output arid, araddr, arlen, arsize, arburst, 
        output arvalid,
        input  arready,
        
        // 读数据通道
        input  rid, rdata, rresp, rlast, 
        input  rvalid,
        output rready
    );
    
    // Modport定义 - 从设备(Slave)视图
    modport slave (    
        // 写地址通道
        input  awid, awaddr, awlen, awsize, awburst, 
        input  awvalid,
        output awready,
        
        // 写数据通道
        input  wdata, wstrb, wlast, 
        input  wvalid,
        output wready,
        
        // 写响应通道
        output bid, bresp,
        output bvalid,
        input  bready,
        
        // 读地址通道
        input  arid, araddr, arlen, arsize, arburst, 
        input  arvalid,
        output arready,
        
        // 读数据通道
        output rid, rdata, rresp, rlast,
        output rvalid,
        input  rready
    );
    



endinterface



`endif

