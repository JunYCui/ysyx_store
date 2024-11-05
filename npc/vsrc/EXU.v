`include "vsrc/para.v"
/* verilator lint_off UNUSEDSIGNAL */
module EXU (
    input clk                 ,
    input rst                 ,

    input [2:0]funct3         ,
    input [6:0]opcode         ,
    input [31:0]imm           ,

    input [31:0]rs1_value     ,
    input [31:0]rs2_value     ,

    output [31:0]rd_value     
);


localparam i2_NR_KEY    = 2     ;
localparam i2_KEY_LEN   = 7     ;
localparam i2_DATA_LEN  = 32    ;


wire [31:0]add_1;
wire [31:0]add_2;
wire [31:0]ALU_res;

wire [31:0]imm_12u;
wire [31:0]imm_12i;

wire overflow;
wire compare;


assign imm_12u = imm;
assign rd_value = ALU_res;
assign add_1 = rs1_value;

/* verilator lint_off IMPLICIT */

MuxKeyInternal #(i2_NR_KEY, i2_KEY_LEN, i2_DATA_LEN, 0) i0 (add_2, opcode, {i2_DATA_LEN{1'b0}}, 
{
`R_opcode,   rs2_value,
`I1_opcode,  imm_12i
}
);


ALU #(
    .BW(6'd32)
) ALU_i0
(
    .d1     (add_1)     ,
    .d2     (add_2)     ,
    .choice (funct3)    ,
    .res    (ALU_res)   ,
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

endmodule


