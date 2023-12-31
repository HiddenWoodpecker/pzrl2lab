#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "parse.h"
#include "calculate.h"

char getOperator(char *str){
    char Ops[] = {'+', '-', '*', '%' ,'&', '|', '^', '~'};
    if (!strlen(str) > 1){
        for (size_t i = 0; i < strlen(str); i++){
            for (size_t j = 0; j < 8; j++){
                if (str[i] == Ops[j]){
                    return Ops[j];
                }
            }
        }
    }
    fprintf(stderr, "%s is not a valid operator", str);
    return '0';
}
bool isBitOp(char op){
    char bitOps[] = {'&', '|', '^'};
    for (size_t i = 0; i < 3; i++){
        if (bitOps[i] == op) {
            return true;
        }
    }
    return false;
}

bool validateOp(char op, LL i1, LL i2){
    if (isBitOp(op) && ((i1 < 0) || (i2 < 0))){
        fprintf(stderr,"Both numbers should be non negative");
        return false;
    }
    if (op == '%' && (i2 == 0)){
        fprintf(stderr,"Division by zero");
        return false;
    }
    return true;
}

bool isValid(char *str, enum numSystem SYS){
    if (SYS == UNKNOWN){
        return false;
    }
    int offset = 0;
    if (str[0] == '-'){
        offset = 1;
    }
    switch (SYS){
        
        case BIN:
            for (size_t i = offset; i < strlen(str); i++){
                if ((int)str[i]<48 || (int)str[i]>49) {// 48 - десятичное значение "0" в ASCII таблице
                        goto notValid;
                    }
            }

        case OCT:
            for (size_t i = 1 + offset; i < strlen(str); i++){
                    if ((int)str[i]<48 || (int)str[i]>55) {
                            goto notValid;
                        }
                }

        case HEX:
            for (size_t i = 2 + offset; i < strlen(str); i++){
                    if ( (int)str[i]<48 || (((int)str[i]>57 && (int)str[i]<97)) || (int)str[i]>102) {// 97 - десятичное значение "a" в ASCII таблице
                            goto notValid;
                        }
                }

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
        fprintf(stderr,"NULL string");
    }
    if (strlen(num) == 1 && num[0] == '0'){
        return BIN;
    }
    if (num[0] == '-'){
        offset = 1;
    }
    if (num[0+offset] == '1'){
        return BIN;
    }

    if (num[0+offset] == '0' && num[1+offset] == 'x'){
        return HEX;
    }

    if (num[0+offset] == '0'){
        return OCT;
    }
    fprintf(stderr, "Unkown numerical system ---- %s", num);
    return UNKNOWN;
}

void printResult(Number n){

    printf("\nResult ");
    if (n.sign == -1){
        printf("-");
        n.iNum = abs(n.iNum) * -1;
    }

    switch (n.nSys){
    
        case HEX:
            printf("0x%s (%d)\n", n.num, n.iNum);
            break;
        case OCT:
            printf("0%s (%d)\n", n.num, n.iNum);
            break;
        case BIN:
            printf("%s (%d)\n", n.num, n.iNum);
            break;
        default:
            break;

    }
    return;
}

void parseInput(char *buf){

    char **tokens = malloc(3*sizeof(char*));
    tokens[0] = NULL;
    tokens[1] = NULL;
    tokens[2] = NULL;
    char *pch = strtok(buf, " ");
    int cnt = 0;

    while (pch != NULL){
        if (cnt==3){
            fprintf(stderr,"Too much values");
            goto End;
        }
        tokens[cnt++] = pch;
        pch = strtok(NULL, " ");
    }

    if (cnt == 0){
        fprintf(stderr,"Empty string");
        goto End;
    }

    switch (cnt){
    
        Number N, n1, n2;
        LL i1;
        char op;
        case 1:

            if (tokens[0][0] != '~'){
                fprintf(stderr, "Not enough values");
                goto End;
            }

            op = getOperator(tokens[0]);
            
            if (op == '0'){
                goto End;
            }

            if (isValid(tokens[0] + 1 , getSystem(tokens[0] + 1) )){
                n1 = parseNum(tokens[0] + 1);
                i1 = calcUnoOperation(op, n1.iNum);
                N.iNum = i1;
                N.nSys = n1.nSys;
                N.sign = (i1 < 0) ? -1: 1;
                itos(i1, N.nSys, N.num);
                printResult(N);
                goto End;
                }
        
        case 2:

            fprintf(stderr,"Invalid number of arguments");
            goto End;

            /*
            if (tokens[0][0] != '~'){
                fprintf(stderr, "Not enough values");
                goto End;
            }
            op = getOperator(tokens[0]);
            if (op == '0'){
                goto End;
            }
            if (isValid(tokens[1] , getSystem(tokens[1]) )){
                tokens[0][strlen(tokens[0])] = '\0';
                n1 = parseNum(tokens[1]);

                i1 = calcUnoOperation(op, n1.iNum);
                
                N.iNum = i1;
                N.nSys = n1.nSys;
                N.sign = (i1 < 0) ? -1: 1;
                itos(i1, N.nSys, N.num);
                printResult(N);
                goto End;
                }
            goto End;
        */
        case 3:

            op = getOperator(tokens[1]);
            if (op == '0'){
                goto End;
            }
            
            if (isValid(tokens[0] , getSystem(tokens[0])) && isValid(tokens[2] , getSystem(tokens[2]))){
                if (op == '~'){
                    fprintf(stderr,"Too much values for ~ operation");
                    goto End;
                }

                tokens[0][strlen(tokens[0])] = '\0';
                tokens[2][strlen(tokens[2])] = '\0';

                n1 = parseNum(tokens[0]);
                n2 = parseNum(tokens[2]);
                
                if (n1.nSys != n2.nSys){
                    fprintf(stderr,"Differnt num systems");
                    goto End;
                }
                if (validateOp(op, n1.iNum, n2.iNum)){
                    i1 = calcBinOperation(op, n1.iNum, n2.iNum);
                    N.iNum = abs(i1);
                    N.nSys = n1.nSys;
                    N.sign = (i1 < 0) ? -1: 1;
                    itos(i1, N.nSys, N.num);
                    printResult(N);
                }
                goto End;
            }
            
        default:
            goto End;
        }
    End:
        free(tokens);
        return;
}

Number parseNum(char *str){
    Number n;
    size_t len = strlen(str);
    int offset = 0;
    if (str == NULL){
        fprintf(stderr,"NULL string");
    }
    if (str[0] == '-'){
        n.sign = -1;
        offset += 1;
    }
    else{
        n.sign = 1;
    }
    n.nSys = getSystem(str);
    isValid(str, n.nSys);    
    n.iNum = stoi(str, n.nSys, n.sign);
    switch (n.nSys){
        case HEX:
            offset += 2;
            break;
        case OCT:
            offset += 1;
            break;
        default:
            break;
    }
    strcpy(n.num, str+offset);
    return n;
}

int ctoi(char c){
    if(isdigit(c)){
        return (int)c - 48;
    }
    else{
        return (int)c - 87;
    }
}

LL stoi(char *str, enum numSystem Sys, int sign){
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
    LL res = 0;
    for (int i = size-1; i >= offset; i--){
        res += ctoi(str[i]) * pow(Sys, size - i -1);
    }
    return res * sign;
}

char itoc(int i, enum numSystem Sys){
    switch (Sys)
    {
    case HEX:
        if (i < 10){
            return (char)(i+48);
        }
        else {
            return (char)(i + 87);
        }
    case BIN:
        return (char)(i + 48);
    case OCT:
        return (char)(i+48);
    default:
        return -1;
    }
    fprintf(stderr,"Неизвестная система исчисления");
    return -1;
}

void reverseStr(char *str){
    int len = strlen(str);
    char *cpy = malloc(len*sizeof(char));
    memcpy(cpy, str, len);
    for (int i = len-1; i >= 0; i--){
        str[i] = cpy[len-1-i];
    }
    free(cpy);
}

char *itos(LL i, enum numSystem Sys, char *dest){

    if (i == 0){
        strcpy(dest, "0\0");
        return "0\0";
    }

    int size = 128;
    char *str = malloc(size*sizeof(char));
    int len = 0;
    int isNegative = i < 0 ? 1:0;
    i = abs(i);

    while (i > 0){
        str[len++] = itoc((i % Sys), Sys);
        if (len + 1 == size){
            char *tmp = realloc(str, size*2);
            size *= 2;
            if (tmp == NULL){
                fprintf(stderr,"Не удалось выделить память");
                return "0\0";
            }
            str = tmp;
            free(tmp);
        }
        i = i / Sys;
    }
    
    str[len++] = '\0';
    reverseStr(str);
    str[len] = '\0';
    strcpy(dest, str);
    free(str);
    return "0\0";
}
