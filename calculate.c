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
            return i1 % i2;
        case '&':
            return i1 & i2;
        case '|':
            return i1 | i2;
        case '^':
            return i1 ^ i2;
        default:
            return -1;
        }
}