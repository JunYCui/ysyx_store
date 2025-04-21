#include "trap.h"
#define LED_BASE 0x10002000
#define KEY_BASE 0x10002004
#define SEG_BASE 0x10002008

int main(void){
    uint16_t led=0x0001;
    uint16_t key;
    uint32_t ysyx_id;
    asm volatile("csrr %0, marchid":"=r"(ysyx_id):);
    *(volatile uint32_t*) SEG_BASE = ysyx_id;
    key = *(volatile uint16_t*) KEY_BASE ;
    while(key !=3)
    {
        key = *(volatile uint16_t*) KEY_BASE ; 
    }
    while (1)
    {
            *(volatile uint16_t*)LED_BASE = led;
            if(led == 0x8000)
            {
                led = 0x0001;
            }
            else {
                led = led << 1;
            }
            for(int i=0;i<1000;i++)
            ;
    }
    
}