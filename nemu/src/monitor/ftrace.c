#include "common.h"
#include "elf.h"


static Elf32_Shdr find_strtab_32(FILE* fp)
{
    Elf32_Ehdr* Ehdr= malloc(sizeof(Elf32_Ehdr)); 
    Elf32_Off section_off;
    Elf32_Half section_num;
    Elf32_Half shstrindex;
   // char type[20];
    char name[50];
    size_t num;
  /*1. 读取表头信息，找到section偏移地址*/
    fseek(fp,0,SEEK_SET);
    num = fread(Ehdr,sizeof(Elf32_Ehdr),1,fp);
    assert(num == 1);
    section_off = Ehdr->e_shoff;
    section_num = Ehdr->e_shnum;
    shstrindex = Ehdr->e_shstrndx;//shstr表头索引
    if(section_off == 0)
    {
        printf("there is no section header table! \n");
    }
    /*2. 读取section，并根据shstr表头索引，找到shstr表里面有name信息*/
    Elf32_Shdr *Eshdr = malloc(sizeof(Elf32_Shdr[section_num]));
    Elf32_Shdr Esh_strtab;
    char *shstrtable= malloc(Eshdr[shstrindex].sh_size);

    fseek(fp,section_off,SEEK_SET);
    num = fread(Eshdr,sizeof(Elf32_Shdr),section_num,fp);
    assert(num == section_num);

    fseek(fp,Eshdr[shstrindex].sh_offset,SEEK_SET);
    num = fread(shstrtable,Eshdr[shstrindex].sh_size,1,fp);
    assert(num == 1);

    printf("[Nr]\t Name \t\t\t Type \t\t\t Addr \t\t Off \t Size  \n");    
    for(int i=0;i<section_num;i++)
    {
    strcpy(name,&shstrtable[Eshdr[i].sh_name]);
    if(strcmp(name,".strtab") == 0)
    {        
        Esh_strtab = Eshdr[i];
        break;
    }
/*
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
    case 0x70000003:strcpy(type,"RISCV_ATTRIBUTE ");break;
    default:
        strcpy(type,"error");
        break;
    }
 
    printf("[%2d]\t %-15s\t %-15s \t %-8x \t %x \t %x  \n",i,name,type,Eshdr[i].sh_addr,
    Eshdr[i].sh_offset,Eshdr[i].sh_size);
    memset(type,0,sizeof(type));
 */
    }
    free(shstrtable);
    free(Ehdr);
    free(Eshdr);

    return Esh_strtab;
}


void init_ftrace(char* elf_file)
{
    char str[20];
    size_t num;
    char osType;
    Elf32_Shdr Esh_strtab;
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
      Esh_strtab = find_strtab_32(fp);

    printf("%d",Esh_strtab.sh_size);
}


