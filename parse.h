#ifndef PARSE
#define PARSE
#include <stdbool.h>
enum numSystem{
    UNKNOWN = -1,
    BIN = 2,
    OCT = 8,
    HEX = 16
};

typedef long long LL;

typedef struct Number{
    enum numSystem nSys;
    LL iNum;
    char num[128];
    int sign;
} Number;

void printResult(Number n);
void reverseStr(char *str);
char getOperator(char *str);
bool isBitOp(char op);
void parseInput(char *buf);
bool validateOp(char op, LL i1, LL i2);
Number parseNum(char *str);
bool isValid(char *str, enum numSystem SYS);
enum numSystem getSystem(char *num);
int ctoi(char c);
LL stoi(char *str, enum numSystem Sys, int sign);
char itoc(int i, enum numSystem Sys);
char *itos(LL i, enum numSystem Sys, char *dest);

#endif