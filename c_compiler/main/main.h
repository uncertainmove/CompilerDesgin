/*************************************************************************
	> File Name: main.h
	> Author: 
	> Mail: 
	> Created Time: 2016年11月10日 星期四 06时49分44秒
 ************************************************************************/

#ifndef _MAIN_H
#define _MAIN_H

#include<stdio.h>
#include<string.h>
#include"Node.h"
#include"Scope.h"
#include"token.h"
#include"syntax.tab.c"
#define H_NUM 5

void RecursionTypeAssign(struct Node *p);  // 语义分析
void CreateSymbolList(struct Node *p);  // 语义分析
void TypeAssign(struct Node *p, char *type);
void TypeInsert(struct Node* parent, struct Node* child);
void InsertSymbol(struct Node *p);
void RecursionTreePrint(struct Node* root, int spaceNum);
void TreePrint(struct Node* root);
void RecursionInsertSymbol(struct Node *p);

#endif
