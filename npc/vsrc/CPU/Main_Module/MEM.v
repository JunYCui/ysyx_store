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
    input                        branch_flag                ,

    output                       R_wen_next                 ,
    output             [  31: 0] MEM_Rdata                  ,
    output             [   3: 0] csr_wen_next               ,
    output             [  31: 0] Ex_result_next             ,
    output             [  31: 0] csrs_next                  ,
    output             [  31: 0] pc_next                    ,
    output             [   4: 0] rd_next                    ,
    output                       mem_ren_next               ,
    output                       jump_flag_next             ,
    output                       branch_flag_next            
);
 
    wire               [  31: 0] mem_wdata                  ;
    wire                         Data_mem_valid             ;


    reg                [  31: 0] pc_reg                     ;
    reg                          mem_ren_reg                ;
    reg                          mem_wen_reg                ;
    reg                          R_wen_reg                  ;
    reg                [   3: 0] csr_wen_reg                ;
    reg                [  31: 0] Ex_result_reg              ;
    reg                [  31: 0] csrs_reg                   ;
    reg                [   4: 0] rd_reg                     ;
    reg                [   2: 0] funct3_reg                 ;
    reg                [  31: 0] rs2_value_reg              ;
    reg                          jump_flag_reg              ;
    reg                          branch_flag_reg            ;

    always @(posedge clk) begin
        if(!rst_n)begin
            pc_reg          <=  0         ;
            mem_ren_reg     <=  0         ;
            mem_wen_reg     <=  0         ;
            R_wen_reg       <=  0         ;
            csr_wen_reg     <=  0         ;
            Ex_result_reg   <=  0         ;
            csrs_reg        <=  0         ;
            rd_reg          <=  0         ;
            funct3_reg      <=  0         ;
            rs2_value_reg   <=  0         ;
            jump_flag_reg   <=  0         ;
            branch_flag_reg <=  0         ;
        end
        else
            begin
            pc_reg          <=  pc        ;
            mem_ren_reg     <=  mem_ren   ;
            mem_wen_reg     <=  mem_wen   ;
            R_wen_reg       <=  R_wen     ;
            csr_wen_reg     <=  csr_wen   ;
            Ex_result_reg   <=  Ex_result ;
            csrs_reg        <=  csrs      ;
            rd_reg          <=  rd        ;
            funct3_reg      <=  funct3    ;
            rs2_value_reg   <=  rs2_value ;
            jump_flag_reg   <=  jump_flag ;
            branch_flag_reg <=  branch_flag;
        end
    end


    assign                       Ex_result_next            = Ex_result_reg;
    assign                       csrs_next                 = csrs_reg;
    assign                       pc_next                   = pc_reg;
    assign                       rd_next                   = rd_reg;
    assign                       mem_ren_next              = mem_ren_reg;

    assign                       mem_wdata                 = rs2_value_reg;
    assign                       Data_mem_valid            = mem_ren_reg|mem_wen_reg;
    assign                       R_wen_next                = R_wen_reg;
    assign                       jump_flag_next            = jump_flag_reg;
    assign                       csr_wen_next              = csr_wen_reg;
    assign                       branch_flag_next          = branch_flag_reg;

AM Data_MEM_inst(
    .valid                       (Data_mem_valid            ),
    .raddr                       (Ex_result_reg             ),
    .wdata                       (mem_wdata                 ),
    .funct3                      (funct3_reg                ),
    .waddr                       (Ex_result_reg             ),
    .wen                         (mem_wen_reg               ),
    .rd_data                     (MEM_Rdata                 ) 
);



endmodule                                                           //MEM

