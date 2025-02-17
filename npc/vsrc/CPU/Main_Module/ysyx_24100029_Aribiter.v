`include "./vsrc/CPU/define/para.v"
//`include "/home/cjy/ysyx-workbench/npc/vsrc/CPU/define/para.v"

module ysyx_24100029_Aribiter #(
    parameter                    DATA_WIDTH                = 32    ,
    parameter                    ADDR_WIDTH                = 32    
)(
    input                        clock                      ,
    input                        reset                      ,
    
    input                        IFU_req                    ,
    input                        LSU_req                    ,

    input              [ADDR_WIDTH-1: 0]IFU_araddr          ,
    input                        IFU_arvalid                ,
    output reg                   IFU_arready                ,
    input              [   3: 0] IFU_arid                   ,
    input              [   7: 0] IFU_arlen                  ,
    input              [   2: 0] IFU_arsize                 ,
    input              [   1: 0] IFU_arburst                ,

    input                        IFU_rready                 ,
    output reg         [DATA_WIDTH-1: 0]IFU_rdata           ,
    output reg         [   1: 0] IFU_rresp                  ,
    output reg                   IFU_rvalid                 ,
    output reg                   IFU_rlast                  ,
    output reg         [   3: 0] IFU_rid                    ,


    input              [ADDR_WIDTH-1: 0]IFU_awaddr          ,
    input                        IFU_awvalid                ,
    output                       IFU_awready                ,
    input              [   3: 0] IFU_awid                   ,
    input              [   7: 0] IFU_awlen                  ,
    input              [   2: 0] IFU_awsize                 ,
    input              [   1: 0] IFU_awburst                ,

    input              [DATA_WIDTH-1: 0]IFU_wdata           ,
    input              [   3: 0] IFU_wstrb                  ,
    input                        IFU_wvalid                 ,
    output                       IFU_wready                 ,
    input                        IFU_wlast                  ,

    output             [   1: 0] IFU_bresp                  ,
    output                       IFU_bvalid                 ,
    input                        IFU_bready                 ,
    output             [   3: 0] IFU_bid                    ,

    input              [ADDR_WIDTH-1: 0]LSU_araddr          ,
    input                        LSU_arvalid                ,
    output reg                   LSU_arready                ,
    input              [   3: 0] LSU_arid                   ,
    input              [   7: 0] LSU_arlen                  ,
    input              [   2: 0] LSU_arsize                 ,
    input              [   1: 0] LSU_arburst                ,


    input                        LSU_rready                 ,
    output reg         [DATA_WIDTH-1: 0]LSU_rdata           ,
    output reg         [   1: 0] LSU_rresp                  ,
    output reg                   LSU_rvalid                 ,
    output reg                   LSU_rlast                  ,
    output reg         [   3: 0] LSU_rid                    ,

    input              [ADDR_WIDTH-1: 0]LSU_awaddr          ,
    input                        LSU_awvalid                ,
    output                       LSU_awready                ,
    input              [   3: 0] LSU_awid                   ,
    input              [   7: 0] LSU_awlen                  ,
    input              [   2: 0] LSU_awsize                 ,
    input              [   1: 0] LSU_awburst                ,
    
    input              [DATA_WIDTH-1: 0]LSU_wdata           ,
    input              [   3: 0] LSU_wstrb                  ,
    input                        LSU_wvalid                 ,
    output                       LSU_wready                 ,
    input                        LSU_wlast                  ,
    
    output             [   1: 0] LSU_bresp                  ,
    output                       LSU_bvalid                 ,
    input                        LSU_bready                 ,
    output             [   3: 0] LSU_bid                    ,

    input                        awready                    ,
    output                       awvalid                    ,
    output             [  31: 0] awaddr                     ,
    output             [   3: 0] awid                       ,
    output             [   7: 0] awlen                      ,
    output             [   2: 0] awsize                     ,
    output             [   1: 0] awburst                    ,

    input                        wready                     ,
    output                       wvalid                     ,
    output             [  31: 0] wdata                      ,
    output             [   3: 0] wstrb                      ,
    output                       wlast                      ,

    output                       bready                     ,
    input                        bvalid                     ,
    input              [   1: 0] bresp                      ,
    input              [   3: 0] bid                        ,
    
    input                        arready                    ,
    output                       arvalid                    ,
    output             [  31: 0] araddr                     ,
    output             [   3: 0] arid                       ,
    output             [   7: 0] arlen                      ,
    output             [   2: 0] arsize                     ,
    output             [   1: 0] arburst                    ,

    output                       rready                     ,
    input                        rvalid                     ,
    input              [   1: 0] rresp                      ,
    input              [  31: 0] rdata                      ,
    input                        rlast                      ,
    input              [   3: 0] rid                         
    
    

);

    reg                [   1: 0] ari_choice                 ;

    always @(posedge clock) begin
        if(reset)
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
            else if(rvalid | bvalid)
                ari_choice <= `Aribiter_choice_IDLE_ysyx_24100029;
        end
        else if(ari_choice == `Aribiter_choice_LSU_ysyx_24100029)begin
            if(IFU_req & (rvalid | bvalid))
                ari_choice <= `Aribiter_choice_IFU_ysyx_24100029;
            else if(rvalid | bvalid)
                ari_choice <= `Aribiter_choice_IDLE_ysyx_24100029;
        end
    end


    always @(*) begin
        if(ari_choice == `Aribiter_choice_IFU_ysyx_24100029)begin
            IFU_awready =awready;
            LSU_awready = 0;
            awvalid = IFU_awvalid ;
            awaddr  = IFU_awaddr  ;
            awid    = IFU_awid    ;
            awlen   = IFU_awlen   ;
            awsize  = IFU_awsize  ;
            awburst = IFU_awburst ;

            IFU_wready = wready;
            LSU_wready = 0;
            wvalid  = IFU_wvalid ;
            wdata   = IFU_wdata  ;
            wstrb   = IFU_wstrb  ;
            wlast   = IFU_wlast  ;
            
            bready  = IFU_bready;
            IFU_bvalid = bvalid;
            IFU_bresp  = bresp ;
            IFU_bid    = bid   ;
            LSU_bvalid = 0     ;
            LSU_bresp  = 0     ;
            LSU_bid    = 0     ;

            IFU_arready = arready;
            LSU_arready = 0;
            arvalid = IFU_arvalid ;
            araddr  = IFU_araddr  ;
            arid    = IFU_arid    ;
            arlen   = IFU_arlen   ;
            arsize  = IFU_arsize  ;
            arburst = IFU_arburst ;
            
            rready  = IFU_rready;
            IFU_rvalid = rvalid;
            IFU_rresp  = rresp ;
            IFU_rdata  = rdata ;
            IFU_rlast  = rlast ;
            IFU_rid    = rid   ;
            LSU_rvalid = 0;
            LSU_rresp  = 0;
            LSU_rdata  = 0;
            LSU_rlast  = 0;
            LSU_rid    = 0;
        end
        else if(ari_choice == `Aribiter_choice_LSU_ysyx_24100029)   begin
            LSU_awready =awready;
            IFU_awready = 0;
            awvalid = LSU_awvalid ;
            awaddr  = LSU_awaddr  ;
            awid    = LSU_awid    ;
            awlen   = LSU_awlen   ;
            awsize  = LSU_awsize  ;
            awburst = LSU_awburst ;

            LSU_wready = wready;
            IFU_wready = 0;
            wvalid  = LSU_wvalid ;
            wdata   = LSU_wdata  ;
            wstrb   = LSU_wstrb  ;
            wlast   = LSU_wlast  ;
            
            bready  = LSU_bready;
            LSU_bvalid = bvalid;
            LSU_bresp  = bresp ;
            LSU_bid    = bid   ;
            IFU_bvalid = 0     ;
            IFU_bresp  = 0     ;
            IFU_bid    = 0     ;

            LSU_arready = arready;
            IFU_arready = 0;
            arvalid = LSU_arvalid ;
            araddr  = LSU_araddr  ;
            arid    = LSU_arid    ;
            arlen   = LSU_arlen   ;
            arsize  = LSU_arsize  ;
            arburst = LSU_arburst ;
            
            rready  = LSU_rready;
            LSU_rvalid = rvalid;
            LSU_rresp  = rresp ;
            LSU_rdata  = rdata ;
            LSU_rlast  = rlast ;
            LSU_rid    = rid   ;
            IFU_rvalid = 0;
            IFU_rresp  = 0;
            IFU_rdata  = 0;
            IFU_rlast  = 0;
            IFU_rid    = 0;
        end
        else begin
            LSU_awready =0;
            IFU_awready = 0;
            awvalid = 0 ;
            awaddr  = 0 ;
            awid    = 0 ;
            awlen   = 0 ;
            awsize  = 0 ;
            awburst = 0 ;
            LSU_wready = 0;
            IFU_wready = 0;
            wvalid  = 0 ;
            wdata   = 0  ;
            wstrb   = 0  ;
            wlast   = 0  ;

            bready  = 0;
            LSU_bvalid = 0;
            LSU_bresp  = 0 ;
            LSU_bid    = 0   ;
            IFU_bvalid = 0     ;
            IFU_bresp  = 0     ;
            IFU_bid    = 0     ;
            LSU_arready = 0;
            IFU_arready = 0;
            arvalid = 0 ;
            araddr  = 0  ;
            arid    = 0    ;
            arlen   = 0   ;
            arsize  = 0  ;
            arburst = 0 ;

            rready  = 0;
            LSU_rvalid = 0;
            LSU_rresp  = 0 ;
            LSU_rdata  = 0 ;
            LSU_rlast  = 0 ;
            LSU_rid    = 0   ;
            IFU_rvalid = 0;
            IFU_rresp  = 0;
            IFU_rdata  = 0;
            IFU_rlast  = 0;
            IFU_rid    = 0;
        end

    end


    
endmodule                                                           //Aribiter
