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

#include <common.h>



void init_monitor(int, char *[]);
void am_init_monitor();
void engine_start();
int is_exit_status_bad();
word_t expr(char *e, bool *success);

int main(int argc, char *argv[]) {
  /* Initialize the monitor. */
#ifdef CONFIG_TARGET_AM
  am_init_monitor();
#else
  init_monitor(argc, argv);
#endif

// test for expr
 /*
  FILE* fp;
  char readbuf[65536+128];
  char exp[65536];
  uint32_t results;
  word_t cresults;
  bool success;
  fp = fopen("/home/cjy/ysyx-workbench/nemu/tools/gen-expr/input" ,"r");
  while(fgets(readbuf,65536+128,fp)!= NULL)
  {
    sscanf(readbuf,"%u",&results);
    int i=0;
    int len=0;
    while(readbuf[i++]!=' ')
    ;
    strcpy(exp,readbuf+i);
    len = strlen(exp);
    exp[len-1] = '\0';
    cresults = expr(exp,&success);
    if(success == true )
    {
      if(cresults == results)
      {
        printf("true! \n");
      }
      else 
      {
        printf("cpu results:%u, real results: %u , exp: %s \n",cresults,results,exp);
        assert(0);
      }
    }
    else 
    {
      assert(0);
      printf("%s\n",exp);
    }
  }
  */
  /* Start engine. */
  engine_start();

  return is_exit_status_bad();
}
