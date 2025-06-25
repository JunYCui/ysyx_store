`include "../define/para.sv"
`include "../define/interface.sv"
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
    wire                                IFU_pred_res                ;
    wire               [  31: 0]        IFU_pred_pc                 ;


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
    wire                                IDU_pred_res                ;

    wire                                IDU_inv_flag                ;
    wire                                IDU_branch_flag             ;
    wire                                IDU_jal_flag                ;
    wire                                IDU_jalr_flag               ;
    wire               [  31: 0]        IDU_jal_pc                  ;
    wire               [  31: 0]        IDU_add1_value              ;
    wire               [  31: 0]        IDU_add2_value              ;
    wire               [   3: 0]        IDU_alu_opcode              ;
    wire               [   4: 0]        IDU_rs1                     ;
    wire               [   4: 0]        IDU_rs2                     ;
    wire               [  31: 0]        IDU_a0_value                ;
    wire               [  31: 0]        IDU_mepc_out                ;
    wire               [  31: 0]        IDU_mtvec_out               ;
    wire               [  31: 0]        IDU_pred_pc                 ;

    wire                                IDU_clear                   ;
    wire               [  31: 0]        IDU_branch_pc               ;
    wire                                IDU_valid                   ;
    wire                                IDU_ready                   ;
    wire               [  31: 0]        IDU_inst                    ;//debug
    wire                                IDU_fence_i_flag            ;
/************************* EXU ********************/
    wire               [  31: 0]        EXU_branch_pc               ;
    wire                                EXU_jalr_flag               ;
    wire                                EXU_jal_flag                ;
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
    wire               [  31: 0]        EXU_pred_pc                 ;
    wire                                EXU_pred_res                ;
    wire                                EXU_clear                   ;

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
    wire                                br_valid                    ;
    wire                                br_is_taken                 ;
    wire               [  31: 0]        br_pc                       ;
    wire               [   1: 0]        br_pc_type                  ;
    wire               [  31: 0]        br_npc                      ;
    wire                                dnpc_flag                   ;
    wire                                EXU_inst_clear              ;
    wire               [  31: 0]        dnpc                        ;
    wire                                icache_clr                  ;
    wire                                stall                       ;
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

    wire [31:0]pred_error;

    assign                              total_count                 = InstR_count + InstI_count + InstS_count + InstB_count + InstU_count + InstJ_count + InstM_count;

    always @(posedge clock) begin
        if(reset)
            instd_clr_num <= 0;
        else if(EXU_inst_clear)
            instd_clr_num <= instd_clr_num + 32'd1 ;
    end

    always @(*)begin
        if(WBU_inst == 32'h00100073 & WBU_valid) begin
        $display("\033[0m\033[1;34m | icache addr \t| flash   \t| sdram   \t| \033[0m");
        $display("\033[0m\033[1;34m | hit         \t| %-d     \t| %-d     \t| \033[0m",flash_hit,sdram_hit);
        $display("\033[0m\033[1;34m | miss        \t| %-d     \t| %-d     \t| \033[0m",flash_miss,sdram_miss);
        $display("\033[0m\033[1;34m | hit_rate    \t| %-d     \t| %-d     \t| \033[0m",flash_hit*100/(flash_hit+flash_miss),sdram_hit*100/(sdram_hit+sdram_miss));
        $display("\033[0m\033[1;34m | total_count \t| InstR_count \t| InstI_count \t| InstS_count \t| InstU_count \t| InstB_count \t| InstJ_count \t| InstM_count \t| \033[0m");
        $display("\033[0m\033[1;34m | %d \t| %d \t| %d \t| %d \t| %d \t| %d \t| %d \t| %d \t| \033[0m",total_count,InstR_count,InstI_count,InstS_count, InstU_count,InstB_count,InstJ_count,InstM_count);
        $display("\033[0m\033[1;34m | fetch_inst \t| flush_decoder_i \t| rate of pred_success    \t|\033[0m");
        $display("\033[0m\033[1;34m | %d \t| %d \t\t|  %d \t|\033[0m",fetch_inst,instd_clr_num,100-100*pred_error/fetch_inst);
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

    axi4_if axi_bus0();
    axi4_if axi_bus1();
    axi4_if axi_bus2();

sram u_sram(
    .clock                              (clock                     ),
    .reset                              (reset                     ),
    .sram_axi                           (axi_bus0.slave            ) 
);


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



  ysyx_24100029_Control Control_inst0 (

    .EXU_branch_pc                      (EXU_branch_pc             ),
    .Ex_result                          (EXU_Ex_result             ),
    .MEM_rd_value                       (WBU_rd_value              ),
    .IDU_rs1_value                      (IDU_rs1_value             ),
    .IDU_rs2_value                      (IDU_rs2_value             ),

    .EXU_branch_flag                    (EXU_branch_flag           ),
    .IDU_jal_flag                       (IDU_jal_flag              ),
    .EXU_jalr_flag                      (EXU_jalr_flag             ),
    .fence_i_flag                       (EXU_fence_i_flag          ),

    .IDU_jal_pc                         (IDU_jal_pc                ),
    .IDU_rs1                            (IDU_rs1                   ),
    .IDU_rs2                            (IDU_rs2                   ),
    .EXU_pc                             (EXU_pc                    ),
    .IDU_pc                             (IDU_pc                    ),
    .EXU_pred_res                       (EXU_pred_res              ),
    .IDU_pred_res                       (IDU_pred_res              ),
    .EXU_pred_pc                        (EXU_pred_pc               ),

    .IDU_valid                          (IDU_valid                 ),
    .EXU_valid                          (EXU_valid                 ),
    .MEM_valid                          (LSU_valid                 ),
    .LSU_ready                          (LSU_ready                 ),
    .EXU_ready                          (EXU_ready                 ),

    .EXU_rd                             (EXU_rd                    ),
    .MEM_rd                             (LSU_rd                    ),
    .EXU_R_Wen                          (EXU_R_wen                 ),
    .MEM_R_Wen                          (LSU_R_wen                 ),
    .EXU_mem_ren                        (EXU_mem_ren               ),

    .br_is_taken                        (br_is_taken               ),
    .br_npc                             (br_npc                    ),
    .br_pc                              (br_pc                     ),
    .br_pc_type                         (br_pc_type                ),
    .br_valid                           (br_valid                  ),

    .stall                              (stall                     ),
    .EXU_rs1_in                         (EXU_rs1_in                ),
    .EXU_rs2_in                         (EXU_rs2_in                ),
    .dnpc                               (dnpc                      ),
    .icache_clr                         (icache_clr                ),
    .EXU_clear                          (EXU_clear                 ),
    .IDU_clear                          (IDU_clear                 ),
    .dnpc_flag                          (dnpc_flag                 ) 
  );







ysyx_24100029_IFU  #(
    .ResetValue                         (ResetValue                ) 
)
IFU_Inst0
(
    .clock                              (clock                     ),
    .reset                              (reset                     ),
    .dnpc                               (dnpc                      ),
    .dnpc_flag                          (dnpc_flag                 ),
    .ifu_pc                             (IFU_pc                    ),
    .ifu_inst                           (IFU_inst                  ),
    .icache_clr                         (icache_clr                ),
    .ifu_pred_pc                        (IFU_pred_pc               ),
    .ifu_pred_res                       (IFU_pred_res              ),
    .icache_axi                         (axi_bus2.master           ),
    .stall                              (stall                     ),

    .req                                (IFU_req                   ),
    .br_is_taken                        (br_is_taken               ),
    .br_valid                           (br_valid                  ),
    .br_npc                             (br_npc                    ),
    .br_pc                              (br_pc                     ),
    .br_pc_type                         (br_pc_type                ),
`ifdef Performance_Count
    .pred_error                         (pred_error),
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

    .pred_res                           (IFU_pred_res              ),
    .pred_pc                            (IFU_pred_pc               ),
    .inst                               (IFU_inst                  ),
    .pc                                 (IFU_pc                    ),
    .rd_value                           (WBU_rd_value              ),
    .csrd                               (WBU_csrd                  ),
    .rd                                 (WBU_rd                    ),
    .R_wen                              (WBU_R_wen                 ),
    .csr_wen                            (WBU_csr_wen               ),
    

    .stall                              (stall                 ),
    .clear                              (IDU_clear                 ),
    .EXU_rs1_in                         (EXU_rs1_in                ),
    .EXU_rs2_in                         (EXU_rs2_in                ),
    .branch_pc                          (IDU_branch_pc             ),
    .rd_next                            (IDU_rd                    ),
    .funct3                             (IDU_funct3                ),
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
    .jal_flag                           (IDU_jal_flag              ),
    .jalr_flag                          (IDU_jalr_flag             ),
    .jal_pc                             (IDU_jal_pc                ),
    .alu_opcode                         (IDU_alu_opcode            ),

    .rs1                                (IDU_rs1                   ),
    .rs2                                (IDU_rs2                   ),
    .a0_value                           (IDU_a0_value              ),
    .mepc_out                           (IDU_mepc_out              ),
    .mtvec_out                          (IDU_mtvec_out             ),
    .pc_next                            (IDU_pc                    ),
    .pred_pc_next                       (IDU_pred_pc               ),
    .pred_res_next                      (IDU_pred_res              ),

    .valid_last                         (IFU_valid                 ),
    .ready_last                         (IDU_ready                 ),
`ifdef Performance_Count
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

ysyx_24100029_EXU EXU_Inst0(
    .clock                              (clock                     ),
    .reset                              (reset                     ),
    .clear                              (EXU_clear                 ),

    .pred_res                           (IDU_pred_res              ),
    .pred_pc                            (IDU_pred_pc               ),
    .funct3                             (IDU_funct3                ),
    .csr_wen                            (IDU_csr_wen               ),
    .R_wen                              (IDU_R_wen                 ),
    .mem_wen                            (IDU_mem_wen               ),
    .mem_ren                            (IDU_mem_ren               ),
    .rd                                 (IDU_rd                    ),
    .branch_pc                          (IDU_branch_pc             ),
    .pc                                 (IDU_pc                    ),

    .jalr_flag                          (IDU_jalr_flag             ),
    .jal_flag                           (IDU_jal_flag              ),
    .alu_opcode                         (IDU_alu_opcode            ),
    .inv_flag                           (IDU_inv_flag              ),
    .branch_flag                        (IDU_branch_flag           ),
    .fetch_i_flag                       (IDU_fence_i_flag          ),

    .add2                               (IDU_add2_value            ),
    .add1                               (IDU_add1_value            ),
    .rs2_value                          (EXU_rs2_in                ),
    .rd_value                           (IDU_rd_value              ),

    .branch_pc_next                     (EXU_branch_pc             ),
    .branch_flag_next                   (EXU_branch_flag           ),
    .jalr_flag_next                     (EXU_jalr_flag             ),
    .jal_flag_next                      (EXU_jal_flag              ),
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
    .pc_next                            (EXU_pc                    ),
    .pred_res_next                      (EXU_pred_res              ),
    .pred_pc_next                       (EXU_pred_pc               ),

`ifdef Performance_Count
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
    .jump_flag                          (EXU_jal_flag || EXU_jalr_flag),

    .R_wen_next                         (LSU_R_wen                 ),
    .LSU_Rdata                          (LSU_Rdata                 ),
    .csr_wen_next                       (LSU_csr_wen               ),
    .Ex_result_next                     (LSU_Ex_result             ),
    .rd_value_next                      (LSU_rd_value              ),
    .rd_next                            (LSU_rd                    ),
    .mem_ren_next                       (LSU_mem_ren               ),
    .jump_flag_next                     (LSU_jump_flag             ),

    .lsu_axi                            (axi_bus1.master           ),
    
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
ysyx_24100029_Aribiter Aribiter_inst(
    .clock                              (clock                     ),
    .reset                              (reset                     ),

    .IFU_req                            (IFU_req                   ),
    .LSU_req                            (LSU_req                   ),

    .ifu_axi                            (axi_bus2.slave            ),
    .lsu_axi                            (axi_bus1.slave            ),

    .aribiter_axi                       (axi_bus0.master           )
    
);



endmodule

