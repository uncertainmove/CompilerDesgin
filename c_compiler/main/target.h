/*************************************************************************
	> File Name: target.h
	> Author: 
	> Mail: 
	> Created Time: 2016年12月13日 星期二 16时56分23秒
 ************************************************************************/

#ifndef _TARGET_H
#define _TARGET_H
#include "frame.h"

typedef struct Taclist* _Taclist;
typedef struct Tac* _Tac;

void target_start(char *, _Taclist);
// sign = 0 : movl $-, %reg
// sign = 1 : movl $-, --(%rbp)
// sign = 2 : movl %reg, --(%rbp)
// sign = 3 : movl --(%rbp), %reg 
// sign = 4 : movl glb, %reg
// sign = 5 : movl %reg, glb
// sign = 6 : movl $-, glb
void movl(FILE *f, int constant, int offset, const char *reg, const char *glb, int sign);
#endif
