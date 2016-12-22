/*************************************************************************
	> File Name: absyn.h 
	> Author: 
	> Mail: 
	> Created Time: 2016年11月02日 星期三 18时42分22秒
 ************************************************************************/

#ifndef _ABSYN_H
#define _ABSYN_H
#include<stdio.h>
#include<stdlib.h>
#include"syntax.tab.h"
#include"semant.h"

enum notoken {array, program, extdeflist, extdef, specifier, def, declist, vardec, dec, extdeclist, fundec, compst, type, structspecifier, opttag, deflist, tag, varlist, paramdec, stmtlist, stmt, exp, args, constant,};

struct Node {
    int name;
    union {
        int int_value;
        char char_value;
        float float_value;
        int value_type;
    }v;
    struct Symbol *symbol;
    int IsBegin;
    char *word_name;
    int type;
    int depth;
    int lineno;
    int listno;
    int capacity;   // 数组大小
    int No_Child;
    union {
        int i; // integer
        char *ID;
        float f;
        int t;
    }palce;
    int ptag; // 用以标志place的类型1,2,3,4,
    struct Node *brother;
    struct Node *child;
};


void insert(struct Node* parent, struct Node* child);
void TreePrint(struct Node* root, int spacenum);
struct Node* NewNode(int node_name, int lineno, int listno, int group);
#endif
