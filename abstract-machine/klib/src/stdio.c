#include <am.h>
#include <klib.h>
#include <klib-macros.h>
#include <stdarg.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)


int vsprintf(char *out, const char *fmt, va_list ap);

int printf(const char *fmt, ...) {
  char strout[200];
  va_list pArgs;
  va_start(pArgs, fmt);
  int num = vsprintf(strout,fmt, pArgs);
  va_end(pArgs);
  putstr(strout);
  return num;
}

int vsprintf(char *out, const char *fmt, va_list ap) {
  const char *p1=fmt;
  char *p2 = out;
  char *Argstrval;
  int Argintval;
  int num=0;
  int store[50];
  int count=0;
  while(*p1 !='\0')
  {
    switch(*p1)
    {
      case '%':
          p1++;
          switch(*p1)
          {
            case 'd':
              Argintval = va_arg(ap, int);
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
              p1++;
              memset(store,0,sizeof(store));
              break;
            case 's':
              Argstrval = va_arg(ap, char*);
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
  *p2 = '\0';
  return num;
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
              p1++;
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
            case '0':case '1':case '2':case'3':case'4':case'5':
            case'6': case'7': case'8': case '9': 
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
  *p2 = '\0';
  return num;
}

int snprintf(char *out, size_t n, const char *fmt, ...) {
  panic("Not implemented");
}

int vsnprintf(char *out, size_t n, const char *fmt, va_list ap) {
  panic("Not implemented");
}

#endif
