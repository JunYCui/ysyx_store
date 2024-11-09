#include <am.h>
#include <klib.h>
#include <klib-macros.h>
#include <stdarg.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

int printf(const char *fmt, ...) {
  panic("Not implemented");
}

int vsprintf(char *out, const char *fmt, va_list ap) {
  panic("Not implemented");
}

int sprintf(char *out, const char *fmt, ...) {
  const char *p1=fmt;
  char *p2 = out;
  char *Argstrval;
  int Argintval;
  int num=0;
  int store[50];
  int count=0;
  va_list pArgs; //创建pArgs变量，用于参数地址
  va_start(pArgs, fmt); 

  while(*p1 !='\0')
  {
    switch(*p1)
    {
      case '%':
          p1++;
          switch(*p1)
          {
            case 'd':
            Argintval = va_arg(pArgs, int);
            while(Argintval)
            {
              store[count++]=Argintval%10;
              Argintval = Argintval/10;
              if(count>50)
                panic("int is too big");
            }
            while(count)
            {
              *(p2++) = store[--count]+48;
              num++;
            }
            memset(store,0,sizeof(store));
            break;
            case 's':
            Argstrval = va_arg(pArgs, char*);
            while(*Argstrval != '\0')
            {
              *(p2++) = *(Argstrval++);
              num++;
            }
            p1++;
            break;

            default:
                  panic("parameter is error");
                  assert(0);  
          }
          break;
      default: 
      *(p2++) =*(p1++);//将fmt赋值给out
      num++;//打印的字符串长度+1
    
    }
  }
  va_end(pArgs);
  return num;
}

int snprintf(char *out, size_t n, const char *fmt, ...) {
  panic("Not implemented");
}

int vsnprintf(char *out, size_t n, const char *fmt, va_list ap) {
  panic("Not implemented");
}

#endif
