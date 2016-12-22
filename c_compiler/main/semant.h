/*************************************************************************
	> File Name: semant.h
	> Author: 
	> Mail: 
	> Created Time: 2016年12月01日 星期四 07时39分18秒
 ************************************************************************/

#ifndef _SEMANT_H
#define _SEMANT_H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"absyn.h"
#include"syntax.tab.h"
#include"frame.h"

typedef struct Type_* Type;
typedef struct FieldList_* FieldList;
typedef struct Temp* _Temp;

struct Symbol {
    int action;     // 符号是否为当前域
    union {
        int return_type;
        int elemtype;
        int structNum; // 结构对应内部编号
    };
    _Temp _temp; // 生成tac时绑定temp
    int address; // 符号存放的相对ebp地址
    int size; // 若为结构体则存放结构体size
    char *name;     // 变量名
    int type;
    struct Node *varlist;
    struct Symbol *var; //指向同一名称的下一外层声明
    struct Symbol *level;  //将同一作用域的所有符号串接
    struct Symbol *structnext;
    int depth;  //记录符号的嵌套深度，用于检查在给定的嵌套层次中是否已添加过某特定符号
    struct Symbol *hash;  //散列表，支持名称的高效查找
};

struct Type_ {
    enum { BASIC, ARRAY, STRUCTURE  } kind;
    union {
        // 基本类型
        int basic;
        // 数组类型信息包括元素类型与数组大小
        struct { Type elem; int size; } array;
        // 结构体类型信息链表
        FieldList structure;
    }u;
};

struct FieldList_ {
    char *name;
    Type type;
    FieldList tail;
};

struct Scope {
    struct Symbol *symbol;
//    struct Scope *next;
//    struct Scope *previous;
    int depth;
};
struct Hash {   // 管理当前作用域的所有符号
    //int hash;
    //struct Hash *next;
    struct Symbol *symbol;
};
void OpenScope();  // 开辟新的作用域
void CloseScope();  // 关闭当前作用域
struct Symbol *EnterSymbol(struct Node *node, int type);  // 添加name到符号表的当前作用域中
struct Symbol* ReturnSymbol(char *name);  // 返回当前作用域中名称为name的表项
struct Symbol* CreateNewSymbol(char *name, char *type);
int DeclaredLocally(char *name);  // 检查name是否位于符号表的当前作用域中
struct Hash *GetHashTable(char *name);
void Add(struct Symbol *symbol);  // 向Hash表中添加表项
void Delete(struct Symbol *symbol); // 从Hash表中简单删除表项
void PrintScopeDisplay(struct Symbol **scopeDisplay);
void PrintHash(struct Hash *hash);
int CheckType(int type1, int type2);
int GetStructNum(char *name);
int FindSTID(int STID, char *name);
void MatchFundecArgs(struct Symbol *symbol, struct Node *args);
int ST(struct Node *node, char *name, int s_type, int *findtype);
void RecursionTypeAssign(struct Node *p);  // 语义分析
void CreateSymbolList(struct Node *p);  // 语义分析
void TypeAssign(struct Node *p, char *type);
void TypeInsert(struct Node* parent, struct Node* child);
void InsertSymbol(struct Node *p);
void RecursionTreePrint(struct Node* root, int spaceNum);
void RecursionInsertSymbol(struct Node *p);
// 为变量分配空间
int ChangeAddr(int *address, struct Symbol *symbol);

// RT
void RTprogram(struct Node *root);
void RTextdeflist(struct Node *root);
void RTextdef(struct Node *root);
int RTspecifier(struct Node *root);
void RTdef(struct Node *root);
void RTdeclist(struct Node *root, int s_type);
void RTvardec(struct Node *root, int s_type);
void RTdec(struct Node *root, int s_type);
void RTextdeclist(struct Node *root, int s_type);
void RTfundec(struct Node *root, int s_type);
void RTcompst(struct Node *root, int s_type);
int RTstructspecifier(struct Node *root);
void RTdeflist(struct Node *root);
int RTtag(struct Node *root);
void RTvarlist(struct Node *root);
int RTparamdec(struct Node *root);
void RTstmtlist(struct Node *root, int s_type);
void RTstmt(struct Node *root, int s_type);
int RTargs(struct Node *, struct Node *var);
int RTexp(struct Node *root, int s_type);

#endif
