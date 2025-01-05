`include "./vsrc/CPU/define/para.v"

module Aribiter #(
    parameter                    DATA_WIDTH                = 32    ,
    parameter                    ADDR_WIDTH                = 32    
)(
    input                        clk                        ,
    input                        rst_n                      ,
    
    input                        IFU_req                    ,
    input                        LSU_req                    ,

    input              [ADDR_WIDTH-1: 0]IFU_araddr          ,
    input                        IFU_arvalid                ,
    output reg                   IFU_arready                ,

    input                        IFU_rready                 ,
    output reg         [DATA_WIDTH-1: 0]IFU_rdata           ,
    output reg                   IFU_rresp                  ,
    output                       IFU_rvalid                 ,

    input              [ADDR_WIDTH-1: 0]IFU_awaddr          ,
    input                        IFU_awvalid                ,
    output                       IFU_awready                ,
    
    input              [DATA_WIDTH-1: 0]IFU_wdata           ,
    input              [   7: 0] IFU_wstrb                  ,
    input                        IFU_wvalid                 ,
    output                       IFU_wready                 ,
    
    output                       IFU_bresp                  ,
    output                       IFU_bvalid                 ,
    input                        IFU_bready                 ,

    input              [ADDR_WIDTH-1: 0]LSU_araddr          ,
    input                        LSU_arvalid                ,
    output reg                   LSU_arready                ,

    input                        LSU_rready                 ,
    output reg         [DATA_WIDTH-1: 0]LSU_rdata           ,
    output reg                   LSU_rresp                  ,
    output                       LSU_rvalid                 ,

    input              [ADDR_WIDTH-1: 0]LSU_awaddr          ,
    input                        LSU_awvalid                ,
    output                       LSU_awready                ,
    
    input              [DATA_WIDTH-1: 0]LSU_wdata           ,
    input              [   7: 0] LSU_wstrb                  ,
    input                        LSU_wvalid                 ,
    output                       LSU_wready                 ,
    
    output                       LSU_bresp                  ,
    output                       LSU_bvalid                 ,
    input                        LSU_bready                 ,

    output             [ADDR_WIDTH-1: 0]araddr              ,
    output                       arvalid                    ,
    input                        arready                    ,
    
    output                       rready                     ,
    input              [DATA_WIDTH-1: 0]rdata               ,
    input                        rresp                      ,
    input                       rvalid                     ,

    output              [ADDR_WIDTH-1: 0]awaddr              ,
    output                        awvalid                    ,
    input                        awready                    ,

    output             [DATA_WIDTH-1: 0]wdata               ,
    output             [   7: 0] wstrb                      ,
    output                       wvalid                     ,
    input                        wready                     ,

    input                        bresp                      ,
    input                        bvalid                     ,
    output                       bready                      



);

    reg                [   1: 0] ari_choice                 ;

    always @(posedge clk) begin
        if(!rst_n)
            ari_choice <= `Aribiter_choice_IDLE_ysyx_24100029;
        else if(ari_choice == `Aribiter_choice_IDLE_ysyx_24100029)begin
            if(LSU_req)
                ari_choice <= `Aribiter_choice_LSU_ysyx_24100029;
            else if(IFU_req)
                ari_choice <= `Aribiter_choice_IFU_ysyx_24100029;
            else    
                ari_choice <= ari_choice;
        end
        else if(ari_choice == `Aribiter_choice_IFU_ysyx_24100029)begin
            if(LSU_req & (rvalid | bvalid))
                ari_choice <= `Aribiter_choice_LSU_ysyx_24100029;
            else if(IFU_req & (rvalid | bvalid))
                ari_choice <= `Aribiter_choice_IFU_ysyx_24100029;
            else if(rvalid | bvalid)
                ari_choice <= `Aribiter_choice_IDLE_ysyx_24100029;
        end
        else if(ari_choice == `Aribiter_choice_LSU_ysyx_24100029)begin
            if(IFU_req & (rvalid | bvalid))
                ari_choice <= `Aribiter_choice_LSU_ysyx_24100029;
            else if(LSU_req & (rvalid | bvalid))
                ari_choice <= `Aribiter_choice_IFU_ysyx_24100029;
            else if(rvalid | bvalid)
                ari_choice <= `Aribiter_choice_IDLE_ysyx_24100029;
        end
    end


    always @(*) begin
        if(ari_choice == `Aribiter_choice_IFU_ysyx_24100029)begin
            araddr = IFU_araddr;
            arvalid = IFU_arvalid;
            IFU_arready = arready;
            LSU_arready = 0;
            rready = IFU_rready;
            LSU_rdata = 0;

            IFU_rdata = rdata;
            LSU_rresp = 0;
            IFU_rresp = rresp;
            LSU_rvalid = 0;
            IFU_rvalid = rvalid;
            
            awaddr = IFU_awaddr;
            awvalid = IFU_awvalid;
            LSU_awready = 0;
            IFU_awready = awready;

            wdata = IFU_wdata;
            wstrb = IFU_wstrb;
            wvalid = IFU_wvalid;
            LSU_wready = 0;
            IFU_wready = wready;
            
            LSU_bresp = 0;
            IFU_bresp = bresp;
            LSU_bvalid = 0;
            IFU_bvalid = bvalid;
            bready = IFU_bready;
        end
        else if(ari_choice == `Aribiter_choice_LSU_ysyx_24100029)   begin
            araddr = LSU_araddr;
            arvalid = LSU_arvalid;
            LSU_arready = arready;
            IFU_arready = 0;
            rready = LSU_rready;
            LSU_rdata = rdata;
            IFU_rdata = 0;
            LSU_rresp = rresp;
            IFU_rresp = 0;
            LSU_rvalid = rvalid;
            IFU_rvalid = 0;
            awaddr = LSU_awaddr;
            awvalid = LSU_awvalid;
            IFU_awready = 0;
            LSU_awready = awready;
            wdata = LSU_wdata;
            wstrb = LSU_wstrb;
            wvalid = LSU_wvalid;
            IFU_wready = 0;
            LSU_wready = wready;
            IFU_wready = 0;
            LSU_bresp = bresp;
            IFU_bresp = 0;
            IFU_bvalid = 0;
            LSU_bvalid = bvalid;
            bready = LSU_bready;
        end
        else begin
            araddr = 0;
            arvalid = 0;
            LSU_arready = 0;
            IFU_arready = 0;
            rready = 0;
            LSU_rdata = 0;
            IFU_rdata = 0;
            LSU_rresp = 0;
            IFU_rresp = 0;
            LSU_rvalid = 0;
            IFU_rvalid = 0;
            awaddr = 0;
            awvalid = 0;
            IFU_awready = 0;
            LSU_awready = 0;
            wdata = 0;
            wstrb = 0;
            wvalid = 0;
            IFU_wready = 0;
            LSU_wready = 0;
            IFU_wready = 0;
            LSU_bresp = 0;
            IFU_bresp = 0;
            IFU_bvalid = 0;
            LSU_bvalid = 0;
            bready = 0;
        end

    end


    
endmodule                                                           //Aribiter
