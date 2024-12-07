#include "ftrace.h"
#include "cpu/decode.h"
#ifdef CONFIG_ITRACE
FUNC_TR func_array[FUNC_MAXNUM];
void disassemble(char *str, int size, uint64_t pc, uint8_t *code, int nbyte);

static void find_strsymtab_32(FILE* fp)
{
    Elf32_Ehdr* Ehdr= (Elf32_Ehdr*)malloc(sizeof(Elf32_Ehdr)); 
    Elf32_Off section_off;
    Elf32_Half section_num;
    Elf32_Half shstrindex;
   // char type[20];
    char name[100];
    size_t num;

/* 1. 读取表头信息，找到section偏移地址 */
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

/* 2. 读取section，并根据shstr表头索引，找到shstr表里面有name信息 */
    Elf32_Shdr *Eshdr = ( Elf32_Shdr *)malloc(sizeof(Elf32_Shdr[section_num]));
    char *shstrtable= (char*)malloc(Eshdr[shstrindex].sh_size);

    fseek(fp,section_off,SEEK_SET);
    num = fread(Eshdr,sizeof(Elf32_Shdr),section_num,fp);
    assert(num == section_num);

    fseek(fp,Eshdr[shstrindex].sh_offset,SEEK_SET);
    num = fread(shstrtable,Eshdr[shstrindex].sh_size,1,fp);
    assert(num == 1);

 //   printf("[Nr]\t Name \t\t\t Type \t\t\t Addr \t\t Off \t Size  \n");    
 /* 3. 根据name 找到strtab 和 symtab */
    Elf32_Shdr Esh_strtab = {};
    Elf32_Shdr Esh_symtab = {};

    for(int i=0;i<section_num;i++)
    {
    strcpy(name,&shstrtable[Eshdr[i].sh_name]);
    if(strcmp(name,".strtab") == 0)
    {        
        Esh_strtab = Eshdr[i];
    }
    else  if(strcmp(name,".symtab") == 0)
    {
        Esh_symtab = Eshdr[i];
    }

    memset(name,0,sizeof(name));
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
 /* 4. 对于 symtab 进行解析 */
    Elf32_Word symnum = Esh_symtab.sh_size/sizeof(Elf32_Sym);
    Elf32_Sym *Esym = (Elf32_Sym *)malloc(sizeof(Elf32_Sym[symnum]));
    char *strtable= (char *)malloc(Esh_strtab.sh_size);
    //char symbind;
    char symtype;
    //char symbind_str[20];
    //char symtype_str[20];
    char symname[20];
    unsigned char func_num=0;

    fseek(fp,Esh_symtab.sh_offset,SEEK_SET);
    num = fread(Esym,sizeof(Elf32_Sym),symnum,fp);
    assert(num == symnum);
    fseek(fp,Esh_strtab.sh_offset,SEEK_SET);
    num = fread(strtable,Esh_strtab.sh_size,1,fp);
    assert(num == 1);

//    printf("\tNum \tValue \t\tSize \tType \t\t Bind\tName \n");
    for(unsigned int i=0;i<symnum;i++)
    {
    strcpy(symname,&strtable[Esym[i].st_name]);
   // symbind = ELF32_ST_BIND(Esym[i].st_info);
    symtype = ELF32_ST_TYPE(Esym[i].st_info);
    if(symtype == STT_FUNC)
    {
        func_array[func_num].addr = Esym[i].st_value;
        strcpy(func_array[func_num].name,symname );
        func_array[func_num].size = Esym[i].st_size;
        func_array[func_num].state = true;
        func_num++;
    }

/*
    switch(symbind)
    {
        case STB_GLOBAL:strcpy(symbind_str,"GLOBAL") ;break;
        case STB_LOCAL:strcpy(symbind_str,"LOCAL");break;
        default: assert(0);break;
    }
    switch(symtype)
    {
        case STT_NOTYPE:strcpy(symtype_str,"NOTYPE");break;
        case STT_SECTION:strcpy(symtype_str,"SECTION");break;
        case STT_FUNC: strcpy(symtype_str,"FUNC");break;
        case STT_FILE: strcpy(symtype_str,"FILE");break;
        case STT_OBJECT: strcpy(symtype_str,"OBJECT");break;
        default: assert(0);break;
    }
    printf("\t%d\t%-10x \t%d \t%-8s \t%s \t %d \n",i,Esym[i].st_value,Esym[i].st_size,symtype_str,symbind_str,Esym[i].st_name);
*/    
}
    free(strtable);
    free(Esym);
    free(shstrtable);
    free(Ehdr);
    free(Eshdr);
}


 void init_ftrace(char* elf_file)
{
    if(elf_file == NULL)
        return;
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
      find_strsymtab_32(fp);

}
uint32_t count;
void ftrace_exe(Decode* s)
{
    char str[128];
    char* inst;
    char* rd;
    char* rs1;
    int ilen = s->snpc - s->pc;//指令长度  
    disassemble(str,sizeof(str),s->pc,(uint8_t *)&s->isa.inst.val, ilen);
    inst = strtok(str,"\t");
    if(inst!= NULL)
    {
        rd = strtok(NULL,",");
        rs1 =strtok(NULL," ");
        if((strcmp(inst,"jal") == 0 ))
        {
            
            for(int i=0;i<FUNC_MAXNUM;i++)
            {
                if(func_array[i].state == true)
                {
                   if(func_array[i].addr == s->dnpc) 
                   {
                    for(unsigned int j=0;j<count;j++)
                    {
                        printf(" ");
                    }
                    printf("0x%x:",s->pc);
                    printf("call [%s@0x%x]\n",func_array[i].name,func_array[i].addr);
                    count++;
                    break;
                   }
                }
                else 
                {
                    break;
                }
            }
            
        }
        else if(strcmp(inst, "jalr") == 0)
        {
             if((strcmp(rd,"zero")==0 )&& (strcmp(rs1,"0(ra)") ==0))
             {
                for(unsigned int i=0;i<FUNC_MAXNUM;i++)
                {
                if(func_array[i].state == true)
                {
                   if(s->dnpc>=func_array[i].addr && s->dnpc<func_array[i].addr+func_array[i].size) 
                   {
                     count--;
                        for(unsigned int j=0;j<count;j++)
                    {
                        printf(" ");
                    }    
                    printf("0x%x:",s->pc);
                    printf("rt   [%s@0x%x]\n",func_array[i].name,func_array[i].addr);
                    break;
                   }
                }
                else 
                {
                    break;
                }
                }
             }
             else 
             {
                for(int i=0;i<FUNC_MAXNUM;i++)
                {
                if(func_array[i].state == true)
                {
                   if(func_array[i].addr == s->dnpc) 
                   {
                    for(unsigned int j=0;j<count;j++)
                    {
                        printf(" ");
                    }
                    printf("0x%x:",s->pc);
                    printf("call [%s@0x%x]\n",func_array[i].name,func_array[i].addr);
                    count++;
                    break;
                   }
                }
                else 
                {
                    break;
                }
                }
             }
        }
    }
}
#endif
