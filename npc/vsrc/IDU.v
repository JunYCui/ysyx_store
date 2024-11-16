`include "./vsrc/para.v"
/* verilator lint_off UNUSEDPARAM */

localparam i0_NR_KEY  = 9; //键值的个数
localparam i0_KEY_LEN = 7; //键值的长度
localparam i0_DATA_LEN= 3; //数据的长度

localparam i1_NR_KEY  = 6;
localparam i1_KEY_LEN = 3;
localparam i1_DATA_LEN= 32;


module IDU(
    input [31:0]inst      ,
    output[4 :0]rs1     ,
    output[4 :0]rs2     ,
    output[4 :0]rd      ,
    output[31:0]imm     ,
    output[2: 0]funct3  ,
    output[6: 0]opcode  ,
    output reg_wen      ,
    output jump_flag
);



wire [2:0]Type;

assign opcode =   inst[6:0]  ;    
assign rs1    =   inst[19:15];
assign rs2    =   inst[24:20];
assign funct3 =   (Type == `J_Type_ysyx_24100029 || Type == `U_Type_ysyx_24100029 )? 3'd0:inst[14:12];
assign rd     =   (Type == `S_Type_ysyx_24100029 || Type == `B_Type_ysyx_24100029)? 5'd0:inst[11:7] ;

assign reg_wen = (Type == `B_Type_ysyx_24100029 || Type == `S_Type_ysyx_24100029 )? 1'b0:1'b1;
assign jump_flag = (opcode == `I2_opcode_ysyx_24100029 || opcode == `J0_opcode_ysyx_24100029)? 1'b1:1'b0;

/* verilator lint_off IMPLICIT */

/* imm 处理*/
// choose type
MuxKeyInternal #(i0_NR_KEY, i0_KEY_LEN, i0_DATA_LEN) i0 (Type, opcode, {i0_DATA_LEN{1'b0}}, 
{`R_opcode_ysyx_24100029 ,  `R_Type_ysyx_24100029,
 `B_opcode_ysyx_24100029 ,  `B_Type_ysyx_24100029,
 `S_opcode_ysyx_24100029 ,  `S_Type_ysyx_24100029,
 `I0_opcode_ysyx_24100029, `I_Type_ysyx_24100029,
 `I1_opcode_ysyx_24100029, `I_Type_ysyx_24100029,
 `I2_opcode_ysyx_24100029, `I_Type_ysyx_24100029,
 `J0_opcode_ysyx_24100029, `J_Type_ysyx_24100029,
 `U0_opcode_ysyx_24100029, `U_Type_ysyx_24100029,
 `U1_opcode_ysyx_24100029, `U_Type_ysyx_24100029
 });

MuxKeyInternal #(i1_NR_KEY, i1_KEY_LEN, i1_DATA_LEN, 0) i1 (imm, Type, {i1_DATA_LEN{1'b0}}, 
{`R_Type_ysyx_24100029,    {i1_DATA_LEN{1'b0}},
 `I_Type_ysyx_24100029,    {20'd0,inst[31:20]},
 `U_Type_ysyx_24100029,    {12'd0,inst[31:12]},
 `J_Type_ysyx_24100029,    {12'd0,inst[31],inst[19:12],inst[20],inst[30:21]},
 `B_Type_ysyx_24100029,    {20'd0,inst[31],inst[7],inst[30:25],inst[11:8]},
 `S_Type_ysyx_24100029,    {20'd0,inst[31:25],inst[11:7]}
 });





endmodule

