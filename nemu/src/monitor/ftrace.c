#include "common.h"
#include "elf.h"


static void find_symtab_32(FILE* fp)
{
    Elf32_Ehdr* Ehdr= malloc(sizeof(Elf32_Ehdr)); 
    uint8_t section_off;
    size_t num;
    num = fread(Ehdr,sizeof(Ehdr),1,fp);
    assert(num == 1);
    section_off = Ehdr->e_shnum;
    if(section_off == 0)
    {
        printf("there is no section header table! \n");
    }
    printf("%u",section_off);
    free(Ehdr);
}


void init_ftrace(char* elf_file)
{
    char str[20];
    size_t num;
    char osType;
    FILE* fp= fopen(elf_file,"rb");// 读取二进制elf_file的二进制的文件
    num = fread(str,1,5,fp);// 读取前5个字节到字符串str中
    if(num != 5)
    {
        printf("fread error!\n");
        assert(0);
    }
    if(str[0]!=ELFMAG0 || str[1]!= ELFMAG1 || str[2]!= ELFMAG2 || str[3] !=ELFMAG3 || str[4] == ELFCLASSNONE)
    {
        printf("file is not elf-file\n");
        assert(0);
    }
    if(str[4] == ELFCLASS32)
    {
        osType = 32;
    }
    else 
    {
        osType = 64;
    }
    if(osType == 32)
    find_symtab_32(fp);
}


