#include "trap.h"
#define SDRAM_BASE 0xa0000000
#define SDRAM_UPBASE 0xa2000000
#define FLASH_BASE 0x30000000
int main(void){
    long long a;
    for(int i=0;i<0x1000;i=i+4)
    {
        *(volatile uint32_t*)(SDRAM_BASE+i) = i;
        a = *(volatile uint32_t*)(SDRAM_BASE+i);
        check(a == i);
        *(volatile uint32_t*)(SDRAM_UPBASE+i) = i;
        a = *(volatile uint32_t*)(SDRAM_UPBASE+i);
        check(a == i);
        printf("i = %d\n",i);
    }

    return 0;
}