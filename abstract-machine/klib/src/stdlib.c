#include <am.h>
#include <klib.h>
#include <klib-macros.h>

extern Area heap;

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)
static unsigned long int next = 1;
static char *hbrk = NULL;
static bool init_flag=0;

int rand(void) {
  // RAND_MAX assumed to be 32767
  next = next * 1103515245 + 12345;
  return (unsigned int)(next/65536) % 32768;
}

void srand(unsigned int seed) {
  next = seed;
}

int abs(int x) {
  return (x < 0 ? -x : x);
}

int atoi(const char* nptr) {
  int x = 0;
  while (*nptr == ' ') { nptr ++; }
  while (*nptr >= '0' && *nptr <= '9') {
    x = x * 10 + *nptr - '0';
    nptr ++;
  }
  return x;
}

void *malloc(size_t size) {
  // On native, malloc() will be called during initializaion of C runtime.
  // Therefore do not call panic() here, else it will yield a dead recursion:
  //   panic() -> putchar() -> (glibc) -> malloc() -> panic(
 if(!init_flag)
  {
  hbrk = (void *)ROUNDUP(heap.start,8);
  init_flag = 1;
  }
  char* old = hbrk;
  size = (size_t)ROUNDUP(size,8); 
  hbrk +=size; 
  return old;
}

void free(void *ptr) {
}

#endif
