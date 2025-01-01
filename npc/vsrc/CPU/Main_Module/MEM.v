/* verilator lint_off UNUSEDSIGNAL */
// signal not use

    localparam                   i4_NR_KEY                 = 5     ; //键值的个数
    localparam                   i4_KEY_LEN                = 3     ; //键值的长度
    localparam                   i4_DATA_LEN               = 32    ; //数据的长度
    localparam                   i5_NR_KEY                 = 3     ; //键值的个数
    localparam                   i5_KEY_LEN                = 3     ; //键值的长度
    localparam                   i5_DATA_LEN               = 8     ; //数据的长度

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
    output                       jump_flag_next             ,


    input                        valid_last                 ,
    output reg                   ready_last                 ,

    input                        ready_next                 ,
    output reg                   valid_next                 ,

    input              [  31: 0] inst                       ,
    output reg         [  31: 0] inst_next                   
);
 
    wire               [  31: 0] mem_wdata                  ;
    wire               [  31: 0] rdata_8i                   ;
    wire               [  31: 0] rdata_16i                  ;
    wire               [  31: 0] rdata_8u                   ;
    wire               [  31: 0] rdata_16u                  ;
    wire               [  31: 0] araddr                     ;
    wire               [  31: 0] awaddr                     ;
    wire               [  31: 0] rdata                      ;
    wire                         rvalid                     ;
    wire                         arready                    ;
    wire               [   7: 0] wmask                      ;

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
    reg                          valid_last_reg             ;

    reg                          arvalid                    ;



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

        end
        else if(valid_last & ready_next)
            begin
            pc_reg          <=  pc          ;
            mem_ren_reg     <=  mem_ren     ;
            mem_wen_reg     <=  mem_wen     ;
            R_wen_reg       <=  R_wen       ;
            csr_wen_reg     <=  csr_wen     ;
            Ex_result_reg   <=  Ex_result   ;
            csrs_reg        <=  csrs        ;
            rd_reg          <=  rd          ;
            funct3_reg      <=  funct3      ;
            rs2_value_reg   <=  rs2_value   ;
            jump_flag_reg   <=  jump_flag   ;
        end
    end

    always @(posedge clk) begin
        if(!rst_n)
            ready_last <= 1'b1;
        else if(rvalid)
            ready_last <= 1'b1;
        else if(mem_ren & ready_last & valid_last)
            ready_last <= 1'b0;
    end
   always @(posedge clk) begin
       if(!rst_n)
            valid_last_reg <= 0;
        else
            valid_last_reg <= valid_last;
   end

    assign                       valid_next                = (valid_last_reg & ~mem_ren_reg) | rvalid ;

    assign                       Ex_result_next            = Ex_result_reg;
    assign                       csrs_next                 = csrs_reg;
    assign                       pc_next                   = pc_reg;
    assign                       rd_next                   = rd_reg;
    assign                       mem_ren_next              = mem_ren_reg;

    assign                       mem_wdata                 = rs2_value_reg;
    assign                       R_wen_next                = R_wen_reg;
    assign                       jump_flag_next            = jump_flag_reg;
    assign                       csr_wen_next              = csr_wen_reg;


    assign                       araddr                    = Ex_result_reg;
    assign                       awaddr                    = Ex_result_reg;
 
 
    always @(posedge clk) begin
        if(!rst_n)
            inst_next <=0;
        else if(valid_last & ready_next)
            inst_next <= inst;
    end



MuxKeyInternal #(i4_NR_KEY, i4_KEY_LEN, i4_DATA_LEN) i4 (MEM_Rdata, funct3_reg, {i4_DATA_LEN{1'b0}},{
  3'b000,rdata_8i,                                                  // lb
  3'b001,rdata_16i,                                                 // lh
  3'b010,rdata,                                                     // lw
  3'b100,rdata_8u,                                                  // 1bu
  3'b101,rdata_16u                                                  // 1hu
});

MuxKeyInternal #(i5_NR_KEY, i5_KEY_LEN, i5_DATA_LEN) i5 (wmask, funct3_reg, {i5_DATA_LEN{1'b0}},{
  3'b000,8'd1,
  3'b001,8'd2,
  3'b010,8'd4
});


    assign                       rdata_8u                  = {24'd0,rdata[7:0]};
    assign                       rdata_16u                 = {16'd0,rdata[15:0]};

/* verilator lint_off PINMISSING */
SRAM
#(
    .DATA_WIDTH                  (32                        ),
    .ADDR_WIDTH                  (32                        ) 
)SRAM_inst1
(
    .rst_n                       (rst_n                     ),
    .clk                         (clk                       ),
  
    .araddr                      (araddr                    ),
    .arvalid                     (mem_ren_reg               ),
    .arready                     (arready                   ),

    .rready                      (mem_ren_reg               ),
    .rdata                       (rdata                     ),
    .rvalid                      (rvalid                    ),

    .awaddr                      (awaddr                    ),
    .awvalid                     (mem_wen_reg               ),

    .wdata                       (mem_wdata                 ),
    .wstrb                       (wmask                     ),
    .wvalid                      (mem_wen_reg               ) 

);

sext #(
    .DATA_WIDTH                  (8                         ),
    .OUT_WIDTH                   (32                        ) 
) sext_i8
(
    .data                        (rdata[7:0]                ),
    .sext_data                   (rdata_8i                  ) 
);

sext #(
    .DATA_WIDTH                  (16                        ),
    .OUT_WIDTH                   (32                        ) 
) sext_i16
(
    .data                        (rdata[15:0]               ),
    .sext_data                   (rdata_16i                 ) 
);



endmodule                                                           //MEM

