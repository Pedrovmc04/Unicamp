#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

int multiplica(int num_args,...){
    int result = 1;
    va_list args;
    va_start(args, num_args);

    for(int i = 0 ; i < num_args ; i++){
        result *= va_arg(args, int);
    }
    va_end(args);

    return result;
}

int main(){

    int mult = 0;
    mult = multiplica(2,3,4);

    printf("%d\n", mult);

    return 0;
}