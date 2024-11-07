import "DPI-C" function void fi();


module cpu_v1
(
    input  clk          ,
    input  rst          ,
    input  [31:0] inst  ,
    output reg [31:0] pc,
    output [31:0]rs1_bo
);


parameter PC_MAX = 32'h80000005;
 

wire [4 :0]rs1   ;
wire [4 :0]rs2   ;
wire [4 :0]rd    ;
wire [31:0]imm   ;
wire [2: 0]funct3;
wire [6: 0]opcode;

wire [31:0]rs1_value;
wire [31:0]rs2_value;

wire [31:0]rd_value;


assign rs1_bo = rs1_value;


always @(posedge clk) begin
    if(!rst)
    pc <= 32'h80000000;
    else if(pc == PC_MAX)
    pc <= 32'h80000000;
    else 
    pc <= pc + 1'b1;
end

always @(*)
begin
    if(inst == 32'h00100073)
        fi();
end
 EXU EXU_inst0
 (
    .clk      (clk)         ,
    .rst      (rst)         ,

    .funct3   (funct3)      ,
    .opcode   (opcode)      ,
    .imm      (imm)         ,

    .rs1_value(rs1_value)   ,
    .rs2_value(rs2_value)   ,

    .rd_value (rd_value)    
);


Reg_Stack Reg_Stack_inst0(
    .rst       (rst     )       ,
    .clk       (clk     )       ,
    .rs1       (rs1     )       ,
    .rs2       (rs2     )       ,
    .rd        (rd      )       ,
    .rd_value  (rd_value)       ,
    .wen       (rst)            ,

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
    .opcode  (opcode )
);






endmodule

