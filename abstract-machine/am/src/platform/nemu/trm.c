#include <am.h>
#include <nemu.h>
#include <klib.h>
//extern char _heap_start;
int main(const char *args);

extern char data_load_start[];
extern char data_size[];
extern char _heap_start[];
Area heap = RANGE(_heap_start, PMEM_END);
#ifndef MAINARGS
#define MAINARGS ""
#endif
static const char mainargs[] = MAINARGS;

void putch(char ch) {
  outb(SERIAL_PORT, ch);
}

void halt(int code) {
  nemu_trap(code);

  // should not reach here
  while (1);
}

void _trm_init() {
  memcpy(_heap_start,data_load_start,(size_t)data_size);
  int ret = main(mainargs);
  halt(ret);
}
