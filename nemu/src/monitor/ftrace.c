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
    case 0:strcpy(type,"SHT_NULL");break;
    case 1:strcpy(type,"SHT_PROGBITS");break;
    case 2:strcpy(type,"SHT_SYMTAB");break;
    case 3:strcpy(type,"SHT_STRTAB");break;
    case 4:strcpy(type,"SHT_RELA");break;
    case 5:strcpy(type,"SHT_HASH");break;
    case 6:strcpy(type,"SHT_DYNAMIC");break;
    case 7:strcpy(type,"SHT_NOTE");break;
    case 8:strcpy(type,"SHT_NOBITS");break;
    case 9:strcpy(type,"SHT_REL");break;
    case 10:strcpy(type,"SHT_SHLIB");break;
    case 11:strcpy(type,"SHT_DYNSYM");break;
    case 0x70000000:strcpy(type,"SHT_LOPROC");break;
    case 0x7fffffff:strcpy(type,"SHT_HIPROC");break;
    case 0x80000000:strcpy(type,"SHT_LOUSER");break;
    case 0xffffffff:strcpy(type,"SHT_HIUSER");break;
    default:strcpy(type,"error");
        break;
    }
    printf("[%d]\t %u \t %15s \t\t Addr \t Off \t Size \t ES \t Flg \t Lk \t Inf \t Al \t \n",i,Eshdr[i].sh_name,type);
    
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


