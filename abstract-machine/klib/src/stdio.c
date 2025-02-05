#include <am.h>
#include <klib.h>
#include <klib-macros.h>
#include <stdarg.h>

enum{FLAG_LEFT=1, FLAG_RIGHT =2,FLAG_ZERO =4, FLAG_NUM =8};

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

int int2hex(char*str, int val)
{
  int count=0;
  if(val == 0)
  {
     str[count++] = val%10 + 0x30;
     return  count;
  }
  while(val!=0)
  {
  switch (val%16)
  {
  case 0:case 1: case 2:
  case 3:case 4: case 5:
  case 6:case 7: case 8:
  case 9:
   str[count++] = val%16 + 0x30;break;
  case 10:   
    str[count++] = 'a';break;
  case 11:
    str[count++] = 'b';break;
  case 12:
    str[count++] = 'c';break;
  case 13:
    str[count++] = 'd';break;
  case 14:
    str[count++] = 'e';break;
  case 15:
    str[count++] = 'f';break;
  }
   val = val/16;
  }
  return count;
}


int int2str(char* str, int val)
{
  int count =0;
  if(val == 0)
  {
     str[count++] = val%10 + 0x30;
     return  count;
  }
  while(val != 0)
  {
    str[count++] = val%10 + 0x30;
    val = val/10;
  }
  return count;
}
int float2str(char* str, double val)
{
    int val_int = 0;   // 整数部分
    int val_dec = 0;
    int count;
    int divide = 1000000;
    int count_dec;
    char str_dec[50];
    val_int = (int)val;
    val_dec = (int)((val-val_int)*divide);//小数点后6位
    count = int2str(str,val_int);
    str[count++] = '.';
    for(count_dec=0;count_dec<6;count_dec++)
    {
       str_dec[count_dec] = val_dec%10 + 0x30;
       val_dec = val_dec/10;
    }
    for(count_dec=5;count_dec>=0;count_dec--)
    { 
       str[count++] = str_dec[count_dec];
    }
  return count;
}
char strout[100];
int vsprintf(char *out, const char *fmt, va_list ap);

int printf(const char *fmt, ...) {
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
  char *Argstrval; // 字符串参数
  int Argintval; // 整数参数
  int num=0; // 返回字符串长度
  char num_store[200]; // 用来保存变量
  int num_count=0;
  int flag;
  int flag_neg; //判断正负
  int strl;
  int i;
  //double ArgFloVal = 0.0; // 接受浮点型

 while(*p1 !='\0')
  {
    switch(*p1)
    {
      case '%':
          p1++;
          flag=0;
          strl=0;
          switch(*p1)
          {
            case '+':flag |= FLAG_RIGHT;p1++;  break;
            case '-':flag |= FLAG_LEFT;p1++; break;
          }
          if(*p1 == '0')
          { 
            flag |= FLAG_ZERO;p1++; 
          }
			    while(*p1>='0'&& *p1 <='9')
			    {
			      flag |= FLAG_NUM;
			      strl =*p1 - 0x30 + strl*10;
			      p1++;
			    }
          if(*p1 == 'l')
          {
            p1++;
          }
          switch (*p1)
          {
          case 'd':
          flag_neg = 0;
          Argintval = va_arg(ap,int);
          if(Argintval <0)
          {
            Argintval = -Argintval;
            flag_neg = 1;
          }
          num_count = int2str(num_store,Argintval);
          if(flag & FLAG_NUM)
          {
            if(flag & FLAG_LEFT)
            {
              if(flag_neg == 1)
              {
                *(p2++) = '-';
                strl--;
              }
              if(flag & FLAG_ZERO)
              {
                while(num_count>0)
                {
                  *(p2++) = num_store[--num_count];
                  strl--;
                } 
                while(strl>0)
                {
                  *(p2++) = ' ';
					        strl--;
                }
              }
              else 
              {
                while(num_count>0)
                {
                  *(p2++) = num_store[--num_count];
                  strl--;
                } 
                while(strl>0)
                {
                  *(p2++) = ' ';
                  strl--;
				        }
              }
            }
            else 
            {
                if(flag & FLAG_ZERO)
                {
                  if(flag_neg == 1)
                  {
                    *(p2++) = '-';
                    strl--;
                  }
                  while(strl > num_count)
                  {
                    *(p2++) = '0';
                    strl--;
                  }
                  while(num_count>0)
                  {
                  *(p2++) = num_store[--num_count];
                  }
                }
                else 
                {
                  while(strl > num_count)
                  {
                    *(p2++) = ' ';
                    strl--;
                  }
                  if(flag_neg == 1)
                  {
                    *(p2++) = '-';
                  }
                  while(num_count>0)
                  {
                  *(p2++) = num_store[--num_count];
                  }
                }
            }
          }
          else 
          {
            if(flag_neg == 1)
              {
                *(p2++) = '-';
              }
            while(num_count>0)
              {
                *(p2++) = num_store[--num_count];
              }
          }
          p1++;
          break;
          case 's':
          i=0;
          Argstrval = va_arg(ap,char*);
          num_count = strlen(Argstrval);
          if(flag & FLAG_NUM)
          {
            if(flag & FLAG_LEFT)
            {
              if(flag & FLAG_ZERO)
              {
                while(i<num_count)
                {
                  *(p2++) =  Argstrval[i++];
                  strl--;
                } 
                while(strl>0)
                {
                  *(p2++) = '0';
					        strl--;
                }
              }
              else 
              {
                while(i<num_count)
                {
                  *(p2++) =  Argstrval[i++];
                  strl--;
                } 
                while(strl>0)
                {
                  *(p2++) = ' ';
                  strl--;
				        }
              }
            }
            else 
            {
              if(flag & FLAG_ZERO)
              {
                while(strl > num_count)
                {
                  *(p2++) = '0';
                  strl--;
                }
                while(i<num_count)
                {
                *(p2++) = Argstrval[i++];
                }
              }
              else 
              {
                while(strl > num_count)
                {
                  *(p2++) = ' ';
                  strl--;
                }
                while(i<num_count)
                {
                *(p2++) = Argstrval[i++];
                }
              }
            }
          }
          else 
          {
            while(i<num_count)
              {
                *(p2++) = Argstrval[i++];
              }
          }
          p1++;
          break;
          case 'f': 
          /*
          flag_neg =0;
          ArgFloVal = va_arg(ap,double);
          if(ArgFloVal <0)
          {
            ArgFloVal = -ArgFloVal;
            flag_neg = 1;
          }
          num_count = float2str(num_store,ArgFloVal);
          if(flag & FLAG_NUM)
          {
            if(flag & FLAG_LEFT)
            {
              if(flag_neg == 1)
              {
                *(p2++) = '-';
                strl--;
              }
              if(flag & FLAG_ZERO)
              {
                while(num_count!=0)
                {
                  *(p2++) = num_store[--num_count];
                  strl--;
                } 
                while(strl>0)
                {
                  *(p2++) = ' ';
					        strl--;
                }
              }
              else 
              {
                while(num_count!=0)
                {
                  *(p2++) = num_store[--num_count];
                  strl--;
                } 
                while(strl>0)
                {
                  *(p2++) = ' ';
                  strl--;
				        }
              }
            }
            else 
            {
                if(flag & FLAG_ZERO)
                {
                  if(flag_neg == 1)
                  {
                    *(p2++) = '-';
                    strl--;
                  }
                  while(strl > num_count)
                  {
                    *(p2++) = '0';
                    strl--;
                  }
                  while(num_count!=0)
                  {
                  *(p2++) = num_store[--num_count];
                  }
                }
                else 
                {
                  while(strl > num_count)
                  {
                    *(p2++) = ' ';
                    strl--;
                  }
                  if(flag_neg == 1)
                  {
                    *(p2++) = '-';
                  }
                  while(num_count!=0)
                  {
                  *(p2++) = num_store[--num_count];
                  }
                }
            }
          }
          else 
          {
            if(flag_neg == 1)
              {
                *(p2++) = '-';
              }
            while(num_count!=0)
              {
                *(p2++) = num_store[--num_count];
              }
          }
          p1++;
          break;
          */
         case 'c':
          Argintval = va_arg(ap,int);
          *(p2++) = Argintval;
          p1++;
          break;
         break;//Todo
         case 'x':
          flag_neg = 0;
          Argintval = va_arg(ap,int);
          if(Argintval <0)
          {
            Argintval = -Argintval;
            flag_neg = 0;
          }
          num_count = int2hex(num_store,Argintval);
          if(flag & FLAG_NUM)
          {
            if(flag & FLAG_LEFT)
            {
              if(flag_neg == 1)
              {
                *(p2++) = '-';
                strl--;
              }
              if(flag & FLAG_ZERO)
              {
                while(num_count>0)
                {
                  *(p2++) = num_store[--num_count];
                  strl--;
                } 
                while(strl>0)
                {
                  *(p2++) = ' ';
					        strl--;
                }
              }
              else 
              {
                while(num_count>0)
                {
                  *(p2++) = num_store[--num_count];
                  strl--;
                } 
                while(strl>0)
                {
                  *(p2++) = ' ';
                  strl--;
				        }
              }
            }
            else 
            {
                if(flag & FLAG_ZERO)
                {
                  if(flag_neg == 1)
                  {
                    *(p2++) = '-';
                    strl--;
                  }
                  while(strl > num_count)
                  {
                    *(p2++) = '0';
                    strl--;
                  }
                  while(num_count>0)
                  {
                  *(p2++) = num_store[--num_count];
                  }
                }
                else 
                {
                  while(strl > num_count)
                  {
                    *(p2++) = ' ';
                    strl--;
                  }
                  if(flag_neg == 1)
                  {
                    *(p2++) = '-';
                  }
                  while(num_count>0)
                  {
                  *(p2++) = num_store[--num_count];
                  }
                }
            }
          }
          else 
          {
            if(flag_neg == 1)
              {
                *(p2++) = '-';
              }
            while(num_count>0)
              {
                *(p2++) = num_store[--num_count];
              }
          }
          p1++;
          break;
         default:
        }
          
      default: 
      *(p2++) =*(p1++);//将fmt赋值给out
    
    }
}
  *p2 = '\0';
  num = strlen(out);
  return num;
}

int sprintf(char *out, const char *fmt, ...) {
  const char *p1=fmt;
  char *p2 = out;
  char *Argstrval; // 字符串参数
  int Argintval; // 整数参数
  int num=0; // 返回字符串长度
  char num_store[50]; // 用来保存变量
  int num_count=0;
  int flag;
  int flag_neg; //判断正负
  int strl;
  int i;
 // double ArgFloVal = 0.0; // 接受浮点型
  va_list pArgs; //创建pArgs变量，用于参数地址
  va_start(pArgs, fmt); 

  while(*p1 !='\0')
  {
    switch(*p1)
    {
      case '%':
          p1++;
          flag=0;
          strl=0;
          switch(*p1)
          {
            case '+':flag |= FLAG_RIGHT;p1++;  break;
            case '-':flag |= FLAG_LEFT;p1++; break;
          }
          if(*p1 == '0')
          { 
            flag |= FLAG_ZERO;p1++; 
          }
			    while(*p1>='0'&& *p1 <='9')
			    {
			      flag |= FLAG_NUM;
			      strl =*p1 - 0x30 + strl*10;
			      p1++;
			    }
          switch (*p1)
          {
          case 'd':
          flag_neg = 0;
          Argintval = va_arg(pArgs,int);
          if(Argintval <0)
          {
            Argintval = -Argintval;
            flag_neg = 1;
          }
          num_count = int2str(num_store,Argintval);
          if(flag & FLAG_NUM)
          {
            if(flag & FLAG_LEFT)
            {
              if(flag_neg == 1)
              {
                *(p2++) = '-';
                strl--;
              }
              if(flag & FLAG_ZERO)
              {
                while(num_count!=0)
                {
                  *(p2++) = num_store[--num_count];
                  strl--;
                } 
                while(strl>0)
                {
                  *(p2++) = ' ';
					        strl--;
                }
              }
              else 
              {
                while(num_count!=0)
                {
                  *(p2++) = num_store[--num_count];
                  strl--;
                } 
                while(strl>0)
                {
                  *(p2++) = ' ';
                  strl--;
				        }
              }
            }
            else 
            {
                if(flag & FLAG_ZERO)
                {
                  if(flag_neg == 1)
                  {
                    *(p2++) = '-';
                    strl--;
                  }
                  while(strl > num_count)
                  {
                    *(p2++) = '0';
                    strl--;
                  }
                  while(num_count!=0)
                  {
                  *(p2++) = num_store[--num_count];
                  }
                }
                else 
                {
                  while(strl > num_count)
                  {
                    *(p2++) = ' ';
                    strl--;
                  }
                  if(flag_neg == 1)
                  {
                    *(p2++) = '-';
                  }
                  while(num_count!=0)
                  {
                  *(p2++) = num_store[--num_count];
                  }
                }
            }
          }
          else 
          {
            if(flag_neg == 1)
              {
                *(p2++) = '-';
              }
            while(num_count!=0)
              {
                *(p2++) = num_store[--num_count];
              }
          }
          p1++;
          break;
          case 's':
          i=0;
          Argstrval = va_arg(pArgs,char*);
          num_count = strlen(Argstrval);
          if(flag & FLAG_NUM)
          {
            if(flag & FLAG_LEFT)
            {
              if(flag & FLAG_ZERO)
              {
                while(i<num_count)
                {
                  *(p2++) =  Argstrval[i++];
                  strl--;
                } 
                while(strl>0)
                {
                  *(p2++) = '0';
					        strl--;
                }
              }
              else 
              {
                while(i<num_count)
                {
                  *(p2++) =  Argstrval[i++];
                  strl--;
                } 
                while(strl>0)
                {
                  *(p2++) = ' ';
                  strl--;
				        }
              }
            }
            else 
            {
              if(flag & FLAG_ZERO)
              {
                while(strl > num_count)
                {
                  *(p2++) = '0';
                  strl--;
                }
                while(i<num_count)
                {
                *(p2++) = Argstrval[i++];
                }
              }
              else 
              {
                while(strl > num_count)
                {
                  *(p2++) = ' ';
                  strl--;
                }
                while(i<num_count)
                {
                *(p2++) = Argstrval[i++];
                }
              }
            }
          }
          else 
          {
            while(i<num_count)
              {
                *(p2++) = Argstrval[i++];
              }
          }
          p1++;
          break;
          case 'f':
          /*
          flag_neg =0;
          ArgFloVal = va_arg(pArgs,double);
          if(ArgFloVal <0)
          {
            ArgFloVal = -ArgFloVal;
            flag_neg = 1;
          }
          num_count = float2str(num_store,ArgFloVal);
          if(flag & FLAG_NUM)
          {
            if(flag & FLAG_LEFT)
            {
              if(flag_neg == 1)
              {
                *(p2++) = '-';
                strl--;
              }
              if(flag & FLAG_ZERO)
              {
                while(num_count!=0)
                {
                  *(p2++) = num_store[--num_count];
                  strl--;
                } 
                while(strl>0)
                {
                  *(p2++) = ' ';
					        strl--;
                }
              }
              else 
              {
                while(num_count!=0)
                {
                  *(p2++) = num_store[--num_count];
                  strl--;
                } 
                while(strl>0)
                {
                  *(p2++) = ' ';
                  strl--;
				        }
              }
            }
            else 
            {
                if(flag & FLAG_ZERO)
                {
                  if(flag_neg == 1)
                  {
                    *(p2++) = '-';
                    strl--;
                  }
                  while(strl > num_count)
                  {
                    *(p2++) = '0';
                    strl--;
                  }
                  while(num_count!=0)
                  {
                  *(p2++) = num_store[--num_count];
                  }
                }
                else 
                {
                  while(strl > num_count)
                  {
                    *(p2++) = ' ';
                    strl--;
                  }
                  if(flag_neg == 1)
                  {
                    *(p2++) = '-';
                  }
                  while(num_count!=0)
                  {
                  *(p2++) = num_store[--num_count];
                  }
                }
            }
          }
          else 
          {
            if(flag_neg == 1)
              {
                *(p2++) = '-';
              }
            while(num_count!=0)
              {
                *(p2++) = num_store[--num_count];
              }
          }
          p1++;
          break;
          */
         case 'c':assert(0);break;//Todo
         case 'x':
          flag_neg = 0;
          Argintval = va_arg(pArgs,int);
          if(Argintval <0)
          {
            Argintval = -Argintval;
            flag_neg = 1;
          }
          num_count = int2hex(num_store,Argintval);
          if(flag & FLAG_NUM)
          {
            if(flag & FLAG_LEFT)
            {
              if(flag_neg == 1)
              {
                *(p2++) = '-';
                strl--;
              }
              if(flag & FLAG_ZERO)
              {
                while(num_count!=0)
                {
                  *(p2++) = num_store[--num_count];
                  strl--;
                } 
                while(strl>0)
                {
                  *(p2++) = ' ';
					        strl--;
                }
              }
              else 
              {
                while(num_count!=0)
                {
                  *(p2++) = num_store[--num_count];
                  strl--;
                } 
                while(strl>0)
                {
                  *(p2++) = ' ';
                  strl--;
				        }
              }
            }
            else 
            {
                if(flag & FLAG_ZERO)
                {
                  if(flag_neg == 1)
                  {
                    *(p2++) = '-';
                    strl--;
                  }
                  while(strl > num_count)
                  {
                    *(p2++) = '0';
                    strl--;
                  }
                  while(num_count!=0)
                  {
                  *(p2++) = num_store[--num_count];
                  }
                }
                else 
                {
                  while(strl > num_count)
                  {
                    *(p2++) = ' ';
                    strl--;
                  }
                  if(flag_neg == 1)
                  {
                    *(p2++) = '-';
                  }
                  while(num_count!=0)
                  {
                  *(p2++) = num_store[--num_count];
                  }
                }
            }
          }
          else 
          {
            if(flag_neg == 1)
              {
                *(p2++) = '-';
              }
            while(num_count!=0)
              {
                *(p2++) = num_store[--num_count];
              }
          }
          p1++;
          break;
         default:assert(0);
          }
      default: 
      *(p2++) =*(p1++);//将fmt赋值给out
    
    }
}
  va_end(pArgs);
  *p2 = '\0';
  num = strlen(out);
  return num;
}

int snprintf(char *out, size_t n, const char *fmt, ...) {
  panic("Not implemented");
}

int vsnprintf(char *out, size_t n, const char *fmt, va_list ap) {
  panic("Not implemented");
}

#endif
