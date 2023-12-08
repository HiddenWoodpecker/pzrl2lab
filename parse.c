#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#include "parse.h"


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
    if (num[0] == '1'){
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

Number parseNum(char *str){
    Number n;
    size_t len = strlen(str);
    if (str == NULL){
        perror("NULL string");
    }
    if (str[0] == '-'){
        n.sign = -1;
    }
    else{
        n.sign = 1;
    }
    n.nSys = getSystem(str);
    isValid(str, n.nSys);    
    n.iNum = str_to_int(str, n.nSys, n.sign);
    strcpy(n.num, str);

}

int ch_to_int(char c){
    if(isdigit(c)){
        return (int)c - 48;
    }
    else{
        return (int)c - 87;
    }
}

int str_to_int(char *str, enum numSystem Sys, int sign){
    size_t size = strlen(str);
    int offset = (sign == 1) ? 0 : 1;
    switch (Sys){
        case OCT:
            offset += 1;
            break;

        case HEX:
            offset += 2;
            break;
        default:
            break;
    }
    int res = 0;
    for (int i = size-1; i >= offset; i--){
        res += ch_to_int(str[i]) * pow(Sys, size - i -1);
    }
    return res;
}
char int_to_str(int i, enum numSystem Sys){



}
