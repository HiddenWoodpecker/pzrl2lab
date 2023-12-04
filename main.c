#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "handlebinary.h"

enum numSystem{
    BIN,
    OCT,
    HEX
};

bool isValid(char *str, enum numSystem SYS){
    switch (SYS){
        
        case BIN:
            for (size_t i = 0; i < strlen(str); i++){
                if ((int)str[i]<48 || (int)str[i]>49) {
                    goto notValid;
                    }
            }
            break;

        case OCT:
            for (size_t i = 1; i < strlen(str); i++){
                    if ((int)str[i]<48 || (int)str[i]>55) {
                        goto notValid;
                        }
                }
            break;

        case HEX:
            for (size_t i = 2; i < strlen(str); i++){
                    if ( (int)str[i]<48 || (((int)str[i]>57 && (int)str[i]<97)) || (int)str[i]>101) {
                        goto notValid;
                        }
                }
            break;  

        default:
            break;
    }
    
    return true;
    notValid:
        fprintf(stderr, "%s is not a valid number\n", str);
        return false;
}

enum numSystem getSystem(char *num){ 
    int offset = 0;
    if (num == NULL){
        perror("NULL string");
    }
    if (num[0] == '-'){
        offset = 1;
    }
    if (strlen(num) < 2+offset){
        return BIN;
    }

    if (num[0+offset] == '0' && num[1+offset] == 'x'){
        return HEX;
    }

    if (num[0+offset] == '0'){
        return OCT;
    }
    return BIN;
}


int main(int argc, char const *argv[]){
    //char s1[] = "0x1a2d\0";
    //char s2[] = "012\0";
    //char s3[] = "0fz12\0";
    //char s4[] = "1010\0";
    printf("%d\n",isValid("0x123", HEX));
    printf("%d\n", bin_to_int("1110\0"));
    printf("%s\n", int_to_bin(8));
    printf("%s\n", int_to_bin(9));
    return 0;
}


