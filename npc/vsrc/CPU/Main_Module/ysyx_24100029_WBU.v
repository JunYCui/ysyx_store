/* verilator lint_off UNUSEDSIGNAL */
// signal not use

module ysyx_24100029_WBU (
    input                        clock                      ,
    input                        reset                      ,

    input              [  31: 0] MEM_Rdata                  ,
    input              [  31: 0] Ex_result                  ,
    input              [  31: 0] csrs                       ,
    input              [  31: 0] pc                         ,
    input              [   4: 0] rd                         ,
    input              [   3: 0] csr_wen                    ,
    input                        R_wen                      ,
    input                        mem_ren                    ,
    input                        jump_flag                  ,
    input              [  31: 0] inst                       ,

    input                        valid                      ,
    output                       ready                      ,

    output reg                   valid_next                 ,
    output reg         [  31: 0] pc_next                    ,
    output reg         [  31: 0] inst_next                  ,
    output                       R_wen_next                 ,
    output             [   3: 0] csr_wen_next               ,
    output             [  31: 0] csrd                       ,
    output             [  31: 0] rd_value                   ,
    output             [   4: 0] rd_next                     
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

    always @(posedge clock) begin
        if(reset)
            valid_next <= 0;
        else
            valid_next <= valid;
    end
    always @(posedge clock) begin
        if(reset)begin
            inst_next <= 0;
            pc_next <= 0;
        end
        else if(valid & ready)begin
            inst_next <= inst;
            pc_next <= pc;
        end
    end


always @(posedge clock) begin
    if(reset)begin
        MEM_Rdata_reg <= 0;
        Ex_result_reg <= 0;
        csrs_reg      <= 0;
        pc_reg        <= 0;
        rd_reg        <= 0;
        csr_wen_reg   <= 0;
        R_wen_reg     <= 0;
        mem_ren_reg   <= 0;
        jump_flag_reg <= 0;
    end
    else if(valid & ready) begin
        MEM_Rdata_reg    <= MEM_Rdata;
        Ex_result_reg    <= Ex_result;
        csrs_reg         <= csrs     ;
        pc_reg           <= pc       ;
        rd_reg           <= rd       ;
        csr_wen_reg      <= csr_wen  ;
        R_wen_reg        <= R_wen    ;
        mem_ren_reg      <= mem_ren  ;
        jump_flag_reg    <= jump_flag;
    end

end
    assign                       rd_value                  =    (jump_flag_reg == 1'd1)           ? 
                                                                pc_reg+4: (mem_ren_reg == 1'b1)   ?
                                                                MEM_Rdata_reg:(csr_wen_reg !=4'd0)?
                                                                csrs_reg:Ex_result_reg;
    assign                       csrd                      = Ex_result_reg;
    assign                       csr_wen_next              = csr_wen_reg;
    assign                       R_wen_next                = R_wen_reg;
    assign                       rd_next                   = rd_reg;
    assign                       ready                     = 1'b1;

endmodule                                                           //WBU
