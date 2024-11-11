#include "common.h"
#include "elf.h"
void init_ftrace(const char* elf_file)
{
    Elf32_Ehdr *elf_hdr = (Elf32_Ehdr*)elf_file;
    printf("%c",elf_hdr->e_ident[1]);

}