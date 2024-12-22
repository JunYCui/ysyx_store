/* verilator lint_off UNUSEDSIGNAL */
// signal not use
module WBU (
    input                        clk                        ,
    input                        rst_n                      ,

    input              [  31: 0] MEM_Rdata                  ,
    input              [  31: 0] Ex_result                  ,
    input              [  31: 0] csrs                       ,
    input              [  31: 0] pc                         ,
    input              [   4: 0] rd                         ,
    input              [   3: 0] csr_wen                    ,
    input                        R_wen                      ,
    input                        mem_ren                    ,
    input                        jump_flag                  ,
    input                        branch_flag                ,

    output                       R_wen_next                 ,
    output             [   3: 0] csr_wen_next               ,
    output             [  31: 0] csrd                       ,
    output             [  31: 0] rd_value                   ,
    output             [   4: 0] rd_next                    ,
    output                       branch_flag_next           ,
);
    reg                [  31: 0] MEM_Rdata_reg              ;
    reg                [  31: 0] Ex_result_reg              ;
    reg                [  31: 0] csrs_reg                   ;
    reg                [  31: 0] pc_reg                     ;
    reg                [   4: 0] rd_reg                     ;
    reg                [   3: 0] csr_wen_reg                ;
    reg                          R_wen_reg                  ;
    reg                          mem_ren_reg                ;
    reg                          jump_flag_reg              ;
    reg                          branch_flag_reg            ;
always @(posedge clk) begin
    if(!rst_n)begin
        MEM_Rdata_reg    <= 0 ;
        Ex_result_reg    <= 0 ;
        csrs_reg         <= 0 ;
        pc_reg           <= 0 ;
        rd_reg           <= 0 ;
        csr_wen_reg      <= 0 ;
        R_wen_reg        <= 0 ;
        mem_ren_reg      <= 0 ;
        jump_flag_reg    <= 0 ;
        branch_flag_reg  <= 0 ;
    end
    else begin
        MEM_Rdata_reg    <= MEM_Rdata;
        Ex_result_reg    <= Ex_result;
        csrs_reg         <= csrs     ;
        pc_reg           <= pc       ;
        rd_reg           <= rd       ;
        csr_wen_reg      <= csr_wen  ;
        R_wen_reg        <= R_wen    ;
        mem_ren_reg      <= mem_ren  ;
        jump_flag_reg    <= jump_flag;
        branch_flag_reg  <= branch_flag;
    end
end



    assign                       rd_value                  = (jump_flag_reg == 1'd1)        ? 
                                                              pc_reg+4: (mem_ren_reg == 1'b1)   ?
                                                              MEM_Rdata_reg:(csr_wen_reg !=4'd0)?
                                                              csrs_reg:Ex_result_reg;
    assign                       csrd                      = Ex_result_reg;
    assign                       csr_wen_next              = csr_wen_reg;
    assign                       R_wen_next                = R_wen_reg;
    assign                       rd_next                   = rd_reg;
    assign                       branch_flag_next          = branch_flag_reg;

endmodule                                                           //WBU
