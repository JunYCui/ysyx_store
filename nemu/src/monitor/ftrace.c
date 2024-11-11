#include "common.h"
#include "elf.h"
void init_ftrace(char* elf_file)
{
    Elf32_Ehdr *elf_hdr = (Elf32_Ehdr*)elf_file;
    printf(" \n ************%x************* \n",elf_hdr->e_ident[2]);

}