import "DPI-C" function void fi();


module cpu_ysyx_24100029
(
    input  clk          ,
    input  rst          ,
    input  [31:0] inst  ,
    output reg [31:0] pc,
    output [31:0]rs1_bo
);


 

wire [4 :0]rs1   ;
wire [4 :0]rs2   ;
wire [4 :0]rd    ;
wire [31:0]imm   ;
wire [2: 0]funct3;
wire [6: 0]opcode;
wire reg_wen;
wire jump_flag;

wire [31:0]rs1_value;
wire [31:0]rs2_value;

wire [31:0]rd_value ;
wire [31:0]snpc     ;
wire [31:0]dnpc     ;
wire [31:0]npc      ;
wire [31:0]EX_result;

assign rs1_bo = rs1_value;
assign snpc = pc + 4;
assign npc = (jump_flag == 1'd1)? dnpc:snpc ;
assign rd_value = (jump_flag == 1'd1)? pc+4 : EX_result ;
assign dnpc = (jump_flag == 1'd1)? EX_result: pc+4;

always @(posedge clk) begin
    if(!rst)
    pc <= 32'h80000000;
    else 
    pc <= npc;
end
/*
always @(*)
begin
    if(inst == 32'h00100073)
        fi();
end
*/
 EXU EXU_inst0
 (
    .clk      (clk)         ,
    .rst      (rst)         ,
    .pc       (pc)          ,

    .funct3   (funct3)      ,
    .opcode   (opcode)      ,
    .imm      (imm)         ,

    .rs1_value(rs1_value)   ,
    .rs2_value(rs2_value)   ,

    .EX_result (EX_result)  
);


Reg_Stack Reg_Stack_inst0(
    .rst       (rst     )       ,
    .clk       (clk     )       ,
    .rs1       (rs1     )       ,
    .rs2       (rs2     )       ,
    .rd        (rd      )       ,
    .rd_value  (rd_value)       ,
    .wen       (reg_wen)        ,

    .rs1_value (rs1_value)      ,
    .rs2_value (rs2_value)
);


IDU IDU_inst0(
    .inst    (inst   ),
    .rs1     (rs1    ),
    .rs2     (rs2    ),
    .rd      (rd     ),
    .imm     (imm    ),
    .funct3  (funct3 ),
    .opcode  (opcode ),
    .reg_wen (reg_wen),
    .jump_flag(jump_flag)
);






endmodule

