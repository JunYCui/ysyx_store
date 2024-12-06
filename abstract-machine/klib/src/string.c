#include <klib.h>
#include <klib-macros.h>
#include <stdint.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

size_t strlen(const char *s) {
  size_t i=0;
  while(s[i]!='\0')
  {
    i++;
  }
  return i;
}

char *strcpy(char *dst, const char *src) {
  size_t i=0;
  while(src[i]!='\0')
  {
    dst[i] = src[i];
    i++;
  }
  dst[i] = '\0';
  return dst;
}

char *strncpy(char *dst, const char *src, size_t n) {
  size_t i=0;
  size_t len = strlen(src);
  if(len<n)
  {
    while(i<len)
    {
      dst[i] = src[i];
      i++;
    }  
    while(i<n)
    {
      dst[i] = 0x00;
      i++;
    }
  }
  else 
  {
    while(i<n)
  {
    dst[i]=src[i];
    i++;
  }
  }
  dst[i] = '\0';
  return dst;
}

char *strcat(char *dst, const char *src) {
  size_t i=0,j=0;
  while(dst[i]!='\0')
  i++;
  while(src[j]!='\0')
  {
    dst[i++]=src[j++];
  }
  dst[i] = '\0';
  return dst;
}

int strcmp(const char *s1, const char *s2) {
  size_t i=0;
  while(s1[i]==s2[i])
  {
    if(s1[i] == '\0')
      return 0;
    i++;
  }
  return s1[i]-s2[i];
}

int strncmp(const char *s1, const char *s2, size_t n) {
  size_t i=0;
  while(s1[i]==s2[i])
  {
    i++;
    if(i == n)
      return 0;
    else 
    {
    if(s1[i] == '\0')
      return 0;
    }
  }
  return s1[i]-s2[i];
}

void *memset(void *s, int c, size_t n) {
  size_t i=0;
  char *p=s;
  for(i=0;i<n;i++)
    *(p+i) =c;
  return s;
}

void *memmove(void *dst, const void *src, size_t n) {

	if (dst < src)
	{
		for (int i = 0; i < n; i++)
		{
			*((char*)dst + i) = *((char*)src + i);
		}
		return dst;
	}
	else if (dst > src)
	{
		for (int i = n-1; i >=0; i--)
		{
			*((char*)dst + i) = *((char*)src + i);
		}
		return dst;
	}
	else
	{
		return dst;
  }

}

void *memcpy(void *out, const void *in, size_t n) {
  char *p0=out;
  const char*p1 = in;
  while(n--)
  {
    *(p0++) = *(p1++);
  }
  return out;
}

int memcmp(const void *s1, const void *s2, size_t n) {
  const char *p1=s1;
  const char *p2=s2;
  size_t i=0;
  while(*(p1+i)==*(p2+i))
  {
    i++;    
    if(i==n)
      return 0;
  }
  return *(p1+i)-*(p2+i);
}

#endif
