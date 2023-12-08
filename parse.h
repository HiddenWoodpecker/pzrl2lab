#ifndef PARSE
#define PARSE

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

Number parseNum(char *str);
bool isValid(char *str, enum numSystem SYS);
enum numSystem getSystem(char *num);
int ch_to_int(char c);
int str_to_int(char *str, enum numSystem Sys, int sign);
char int_to_str(int i, enum numSystem Sys);
#endif