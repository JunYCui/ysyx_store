`include "vsrc/para.v"
/* verilator lint_off UNUSEDSIGNAL */
module EXU (
    input clk                 ,
    input rst                 ,
    input [31:0]pc            ,

    input [2:0]funct3         ,
    input [6:0]opcode         ,
    input [31:0]imm           ,

    input [31:0]rs1_value     ,
    input [31:0]rs2_value     ,

    output [31:0]EX_result    
);


localparam NR_KEY_add2   =  5     ;
localparam KEY_LEN_add2   = 7     ;
localparam DATA_LEN_add2  = 32    ;

localparam NR_KEY_add1   =  5     ;
localparam KEY_LEN_add1   = 7     ;
localparam DATA_LEN_add1  = 32    ;



wire [31:0]add_1;
wire [31:0]add_2;


wire [31:0]imm_12u;
wire [31:0]imm_12i;

wire [31:0]imm_20u;
wire [31:0]imm_20i;

wire overflow;
wire compare;


assign imm_12u = {20'd0,imm[11:0]};
assign imm_20u = {12'd0,imm[19:0]};

/* verilator lint_off IMPLICIT */

MuxKeyInternal #(NR_KEY_add2, KEY_LEN_add2, DATA_LEN_add2, 0) i1 (add_2, opcode, {DATA_LEN_add2{1'b0}}, 
{
`R_opcode_ysyx_24100029,   rs2_value            ,
`I1_opcode_ysyx_24100029,  imm_12i              ,
`U0_opcode_ysyx_24100029,  imm_20i              ,
`U1_opcode_ysyx_24100029,  {imm[19:0],12'd0}    ,
`J0_opcode_ysyx_24100029,  {imm_20i[31:1],1'd0}              
}
);

MuxKeyInternal #(NR_KEY_add1, KEY_LEN_add1, DATA_LEN_add1, 0) i2 (add_1, opcode, {DATA_LEN_add1{1'b0}}, 
{
`R_opcode_ysyx_24100029,   rs1_value    ,
`I1_opcode_ysyx_24100029,  rs1_value    ,
`U0_opcode_ysyx_24100029,  32'd0        ,
`U1_opcode_ysyx_24100029,  pc           ,
`J0_opcode_ysyx_24100029,  pc           
}
);


ALU #(
    .BW(6'd32)
) ALU_i0
(
    .d1     (add_1)     ,
    .d2     (add_2)     ,
    .choice (funct3)    ,
    .res    (EX_result) ,
    .overflow(overflow) ,
    .compare (compare) 

);

sext #(
    .DATA_WIDTH(12),
    .OUT_WIDTH(32)
) sext_i12
(
    .data(imm[11:0])          ,
    .sext_data(imm_12i)
);

sext #(
    .DATA_WIDTH(20),
    .OUT_WIDTH(32)
) sext_i20
(
    .data(imm[19:0])          ,
    .sext_data(imm_20i)
);



endmodule


