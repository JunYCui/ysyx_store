#include "common.h"
#include "elf.h"


static void find_symtab_32(FILE* fp)
{
    Elf32_Ehdr* Ehdr= malloc(sizeof(Elf32_Ehdr)); 
    Elf32_Off section_off;
    Elf32_Half section_num;
    char type[20];
    size_t num;
    fseek(fp,0,SEEK_SET);
    num = fread(Ehdr,sizeof(Elf32_Ehdr),1,fp);
    assert(num == 1);
    section_off = Ehdr->e_shoff;
    section_num = Ehdr->e_shnum;
    if(section_off == 0)
    {
        printf("there is no section header table! \n");
    }
    Elf32_Shdr *Eshdr = malloc(sizeof(Elf32_Shdr[section_num]));
    fseek(fp,section_off,SEEK_SET);
    num = fread(Eshdr,sizeof(Elf32_Shdr),section_num,fp);
    assert(num == section_num);
    printf("[Nr]\t Name \t\t Type \t\t Addr \t Off \t Size \t ES \t Flg \t Lk \t Inf \t Al \t \n");
    for(int i=0;i<section_num;i++)
    {
    switch (Eshdr[i].sh_type)
    {
    case SHT_NULL:strcpy(type,"NULL");break;
    case SHT_PROGBITS:strcpy(type,"PROGBITS");break;
    case SHT_SYMTAB:strcpy(type,"SYMTAB");break;
    case SHT_STRTAB:strcpy(type,"STRTAB");break;
    case SHT_RELA:strcpy(type,"RELA");break;
    case SHT_HASH:strcpy(type,"HASH");break;
    case SHT_DYNAMIC:strcpy(type,"DYNAMIC");break;
    case SHT_NOTE:strcpy(type,"NOTE");break;
    case SHT_NOBITS:strcpy(type,"NOBITS");break;
    case SHT_REL:strcpy(type,"REL");break;
    case SHT_SHLIB:strcpy(type,"SHLIB");break;
    case SHT_DYNSYM:strcpy(type,"DYNSYM");break;
    case SHT_LOPROC:strcpy(type,"LOPROC");break;
    case SHT_HIPROC:strcpy(type,"HIPROC");break;
    case SHT_LOUSER:strcpy(type,"LOUSER");break;
    case SHT_HIUSER:strcpy(type,"HIUSER");break;
    default:
        printf("*******%x***********\n",Eshdr[i].sh_type);
        strcpy(type,"error");
        break;
    }
    printf("[%d]\t %u \t %15s \t Addr \t Off \t Size \t ES \t Flg \t Lk \t Inf \t Al \t \n",i,Eshdr[i].sh_name,type);
    
    }
    free(Ehdr);
    free(Eshdr);
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


