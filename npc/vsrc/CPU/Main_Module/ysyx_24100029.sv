`include "../define/para.v"
`ifdef Performance_Count
import "DPI-C" function void fi(int val);
`endif

module ysyx_24100029 #(
    parameter                           ResetValue                 = 32'h30000000
)
(
    input                               clock                      ,
    input                               reset                      ,
    input                               io_interrupt                
`ifndef NPC
    ,input                                  io_master_awready          ,
    output                              io_master_awvalid          ,
    output             [  31: 0]        io_master_awaddr           ,// writer address
    output             [   3: 0]        io_master_awid             ,// adress write ID for transcation order
    output             [   7: 0]        io_master_awlen            ,// burst lenth = awlen[7:0]+ 1
    output             [   2: 0]        io_master_awsize           ,// burst size (Bytes in transfer)
    output             [   1: 0]        io_master_awburst          ,// burst type, three types // 1.FIXED 2. incr 3.wrap
    
    input                               io_master_wready           ,
    output                              io_master_wvalid           ,
    output             [  31: 0]        io_master_wdata            ,
    output             [   3: 0]        io_master_wstrb            ,// 
    output                              io_master_wlast            ,// This signal indicates the last transfer in a write burst

    output                              io_master_bready           ,
    input                               io_master_bvalid           ,
    input              [   1: 0]        io_master_bresp            ,
    input              [   3: 0]        io_master_bid              ,

    input                               io_master_arready          ,
    output                              io_master_arvalid          ,
    output             [  31: 0]        io_master_araddr           ,
    output             [   3: 0]        io_master_arid             ,
    output             [   7: 0]        io_master_arlen            ,
    output             [   2: 0]        io_master_arsize           ,
    output             [   1: 0]        io_master_arburst          ,

    output                              io_master_rready           ,
    input                               io_master_rvalid           ,
    input              [   1: 0]        io_master_rresp            ,
    input              [  31: 0]        io_master_rdata            ,
    input                               io_master_rlast            ,
    input              [   3: 0]        io_master_rid              ,


    output                              io_slave_awready           ,
    input                               io_slave_awvalid           ,
    input              [   3: 0]        io_slave_awid              ,
    input              [  31: 0]        io_slave_awaddr            ,
    input              [   7: 0]        io_slave_awlen             ,
    input              [   2: 0]        io_slave_awsize            ,
    input              [   1: 0]        io_slave_awburst           ,

    output                              io_slave_wready            ,
    input                               io_slave_wvalid            ,
    input              [  31: 0]        io_slave_wdata             ,
    input              [   3: 0]        io_slave_wstrb             ,
    input                               io_slave_wlast             ,
    
    input                               io_slave_bready            ,
    output                              io_slave_bvalid            ,
    output             [   3: 0]        io_slave_bid               ,
    output             [   1: 0]        io_slave_bresp             ,
    
    output                              io_slave_arready           ,
    input                               io_slave_arvalid           ,
    input              [   3: 0]        io_slave_arid              ,
    input              [  31: 0]        io_slave_araddr            ,
    input              [   7: 0]        io_slave_arlen             ,
    input              [   2: 0]        io_slave_arsize            ,
    input              [   1: 0]        io_slave_arburst           ,
    
    input                               io_slave_rready            ,
    input                               io_slave_rvalid            ,
    input              [   3: 0]        io_slave_rid               ,
    input              [  31: 0]        io_slave_rdata             ,
    input              [   1: 0]        io_slave_rresp             ,
    input                               io_slave_rlast              
`endif
);

    wire               [  31: 0]        IFU_inst                    ;
    wire                                IFU_valid                   ;
    wire                                IFU_req                     ;
    wire               [  31: 0]        IFU_pc                      ;
    wire               [  31: 0]        IFU_snpc                    ;

    wire                                IFU_awready                 ;
    wire                                IFU_awvalid                 ;
    wire               [  31: 0]        IFU_awaddr                  ;
    wire               [   3: 0]        IFU_awid                    ;
    wire               [   7: 0]        IFU_awlen                   ;
    wire               [   2: 0]        IFU_awsize                  ;
    wire               [   1: 0]        IFU_awburst                 ;

    wire                                IFU_wready                  ;
    wire                                IFU_wvalid                  ;
    wire               [  31: 0]        IFU_wdata                   ;
    wire               [   3: 0]        IFU_wstrb                   ;
    wire                                IFU_wlast                   ;

    wire                                IFU_bready                  ;
    wire                                IFU_bvalid                  ;
    wire               [   1: 0]        IFU_bresp                   ;
    wire               [   3: 0]        IFU_bid                     ;

    wire                                IFU_arready                 ;
    wire                                IFU_arvalid                 ;
    wire               [  31: 0]        IFU_araddr                  ;
    wire               [   3: 0]        IFU_arid                    ;
    wire               [   7: 0]        IFU_arlen                   ;
    wire               [   2: 0]        IFU_arsize                  ;
    wire               [   1: 0]        IFU_arburst                 ;

    wire                                IFU_rready                  ;
    wire                                IFU_rvalid                  ;
    wire               [   1: 0]        IFU_rresp                   ;
    wire               [  31: 0]        IFU_rdata                   ;
    wire                                IFU_rlast                   ;
    wire               [   3: 0]        IFU_rid                     ;


/************************* IDU ********************/
    wire               [  31: 0]        IDU_pc                      ;
    wire               [   4: 0]        IDU_rd                      ;
    wire               [   2: 0]        IDU_funct3                  ;
    wire                                IDU_mret_flag               ;
    wire                                IDU_ecall_flag              ;
    wire               [  31: 0]        IDU_rs2_value               ;
    wire               [  31: 0]        IDU_rs1_value               ;
    wire               [   3: 0]        IDU_csr_wen                 ;
    wire                                IDU_R_wen                   ;
    wire               [  31: 0]        IDU_rd_value                ;
    wire                                IDU_mem_wen                 ;
    wire                                IDU_mem_ren                 ;

    wire                                IDU_inv_flag                ;
    wire                                IDU_branch_flag             ;
    wire                                IDU_jump_flag               ;
    wire               [  31: 0]        IDU_add1_value              ;
    wire               [  31: 0]        IDU_add2_value              ;
    wire               [   3: 0]        IDU_alu_opcode              ;
    wire               [   4: 0]        IDU_rs1                     ;
    wire               [   4: 0]        IDU_rs2                     ;
    wire               [  31: 0]        IDU_a0_value                ;
    wire               [  31: 0]        IDU_mepc_out                ;
    wire               [  31: 0]        IDU_mtvec_out               ;

    wire               [  31: 0]        IDU_branch_pc               ;
    wire                                IDU_valid                   ;
    wire                                IDU_ready                   ;
    wire               [  31: 0]        IDU_inst                    ;//debug
    wire                                IDU_fence_i_flag            ;
/************************* EXU ********************/
    wire               [  31: 0]        EXU_branch_pc               ;
    wire                                EXU_jump_flag               ;
    wire               [   2: 0]        EXU_funct3                  ;
    wire               [  31: 0]        EXU_rs2_value               ;
    wire               [   4: 0]        EXU_rd                      ;
    wire               [  31: 0]        EXU_rd_value                ;
    wire               [   3: 0]        EXU_csr_wen                 ;
    wire                                EXU_R_wen                   ;
    wire                                EXU_mem_wen                 ;
    wire                                EXU_mem_ren                 ;
    wire               [  31: 0]        EXU_pc                      ;
    wire               [  31: 0]        EXU_Ex_result               ;
    wire                                EXU_branch_flag             ;
    wire               [  31: 0]        EXU_rs1_in                  ;
    wire               [  31: 0]        EXU_rs2_in                  ;
    wire                                EXU_fence_i_flag            ;

    wire                                EXU_valid                   ;
    wire                                EXU_ready                   ;
    wire               [  31: 0]        EXU_inst                    ;
/************************* LSU ********************/
    wire                                LSU_jump_flag               ;
    wire                                LSU_R_wen                   ;
    wire               [  31: 0]        LSU_Rdata                   ;
    wire               [   3: 0]        LSU_csr_wen                 ;
    wire               [  31: 0]        LSU_Ex_result               ;
    wire               [  31: 0]        LSU_rd_value                ;
    wire               [  31: 0]        LSU_pc                      ;

    wire               [   4: 0]        LSU_rd                      ;
    wire                                LSU_mem_ren                 ;

    wire                                LSU_awready                 ;
    wire                                LSU_awvalid                 ;
    wire               [  31: 0]        LSU_awaddr                  ;
    wire               [   3: 0]        LSU_awid                    ;
    wire               [   7: 0]        LSU_awlen                   ;
    wire               [   2: 0]        LSU_awsize                  ;
    wire               [   1: 0]        LSU_awburst                 ;

    wire                                LSU_wready                  ;
    wire                                LSU_wvalid                  ;
    wire               [  31: 0]        LSU_wdata                   ;
    wire               [   3: 0]        LSU_wstrb                   ;
    wire                                LSU_wlast                   ;

    wire                                LSU_bready                  ;
    wire                                LSU_bvalid                  ;
    wire               [   1: 0]        LSU_bresp                   ;
    wire               [   3: 0]        LSU_bid                     ;

    wire                                LSU_arready                 ;
    wire                                LSU_arvalid                 ;
    wire               [  31: 0]        LSU_araddr                  ;
    wire               [   3: 0]        LSU_arid                    ;
    wire               [   7: 0]        LSU_arlen                   ;
    wire               [   2: 0]        LSU_arsize                  ;
    wire               [   1: 0]        LSU_arburst                 ;

    wire                                LSU_rready                  ;
    wire                                LSU_rvalid                  ;
    wire               [   1: 0]        LSU_rresp                   ;
    wire               [  31: 0]        LSU_rdata                   ;
    wire                                LSU_rlast                   ;
    wire               [   3: 0]        LSU_rid                     ;

    wire                                LSU_valid                   ;
    wire                                LSU_ready                   ;
    wire               [  31: 0]        LSU_inst                    ;

    wire                                LSU_req                     ;
/************************* WBU ********************/
    wire               [  31: 0]        WBU_pc                      ;
    wire               [  31: 0]        WBU_inst                    ;
    wire               [  31: 0]        WBU_rd_value                ;
    wire               [  31: 0]        WBU_csrd                    ;
    wire               [   4: 0]        WBU_rd                      ;
    wire                                WBU_R_wen                   ;
    wire               [   3: 0]        WBU_csr_wen                 ;
    wire                                WBU_ready                   ;
    wire                                WBU_valid                   ;
 //   wire                         WBU_valid                  ;

 /************************* SRAM ********************/

    wire               [  31: 0]        araddr                      ;
    wire                                arvalid                     ;
    wire                                arready                     ;

    wire                                rready                      ;
    wire               [  31: 0]        rdata                       ;
    wire                                rresp                       ;
    wire                                rvalid                      ;
    
    wire               [  31: 0]        awaddr                      ;
    wire                                awvalid                     ;
    wire                                awready                     ;
    
    wire               [  31: 0]        wdata                       ;
    wire               [   7: 0]        wstrb                       ;
    wire                                wvalid                      ;
    wire                                wready                      ;
    
    wire                                bresp                       ;
    wire                                bvalid                      ;
    wire                                bready                      ;


/*            PERSONAL              */

    wire                                dnpc_flag                   ;
    wire                                EXU_inst_clear              ;
    wire               [  31: 0]        dnpc                        ;
    wire                                icache_clr                  ;
/********************Aribiter**************/

    wire                                Aribiter_awready            ;
    wire                                Aribiter_awvalid            ;
    wire               [  31: 0]        Aribiter_awaddr             ;
    wire               [   3: 0]        Aribiter_awid               ;
    wire               [   7: 0]        Aribiter_awlen              ;
    wire               [   2: 0]        Aribiter_awsize             ;
    wire               [   1: 0]        Aribiter_awburst            ;
    wire                                Aribiter_wready             ;
    wire                                Aribiter_wvalid             ;
    wire               [  31: 0]        Aribiter_wdata              ;
    wire               [   3: 0]        Aribiter_wstrb              ;
    wire                                Aribiter_wlast              ;
    wire                                Aribiter_bready             ;
    wire                                Aribiter_bvalid             ;
    wire               [   1: 0]        Aribiter_bresp              ;
    wire               [   3: 0]        Aribiter_bid                ;
    wire                                Aribiter_arready            ;
    wire                                Aribiter_arvalid            ;
    wire               [  31: 0]        Aribiter_araddr             ;
    wire               [   3: 0]        Aribiter_arid               ;
    wire               [   7: 0]        Aribiter_arlen              ;
    wire               [   2: 0]        Aribiter_arsize             ;
    wire               [   1: 0]        Aribiter_arburst            ;
    wire                                Aribiter_rready             ;
    wire                                Aribiter_rvalid             ;
    wire               [   1: 0]        Aribiter_rresp              ;
    wire               [  31: 0]        Aribiter_rdata              ;
    wire                                Aribiter_rlast              ;
    wire               [   3: 0]        Aribiter_rid                ;




/******************************** CLNT **************************/
    wire                                CLNT_awready                ;
    wire                                CLNT_awvalid                ;
    wire               [  31: 0]        CLNT_awaddr                 ;
    wire               [   3: 0]        CLNT_awid                   ;
    wire               [   7: 0]        CLNT_awlen                  ;
    wire               [   2: 0]        CLNT_awsize                 ;
    wire               [   1: 0]        CLNT_awburst                ;
    wire                                CLNT_wready                 ;
    wire                                CLNT_wvalid                 ;
    wire               [  31: 0]        CLNT_wdata                  ;
    wire               [   3: 0]        CLNT_wstrb                  ;
    wire                                CLNT_wlast                  ;
    wire                                CLNT_bready                 ;
    wire                                CLNT_bvalid                 ;
    wire               [   1: 0]        CLNT_bresp                  ;
    wire               [   3: 0]        CLNT_bid                    ;
    wire                                CLNT_arready                ;
    wire                                CLNT_arvalid                ;
    wire               [  31: 0]        CLNT_araddr                 ;
    wire               [   3: 0]        CLNT_arid                   ;
    wire               [   7: 0]        CLNT_arlen                  ;
    wire               [   2: 0]        CLNT_arsize                 ;
    wire               [   1: 0]        CLNT_arburst                ;
    wire                                CLNT_rready                 ;
    wire                                CLNT_rvalid                 ;
    wire               [   1: 0]        CLNT_rresp                  ;
    wire               [  31: 0]        CLNT_rdata                  ;
    wire                                CLNT_rlast                  ;
    wire               [   3: 0]        CLNT_rid                    ;

/***************Performance Count*********************/
`ifdef Performance_Count
    wire               [  31: 0]        fetch_inst                  ;
    reg                [  31: 0]        instd_clr_num               ;// decode clear num
    wire               [  31: 0]        InstR_count                 ;
    wire               [  31: 0]        InstI_count                 ;
    wire               [  31: 0]        InstS_count                 ;
    wire               [  31: 0]        InstB_count                 ;
    wire               [  31: 0]        InstU_count                 ;
    wire               [  31: 0]        InstJ_count                 ;
    wire               [  31: 0]        InstM_count                 ;
    wire               [  31: 0]        total_count                 ;
    wire               [  31: 0]        Exu_count                   ;
    wire               [  31: 0]        lsu_cycle                   ;
    wire               [  31: 0]        flash_hit,flash_miss,sdram_hit,sdram_miss  ;

    assign                              total_count                 = InstR_count + InstI_count + InstS_count + InstB_count + InstU_count + InstJ_count + InstM_count;

    always @(posedge clock) begin
        if(reset)
            instd_clr_num <= 0;
        else if(EXU_inst_clear)
            instd_clr_num <= instd_clr_num + 32'd1 ;
    end

    always @(*)begin
        if(WBU_inst == 32'h00100073) begin
        $display("\033[0m\033[1;34m | icache addr \t| flash   \t| sdram   \t| \033[0m");
        $display("\033[0m\033[1;34m | hit         \t| %-d     \t| %-d     \t| \033[0m",flash_hit,sdram_hit);
        $display("\033[0m\033[1;34m | miss        \t| %-d     \t| %-d     \t| \033[0m",flash_miss,sdram_miss);
        $display("\033[0m\033[1;34m | hit_rate    \t| %-d     \t| %-d     \t| \033[0m",flash_hit*100/(flash_hit+flash_miss),sdram_hit*100/(sdram_hit+sdram_miss));
        $display("\033[0m\033[1;34m | total_count \t| InstR_count \t| InstI_count \t| InstS_count \t| InstU_count \t| InstB_count \t| InstJ_count \t| InstM_count \t| \033[0m");
        $display("\033[0m\033[1;34m | %d \t| %d \t| %d \t| %d \t| %d \t| %d \t| %d \t| %d \t| \033[0m",total_count,InstR_count,InstI_count,InstS_count, InstU_count,InstB_count,InstJ_count,InstM_count);
        $display("\033[0m\033[1;34m | fetch_inst \t| flush_decoder_i \t| \033[0m");
        $display("\033[0m\033[1;34m | %d \t| %d \t\t|\033[0m",fetch_inst,instd_clr_num);
        $display("\033[0m\033[1;34m | exu_cycle \t| lsu_cycle \t| \033[0m");
        $display("\033[0m\033[1;34m | %d \t| %d \t| \033[0m",Exu_count,lsu_cycle);
            if(IDU_a0_value == 0)begin
                $display("\033[32;42m Hit The Good TRAP \033[0m");
                fi(0);
            end
            else begin
                $display("\033[32;42m Hit The Bad TRAP \033[0m");
                fi(1);
            end
        end
    end



    reg                                 skip                        ;
    wire                                mem_ren_flag                ;
    wire                                mem_wen_flag                ;
    wire               [  31: 0]        paddr                       ;
    wire                                lsu_mem_wen                 ;

`ifdef NPC
always @(*) begin
    if(mem_ren_flag || mem_wen_flag)begin
        if ((paddr <=32'ha1000000 && paddr >= 32'ha0000000))begin
                skip = 1;
        end
        else
                skip = 0;
    end
    else
        skip = 0;
end
`else
always @(*) begin
    if(mem_ren_flag || mem_wen_flag)begin
        if ((paddr <=32'h2000008 && paddr >= 32'h2000000) || (paddr >= 32'h10000000 && paddr <= 32'h10000fff))
                skip = 1;
        else
                skip = 0;
    end
    else
        skip = 0;
end
`endif

task Getinst;
    output                              bit[31:0] inst             ;
    inst = WBU_inst;
endtask

task  GetPC;
    output                              bit[31:0]pc                ;
    pc = WBU_pc;
endtask

task Getvalid;
    output                              bit  valid                 ;
    valid = WBU_valid;
endtask

task Getskip_flag;
    output                              bit skip_flag              ;
    skip_flag = skip;
endtask
export "DPI-C" task Getskip_flag;
export "DPI-C" task Getvalid;
export "DPI-C" task GetPC;
export "DPI-C" task Getinst;

`endif

`ifdef NPC

    wire                                io_master_awready           ;
    wire                                io_master_awvalid           ;
    wire               [  31: 0]        io_master_awaddr            ;
    wire               [   3: 0]        io_master_awid              ;
    wire               [   7: 0]        io_master_awlen             ;
    wire               [   2: 0]        io_master_awsize            ;
    wire               [   1: 0]        io_master_awburst           ;
    wire                                io_master_wready            ;
    wire                                io_master_wvalid            ;
    wire               [  31: 0]        io_master_wdata             ;
    wire               [   3: 0]        io_master_wstrb             ;
    wire                                io_master_wlast             ;
    wire                                io_master_bready            ;
    wire                                io_master_bvalid            ;
    wire               [   1: 0]        io_master_bresp             ;
    wire               [   3: 0]        io_master_bid               ;
    wire                                io_master_arready           ;
    wire                                io_master_arvalid           ;
    wire               [  31: 0]        io_master_araddr            ;
    wire               [   3: 0]        io_master_arid              ;
    wire               [   7: 0]        io_master_arlen             ;
    wire               [   2: 0]        io_master_arsize            ;
    wire               [   1: 0]        io_master_arburst           ;
    wire                                io_master_rready            ;
    wire                                io_master_rvalid            ;
    wire               [   1: 0]        io_master_rresp             ;
    wire               [  31: 0]        io_master_rdata             ;
    wire                                io_master_rlast             ;
    wire               [   3: 0]        io_master_rid               ;

sram u_sram(
    .clock                              (clock                     ),
    .reset                              (reset                     ),
    .awready                            (io_master_awready         ),
    .awvalid                            (io_master_awvalid         ),
    .awaddr                             (io_master_awaddr          ),
    .awid                               (io_master_awid            ),
    .awlen                              (io_master_awlen           ),
    .awsize                             (io_master_awsize          ),
    .awburst                            (io_master_awburst         ),
    .wready                             (io_master_wready          ),
    .wvalid                             (io_master_wvalid          ),
    .wdata                              (io_master_wdata           ),
    .wstrb                              (io_master_wstrb           ),
    .wlast                              (io_master_wlast           ),
    .bready                             (io_master_bready          ),
    .bvalid                             (io_master_bvalid          ),
    .bresp                              (io_master_bresp           ),
    .bid                                (io_master_bid             ),
    .arready                            (io_master_arready         ),
    .arvalid                            (io_master_arvalid         ),
    .araddr                             (io_master_araddr          ),
    .arid                               (io_master_arid            ),
    .arlen                              (io_master_arlen           ),
    .arsize                             (io_master_arsize          ),
    .arburst                            (io_master_arburst         ),
    .rready                             (io_master_rready          ),
    .rvalid                             (io_master_rvalid          ),
    .rresp                              (io_master_rresp           ),
    .rdata                              (io_master_rdata           ),
    .rlast                              (io_master_rlast           ),
    .rid                                (io_master_rid             ) 
);

`endif


ysyx_24100029_Control Control_inst0(

    .clock                              (clock                     ),
    .reset                              (reset                     ),
    .mtvec_out                          (IDU_mtvec_out             ),
    .mepc_out                           (IDU_mepc_out              ),

    .branch_pc                          (EXU_branch_pc             ),
    .Ex_result                          (EXU_Ex_result             ),
    .MEM_Ex_result                      (LSU_Ex_result             ),
    .IDU_rs1_value                      (IDU_rs1_value             ),
    .IDU_rs2_value                      (IDU_rs2_value             ),
    .MEM_Rdata                          (LSU_Rdata                 ),

    .branch_flag                        (EXU_branch_flag           ),
    .jump_flag                          (EXU_jump_flag             ),
    .mret_flag                          (IDU_mret_flag             ),
    .ecall_flag                         (IDU_ecall_flag            ),
    .fence_i_flag                       (EXU_fence_i_flag          ),

    .MEM_mem_ren                        (LSU_mem_ren               ),

    .IDU_rs1                            (IDU_rs1                   ),
    .IDU_rs2                            (IDU_rs2                   ),

    .IDU_valid                          (IDU_valid                 ),
    .EXU_valid                          (EXU_valid                 ),
    .MEM_valid                          (LSU_valid                 ),

    .EXU_rd                             (EXU_rd                    ),
    .MEM_rd                             (LSU_rd                    ),

    .EXU_R_Wen                          (EXU_R_wen                 ),
    .MEM_R_Wen                          (LSU_R_wen                 ),

    .EXU_rs1_in                         (EXU_rs1_in                ),
    .EXU_rs2_in                         (EXU_rs2_in                ),
    .dnpc                               (dnpc                      ),
    .icache_clr                         (icache_clr                ),
    .EXU_inst_clear                     (EXU_inst_clear            ),
    .dnpc_flag                          (dnpc_flag                 ) 
);





/*
ysyx_24100029_IFU  #(
    .ResetValue                         (ResetValue                ) 
)
IFU_Inst0
(
    .clock                              (clock                     ),
    .reset                              (reset                     ),
    .dnpc                               (dnpc                      ),
    .dnpc_flag                          (dnpc_flag                 ),
    .pc                                 (IFU_pc                    ),
    .snpc                               (IFU_snpc                  ),
    .inst                               (IFU_inst                  ),
    .icache_clr                         (icache_clr                ),

    .awready                            (IFU_awready               ),
    .awvalid                            (IFU_awvalid               ),
    .awaddr                             (IFU_awaddr                ),
    .awid                               (IFU_awid                  ),
    .awlen                              (IFU_awlen                 ),
    .awsize                             (IFU_awsize                ),
    .awburst                            (IFU_awburst               ),
 
    .wready                             (IFU_wready                ),
    .wvalid                             (IFU_wvalid                ),
    .wdata                              (IFU_wdata                 ),
    .wstrb                              (IFU_wstrb                 ),
    .wlast                              (IFU_wlast                 ),
     
    .bready                             (IFU_bready                ),
    .bvalid                             (IFU_bvalid                ),
    .bresp                              (IFU_bresp                 ),
    .bid                                (IFU_bid                   ),
     
    .arready                            (IFU_arready               ),
    .arvalid                            (IFU_arvalid               ),
    .araddr                             (IFU_araddr                ),
    .arid                               (IFU_arid                  ),
    .arlen                              (IFU_arlen                 ),
    .arsize                             (IFU_arsize                ),
    .arburst                            (IFU_arburst               ),
     
    .rready                             (IFU_rready                ),
    .rvalid                             (IFU_rvalid                ),
    .rresp                              (IFU_rresp                 ),
    .rdata                              (IFU_rdata                 ),
    .rlast                              (IFU_rlast                 ),
    .rid                                (IFU_rid                   ),
    
    .req                                (IFU_req                   ),
`ifdef Performance_Count
    .fetch_inst                         (fetch_inst                ),
    .flash_hit                          (flash_hit                 ),
    .flash_miss                         (flash_miss                ),
    .sdram_hit                          (sdram_hit                 ),
    .sdram_miss                         (sdram_miss                ),
`endif
    .ready                              (IDU_ready                 ),
    .valid                              (IFU_valid                 ) 
);

ysyx_24100029_IDU IDU_Inst0(
    .clock                              (clock                     ),
    .reset                              (reset                     ),

    .snpc                               (IFU_snpc                  ),
    .inst                               (IFU_inst                  ),
    .pc                                 (IFU_pc                    ),
    .rd_value                           (WBU_rd_value              ),
    .csrd                               (WBU_csrd                  ),
    .rd                                 (WBU_rd                    ),
    .R_wen                              (WBU_R_wen                 ),
    .csr_wen                            (WBU_csr_wen               ),

    .EXU_rs1_in                         (EXU_rs1_in                ),
    .EXU_rs2_in                         (EXU_rs2_in                ),
    .branch_pc                          (IDU_branch_pc             ),
    .rd_next                            (IDU_rd                    ),
    .funct3                             (IDU_funct3                ),
    .mret_flag                          (IDU_mret_flag             ),
    .ecall_flag                         (IDU_ecall_flag            ),
    .fence_i_flag                       (IDU_fence_i_flag          ),

    .add2_value                         (IDU_add2_value            ),
    .add1_value                         (IDU_add1_value            ),
    .rs1_value                          (IDU_rs1_value             ),
    .rs2_value                          (IDU_rs2_value             ),
    .csr_wen_next                       (IDU_csr_wen               ),
    .R_wen_next                         (IDU_R_wen                 ),
    .rd_value_next                      (IDU_rd_value              ),

    .mem_wen                            (IDU_mem_wen               ),
    .mem_ren                            (IDU_mem_ren               ),
    .inv_flag                           (IDU_inv_flag              ),
    .branch_flag                        (IDU_branch_flag           ),
    .jump_flag                          (IDU_jump_flag             ),
    .alu_opcode                         (IDU_alu_opcode            ),

    .rs1                                (IDU_rs1                   ),
    .rs2                                (IDU_rs2                   ),
    .a0_value                           (IDU_a0_value              ),
    .mepc_out                           (IDU_mepc_out              ),
    .mtvec_out                          (IDU_mtvec_out             ),

    .valid_last                         (IFU_valid                 ),
    .ready_last                         (IDU_ready                 ),
`ifdef Performance_Count
    .pc_next                            (IDU_pc                    ),
    .InstR_count                        (InstR_count               ),
    .InstI_count                        (InstI_count               ),
    .InstS_count                        (InstS_count               ),
    .InstB_count                        (InstB_count               ),
    .InstU_count                        (InstU_count               ),
    .InstJ_count                        (InstJ_count               ),
    .InstM_count                        (InstM_count               ),
    .inst_next                          (IDU_inst                  ),
`endif
    .ready_next                         (EXU_ready                 ),
    .valid_next                         (IDU_valid                 ) 

);
*/
ysyx_24100029_EXU EXU_Inst0(
    .clock                              (clock                     ),
    .reset                              (reset                     ),
    .EXU_inst_clr                       (EXU_inst_clear            ),

    .funct3                             (IDU_funct3                ),
    .csr_wen                            (IDU_csr_wen               ),
    .R_wen                              (IDU_R_wen                 ),
    .mem_wen                            (IDU_mem_wen               ),
    .mem_ren                            (IDU_mem_ren               ),
    .rd                                 (IDU_rd                    ),
    .branch_pc                          (IDU_branch_pc             ),

    .alu_opcode                         (IDU_alu_opcode            ),
    .inv_flag                           (IDU_inv_flag              ),
    .jump_flag                          (IDU_jump_flag             ),
    .branch_flag                        (IDU_branch_flag           ),
    .fetch_i_flag                       (IDU_fence_i_flag          ),

    .add2                               (IDU_add2_value            ),
    .add1                               (IDU_add1_value            ),
    .rs2_value                          (EXU_rs2_in                ),
    .rd_value                           (IDU_rd_value              ),

    .branch_pc_next                     (EXU_branch_pc             ), 
    .branch_flag_next                   (EXU_branch_flag           ),
    .jump_flag_next                     (EXU_jump_flag             ),
    .funct3_next                        (EXU_funct3                ),
    .rs2_value_next                     (EXU_rs2_value             ),
    .rd_next                            (EXU_rd                    ),
    .rd_value_next                      (EXU_rd_value              ),
    .csr_wen_next                       (EXU_csr_wen               ),
    .R_wen_next                         (EXU_R_wen                 ),
    .mem_wen_next                       (EXU_mem_wen               ),
    .mem_ren_next                       (EXU_mem_ren               ),
    .EX_result                          (EXU_Ex_result             ),
    .fetch_i_flag_next                  (EXU_fence_i_flag          ),
`ifdef Performance_Count
    .pc_next                            (EXU_pc                    ),
    .pc                                 (IDU_pc                    ),
    .Exu_count                          (Exu_count                 ),
    .inst                               (IDU_inst                  ),
    .inst_next                          (EXU_inst                  ),
`endif
    .valid_last                         (IDU_valid                 ),
    .ready_last                         (EXU_ready                 ),

    .ready_next                         (LSU_ready                 ),
    .valid_next                         (EXU_valid                 ) 


);

ysyx_24100029_LSU LSU_Inst0
(
    .clock                              (clock                     ),
    .reset                              (reset                     ),

    .mem_ren                            (EXU_mem_ren               ),
    .mem_wen                            (EXU_mem_wen               ),
    .R_wen                              (EXU_R_wen                 ),
    .csr_wen                            (EXU_csr_wen               ),
    .Ex_result                          (EXU_Ex_result             ),
    .rd_value                           (EXU_rd_value              ),
    .rd                                 (EXU_rd                    ),
    .funct3                             (EXU_funct3                ),
    .rs2_value                          (EXU_rs2_value             ),
    .jump_flag                          (EXU_jump_flag             ),

    .R_wen_next                         (LSU_R_wen                 ),
    .LSU_Rdata                          (LSU_Rdata                 ),
    .csr_wen_next                       (LSU_csr_wen               ),
    .Ex_result_next                     (LSU_Ex_result             ),
    .rd_value_next                      (LSU_rd_value              ),
    .rd_next                            (LSU_rd                    ),
    .mem_ren_next                       (LSU_mem_ren               ),
    .jump_flag_next                     (LSU_jump_flag             ),

    .awready                            (LSU_awready               ),
    .awvalid                            (LSU_awvalid               ),
    .awaddr                             (LSU_awaddr                ),
    .awid                               (LSU_awid                  ),
    .awlen                              (LSU_awlen                 ),
    .awsize                             (LSU_awsize                ),
    .awburst                            (LSU_awburst               ),
    .wready                             (LSU_wready                ),
    .wvalid                             (LSU_wvalid                ),
    .wdata                              (LSU_wdata                 ),
    .wstrb                              (LSU_wstrb                 ),
    .wlast                              (LSU_wlast                 ),
 
    .bready                             (LSU_bready                ),
    .bvalid                             (LSU_bvalid                ),
    .bresp                              (LSU_bresp                 ),
    .bid                                (LSU_bid                   ),
 
    .arready                            (LSU_arready               ),
    .arvalid                            (LSU_arvalid               ),
    .araddr                             (LSU_araddr                ),
    .arid                               (LSU_arid                  ),
    .arlen                              (LSU_arlen                 ),
    .arsize                             (LSU_arsize                ),
    .arburst                            (LSU_arburst               ),
 
    .rready                             (LSU_rready                ),
    .rvalid                             (LSU_rvalid                ),
    .rresp                              (LSU_rresp                 ),
    .rdata                              (LSU_rdata                 ),
    .rlast                              (LSU_rlast                 ),
    .rid                                (LSU_rid                   ),
    
    .req                                (LSU_req                   ),

`ifdef Performance_Count
    .pc_next                            (LSU_pc                    ),
    .pc                                 (EXU_pc                    ),
    .mem_wflag                          (lsu_mem_wen               ),
    .lsu_cycle                          (lsu_cycle                 ),
    .inst                               (EXU_inst                  ),
    .inst_next                          (LSU_inst                  ),
`endif
    .valid_last                         (EXU_valid                 ),
    .ready_last                         (LSU_ready                 ),

    .ready_next                         (WBU_ready                 ),
    .valid_next                         (LSU_valid                 ) 

);

ysyx_24100029_WBU WBU_inst0
(
    .clock                              (clock                     ),
    .reset                              (reset                     ),

    .MEM_Rdata                          (LSU_Rdata                 ),
    .Ex_result                          (LSU_Ex_result             ),
    .rd_value                           (LSU_rd_value              ),
    .rd                                 (LSU_rd                    ),
    .csr_wen                            (LSU_csr_wen               ),
    .R_wen                              (LSU_R_wen                 ),
    .mem_ren                            (LSU_mem_ren               ),
    .jump_flag                          (LSU_jump_flag             ),

    .R_wen_next                         (WBU_R_wen                 ),
    .csr_wen_next                       (WBU_csr_wen               ),
    .csrd                               (WBU_csrd                  ),
    .rd_value_next                      (WBU_rd_value              ),

    .valid                              (LSU_valid                 ),
    .ready                              (WBU_ready                 ),
`ifdef Performance_Count
    .pc                                 (LSU_pc                    ),
    .pc_next                            (WBU_pc                    ),
    .mem_wen_reg                        (lsu_mem_wen               ),
    .mem_wen_flag                       (mem_wen_flag              ),
    .mem_ren_flag                       (mem_ren_flag              ),
    .paddr                              (paddr                     ),
    .inst                               (LSU_inst                  ),
    .inst_next                          (WBU_inst                  ),
`endif
    .rd_next                            (WBU_rd                    ),
    .valid_next                         (WBU_valid                 ) 
);
/* verilator lint_off PINMISSING */
ysyx_24100029_Aribiter #(
    .DATA_WIDTH                         (32                        ),
    .ADDR_WIDTH                         (32                        ) 
)Aribiter_inst(
    .clock                              (clock                     ),
    .reset                              (reset                     ),

    .IFU_req                            (IFU_req                   ),
    .LSU_req                            (LSU_req                   ),

    .IFU_araddr                         (IFU_araddr                ),
    .IFU_arvalid                        (IFU_arvalid               ),
    .IFU_arready                        (IFU_arready               ),
    .IFU_arid                           (IFU_arid                  ),
    .IFU_arlen                          (IFU_arlen                 ),
    .IFU_arsize                         (IFU_arsize                ),
    .IFU_arburst                        (IFU_arburst               ),

    .IFU_rready                         (IFU_rready                ),
    .IFU_rdata                          (IFU_rdata                 ),
    .IFU_rresp                          (IFU_rresp                 ),
    .IFU_rvalid                         (IFU_rvalid                ),
    .IFU_rlast                          (IFU_rlast                 ),
    .IFU_rid                            (IFU_rid                   ),

    .IFU_awaddr                         (IFU_awaddr                ),
    .IFU_awvalid                        (IFU_awvalid               ),
    .IFU_awready                        (IFU_awready               ),
    .IFU_awid                           (IFU_awid                  ),
    .IFU_awlen                          (IFU_awlen                 ),
    .IFU_awsize                         (IFU_awsize                ),
    .IFU_awburst                        (IFU_awburst               ),

    .IFU_wdata                          (IFU_wdata                 ),
    .IFU_wstrb                          (IFU_wstrb                 ),
    .IFU_wvalid                         (IFU_wvalid                ),
    .IFU_wready                         (IFU_wready                ),
    .IFU_wlast                          (IFU_wlast                 ),

    .IFU_bresp                          (IFU_bresp                 ),
    .IFU_bvalid                         (IFU_bvalid                ),
    .IFU_bready                         (IFU_bready                ),
    .IFU_bid                            (IFU_bid                   ),

    .LSU_awready                        (LSU_awready               ),
    .LSU_awvalid                        (LSU_awvalid               ),
    .LSU_awaddr                         (LSU_awaddr                ),
    .LSU_awid                           (LSU_awid                  ),
    .LSU_awlen                          (LSU_awlen                 ),
    .LSU_awsize                         (LSU_awsize                ),
    .LSU_awburst                        (LSU_awburst               ),
    .LSU_wready                         (LSU_wready                ),
    .LSU_wvalid                         (LSU_wvalid                ),
    .LSU_wdata                          (LSU_wdata                 ),
    .LSU_wstrb                          (LSU_wstrb                 ),
    .LSU_wlast                          (LSU_wlast                 ),
    .LSU_bready                         (LSU_bready                ),
    .LSU_bvalid                         (LSU_bvalid                ),
    .LSU_bresp                          (LSU_bresp                 ),
    .LSU_bid                            (LSU_bid                   ),

    .LSU_arready                        (LSU_arready               ),
    .LSU_arvalid                        (LSU_arvalid               ),
    .LSU_araddr                         (LSU_araddr                ),
    .LSU_arid                           (LSU_arid                  ),
    .LSU_arlen                          (LSU_arlen                 ),
    .LSU_arsize                         (LSU_arsize                ),
    .LSU_arburst                        (LSU_arburst               ),
    .LSU_rready                         (LSU_rready                ),
    .LSU_rvalid                         (LSU_rvalid                ),
    .LSU_rresp                          (LSU_rresp                 ),
    .LSU_rdata                          (LSU_rdata                 ),
    .LSU_rlast                          (LSU_rlast                 ),
    .LSU_rid                            (LSU_rid                   ),

    .awready                            (Aribiter_awready          ),
    .awvalid                            (Aribiter_awvalid          ),
    .awaddr                             (Aribiter_awaddr           ),
    .awid                               (Aribiter_awid             ),
    .awlen                              (Aribiter_awlen            ),
    .awsize                             (Aribiter_awsize           ),
    .awburst                            (Aribiter_awburst          ),
    .wready                             (Aribiter_wready           ),
    .wvalid                             (Aribiter_wvalid           ),
    .wdata                              (Aribiter_wdata            ),
    .wstrb                              (Aribiter_wstrb            ),
    .wlast                              (Aribiter_wlast            ),
    .bready                             (Aribiter_bready           ),
    .bvalid                             (Aribiter_bvalid           ),
    .bresp                              (Aribiter_bresp            ),
    .bid                                (Aribiter_bid              ),

    .arready                            (Aribiter_arready          ),
    .arvalid                            (Aribiter_arvalid          ),
    .araddr                             (Aribiter_araddr           ),
    .arid                               (Aribiter_arid             ),
    .arlen                              (Aribiter_arlen            ),
    .arsize                             (Aribiter_arsize           ),
    .arburst                            (Aribiter_arburst          ),
    .rready                             (Aribiter_rready           ),
    .rvalid                             (Aribiter_rvalid           ),
    .rresp                              (Aribiter_rresp            ),
    .rdata                              (Aribiter_rdata            ),
    .rlast                              (Aribiter_rlast            ),
    .rid                                (Aribiter_rid              ) 
    


);
ysyx_24100029_CLINT CLNT(
    .reset                              (reset                     ),
    .clock                              (clock                     ),

    .araddr                             (CLNT_araddr               ),
    .arvalid                            (CLNT_arvalid              ),
    .arready                            (CLNT_arready              ),
    .arid                               (CLNT_arid                 ),
    .arlen                              (CLNT_arlen                ),
    .arsize                             (CLNT_arsize               ),
    .arburst                            (CLNT_arburst              ),
    .rready                             (CLNT_rready               ),
    .rdata                              (CLNT_rdata                ),
    .rresp                              (CLNT_rresp                ),
    .rvalid                             (CLNT_rvalid               ),
    .rlast                              (CLNT_rlast                ),
    .rid                                (CLNT_rid                  ),
    .awaddr                             (CLNT_awaddr               ),
    .awvalid                            (CLNT_awvalid              ),
    .awready                            (CLNT_awready              ),
    .awid                               (CLNT_awid                 ),
    .awlen                              (CLNT_awlen                ),
    .awsize                             (CLNT_awsize               ),
    .awburst                            (CLNT_awburst              ),
    .wdata                              (CLNT_wdata                ),
    .wstrb                              (CLNT_wstrb                ),
    .wvalid                             (CLNT_wvalid               ),
    .wready                             (CLNT_wready               ),
    .wlast                              (CLNT_wlast                ),
    .bresp                              (CLNT_bresp                ),
    .bvalid                             (CLNT_bvalid               ),
    .bready                             (CLNT_bready               ),
    .bid                                (CLNT_bid                  ) 
);
ysyx_24100029_Xbar Xbar(

    .reset                              (reset                     ),
    .clock                              (clock                     ),

    .araddr                             (Aribiter_araddr           ),
    .arvalid                            (Aribiter_arvalid          ),
    .arready                            (Aribiter_arready          ),
    .arid                               (Aribiter_arid             ),
    .arlen                              (Aribiter_arlen            ),
    .arsize                             (Aribiter_arsize           ),
    .arburst                            (Aribiter_arburst          ),

    .rready                             (Aribiter_rready           ),
    .rdata                              (Aribiter_rdata            ),
    .rresp                              (Aribiter_rresp            ),
    .rvalid                             (Aribiter_rvalid           ),
    .rlast                              (Aribiter_rlast            ),
    .rid                                (Aribiter_rid              ),

    .awaddr                             (Aribiter_awaddr           ),
    .awvalid                            (Aribiter_awvalid          ),
    .awready                            (Aribiter_awready          ),
    .awid                               (Aribiter_awid             ),
    .awlen                              (Aribiter_awlen            ),
    .awsize                             (Aribiter_awsize           ),
    .awburst                            (Aribiter_awburst          ),

    .wdata                              (Aribiter_wdata            ),
    .wstrb                              (Aribiter_wstrb            ),
    .wvalid                             (Aribiter_wvalid           ),
    .wready                             (Aribiter_wready           ),
    .wlast                              (Aribiter_wlast            ),

    .bresp                              (Aribiter_bresp            ),
    .bvalid                             (Aribiter_bvalid           ),
    .bready                             (Aribiter_bready           ),
    .bid                                (Aribiter_bid              ),

    .CLNT_awready                       (CLNT_awready              ),
    .CLNT_awvalid                       (CLNT_awvalid              ),
    .CLNT_awaddr                        (CLNT_awaddr               ),
    .CLNT_awid                          (CLNT_awid                 ),
    .CLNT_awlen                         (CLNT_awlen                ),
    .CLNT_awsize                        (CLNT_awsize               ),
    .CLNT_awburst                       (CLNT_awburst              ),

    .CLNT_wready                        (CLNT_wready               ),
    .CLNT_wvalid                        (CLNT_wvalid               ),
    .CLNT_wdata                         (CLNT_wdata                ),
    .CLNT_wstrb                         (CLNT_wstrb                ),
    .CLNT_wlast                         (CLNT_wlast                ),

    .CLNT_bready                        (CLNT_bready               ),
    .CLNT_bvalid                        (CLNT_bvalid               ),
    .CLNT_bresp                         (CLNT_bresp                ),
    .CLNT_bid                           (CLNT_bid                  ),

    .CLNT_arready                       (CLNT_arready              ),
    .CLNT_arvalid                       (CLNT_arvalid              ),
    .CLNT_araddr                        (CLNT_araddr               ),
    .CLNT_arid                          (CLNT_arid                 ),
    .CLNT_arlen                         (CLNT_arlen                ),
    .CLNT_arsize                        (CLNT_arsize               ),
    .CLNT_arburst                       (CLNT_arburst              ),

    .CLNT_rready                        (CLNT_rready               ),
    .CLNT_rvalid                        (CLNT_rvalid               ),
    .CLNT_rresp                         (CLNT_rresp                ),
    .CLNT_rdata                         (CLNT_rdata                ),
    .CLNT_rlast                         (CLNT_rlast                ),
    .CLNT_rid                           (CLNT_rid                  ),

    .SOC_awready                        (io_master_awready         ),
    .SOC_awvalid                        (io_master_awvalid         ),
    .SOC_awaddr                         (io_master_awaddr          ),
    .SOC_awid                           (io_master_awid            ),
    .SOC_awlen                          (io_master_awlen           ),
    .SOC_awsize                         (io_master_awsize          ),
    .SOC_awburst                        (io_master_awburst         ),

    .SOC_wready                         (io_master_wready          ),
    .SOC_wvalid                         (io_master_wvalid          ),
    .SOC_wdata                          (io_master_wdata           ),
    .SOC_wstrb                          (io_master_wstrb           ),
    .SOC_wlast                          (io_master_wlast           ),

    .SOC_bready                         (io_master_bready          ),
    .SOC_bvalid                         (io_master_bvalid          ),
    .SOC_bresp                          (io_master_bresp           ),
    .SOC_bid                            (io_master_bid             ),

    .SOC_arready                        (io_master_arready         ),
    .SOC_arvalid                        (io_master_arvalid         ),
    .SOC_araddr                         (io_master_araddr          ),
    .SOC_arid                           (io_master_arid            ),
    .SOC_arlen                          (io_master_arlen           ),
    .SOC_arsize                         (io_master_arsize          ),
    .SOC_arburst                        (io_master_arburst         ),

    .SOC_rready                         (io_master_rready          ),
    .SOC_rvalid                         (io_master_rvalid          ),
    .SOC_rresp                          (io_master_rresp           ),
    .SOC_rdata                          (io_master_rdata           ),
    .SOC_rlast                          (io_master_rlast           ),
    .SOC_rid                            (io_master_rid             ) 
);

endmodule

