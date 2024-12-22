/* verilator lint_off UNUSEDSIGNAL */
// signal not use
module MEM (
    input                        clk                        ,
    input                        rst_n                      ,
    input              [  31: 0] pc                         ,
    input                        mem_ren                    ,
    input                        mem_wen                    ,
    input                        R_wen                      ,
    input              [   3: 0] csr_wen                    ,
    input              [  31: 0] Ex_result                  ,
    input              [  31: 0] csrs                       ,
    input              [   4: 0] rd                         ,
    input              [   2: 0] funct3                     ,
    input              [  31: 0] rs2_value                  ,
    input                        jump_flag                  ,

    output                       R_wen_next                 ,
    output             [  31: 0] MEM_Rdata                  ,
    output             [   3: 0] csr_wen_next               ,
    output             [  31: 0] Ex_result_next             ,
    output             [  31: 0] csrs_next                  ,
    output             [  31: 0] pc_next                    ,
    output             [   4: 0] rd_next                    ,
    output                       mem_ren_next               ,
    output                       jump_flag_next              
);

    wire               [  31: 0] mem_wdata                  ;
    wire                         Data_mem_valid             ;

    assign                       Ex_result_next            = Ex_result;
    assign                       csrs_next                 = csrs;
    assign                       pc_next                   = pc;
    assign                       rd_next                   = rd;
    assign                       mem_ren_next              = mem_ren;

    assign                       mem_wdata                 = rs2_value;
    assign                       Data_mem_valid            = mem_ren|mem_wen;
    assign                       R_wen_next                = R_wen;
    assign                       jump_flag_next            = jump_flag;
    assign                       csr_wen_next              = csr_wen;

AM Data_MEM_inst(
    .valid                       (Data_mem_valid            ),
    .raddr                       (Ex_result                 ),
    .wdata                       (mem_wdata                 ),
    .funct3                      (funct3                    ),
    .waddr                       (Ex_result                 ),
    .wen                         (mem_wen                   ),
    .rd_data                     (MEM_Rdata                 ) 
);



endmodule                                                           //MEM

