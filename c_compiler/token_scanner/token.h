/*************************************************************************
	> File Name: token.h
	> Author: 
	> Mail: 
	> Created Time: 2016年10月26日 星期三 18时59分23秒
 ************************************************************************/

#ifndef _TOKEN_H
#define _TOKEN_H
#include<stdio.h>
#include<stdlib.h>
#include"../syntax/syntax.tab.h"

typedef struct YYLTYPE {
    int first_line;
    int first_column;
    int last_line;
    int last_column;
}YYLTYPE;
void print(char *s);
#endif
