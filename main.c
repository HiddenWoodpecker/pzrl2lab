#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "calculate.h"
#include "parse.h"

int main(int argc, char const *argv[]){
   
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
    buf[len++] = '\0';
    parseInput(buf);
    free(buf);
    return 0;
}


