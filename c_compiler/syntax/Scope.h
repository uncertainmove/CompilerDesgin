/*************************************************************************
	> File Name: Scope.h
	> Author: zengzhen
	> Mail: u201414816@hust.edu.cn
	> Created Time: 2016年11月03日 星期四 09时33分24秒
 ************************************************************************/

#ifndef _SCOPE_H
#define _SCOPE_H
struct Symbol {
    int number;
    int action;     // 符号是否为当前域
    int isArray;
    int isFunc;
    int isVariable;
    int isStruct;
    char *name;
    char *type;
    struct Symbol *var; //指向同一名称的下一外层声明
    struct Symbol *level;  //将同一作用域的所有符号串接
    int depth;  //记录符号的嵌套深度，用于检查在给定的嵌套层次中是否已添加过某特定符号
    struct Symbol *hash;  //散列表，支持名称的高效查找
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
void EnterSymbol(char *name, char *type);  // 添加name到符号表的当前作用域中
struct Symbol* ReturnSymbol(char *name);  // 返回当前作用域中名称为name的表项
struct Symbol* CreateNewSymbol(char *name, char *type);
int DeclaredLocally(char *name);  // 检查name是否位于符号表的当前作用域中
struct Hash *GetHashTable(char *name);
void Add(struct Symbol *symbol);  // 向Hash表中添加表项
void Delete(struct Symbol *symbol); // 从Hash表中简单删除表项
void PrintScopeDisplay(struct Symbol **scopeDisplay);
void PrintHash(struct Hash *hash);
#endif
