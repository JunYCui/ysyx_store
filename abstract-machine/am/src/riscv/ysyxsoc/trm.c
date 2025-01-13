#include <am.h>
#include <klib-macros.h>
#include <riscv/riscv.h>

#define PMEM_SIZE (128 * 1024 * 1024)
#define SERIAL_PORT 0x10000000

extern char _pmem_start;
extern char _heap_start;
int main(const char *args);
#define PMEM_END  ((uintptr_t)&_pmem_start + PMEM_SIZE)

Area heap = RANGE(&_heap_start, PMEM_END);

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
    int ret = main(mainargs);
    halt(ret);
}
