#include "npc_init.h"
#include "npc_memory.h"


void init_sdb();
void init_ftrace(char* elf_file);
void npc_cpu_init();
extern "C" void init_disasm(const char *triple);
void init_difftest(char *ref_so_file, long img_size, int port) ;
void sdb_set_batch_mode();
uint8_t *pmem = NULL;
char *img_file = NULL;
static char *elf_file = NULL;
static char *diff_so_file = NULL;
static int difftest_port = 1234;

static const uint32_t img [] = {
  0x00000297,  // auipc t0,0
  0x00028823,  // sb  zero,16(t0)
  0x0102c503,  // lbu a0,16(t0)
  0x00100073,  // ebreak (used as nemu_trap)
  0xdeadbeef,  // some data
};

static void init_mem() {
  pmem = (uint8_t*)malloc(CONFIG_MSIZE);
  assert(pmem);
}

static int parse_args(int argc, char *argv[]) {
  const struct option table[] = {
    {0          , 0                , NULL,  0 },
    {"batch"    , no_argument      , NULL, 'b'},
    {"elf"      , required_argument, NULL, 'e'},
    {"diff"     , required_argument, NULL, 'd'},
    {"port"     , required_argument, NULL, 'p'},
  };
  int o;
  while ( (o = getopt_long(argc, argv, "-e:d:p:b", table, NULL)) != -1) {
    switch (o) {
      case 'b': sdb_set_batch_mode();break;
      case 'e': elf_file = optarg;break;
      case 'p': sscanf(optarg, "%d", &difftest_port); break;
      case 'd': diff_so_file = optarg; break;
      case 1: img_file = optarg; return 0;
      default:
        printf("Usage: %s [OPTION...] IMAGE [args]\n\n", argv[0]);
        printf("\t-e,--elf=FILE           input ELF FILE\n");
        printf("\t-d,--diff=REF_SO        run DiffTest with reference REF_SO\n");
        printf("\t-p,--port=PORT          run DiffTest with port PORT\n");
        printf("\n");
        exit(0);
    }
  }
  return 0;
}

static long load_img() {
  if (img_file == NULL) {
    printf("No image is given. Use the default build-in image. \n");

  }

  FILE *fp = fopen(img_file, "rb");


  fseek(fp, 0, SEEK_END);
  long size = ftell(fp);

  printf("The image is %s, size = %ld \n", img_file, size);

  fseek(fp, 0, SEEK_SET);
  int ret = fread(guest_to_host(RESET_VECTOR), size, 1, fp);
  assert(ret == 1);

  fclose(fp);

  return size;
}



void init_monitor(int argc, char *argv[])
{
  init_mem();

  parse_args(argc, argv);

  long img_size = load_img();

  init_ftrace(elf_file);

  init_sdb();

  npc_cpu_init();

  init_difftest(diff_so_file, img_size, difftest_port);

  init_disasm("riscv32""-pc-linux-gnu");
  assert(0);
}