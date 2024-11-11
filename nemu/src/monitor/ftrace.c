#include "common.h"
#include "elf.h"
void init_ftrace(char* elf_file)
{
    char str[20];
    size_t num;
    FILE* fp= fopen(elf_file,"rb");
    num = fread(str,1,5,fp);
    if(num == 5)
    printf("*****%s*****",str);
}