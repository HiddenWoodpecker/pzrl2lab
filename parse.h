#ifndef PARSE
#define PARSE
#include <stdbool.h>
enum numSystem{
    BIN = 2,
    OCT = 8,
    HEX = 16
};

typedef struct Number{
    enum numSystem nSys;
    int iNum;
    char num[128];
    int sign;
} Number;
void printResult(Number n);
void reverseStr(char *str);
char getOperator(char *str);
void parseInput(char *buf);
Number parseNum(char *str);
bool isValid(char *str, enum numSystem SYS);
enum numSystem getSystem(char *num);
int ctoi(char c);
int stoi(char *str, enum numSystem Sys, int sign);
char itoc(int i, enum numSystem Sys);
char* itos(int i, enum numSystem Sys);

#endif