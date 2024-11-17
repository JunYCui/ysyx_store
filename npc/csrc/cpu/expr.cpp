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


/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <regex.h>
#include <npc_memory.h>
#include <math.h>
#include <npc_reg.h>

extern Vcpu_ysyx_24100029 *top ;

enum {
  TK_NOTYPE = 256,TK_int,TK_HEX,
  TK_AND,TK_NEQ,TK_EQ,
  TK_DEREF,TK_NEG,TK_REG
  /* TODO: Add more token types */

};

static struct rule {
  const char *regex;
  int token_type;
} rules[] = {

  /* TODO: Add more rules.
   * Pay attention to the precedence level of different rules.
   */ 
  {"0x[0-9\\a-f\\A-F]+",TK_HEX}, // HEX 
  {"[0-9]+(u)?", TK_int},   // int
  {" +", TK_NOTYPE},    // spaces
  {"\\+", '+'},         // plus
  {"==", TK_EQ},        // equal
  {"\\*", '*'},         // mutiplication
  {"\\-", '-'},         // subtraction
  {"\\/", '/'},         // division
  {"\\(", '('},         // left bracket
  {"\\)", ')'},          // right bracket
  {"&&", TK_AND},         //AND
  {"!=", TK_NEQ},          // not equal
  {"\\$[0-9a-zA-Z]+", TK_REG} // regsiter
};

#define NR_REGEX ARRLEN(rules)

static regex_t re[NR_REGEX] = {};

/* Rules are used for many times.
 * Therefore we compile them only once before any usage.
 */
void init_regex() {
  int i;
  char error_msg[128];
  int ret;

  for (i = 0; i < NR_REGEX; i ++) {
    ret = regcomp(&re[i], rules[i].regex, REG_EXTENDED);
    if (ret != 0) {
      regerror(ret, &re[i], error_msg, 128);
      printf("regex compilation failed: %s\n%s", error_msg, rules[i].regex);
    }
  }
}

typedef struct token {
  int type;
  char str[32];
} Token;

static Token tokens[65535] __attribute__((used)) = {};
static int nr_token __attribute__((used))  = 0;

static bool make_token(char *e) {
  int position = 0;
  int i;
  regmatch_t pmatch;

  nr_token = 0;
  memset(tokens,0,sizeof(tokens));
  while (e[position] != '\0') {
    /* Try all rules one by one. */
    for (i = 0; i < NR_REGEX; i ++) {
      if (regexec(&re[i], e + position, 1, &pmatch, 0) == 0 && pmatch.rm_so == 0) {
        char *substr_start = e + position;
        int substr_len = pmatch.rm_eo;

       /* Log("match rules[%d] = \"%s\" at position %d with len %d: %.*s",
            i, rules[i].regex, position, substr_len, substr_len, substr_start);*/

        position += substr_len;
        /* TODO: Now a new token is recognized with rules[i]. Add codes
         * to record the token in the array `tokens'. For certain types
         * of tokens, some extra actions should be performed.
         */
        switch (rules[i].token_type) 
        {
          case '/':tokens[nr_token++].type = '/' ; break;
          case '*':tokens[nr_token++].type = '*'; break;
          case '+':tokens[nr_token++].type = '+'; break;
          case '-':tokens[nr_token++].type = '-';  break;
          case  TK_NOTYPE: break;
          case '(':tokens[nr_token++].type = '('; break;
          case ')':tokens[nr_token++].type = ')'; break;
          case TK_int:tokens[nr_token].type = TK_int;strncpy(tokens[nr_token].str,substr_start,substr_len);nr_token++; break;
          case TK_HEX:tokens[nr_token].type = TK_HEX;strncpy(tokens[nr_token].str,substr_start,substr_len);nr_token++; break;
          case TK_AND:tokens[nr_token++].type = TK_AND;break;
          case TK_NEQ:tokens[nr_token++].type = TK_NEQ; break;
          case TK_EQ:tokens[nr_token++].type = TK_EQ; break;
          case TK_REG:tokens[nr_token].type = TK_REG;strncpy(tokens[nr_token].str,substr_start+1,substr_len-1);nr_token++; break;

          default: assert(0);
        }
        

        break;
      }
    }

    if (i == NR_REGEX) {
      printf("no match at position %d\n%s\n%*.s^\n", position, e, position, "");
      return false;
    }
  }

  return true;
}
static word_t eval(uint32_t p ,uint32_t q);

word_t expr(char *e, bool *success) {
  uint32_t i = 0;
  if (!make_token(e)) {
    *success = false;
    return 0;
  }
  else 
  *success = true;
  /* TODO: Insert codes to evaluate the expression. */
  
  for (i = 0; i < nr_token; i ++) 
  {
  if (tokens[i].type == '*' && (i == 0 || (tokens[i - 1].type !=  TK_int && tokens[i - 1].type !=  TK_HEX  && tokens[i - 1].type !=  ')')  ) ) 
  {
    tokens[i].type = TK_DEREF;//判断是取地址符号还是乘法
  }
  else if (tokens[i].type == '-' && (i == 0 || (tokens[i - 1].type !=  TK_int && tokens[i - 1].type !=  TK_HEX  && tokens[i - 1].type !=  ')' ) ) ) 
  {
    tokens[i].type = TK_NEG;// 判断是负号，还是减号
  }
  }

  return eval(0,nr_token-1);
}


static uint8_t check_parentheses(uint32_t p, uint32_t q)
{
  uint32_t i,flag=0;
  int state=0;
  if( tokens[p].type == '(' && tokens[q].type == ')')
    {
      for(i=p+1;i<q;i++)
      {
        if(tokens[i].type == '(')
        {
          state++;     
        }
        else if(tokens[i].type == ')') 
        {
          state--;  

        }
        if(state == -1)
        {        
          flag = 1; // 并不匹配，(a+b)+(c+d)
        }
        else if(state <-1)
        {
          printf(" bracket error \n");
          assert(0);
        }
        }
    }
  else
      return false;           

   if(state == 0)
   {
    if(flag == 0)
    return true;
    else 
    return false;
   }
   else 
   {
    printf(" lack bracket \n");
    assert(0);
   }
    
  return 0;
}

static word_t eval(uint32_t p ,uint32_t q)
{
  uint32_t i,position_add=0,position_mut=0,position=0,position_single=0,position_eq=0,position_and=0;
  bool flag_add=0,flag_mut=0,flag_single=0,flag_eq=0,flag_and=0;
  int state=0;
  word_t val1=0,val2=0;
  if( p > q )
  {
    printf(" p>q  error \n ");
    assert(0);
  }
  else if (p == q)
  {
    uint32_t num;
    bool success;
    if(tokens[p].type == TK_int )
    {
      sscanf(tokens[p].str,"%u",&num);// 无符号整数
    }
    else if(tokens[p].type == TK_HEX)
    {
      sscanf(tokens[p].str,"%x",&num);
    }
    else if(tokens[p].type == TK_REG)
    {
      if(strcmp(tokens[p].str,"pc")== 0)
      {
        num = top->pc;
        return num;
      }
      else 
    {
      num = isa_reg_str2val(tokens[p].str,&success);
      if(success == true)
      {
        return num;
      }
      else 
      {
        printf(" register does not exist. ");
        assert(0);
      }
    }
    }
    else
    { 
    printf(" p==q error \n");
    assert(0);
    }
    return num;
  }
  else if (check_parentheses(p,q) == true)
  {
    return eval(p+1,q-1);
  }
  else 
  {  
    for(i=p;i<=q;i++)
    {
      if(tokens[i].type == '(')
      {
        state ++;
      }
      else if(tokens[i].type == ')')
      {
        state --;
      }
      if(state == 0)
      {
        switch(tokens[i].type)
      {
        case TK_AND:flag_and=1;position_and = i;break;
        case TK_EQ:flag_eq = 1;position_eq = i;break;
        case TK_NEQ:flag_eq = 1;position_eq = i;break;
        case '*':flag_mut=1;position_mut = i;break;
        case '/':flag_mut=1;position_mut = i;break;
        case '+':flag_add=1;position_add=i;break;
        case '-':flag_add= 1;position_add=i;break;
        case TK_NEG:if(flag_single ==0) {flag_single=1;position_single = i;}break;
        case TK_DEREF:if(flag_single ==0) {flag_single=1;position_single = i;}break;
      }
      }
    }    
      if(flag_and == 1)
      {
        position = position_and;
      }
      else if (flag_eq == 1)
      {
        position = position_eq;
      }
      else if(flag_add==1)
      {
        position = position_add;
      }
      else if (flag_mut == 1)
      {
        position = position_mut;
      }
      else if (flag_single== 1)
      {
        position = position_single;
      }
      else 
      {
        printf("%d %d %d %d  \n",tokens[p].type,tokens[q].type,p,q);
        printf("expr error!\n");
        assert(0);
      }
    if(flag_add || flag_mut || flag_eq || flag_and) // 二元操作符
    {
      val1 = eval(p,position-1);
      val2 = eval(position+1,q);
      switch(tokens[position].type)
    {   
    case '/':if(val2 !=0){return val1/val2;}else { printf("dividened can not be 0 \n"); assert(0); } break;
    case '*':return val1*val2;break;
    case '+':return val1+val2;break;
    case '-':return val1-val2;break;
    case TK_EQ:return val1==val2;break;
    case TK_NEQ:return val1!=val2;break;
    case TK_AND:return val1&&val2;break;
    default:assert(0);
    }
    }
    else  //一元操作符
    {
      switch (tokens[position].type)
      {
      case TK_NEG:return -eval(position+1,q);break;
      case TK_DEREF:return paddr_read(eval(position+1,q), 4); break;
     
      }
    }
  }
  return 0;
}

