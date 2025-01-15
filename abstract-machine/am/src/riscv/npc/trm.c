#include <am.h>
#include <klib-macros.h>
#include <riscv/riscv.h>

#define DEVICE_BASE 0xa0000000

#define UART_ADDR (DEVICE_BASE + 0x00003f8)
#define RTC_ADDR  (DEVICE_BASE + 0x0000048)


extern char _heap_start;
int main(const char *args);

extern char _stack_top;
#define PMEM_SIZE (1 * 1024 * 1024)
#define PMEM_END  ((uintptr_t)&_stack_top - PMEM_SIZE)

Area heap = RANGE(&_heap_start, PMEM_END);
#ifndef MAINARGS
#define MAINARGS ""
#endif
static const char mainargs[] = MAINARGS;

void putch(char ch) {
  outb(UART_ADDR,ch);
}

void halt(int code) {
  asm volatile("mv a0, %0; ebreak" : :"r"(code));
  while (1) ;
  
}

void _trm_init() {
  int ret = main(mainargs);
  halt(ret);
}
