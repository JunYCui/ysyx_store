#include "stdio.h"
#include "stdlib.h"

int main(void){
    printf("mainargs = %s",getenv("mainargs"));
    return 0;
}