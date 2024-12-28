module Reg_Stack(
    input                        rst_n                      ,
    input                        clk                        ,
    input              [  31: 0] pc                         ,
    input                        ecall_flag                 ,

    input              [   4: 0] rs1                        ,
    input              [   4: 0] rs2                        ,
    input              [   4: 0] rd                         ,
    input              [  31: 0] rd_value                   ,


    input              [  31: 0] csr_addr                   ,
    input                        R_wen                      ,
    input              [   3: 0] csr_wen                    ,
    input              [  31: 0] csrd                       ,

    output             [  31: 0] rs1_value                  ,
    output             [  31: 0] rs2_value                  ,
    output             [  31: 0] a0_value                   ,
    output             [  31: 0] csrs                       ,
    output             [  31: 0] mepc_out                   ,
    output             [  31: 0] mtvec_out                   
);

    wire               [  31: 0] wdata                      ;

    wire               [  31: 0] mcause_out                 ;
    wire               [  31: 0] mstatus_out                ;



    assign                       wdata                     = (rd == 5'd0)? 32'd0:rd_value;

    assign                       csrs                      = (csr_addr == 32'h341)? mepc_out   :
                                                             (csr_addr == 32'h342)? mcause_out :
                                                             (csr_addr == 32'h300)? mstatus_out:
                                                             (csr_addr == 32'h305)? mtvec_out:32'd0;



CSR #(32,0) CSR_inst(
    .clk                         (clk                       ),
    .rst_n                       (rst_n                     ),

    .pc                          (pc                        ),
    .ecall_flag                  (ecall_flag                ),
    .csrd                        (csrd                      ),


    .csr_wen                     (csr_wen                   ),

    .mepc_out                    (mepc_out                  ),
    .mcause_out                  (mcause_out                ),
    .mstatus_out                 (mstatus_out               ),
    .mtvec_out                   (mtvec_out                 ) 


);

RegisterFile #(5, 32) Reg_inst(
    .clk                         (clk                       ),
    .wdata                       (wdata                     ),
    .waddr                       (rd                        ),
    .wen                         (R_wen                     ),
    .rst_n                       (rst_n                     ),
    .rs1_addr                    (rs1                       ),
    .rs2_addr                    (rs2                       ),

    .rs1_value                   (rs1_value                 ),
    .rs2_value                   (rs2_value                 ),
    .a0_value                    (a0_value                  ) 
);


endmodule

