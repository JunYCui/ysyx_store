module CSR #(
    parameter                    CSR_WIDTH                 = 32    ,
    parameter                    RESET_VAL                 = 0     
)
(
    input                        clk                        ,
    input                        rst_n                      ,
    input              [  31: 0] mepc_in                    ,
    input              [  31: 0] mcause_in                  ,
    input              [  31: 0] mstatus_in                 ,
    input              [  31: 0] mtvec_in                   ,
    input              [   3: 0] csr_wen                    ,

    output             [  31: 0] mepc_out                   ,
    output             [  31: 0] mcause_out                 ,
    output             [  31: 0] mstatus_out                ,
    output             [  31: 0] mtvec_out                   
);


Reg #(
    .WIDTH                       (CSR_WIDTH                 ),
    .RESET_VAL                   (RESET_VAL                 ) 
) CSR_MEPC(
    .clk                         (clk                       ),
    .rst                         (rst_n                     ),
    .din                         (mepc_in                   ),
    .dout                        (mepc_out                  ),
    .wen                         (csr_wen[0]                ) 
);

Reg #(
    .WIDTH                       (CSR_WIDTH                 ),
    .RESET_VAL                   (RESET_VAL                 ) 
) CSR_MCAUSE(
    .clk                         (clk                       ),
    .rst                         (rst_n                     ),
    .din                         (mcause_in                 ),
    .dout                        (mcause_out                ),
    .wen                         (csr_wen[1]                ) 
);

Reg #(
    .WIDTH                       (CSR_WIDTH                 ),
    .RESET_VAL                   (32'h1800                  ) 
) CSR_MSTATUS(
    .clk                         (clk                       ),
    .rst                         (rst_n                     ),
    .din                         (mstatus_in                ),
    .dout                        (mstatus_out               ),
    .wen                         (csr_wen[2]                ) 
);

Reg #(
    .WIDTH                       (CSR_WIDTH                 ),
    .RESET_VAL                   (RESET_VAL                 ) 
) CSR_MTVEC(
    .clk                         (clk                       ),
    .rst                         (rst_n                     ),
    .din                         (mtvec_in                  ),
    .dout                        (mtvec_out                 ),
    .wen                         (csr_wen[3]                ) 
);



endmodule                                                           //CSR
