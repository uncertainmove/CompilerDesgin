/*************************************************************************
	> File Name: absyn.c
	> Author: 
	> Mail: 
	> Created Time: 2016年12月01日 星期四 07时20分57秒
 ************************************************************************/

#include"absyn.h"

struct Node *p;

/* --NewNode-- */
struct Node* NewNode(int node_name, int lineno, int listno, int isWhat) {
    struct Node *p = (struct Node*)malloc(sizeof(struct Node));
    if(p == NULL) {
        printf("Error: out of memory.\n");
        exit(1);
    }
    p->name = node_name;
    p->lineno = lineno;
    p->listno = listno;
    p->type = isWhat;    //语义分析时赋值
    p->brother = NULL;
    p->child = NULL;
    p->No_Child = 0;
    p->IsBegin = 0;
    return p;
}

/* --insert-- */
void insert(struct Node* parent, struct Node* child) {
    struct Node *p;
    if(child == NULL) {
        return;
    }
    if(parent->No_Child == 0) {
        parent->child = child;
        child->IsBegin = 1;
        parent->No_Child = 1;
    }
    else {
        p = parent->child;
        while(p->brother!= NULL) {
            p = p->brother;
        }
        p->brother = child;
        child->IsBegin = 0;
        parent->No_Child++;
    }
}

/* --TreePrint-- */
void TreePrint(struct Node* root, int spaceNum) {
    int i;
    struct Node *tmp;
    tmp = root;
    if(tmp) {
        i = spaceNum;
        while(i > 0) {
            printf(" ");
            i--;
        }
        switch(tmp->name) {
            case program:
                printf("program [%d]\n", tmp->lineno);
                break;
            case extdeflist:
                printf("extdeflist [%d]\n", tmp->lineno);
                break;
            case extdef:
                printf("extdef [%d]\n", tmp->lineno);
                break;
            case specifier:
                printf("specifier [%d]\n", tmp->lineno);
                break;
            case def:
                printf("def [%d]\n", tmp->lineno);
                break;
            case declist:
                printf("declist [%d]\n", tmp->lineno);
                break;
            case vardec:
                printf("vardec [%d]\n", tmp->lineno);
                if(tmp->type == WORD) {
                    i = spaceNum;
                    while(i > 0) {
                        printf(" ");
                        i--;
                    }
                    printf("  ID : %s\n", tmp->word_name);
                }
                break;
            case dec:
                printf("dec [%d]\n", tmp->lineno);
                break;
            case extdeclist:
                printf("extdeclist [%d]\n", tmp->lineno);
                break;
            case fundec:
                printf("fundec [%d]\n", tmp->lineno);
                break;
            case compst:
                printf("compst [%d]\n", tmp->lineno);
                break;
            case type:
                printf("type : %d [%d]\n", tmp->type, tmp->lineno);
                break;
            case structspecifier:
                printf("structspecifier [%d]\n", tmp->lineno);
                break;
            case opttag:
                printf("opttag [%d]\n", tmp->lineno);
                break;
            case deflist:
                printf("deflist [%d]\n", tmp->lineno);
                break;
            case tag:
                printf("tag [%d]\n", tmp->lineno);
                break;
            case varlist:
                printf("varlist [%d]\n", tmp->lineno);
                break;
            case paramdec:
                printf("paramdec [%d]\n", tmp->lineno);
                break;
            case stmtlist:
                printf("stmtlist [%d]\n", tmp->lineno);
                break;
            case stmt:
                printf("stmt [%d]\n", tmp->lineno);
                break;
            case exp:
                printf("exp [%d]\n", tmp->lineno);
                break;
            case args:
                printf("args [%d]\n", tmp->lineno);
                break;
            case constant:
                printf("constant : %d [%d]\n", tmp->lineno, tmp->v.int_value);
                break;
        }
        if(root->child) {
            TreePrint(tmp->child, spaceNum+2);
        }
        if(tmp->brother != NULL){
            TreePrint(tmp->brother, spaceNum);
        }
    }
}
