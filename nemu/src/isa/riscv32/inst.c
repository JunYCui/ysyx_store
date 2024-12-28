/***************************************************************************************
* Copyright (c) 2014-2022 Zihao Yu, Nanjing University
*
* NEMU is licensed under Mulan PSL v2.
* You can use this software according to the terms and conditions of the Mulan PSL v2.
* You may obtain a copy of Mulan PSL v2 at:
*          http://license.coscl.org.cn/MulanPSL2
*
* THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
* EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
* MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
*
* See the Mulan PSL v2 for more details.
***************************************************************************************/

#include "local-include/reg.h"
#include <cpu/cpu.h>
#include <cpu/ifetch.h>
#include <cpu/decode.h>
#include <isa-def.h>
word_t isa_raise_intr(word_t NO, vaddr_t epc);

#define R(i) gpr(i)
#define Mr vaddr_read
#define Mw vaddr_write

enum {
  TYPE_I, TYPE_U, TYPE_S,
  TYPE_N, TYPE_J, TYPE_RE,
  TYPE_B,TYPE_M// none
};

#define src1R() do { *src1 = R(rs1); } while (0)
#define src2R() do { *src2 = R(rs2); } while (0)
#define immI() do { *imm = SEXT(BITS(i, 31, 20), 12); } while(0)
#define immU() do { *imm = SEXT(BITS(i, 31, 12), 20) << 12; } while(0)
#define immS() do { *imm = (SEXT(BITS(i, 31, 25), 7) << 5) | BITS(i, 11, 7); } while(0)
#define immJ() do { *imm = SEXT(BITS(i, 31, 31)<<19 | (BITS(i, 19, 12)<<11 | BITS(i, 20, 20)<<10 | BITS(i, 30, 21)) , 20)<<1;}while (0)
#define immB() do { *imm = SEXT(BITS(i, 31, 31)<<11 | (BITS(i, 7, 7)<<10 | BITS(i, 30, 25)<<4 | BITS(i, 11, 8)) , 12)<<1;}while (0)
#define immM() do { *imm = (word_t)BITS(i, 31, 20); } while(0)
int compare(word_t in1, word_t in2);

static void decode_operand(Decode *s, int *rd, word_t *src1, word_t *src2, word_t *imm, int type) {
  uint32_t i = s->isa.inst.val;
  int rs1 = BITS(i, 19, 15);
  int rs2 = BITS(i, 24, 20);
  *rd     = BITS(i, 11, 7);
  switch (type) {
    case TYPE_I: src1R();          immI(); break;
    case TYPE_U:                   immU(); break;
    case TYPE_S: src1R(); src2R(); immS(); break;
    case TYPE_J:                   immJ(); break;
    case TYPE_RE: src1R(); src2R();        break;
    case TYPE_B:src1R(); src2R();  immB(); break;
    case TYPE_M:src1R(); immM();          break;
  }
}

static int decode_exec(Decode *s) {
  int rd = 0;
  word_t src1 = 0, src2 = 0, imm = 0;
  s->dnpc = s->snpc;


#define INSTPAT_INST(s) ((s)->isa.inst.val)
#define INSTPAT_MATCH(s, name, type, ... /* execute body */ ) { \
  decode_operand(s, &rd, &src1, &src2, &imm, concat(TYPE_, type)); \
  __VA_ARGS__ ; \
}

  INSTPAT_START();
  INSTPAT("??????? ????? ????? ??? ????? 00101 11", auipc  , U, R(rd) = s->pc + imm);// PC加立即数
  INSTPAT("??????? ????? ????? ??? ????? 01101 11", lui  , U, R(rd) = imm);// 立即数加载

  INSTPAT("??????? ????? ????? ??? ????? 11011 11", jal    , J,  s->dnpc =s->pc + imm  ,R(rd)= s->pc + 4);

  INSTPAT("??????? ????? ????? 000 ????? 11000 11", beq    , B,  if(src1 == src2) {s->dnpc =s->pc+imm;}   );
  INSTPAT("??????? ????? ????? 001 ????? 11000 11", bne    , B,  if(src1 != src2) {s->dnpc =s->pc+imm;}  );
  INSTPAT("??????? ????? ????? 101 ????? 11000 11", bge    , B,  if(compare(src1,src2)>-1) {s->dnpc =s->pc+imm;}  );
  INSTPAT("??????? ????? ????? 111 ????? 11000 11", bgeu   , B,  if(src1 >= src2) {s->dnpc =s->pc+imm;}  );
  INSTPAT("??????? ????? ????? 100 ????? 11000 11", blt    , B,  if(compare(src1,src2)==-1) {s->dnpc =s->pc+imm;}  );
  INSTPAT("??????? ????? ????? 110 ????? 11000 11", bltu   , B,  if(src1 < src2) {s->dnpc =s->pc+imm;}  );

  INSTPAT("??????? ????? ????? 000 ????? 00100 11", addi   , I, R(rd) = src1 + imm );
  INSTPAT("??????? ????? ????? 100 ????? 00000 11", lbu    , I, R(rd) = Mr((src1 + imm), 1));
  INSTPAT("??????? ????? ????? 000 ????? 11001 11", jalr   , I, s->dnpc = (src1+imm)&(~1); R(rd)= s->pc + 4) ;
  INSTPAT("??????? ????? ????? 011 ????? 00100 11", sltiu  , I, if(src1 < imm){R(rd) = 1;}else{R(rd) = 0; } );  
  INSTPAT("??????? ????? ????? 010 ????? 00000 11", lw     , I, R(rd) = Mr((src1 + imm), 4));
  INSTPAT("??????? ????? ????? 001 ????? 00000 11", lh     , I, R(rd) = SEXT(Mr((src1 + imm), 2), 16));
  INSTPAT("??????? ????? ????? 000 ????? 00000 11", lb     , I, R(rd) = SEXT(Mr((src1 + imm), 1), 8));
  INSTPAT("??????? ????? ????? 101 ????? 00000 11", lhu    , I, R(rd) = Mr((src1 + imm), 2));
  INSTPAT("0100000 ????? ????? 101 ????? 00100 11", srai   , I, R(rd) =((int32_t)src1 >> BITS(imm,4,0))  );//立即数算术右移
  INSTPAT("0000000 ????? ????? 101 ????? 00100 11", srli   , I, R(rd) = src1 >> BITS(imm,4,0) );//立即数逻辑右移
  INSTPAT("??????? ????? ????? 100 ????? 00100 11", xori   , I, R(rd) = src1 ^ imm );  
  INSTPAT("??????? ????? ????? 110 ????? 00100 11", ori    , I, R(rd) = src1 | imm );  
  INSTPAT("??????? ????? ????? 111 ????? 00100 11", andi   , I, R(rd) = src1 & imm ); 
  INSTPAT("0000000 ????? ????? 001 ????? 00100 11", slli   , I, R(rd) = src1 << BITS(imm,4,0)  ); //立即数逻辑左移
  INSTPAT("??????? ????? ????? 010 ????? 00100 11", slti   , I, R(rd) = ((int32_t)src1 < (int32_t)imm) ); 

  INSTPAT("??????? ????? ????? 010 ????? 01000 11", sw     , S, Mw((src1 + imm), 4, src2));
  INSTPAT("??????? ????? ????? 000 ????? 01000 11", sb     , S, Mw((src1 + imm), 1, src2));
  INSTPAT("??????? ????? ????? 001 ????? 01000 11", sh     , S, Mw((src1 + imm), 2, src2));

  INSTPAT("0000000 ????? ????? 000 ????? 01100 11", add    , RE, R(rd) = src1 + src2);
  INSTPAT("0000000 ????? ????? 011 ????? 01100 11", sltu   , RE, if(src1 < src2){R(rd) = 1;}else{R(rd) = 0; } );
  INSTPAT("0000000 ????? ????? 100 ????? 01100 11", xor    , RE, R(rd) = src1 ^ src2 );
  INSTPAT("0000000 ????? ????? 110 ????? 01100 11", or     , RE, R(rd) = src1 | src2 ); 
  INSTPAT("0000000 ????? ????? 111 ????? 01100 11", and    , RE, R(rd) = src1 & src2 ); 
  INSTPAT("0100000 ????? ????? 000 ????? 01100 11", sub    , RE, R(rd) = src1 - src2);
  INSTPAT("0000000 ????? ????? 001 ????? 01100 11", sll    , RE, R(rd) = src1 << src2); // shift left logical 
  INSTPAT("0000001 ????? ????? 000 ????? 01100 11", mul    , RE, R(rd) = (int64_t)(int32_t)src1 * (int64_t)(int32_t)src2);
  INSTPAT("0000001 ????? ????? 100 ????? 01100 11", div1   , RE, if((int32_t)src2 == -1){R(rd) = 0x80000000;}else if(src2!=0) {R(rd) = (int32_t)src1 / (int32_t)src2 ;} else {R(rd) = -1;} );
  INSTPAT("0000001 ????? ????? 101 ????? 01100 11", divu   , RE, if(src2!=0) {R(rd) = (uint64_t)src1 / (uint64_t)src2;} else {R(rd) = 0xffffffff;});
  INSTPAT("0000001 ????? ????? 110 ????? 01100 11", rem    , RE, if((int32_t)src2 == -1){R(rd) = 0;}else if(src2 !=0){R(rd) = (int32_t)src1 % (int32_t)src2 ;} else {R(rd)=(int32_t)src1;});
  INSTPAT("0000001 ????? ????? 111 ????? 01100 11", remu   , RE, if(src2 !=0){R(rd) = (uint32_t)src1 % (uint32_t)src2;} else {R(rd)=(uint32_t)src1;} );
  INSTPAT("0000000 ????? ????? 010 ????? 01100 11", slt    , RE, if(compare(src1, src2)==-1){R(rd) = 1;}else{R(rd) = 0; } );
  INSTPAT("0000001 ????? ????? 001 ????? 01100 11", mulh   , RE, R(rd) = (int64_t)(int32_t)src1 * (int64_t)(int32_t)src2 >>32);
  INSTPAT("0000001 ????? ????? 011 ????? 01100 11", mulhu  , RE, R(rd) = (uint64_t)src1 * (uint64_t)src2 >>32);
  INSTPAT("0000001 ????? ????? 010 ????? 01100 11", mulsu  , RE, R(rd) = (int64_t)(int32_t)src1 * (int64_t)(uint32_t)src2 >>32);
  INSTPAT("0100000 ????? ????? 101 ????? 01100 11", sra    , RE, R(rd) = (int32_t)src1 >> src2); 
  INSTPAT("0000000 ????? ????? 101 ????? 01100 11", srl    , RE, R(rd) = ((uint64_t)src1) >> src2); 


  INSTPAT("??????? ????? ????? 001 ????? 11100 11", csrrw  , M, if(rd == 0){cpu.csr[imm] = src1; } else {R(rd) = cpu.csr[imm]; cpu.csr[imm] = src1;} );
  INSTPAT("??????? ????? ????? 010 ????? 11100 11", csrrs  , M, if(rd == 0){cpu.csr[imm] = cpu.csr[imm]|src1; } else {R(rd) = cpu.csr[imm]; cpu.csr[imm] = cpu.csr[imm]|src1;} );
  INSTPAT("0011000 00010 00000 000 00000 11100 11", mret   , N, s->dnpc = cpu.csr[MEPC]); 
  INSTPAT("0000000 00000 00000 000 00000 11100 11", ecall  , N, s->dnpc = isa_raise_intr(11,s->pc+4);); 
  INSTPAT("0000000 00001 00000 000 00000 11100 11", ebreak , N, NEMUTRAP(s->pc, R(10))); // R(10) is $a0 
  INSTPAT("??????? ????? ????? ??? ????? ????? ??", inv    , N, INV(s->pc));

  INSTPAT_END();

  R(0) = 0; // reset $zero to 0

  return 0;
}

int isa_exec_once(Decode *s) {
  s->isa.inst.val = inst_fetch(&s->snpc, 4);
  return decode_exec(s);
}

// personal function
// 补码比较
int compare(word_t in1, word_t in2)
{
  int32_t signed_in1,signed_in2;
  signed_in1 =(int32_t)in1;
  signed_in2 =(int32_t)in2;
  if(signed_in1 > signed_in2)
    return 1;
  else if(signed_in1 == signed_in2)
    return 0;
  else 
    return -1;
   
}