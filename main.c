#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "calculate.h"
#include "parse.h"

int main(int argc, char const *argv[]){
    char test[128] = "0x123 + 0x1\0";
   
    int bufsize = 128;
    char* buf = malloc(bufsize*sizeof(char));
    int len = 0;
    char c;
    printf("Input:");
    while((c = getchar()) != '\n'){
        if (len+1 == bufsize){
            char *tmp = realloc(buf, bufsize*2*sizeof(char));
            bufsize *= 2;
            if (tmp == NULL){
                perror("Not enough memory");
                return -1;
            }
            buf = tmp;
        }
        buf[len++] = c;
    }
    printf("%d len\n", len);
    buf[len++] = '\0';
    printf("buf = %s len = %d strlen = %d\n", buf, len, strlen(buf));

    parseInput(buf);

    free(buf);
    return 0;
}


