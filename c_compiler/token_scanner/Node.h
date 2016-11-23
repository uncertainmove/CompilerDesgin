/*************************************************************************
	> File Name: Node.h
	> Author: 
	> Mail: 
	> Created Time: 2016年11月02日 星期三 18时42分22秒
 ************************************************************************/

#ifndef _NODE_H
#define _NODE_H
struct Node {
    char *name;
    int IsBegin;
    int group;
    char *type;
    int No_Line;
    int No_Child;
    struct Node *brother;
    struct Node *child;
};

void insert(struct Node* parent, struct Node* child);
void treePrint(struct Node* root);
void recursionTreePrint(struct Node* root, int spaceNum);
#endif
