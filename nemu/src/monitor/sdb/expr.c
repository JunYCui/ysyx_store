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
  {"[0-9]", TK_int},   // 0-9 int
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

static Token tokens[32] __attribute__((used)) = {};
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
        printf("%d",substr_len);
        /* TODO: Now a new token is recognized with rules[i]. Add codes
         * to record the token in the array `tokens'. For certain types
         * of tokens, some extra actions should be performed.
         */

        switch (rules[i].token_type) 
        {
          case '/': tokens[nr_token++].type = '/' ; break;
          case '*':tokens[nr_token++].type = '*'; break;
          case '+':tokens[nr_token++].type = '+'; break;
          case '-':tokens[nr_token++].type = '-'; break;
          case '(':tokens[nr_token++].type = ')'; break;
          case ')':tokens[nr_token++].type = '('; break;
          case TK_int:tokens[nr_token].type = TK_int;strcpy(tokens[nr_token].str , &e[position-substr_len]); nr_token++;  break;
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

  /* TODO: Insert codes to evaluate the expression. */
  return eval(0,nr_token-1);
}


static bool check_parentheses(uint8_t p, uint8_t q)
{
  if(p=='('&& q == ')')
    return true;
  else 
    return false;
}

static word_t eval(uint8_t p ,uint8_t q)
{
  uint8_t i,position=0;
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
    return atoi(tokens[p].str);
    }
    else
    { 
    printf(" p==q error ");
    assert(0);
    }
  }
  else if ( check_parentheses(p,q) == true )
  {
    eval(p-1,q-1);
  }
  else 
  {
    for(i=p;i<=q;i++)
    {
      if(tokens[i].type == '*' || tokens[i].type == '/' || tokens[i].type == '+' || tokens[i].type == '-')
      {
        position = i;
        break;
      }
    }    
      val1 = eval(p,position-1);
      val2 = eval(position+1,q);

      switch(tokens[position].type)
   {   
    case '/':return val1/val2;break;
    case '*':return val1*val2;break;
    case '+':return val1+val2;break;
    case '-':return val1-val2;break;
    default:assert(0);
   }

  }
  return 0;
}

