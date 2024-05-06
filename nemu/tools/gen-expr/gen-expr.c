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

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>

// this should be enough
static char buf[65536] = {};
static char code_buf[65536 + 128] = {}; // a little larger than `buf`
static char *code_format =
"#include <stdio.h>\n"
"int main() { "
"  unsigned result = %s; "
"  printf(\"%%u\", result); "
"  return 0; "
"}";

static uint32_t choose(uint32_t max)
{
  uint32_t num = rand()%max ;
  return num;
}

static void gen_bracket(uint8_t choose)
{
  uint8_t bracket;
  unsigned char str[2];
  switch(choose)
  {
    case 0:bracket = '(';break;
    case 1:bracket = ')';break;
  }
  str[0] = bracket;
  str[1] = '\0';
  strcat(buf,str);
}


static void gen_op()
{
  uint8_t op;
  unsigned char str[2];
  switch(choose(4))
  {
    case 0:op = '+';break;
    case 1:op = '-';break;
    case 2:op = '*';break;
    case 3:op = '/';break;
    default:op = '+';break;
  }
  str[0] = op;
  str[1] = '\0';
  strcat(buf,str);
}
static void gen_blank()
{
  unsigned char str[2];
  if(choose(2))
  {
    str[0] = ' ';
    str[1] = '\0';
    strcat(buf,str);
  }

}

static void gen_num()
{
  uint8_t num; 
  unsigned char str[32];
  num = rand()%100+1;
  sprintf(str,"%d",num);
  strcat(str,"u"); 
  strcat(buf,str);
}
uint16_t count=0;
static void gen_rand_expr() 
{
  gen_blank();
  if(count++ < 2000)
  {
  switch(choose(3))
  {
    case 0:gen_num();break;
    case 1:gen_bracket(0); gen_rand_expr(); gen_bracket(1); break;
    default: gen_rand_expr();gen_op();gen_rand_expr();  break;
  }
  }
  else 
  {
    gen_num();
  }  
  gen_blank();
}


int main(int argc, char *argv[]) {
  int seed = time(0);
  srand(seed);
  int loop = 1;
  if (argc > 1) {
    sscanf(argv[1], "%d", &loop);
  }
  int i;
  for (i = 0; i < loop; i ++) {
    memset(buf,0,sizeof(buf));
    count=0;
    gen_rand_expr();
    sprintf(code_buf, code_format, buf);

    FILE *fp = fopen("/tmp/.code.c", "w");
    assert(fp != NULL);
    fputs(code_buf, fp);
    fclose(fp);

    int ret = system("gcc /tmp/.code.c -Wall -Werror -o /tmp/.expr");
    if (ret != 0) continue;

    fp = popen("/tmp/.expr", "r");
    assert(fp != NULL);

    int result;
    ret = fscanf(fp, "%d", &result);
     pclose(fp);

    printf("%u %s\n", result, buf);
  }
  return 0;
}
