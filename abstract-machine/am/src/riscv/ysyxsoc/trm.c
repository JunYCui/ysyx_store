#include <am.h>
#include <klib-macros.h>
#include <riscv/riscv.h>
#include <klib.h>
#define SRAM_SIZE (128 *1024 *1024)
#define SERIAL_PORT 0x10000000

#define LCR (SERIAL_PORT+0x03)
#define Divisor_LSB  (SERIAL_PORT+0x00)
#define Divisor_MSB  (SERIAL_PORT+0x01)
#define FCR (SERIAL_PORT+0x02)
#define IER (SERIAL_PORT+0x01)
#define LSR (SERIAL_PORT+0x05)

extern char _ssbl_size[] ;
extern char _ssbl_start[];
extern char _ssbl_loadstart[];
extern char data_load_start[];
extern char data_size[];
extern char _heap_start[];
extern char data_start[];
int main(const char *args);
Area heap = RANGE(_heap_start, _heap_start+SRAM_SIZE);

#ifndef MAINARGS
#define MAINARGS ""
#endif
static const char mainargs[] = MAINARGS;

void uart_init(){
    outb(LCR,0x83); // Set 8 bits of each character and allow access to the Devisor Latch 
    outb(Divisor_MSB,0x00);
    outb(Divisor_LSB,0x01);
    outb(LCR,0x03); // clear access to the Driver Latch
    outb(FCR,0x80); // set fifo interupt triggle level = 14bytes
    outb(IER,0x00); // disable all interrupt 
}
extern void id_display(void);

void display(int a, int b)
{
    printf("ysyx = 0x%x \n",a);
    printf("ID:%d \n",b);
    return;
}

void putch(char ch) {
    uint8_t status = inb(LSR) & 0x20; // 6th Bits of LSR 
    if(status !=0)
        outb(SERIAL_PORT,ch);
    else {
        while(status ==0){
            status = inb(LSR) & 0x20; 
        }
        outb(SERIAL_PORT,ch);
    }

}
void halt(int code) {
    asm volatile("mv a0, %0; ebreak" : :"r"(code));

  // should not reach here
    while (1);
}

void _trm_init() {
    uart_init();
    id_display();
    int ret = main(mainargs);
    halt(ret);
}

void __attribute__((section(".ssbl"))) ssbl_init(){
    char *p0=data_start;
    const char*p1 = data_load_start;
    size_t n = (size_t) data_size;
    while(n--)
    {
      *(p0++) = *(p1++);
    }
    _trm_init();
} 
void __attribute__((section(".fsbl"))) fsbl_init(){
    char *p0=_ssbl_start;
    const char*p1 = _ssbl_loadstart;
    size_t n = (size_t) _ssbl_size;
    while(n--)
    {
      *(p0++) = *(p1++);
    }
    ssbl_init();
}

