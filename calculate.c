#include "parse.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

LL calcUnoOperation(char operation, LL i1){
    if (operation != '~'){
        perror("Неизвестная унарная операция");
        return -1;
    }
    return ~i1;
}

LL calcBinOperation(char operation, LL i1, LL i2){
    switch (operation){
        case '+':
            return i1 + i2;
        case '-':
            return i1 - i2;
        case '*':
            return i1 * i2;
        case '%':
            if (i2 == 0){
                perror("Деление на ноль запрещено");
                return -1;
            }
            return i1 % i2;
        case '&':
            if (i1 < 0 || i2 < 0){
                perror("Операнды для побитовой операции должны быть неотрицательным");
                return -1;
            }
            return i1 & i2;
        case '|':
            if (i1 < 0 || i2 < 0){
                perror("Операнды для побитовой операции должны быть неотрицательным");
                return -1;
            }
            return i1 | i2;
        case '^':
            if (i1 < 0 || i2 < 0){
                perror("Операнды для побитовой операции должны быть неотрицательным");
                return -1;
            }
            return i1 ^ i2;
        default:
            return -1;
        }
}