module WBU (
    input                        clk                        ,
    input                        rst_n                      ,
    input              [  31: 0] MEM_Rdata                  ,
    input              [  31: 0] Ex_result                  ,
    input              [  31: 0] csrs                       ,
    input              [  31: 0] pc                         ,
    input              [   4: 0] rd                         ,
    input              [   3: 0] csr_wen                    ,
    input                        mem_ren                     

    output             [   3: 0] csr_wen_next               ,
    output             [  31: 0] csrd                       ,
    output             [  31: 0] rd_value                   ,
);



    assign                       rd_value                  = (jump_flag == 1'd1)? pc+4 : (mem_ren == 1'b1)?  mem_rdata:(csr_wen !=4'd0)? csrs:EX_result;
    assign 



endmodule                                                           //WBU
