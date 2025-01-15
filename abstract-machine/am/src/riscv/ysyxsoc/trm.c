#include <am.h>
#include <klib-macros.h>
#include <riscv/riscv.h>
#include <klib.h>
#define SRAM_SIZE (8 * 1024)
#define SERIAL_PORT 0x10000000

extern char data_load_start[];
extern char data_size[];
extern char _heap_start[];
int main(const char *args);
Area heap = RANGE(_heap_start, _heap_start+SRAM_SIZE);

#ifndef MAINARGS
#define MAINARGS ""
#endif
static const char mainargs[] = MAINARGS;

void putch(char ch) {
    outb(SERIAL_PORT, ch);
}

void halt(int code) {
    asm volatile("mv a0, %0; ebreak" : :"r"(code));

  // should not reach here
    while (1);
}

void _trm_init() {
    memcpy(_heap_start,data_load_start,(size_t)data_size);
    int ret = main(mainargs);
    halt(ret);
}
