`ifndef __STRUCT_SV__
`define __STRUCT_SV__

typedef enum logic[3:0] {  
    OP_NONE,
    OP_LOAD, 
    OP_STORE, 
    OP_BRANCH,
    OP_JALR, 
    OP_REG, 
    OP_JAL,
    OP_CSR,
    OP_IMM,
    OP_LUI,
    OP_AUIPC
} rv_op_e;

typedef struct packed {
    logic [31:0] imm;
    logic [31:0] pc;
    logic [4:0] rs1;
    logic [4:0] rs2;
    logic [4:0] rd;
    logic [3:0] alu_op;
    rv_op_e inst_op;
    logic [2:0] funct3;
    logic ecall_flag;
    logic mret_flag;
    logic fence_i_flag;
    logic pred_res;
} rv_decode_pkt_t;


typedef enum logic[1:0] {  
    BR_TYPE_JAL,
    BR_TYPE_CALL,
    BR_TYPE_RET
} rv_br_type;



`endif


