#include "parse.h"
#include <stdlib.h>
#include <stdbool.h>
int calcUnoOperation(char operation, int i1){
    if (operation != '~'){
        perror("Неизвестная унарная операция");
        return -1;
    }
    return ~i1;
}

int calcBinOperation(char operation, int i1, int i2){
    switch (operation){
        case '+':
            
            return i1 + i2;
            break;
        case '-':
            return i1 - i2;
            break;
        
        case '*':
            return i1 * i2;
            break;
        case '%':
            return i1 % i2;
            break;
        case '&':
            if (i1 < 0 || i2 < 0){
                perror("Операнды для побитовой операции должны быть неотрицательным");
                return -1;
            }
            return i1 & i2;
            break;
        case '|':
            if (i1 < 0 || i2 < 0){
                perror("Операнды для побитовой операции должны быть неотрицательным");
                return -1;
            }
            return i1 | i2;
            break;
        case '^':
            if (i1 < 0 || i2 < 0){
                perror("Операнды для побитовой операции должны быть неотрицательным");
                return -1;
            }
            return i1 ^ i2;
            break;
        default:
            return -1;
            break;
        }
    return -1;
}