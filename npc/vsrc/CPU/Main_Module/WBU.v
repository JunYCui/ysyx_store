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

    output                       R_wen_next                 ,
    output             [   3: 0] csr_wen_next               ,
    output             [  31: 0] csrd                       ,
    output             [  31: 0] rd_value                   ,
    output             [   4: 0] rd_next                     
);

    assign                       rd_value                  = (jump_flag == 1'd1)        ? 
                                                              pc+4: (mem_ren == 1'b1)   ?
                                                              MEM_Rdata:(csr_wen !=4'd0)?
                                                              csrs:Ex_result;
    assign                       csrd                      = Ex_result;
    assign                       csr_wen_next              = csr_wen;
    assign                       R_wen_next                = R_wen;
    assign                       rd_next                   = rd;


endmodule                                                           //WBU
