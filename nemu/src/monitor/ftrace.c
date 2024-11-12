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
    Elf32_Shdr *exchange = malloc(sizeof(Elf32_Shdr));
    Elf32_Shdr *Eshdr = malloc(sizeof(Elf32_Shdr[section_num]));
    fseek(fp,section_off,SEEK_SET);
    num = fread(Eshdr,sizeof(Elf32_Shdr),section_num,fp);
    for(int i=0;i<section_num-1;i++)
    {
        for(int j=i;j<section_num;j++)
        if(Eshdr[i].sh_name > Eshdr[j].sh_name)
        {
            *exchange = Eshdr[i];
            Eshdr[i] = Eshdr[j]; 
            Eshdr[j] = Eshdr[i];
        }

    }
    free(exchange);
    assert(num == section_num);
    printf("[Nr]\t Name \t Type \t\t\t Addr \t\t Off \t Size  \n");
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
    case 0x70000003:strcpy(type,"RISCV_ATTRIBUTE ");break;
    default:
        strcpy(type,"error");
        break;
    }
    printf("[%d]\t %u \t %-15s \t %-8x \t %x \t %x  \n",i,Eshdr[i].sh_name,type,Eshdr[i].sh_addr,
    Eshdr[i].sh_offset,Eshdr[i].sh_size);
    
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


