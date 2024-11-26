#include "npc_common.h"
#include "npc_memory.h"
#include "npc_cpu_exec.h"
#include "npc_sdb.h"
#include "npc_reg.h"
#include <readline/readline.h>
#include <readline/history.h>
#include "npc_isa.h"

extern NPCState npc_state;

word_t expr(char *e, bool *success);
void init_regex() ;
void init_wp_pool() ;
WP* new_wp();
void free_wp(int NO);
void Wp_info_w(void);
void Wp_info_f(void);
void Cpu_Wp(void);

static int is_batch_mode = false;

void sdb_set_batch_mode() {
  is_batch_mode = true;
}


static char* rl_gets() {
  static char *line_read = NULL;

  if (line_read) {
    free(line_read);
    line_read = NULL;
  }

  line_read = readline("(npc) ");

  if (line_read && *line_read) {
    add_history(line_read);
  }

  return line_read;
}


static int cmd_help(char *args);

static int cmd_c(char *args) {
  cpu_exec(-1);
  npc_state.state = NPC_RUNNING;
  return 0;
}


static int cmd_q(char *args) {
  npc_state.state = NPC_QUIT;
  return -1;
}

static int cmd_si(char *args) //单步执行
{
  uint64_t n;
  char *arg = strtok(NULL, " ");
  char *arg1 = strtok(NULL, " ");
  if(arg1 != NULL)
  {
    printf(" parameters are too much \n");
    return 0;
  }
  if(arg == NULL) // 没有输入,默认为1
  n = 1;
  else if (atoi(arg))
  {
  n = atoi(arg);
  if(n>9)
  {
    printf("n is our of boudary \n");
    return 0;
  }
  }
  else
  {
  printf(" please enter integer \n");
  return 0;
  }
  cpu_exec(n);
  return 0;
}

static int cmd_info(char *args)
{
  char *arg = strtok(NULL, " ");
  char *arg1 = strtok(NULL, " ");
  if(arg1 != NULL)
  {
    printf(" parameters are too much \n");
    return 0;
  }
  if(arg ==  NULL)
  {
    printf(" no parameter \n");
  }
  else if (strcmp(arg,"r") == 0)
  {
    isa_reg_display(); //打印存储器状态
  }
  else if (strcmp(arg,"w") == 0)
  {
    Wp_info_w(); 
  }
  else if (strcmp(arg,"f") == 0)
  {
    Wp_info_f();
  }
  else 
  {
    printf(" no parameter \n");
  }
  return 0;
}

static int cmd_x(char *args)
{
  char *arg = strtok(NULL, " ");  
  char *arg1 = strtok(NULL, " ");
  char *arg2 = strtok(NULL, " ");
  bool success;
  if(arg2 != NULL)
  {
    printf(" parameters are too much \n ");
    return 0;
  }
  int16_t n,i;
  uint32_t address_base;
  if(arg ==  NULL )
  {
    printf(" lack parameter \n");
    return 0;
  }
  else 
  {
    n = atoi(arg);
  }

   if(arg1 ==  NULL )
  {
    printf(" lack parameter \n");
    return 0;
  }
  else 
  {
    address_base = expr(arg1,&success);
    if(success == false)
    {
      printf("expression is error");
      return 0 ;
    }
  }
  for(i=0;i<n;i++)
  {
    printf("%d \n", i);
    printf(" 0x%x \n",paddr_read(address_base+i*4,4)); //读取内存函数
    printf(" %d \n",paddr_read(address_base+i*4,4));
  }
   return 0;
}

static int cmd_p(char *args)
{
  bool success;
  char *arg = strtok(NULL, "");
  int exp_value;
 if(arg == NULL)
  {
    printf(" lack parameter \n");
    return 0;
  }
  else 
  {
    exp_value = expr(arg,&success);
    if(success == false)
    {
      printf("expression is error \n");
      return 0;
    }
    printf(" %u \n",exp_value);
  }
  return 0 ;
}

static int cmd_w(char *args)
{
  char *arg = strtok(NULL,"");
  //char *arg1 = strtok(NULL,"");
  WP* wp1;
  bool flag=false;
  uint32_t val=0;

  if(arg == NULL)
  {
    printf("lack parameter!\n ");
    return 0;
  }
  wp1 = new_wp();
  strcpy(wp1->exp,arg);
  val =  expr(arg,&flag);
  if(flag == true)
  {
    wp1->value = val;
  }
  else 
  {
    printf("expr is error!\n");
    assert(0);
  }
  printf("Hardware %d:%s\n",wp1->NO,wp1->exp);

  return 0;
}

static int cmd_d(char *args)
{
  char *arg = strtok(NULL," ");
  char *arg1 = strtok(NULL," ");
  uint8_t NO;
  if(arg1 != NULL)
  {
    printf("parameters are too much! \n");
    return 0;
  } 
  else if(arg == NULL)
  {
    printf("lack parameter!\n ");
    return 0;
  }
  NO = atoi(arg);
  free_wp(NO);
  printf("watchpoint %d is deleted \n", NO);
  return 0;
}


static struct {
  const char *name;
  const char *description;
  int (*handler) (char *);
} cmd_table [] = {
  { "help", "Display information about all supported commands", cmd_help },
  { "c", "Continue the execution of the program ", cmd_c},
  { "q", "Exit NPC", cmd_q },
  { "si", "execute n instructions: si+num", cmd_si},
  { "info", "print program status: 1.info+w(watchpoints)  2. info+r(reg) 3. info+f(free watchpoints)", cmd_info},
  {"x", "check the memory: x+n+address",cmd_x},
  {"p", "calculate expression: p+exp", cmd_p},
  {"w", "create watchpoint: w+n", cmd_w},
  {"d", "delete watchpoint: d+n", cmd_d}
  /* TODO: Add more commands */

};
#define NR_CMD ARRLEN(cmd_table)

static int cmd_help(char *args) {
  /* extract the first argument */
  char *arg = strtok(NULL, " ");
  int i;

  if (arg == NULL) {
    /* no argument given */
    for (i = 0; i < NR_CMD; i ++) {
      printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
    }
  }
  else {
    for (i = 0; i < NR_CMD; i ++) {
      if (strcmp(arg, cmd_table[i].name) == 0) {
        printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
        return 0;
      }
    }
    printf("Unknown command '%s'\n", arg);
  }
  return 0;
}


void sdb_mainloop() {
  if (is_batch_mode) {
    cmd_c(NULL);
    return;
  }

  for (char *str; (str = rl_gets()) != NULL; ) {
    char *str_end = str + strlen(str);

    /* extract the first token as the command */
    char *cmd = strtok(str, " ");
    if (cmd == NULL) { continue; }

    /* treat the remaining string as the arguments,
     * which may need further parsing
     */
    char *args = cmd + strlen(cmd) + 1;
    if (args >= str_end) {
      args = NULL;
    }

    int i;
    for (i = 0; i < NR_CMD; i ++) {
      if (strcmp(cmd, cmd_table[i].name) == 0) {
        if (cmd_table[i].handler(args) < 0) { return; }
        break;
      }
    }

    if (i == NR_CMD) { printf("Unknown command '%s'\n", cmd); }
  }
}


void init_sdb() {
  /* Compile the regular expressions. */
  init_regex();

  init_wp_pool() ;
}