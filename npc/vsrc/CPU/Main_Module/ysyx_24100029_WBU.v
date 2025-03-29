/* verilator lint_off UNUSEDSIGNAL */
// signal not use
`include "../define/para.v"
module ysyx_24100029_WBU (
    input                               clock                      ,
    input                               reset                      ,

    input              [  31: 0]        MEM_Rdata                  ,
    input              [  31: 0]        Ex_result                  ,
    input              [  31: 0]        rd_value                   ,
    input              [   4: 0]        rd                         ,
    input              [   3: 0]        csr_wen                    ,
    input                               R_wen                      ,
    input                               mem_ren                    ,
    input                               jump_flag                  ,


    input                               valid                      ,
    output                              ready                      ,

    output                              valid_next                 ,
    output                              R_wen_next                 ,
    output             [   3: 0]        csr_wen_next               ,
    output             [  31: 0]        csrd                       ,
`ifdef Performance_Count
    input              [  31: 0]        pc                         ,
    output             [  31: 0]        pc_next                    ,
    input                               mem_wen_reg                ,
    output                              mem_wen_flag               ,
    output                              mem_ren_flag               ,
    output             [  31: 0]        paddr                      ,
    input              [  31: 0]        inst                       ,
    output             [  31: 0]        inst_next                  ,
`endif
    output             [  31: 0]        rd_value_next              ,
    output             [   4: 0]        rd_next                     
);


`ifdef Performance_Count
    assign                              mem_ren_flag                = mem_ren;
    assign                              paddr                       = Ex_result;
    assign                              mem_wen_flag                = mem_wen_reg;
    assign                              pc_next                     = pc;
    assign                              inst_next                   = inst;
`endif

    assign                              valid_next                  = valid;
    assign                              rd_value_next               = (jump_flag | (|csr_wen) )? 
                                                                        rd_value : (mem_ren)   ?
                                                                        MEM_Rdata: Ex_result;
    assign                              csrd                        = Ex_result;
    assign                              csr_wen_next                = csr_wen;
    assign                              R_wen_next                  = R_wen&valid;
    assign                              rd_next                     = rd;
    assign                              ready                       = 1'b1;

endmodule                                                           //WBU
