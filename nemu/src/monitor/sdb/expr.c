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

#include <isa.h>

/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <regex.h>

enum {
  TK_NOTYPE = 256, TK_EQ,TK_int

  /* TODO: Add more token types */

};

static struct rule {
  const char *regex;
  int token_type;
} rules[] = {

  /* TODO: Add more rules.
   * Pay attention to the precedence level of different rules.
   */
  {"[0-9]+", TK_int},   // int
  {" +", TK_NOTYPE},    // spaces
  {"\\+", '+'},         // plus
  {"==", TK_EQ},        // equal
  {"\\*", '*'},         // mutiplication
  {"\\-", '-'},         // subtraction
  {"\\/", '/'},         // division
  {"\\(", '('},         // left bracket
  {"\\)", ')'}          // right bracket
 
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
      panic("regex compilation failed: %s\n%s", error_msg, rules[i].regex);
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

  while (e[position] != '\0') {
    /* Try all rules one by one. */
    for (i = 0; i < NR_REGEX; i ++) {
      if (regexec(&re[i], e + position, 1, &pmatch, 0) == 0 && pmatch.rm_so == 0) {
        char *substr_start = e + position;
        int substr_len = pmatch.rm_eo;

        Log("match rules[%d] = \"%s\" at position %d with len %d: %.*s",
            i, rules[i].regex, position, substr_len, substr_len, substr_start);

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
          case TK_int:tokens[nr_token].type = TK_int;strcpy(tokens[nr_token].str,&e[position-substr_len]);nr_token++; break;
          default: TODO();
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
static word_t eval(uint8_t p ,uint8_t q);

word_t expr(char *e, bool *success) {
  if (!make_token(e)) {
    *success = false;
    return 0;
  }
  else 
  *success = true;
  /* TODO: Insert codes to evaluate the expression. */
  return eval(0,nr_token-1);
}


static uint8_t check_parentheses(uint8_t p, uint8_t q)
{
  uint8_t i,flag=0;
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
        if(state<0&&state>-2)
        {
          flag = 1;
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
    return 1;
    else 
    return 2;
   }
   else 
   {
    printf(" lack bracket \n");
    assert(0);
   }
    
  return 0;
}

static word_t eval(uint8_t p ,uint8_t q)
{
  uint8_t i,position_add=0,position_mut=0,position=0;
  bool flag_add=0,flag_mut=0;
  int state=0;
  word_t val1,val2;
  if( p > q )
  {
    printf(" p>q  error \n ");
    assert(0);
  }
  else if (p == q)
  {
    if(tokens[p].type == TK_int)
    {
    return (uint32_t)atoi(tokens[p].str);
    }
    else
    { 
    printf(" p==q error \n");
    assert(0);
    }
  }
  else if ( check_parentheses(p,q) == 1 )
  {
    return (uint32_t)eval(p+1,q-1);
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
      if(tokens[i].type == '+' || tokens[i].type == '-')
      {
        flag_add = 1;
        position_add = i;
      }
      if(tokens[i].type == '*' || tokens[i].type == '/')
      {
        flag_mut=1;
        position_mut = i;
      }
      }
    }    
    if(flag_add == 1)
    {
      position = position_add;
    }
    else if(flag_mut == 1)
    {
      position = position_mut;
    } 
    else 
    {
      printf("expr is error!\n");
      assert(0);
    }
    val1 = eval(p,position-1);
    val2 = eval(position+1,q);

      switch(tokens[position].type)
   {   
    case '/':if(val2 !=0){return (uint32_t)val1/val2;}else { printf("dividened can not be 0 \n"); assert(0); } break;
    case '*':return (uint32_t)val1*val2;break;
    case '+':return (uint32_t)val1+val2;break;
    case '-':return (uint32_t)val1-val2;break;
    default:assert(0);
   }
  }
  return 0;
}

