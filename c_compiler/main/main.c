/*************************************************************************
	> File Name: main.c
	> Author: 
	> Mail: 
	> Created Time: 2016年11月10日 星期四 06时01分57秒
 ************************************************************************/

#include"main.h"

#undef YYDEBUG
#define YYDEBUG 1

#define controller 1

struct Node *p;
struct Symbol *structlink;
struct Hash h[H_NUM];  //Hash表
struct Symbol *scopeDisplay[7]; //符号表 
int depth = 0;  // 指示当前嵌套深度

int main(int argc, char **argv) {
    if(argc <= 1) return 1;
    FILE* f = fopen(argv[1], "r");
    if(!f){
        perror(argv[1]);
        return 1;
    }
    yyrestart(f);
    //yydebug = 1;
    yyparse();
    //h.hash = 0;
    //h.next = NULL;
    structlink= NULL;
    h[0].symbol = NULL;
    h[1].symbol = NULL;
    h[2].symbol = NULL;
    h[3].symbol = NULL;
    h[4].symbol = NULL;
    for(int i = 1; i < 5; i++) {
        scopeDisplay[i] = NULL;
    }
    TreePrint(p);
    //printf("begin RT\n");
    //RT(p, -1);
    //PrintScopeDisplay(scopeDisplay);
    //PrintHash(h);
    return 0;
}

//******************************************************************************************************
/* --RT-- */
int RT(struct Node *root, int s_type) {
// RT会在遍历specifier节点时返回其声明类型
    struct Symbol *symbol, *t_symbol;
    int spe_type;
    struct Node *node, *tmp;
    int STID;
    tmp = root;
    if(!root) return -1;
    switch(tmp->name) {
            case program:
                if(controller) printf("program \n");
                RT(tmp->child, -1);
                break;
            case extdeflist:
                if(controller) printf("extdeflist [%d]\n", tmp->lineno);
                if(tmp->child) {
                    RT(tmp->child, -1);
                    RT(tmp->child->brother, -1);
                }
                break;
            case extdef:
                if(controller) printf("extdef [%d]\n", tmp->lineno);
                spe_type = RT(tmp->child, -1);
                switch(tmp->type) {
                    case extdeclist:
                        RT(tmp->child->brother, spe_type);
                        break;
                    case fundec:
                        RT(tmp->child->brother, spe_type);
                        RT(tmp->child->brother->brother, spe_type);
                        CloseScope();
                        break;
                }
                break;
            case specifier:
                if(controller) printf("specifier [%d]\n", tmp->lineno);
                switch(tmp->type) {
                    case type:
                       spe_type =  RT(tmp->child, -1);
                        break;
                    case structspecifier:
                        spe_type = RT(tmp->child, s_type);
                        break;
                }
                break;
            case def:
                if(controller) printf("def [%d]\n", tmp->lineno);
                spe_type = RT(tmp->child, s_type);
                RT(tmp->child->brother, spe_type);
                break;
            case declist:
                if(controller) printf("declist [%d]\n", tmp->lineno);
                if(tmp->child) {
                    RT(tmp->child, s_type);
                    RT(tmp->child->brother, s_type);
                }
                break;
            case vardec:
                if(controller) printf("vardec [%d]\n", tmp->lineno);
                switch(tmp->type) {
                    case WORD:
                        if(DeclaredLocally(tmp->word_name)) {
                            printf("Error type ay line %d:%d: ID \"%s\" defined\n", tmp->lineno, tmp->listno, tmp->word_name);
                        }
                    else {
                        symbol = EnterSymbol(tmp, s_type); // 加入符号表 
                        tmp->v.value_type = s_type; 
                    }
                        break;
                    case array:
                        node = tmp;
                        while(node->child) node = node->child;
                        if(DeclaredLocally(node->word_name)) {
                            printf("Error type ay line %d:%d: ID \"%s\" defined\n", node->lineno, node->listno, node->word_name);
                        }
                        else {
                            symbol = EnterSymbol(node, array);
                            symbol->elemtype = s_type;
                            symbol->varlist = tmp->child;
                            tmp->v.value_type = s_type;
                        }
                        break;
                }
                break;
            case dec:
                if(controller) printf("dec [%d]\n", tmp->lineno);
                switch(tmp->type) {
                    case vardec:
                        RT(tmp->child, s_type);
                        break;
                    case ASSIGNOP:
                        RT(tmp->child, s_type);
                        if(!CheckType(s_type, RT(tmp->child->brother, -1))) {
                            printf("Error type at line %d:%d: Assign not matched\n", tmp->lineno, tmp->listno);
                        }
                        break;
                }
                break;
            case extdeclist:
                if(controller) printf("extdeclist [%d]\n", tmp->lineno);
                if(tmp->child) {
                    RT(tmp->child, s_type);
                    RT(tmp->child->brother, s_type);
                }
                break;
            case fundec:
                if(controller) printf("fundec [%d]\n", tmp->lineno);
                symbol = EnterSymbol(tmp, fundec);
                symbol->return_type = s_type;
                symbol->varlist = tmp->child; // 下挂参数列表
                OpenScope();
                if(tmp->child) {
                    RT(tmp->child, -1);
                }
                break;
            case compst:
                if(controller) printf("compst [%d]\n", tmp->lineno);
                // deflist may empty
                RT(tmp->child, s_type);
                if(tmp->child) RT(tmp->child->brother, s_type);
                break;
            case type:
                if(controller) printf("type : %d [%d]\n", tmp->type, tmp->lineno);
                spe_type = tmp->type;
                break;
            case structspecifier:
                if(controller) printf("structspecifier [%d]\n", tmp->lineno);
                switch(tmp->type) {
                    case opttag:
                        if((spe_type = GetStructNum(tmp->child->word_name)) != -1) {
                            printf("Error type at line %d:%d: Struct \"%s\" already defined\n", tmp->child->lineno, tmp->child->listno, tmp->child->word_name);
                        }
                        else {
                            symbol = EnterSymbol(tmp->child, STRUCT);
                            symbol->varlist = tmp->child->brother;
                            // 构建结构链表
                            if(!structlink) {
                                structlink = symbol;
                                symbol->structNum = 1;
                                structlink->structnext = NULL;
                            }
                            else {
                                t_symbol = structlink;
                                symbol->structnext = t_symbol->structnext;
                                t_symbol->structnext = symbol;
                                symbol->structNum = t_symbol->structNum + 1;
                            }
                        }
                        OpenScope();
                        RT(tmp->child->brother, -1);
                        CloseScope();
                        break;
                    case tag:
                        if(!(symbol = ReturnSymbol(tmp->child->word_name))) {
                            printf("Error type at line %d:%d: struct \"%s\" not defined\n", tmp->child->lineno, tmp->child->listno, tmp->child->word_name);
                            spe_type = -1;
                        }
                        else {
                            if(symbol->type != STRUCT) {
                                printf("Error type at line %d:%d: \"%s\" not struct\n", tmp->child->lineno, tmp->child->listno, tmp->child->word_name);
                                spe_type = -1;
                            }
                            else spe_type = symbol->structNum;
                        }
                        break;
                }
                break;
            case deflist:
                if(controller) printf("deflist [%d]\n", tmp->lineno);
                if(tmp->child) {
                    RT(tmp->child, -1);
                    RT(tmp->child->brother, -1);
                }
                break;
            case tag:
                if(controller) printf("tag [%d]\n", tmp->lineno);
                if(!ReturnSymbol(tmp->word_name)) {
                    printf("Error type at line %d:%d: Undifined struct \"%s\"\n", tmp->lineno, tmp->listno, tmp->word_name);
                }
                spe_type = GetStructNum(tmp->word_name);
                break;
            case varlist:
                if(controller) printf("varlist [%d]\n", tmp->lineno);
                if(tmp->child) {
                    RT(tmp->child, -1);
                    RT(tmp->child->brother, -1);
                }
                break;
            case paramdec:
                if(controller) printf("paramdec [%d]\n", tmp->lineno);
                spe_type = RT(tmp->child, -1);
                RT(tmp->child->brother, spe_type);
                break;
            case stmtlist:
                if(controller) printf("stmtlist [%d]\n", tmp->lineno);
                if(tmp->child) {
                    RT(tmp->child, s_type);
                    RT(tmp->child->brother, s_type);
                }
                break;
            case stmt:
                if(controller) printf("stmt [%d]\n", tmp->lineno);
                switch(tmp->type) {
                    case exp:
                        RT(tmp->child, -1);
                        break;
                    case compst:
                        OpenScope();
                        RT(tmp->child, -1);
                        CloseScope();
                        break;
                    case RETURN:
                        if(tmp->child) {
                            if(!CheckType(s_type, RT(tmp->child, -1))) {
                                printf("Error type at line %d:%d: Function return not matched\n", tmp->lineno, tmp->listno);
                            }
                        }
                        else {
                            if(!CheckType(s_type, VOID)) {
                                printf("Error type at line %d:%d: Function return not matched\n", tmp->lineno, tmp->listno);
                            }
                        }
                        break;
                    case IF:
                        if(!CheckType(INT, RT(tmp->child, -1))) {
                            printf("Error type at line %d:%d: IF need INT\n", tmp->lineno, tmp->listno);
                        }
                        printf(" depth : %d\n", depth);
                        RT(tmp->child->brother, s_type);
                        if(tmp->child->brother->brother) RT(tmp->child->brother->brother, s_type);
                        break;
                    case WHILE:
                        if(!CheckType(INT, RT(tmp->child, -1))) {
                            printf("Error type at line %d:%d: WHILE need INT\n", tmp->lineno, tmp->listno);
                        }
                        RT(tmp->child->brother, -1);
                        break;
                }
                break;
            case exp:
                if(controller) printf("exp [%d]\n", tmp->lineno);
                switch(tmp->type) {
                    case ASSIGNOP:
                        if(tmp->child->type == fundec) {
                            printf("Error type at line %d:%d: \"%s\" is left operate\n", tmp->lineno, tmp->listno, tmp->child->word_name);
                        } 
                        else if(tmp->child->type == constant) {
                            printf("Error type at line %d:%d: \"%d\" is left operate\n", tmp->lineno, tmp->listno, tmp->child->child->v.int_value);
                        }
                        if(!CheckType(spe_type = RT(tmp->child, -1), RT(tmp->child->brother, -1))) {
                            printf("Error type at line %d:%d: ASSIGN not matched\n", tmp->lineno, tmp->listno);
                        }
                        break;
                    case AND:
                        if(!CheckType(RT(tmp->child, -1), RT(tmp->child->brother, -1))) {
                            printf("Error type at line %d:%d: AND not matched\n", tmp->lineno, tmp->listno);
                        }
                        spe_type = INT;
                        break;
                    case OR:
                        if(!CheckType(RT(tmp->child, -1), RT(tmp->child->brother, -1))) {
                            printf("Error type at line %d:%d: OR not matched\n", tmp->lineno, tmp->listno);
                        }
                        spe_type = INT;
                        break;
                    case JUDGE_BIGGER:
                        if(!CheckType(RT(tmp->child, -1), RT(tmp->child->brother, -1))) {
                            printf("Error type at line %d:%d: JUDGE_BIGGER not matched\n", tmp->lineno, tmp->listno);
                        }
                        spe_type = INT;
                        break;
                    case JUDGE_SMALLER:
                        if(!CheckType(RT(tmp->child, -1), RT(tmp->child->brother, -1))) {
                            printf("Error type at line %d:%d: JUDGE_SMALLER not matched\n", tmp->lineno, tmp->listno);
                        }
                        spe_type = INT;
                        break;
                    case JUDGE_BIGGER_EQUAL:
                        if(!CheckType(RT(tmp->child, -1), RT(tmp->child->brother, -1))) {
                            printf("Error type at line %d:%d: JUDGE_BIGGER_EQUAL not matched\n", tmp->lineno, tmp->listno);
                        }
                        spe_type = INT;
                        break;
                    case JUDGE_SMALLER_EQUAL:
                        if(!CheckType(RT(tmp->child, -1), RT(tmp->child->brother, -1))) {
                            printf("Error type at line %d:%d: JUDGE_SMALLER_EQUAL not matched\n", tmp->lineno, tmp->listno);
                        }
                        spe_type = INT;
                        break;
                    case JUDGE_NOT_EQUAL:
                        if(!CheckType(RT(tmp->child, -1), RT(tmp->child->brother, -1))) {
                            printf("Error type at line %d:%d: '<=' not matched\n", tmp->lineno, tmp->listno);
                        }
                        spe_type = INT;
                        break;
                    case JUDGE_EQUAL:
                        if(!CheckType(RT(tmp->child, -1), RT(tmp->child->brother, -1))) {
                            //printf("Error type at line %d:%d: '==' not matched\n", tmp->lineno, tmp->listno);
                        }
                        spe_type = INT;
                        break;
                    case PLUS:
                        if(!CheckType(spe_type = RT(tmp->child, -1), RT(tmp->child->brother, -1))) {
                            printf("Error type at line %d:%d: '+' not matched\n", tmp->lineno, tmp->listno);
                        }
                        break;
                    case SUB:
                        if(!CheckType(spe_type = RT(tmp->child, -1), RT(tmp->child->brother, -1))) {
                            printf("Error type at line %d:%d: '-' not matched\n", tmp->lineno, tmp->listno);
                        }
                        break;
                    case MUL:
                        // need to compelt star
                        if(!CheckType(spe_type = RT(tmp->child, -1), RT(tmp->child->brother, -1))) {
                            printf("Error type at line %d:%d: '*' not matched\n", tmp->lineno, tmp->listno);
                        }
                        break;
                    case DIV:
                        if(!CheckType(spe_type = RT(tmp->child, -1), RT(tmp->child->brother, -1))) {
                            printf("Error type at line %d:%d: '/' not matched\n", tmp->lineno, tmp->listno);
                        }
                        break;
                    case exp:
                        spe_type = RT(tmp->child, -1);
                        break;
                    case NOT:
                        if(!CheckType(INT, RT(tmp->child, -1))) {
                            printf("Error type at line %d:%d: '!' not matched\n", tmp->lineno, tmp->listno);
                        }
                        spe_type = INT;
                        break;
                    case fundec:
                        symbol = ReturnSymbol(tmp->word_name);
                        if(symbol) {
                            spe_type = symbol->return_type;
                            if(symbol->type != fundec) {
                                printf("Error type at line %d:%d: \"%s\" not function\n", tmp->lineno, tmp->listno, tmp->word_name);
                            }
                            else if(tmp->child) MatchFundecArgs(symbol, tmp->child);
                        }
                        else {
                            printf("Error type at line %d:%d: Function \"%s\" not defined\n", tmp->lineno, tmp->listno, tmp->word_name);
                            spe_type = -1;
                        }
                        RT(tmp->child, -1);
                        break;
                    case array:
                        spe_type = RT(tmp->child, array);
                        if(!CheckType(INT, RT(tmp->child->brother, -1))) {
                            printf("Error type at line %d:%d: array need int\n", tmp->lineno, tmp->listno);
                        }
                        break;
                    case POINT:
                        if((STID = RT(tmp->child, STRUCT)) == -1) {
                            printf("Error type at line %d:%d: Illegal use of \".\"\n", tmp->lineno, tmp->listno);
                        }
                        else {
                            // 返回元素类型
                            spe_type = FindSTID(STID, tmp->word_name); // 查找对应结构是否存在该元素
                            if(spe_type == -1) {
                                printf("Error type at line %d:%d: \"%s\" not struct member\n", tmp->lineno, tmp->listno, tmp->word_name);
                            }
                        }
                        break;
                    case WORD:
                        spe_type = -1;
                        if(s_type == array) {
                            // 查询此节点是否为array
                            symbol = ReturnSymbol(tmp->word_name);
                            if(symbol) {
                                if(symbol->type == array)
                                    spe_type = symbol->elemtype;
                                else 
                                    printf("Error type at line %d:%d: \"%s\" not an array\n", tmp->lineno, tmp->listno, tmp->word_name);
                            }
                            else {
                                printf("Error type at line %d:%d: \"%s\" not defined\n", tmp->lineno, tmp->listno, tmp->word_name);
                                spe_type = -1;
                            }
                        }
                        else if(s_type == STRUCT) {
                            symbol = ReturnSymbol(tmp->word_name);
                            if(symbol) {
                                spe_type = symbol->type;
                                if(spe_type == INT || spe_type == FLOAT || spe_type == CHAR) {
                                    printf("Error type at line %d:%d: \"%s\" not a struct\n", tmp->lineno, tmp->listno, tmp->word_name);
                                    spe_type = -1;
                                }
                            }
                            else {
                                printf("Error type at line %d:%d: \"%s\" not a struct\n", tmp->lineno, tmp->listno, tmp->word_name);
                                spe_type = -1;
                            }
                        }
                        else {
                            symbol = ReturnSymbol(tmp->word_name);
                            if(symbol) {
                                spe_type = symbol->type;
                            }
                            else {
                                printf("Error type at line %d:%d: \"%s\" not defined\n", tmp->lineno, tmp->listno, tmp->word_name);
                                spe_type = -1;
                            }
                        }
                        break;
                    case constant:
                        spe_type = RT(tmp->child, -1);
                        break;
                }
                break;
            case args:
                if(controller) printf("args [%d]\n", tmp->lineno);
                RT(tmp->child, -1);
                if(tmp->child->brother) RT(tmp->child->brother, -1);
                break;
            case constant:
                if(controller) printf("constant : %d \n", tmp->lineno);
                switch(tmp->type)
                spe_type = tmp->type;
                break;
        }
    return spe_type;
}

int CheckType(int type1, int type2) {
    if(type1 == type2) return 1;
    else return 0;
}

struct Symbol *CreateSymbol(struct Node *node, int type) {
    struct Symbol *symbol = NULL;
    symbol = (struct Symbol*)malloc(sizeof(struct Symbol));
    if(!symbol) printf("分配失败!\n");
    symbol->name = (char *)malloc(sizeof(char) * (strlen(node->word_name) + 1));
    strcpy(symbol->name, node->word_name);
    symbol->type = type;
    symbol->varlist = NULL;
    symbol->level = NULL;
    symbol->hash = NULL;
    symbol->depth = depth;
    symbol->structnext = NULL;
    symbol->action= 0;
    symbol->elemtype = 0;
    return symbol;
}


/* --EnterSymbol-- */
struct Symbol *EnterSymbol(struct Node *node, int type) {
    struct Symbol *oldsym, *newsym;
    newsym = CreateSymbol(node, type);
    oldsym = ReturnSymbol(newsym->name);
    if(oldsym != NULL && oldsym->depth == depth && oldsym->action) {
        printf("Error type at line %d:%d: \"%s\" is defined\n", node->lineno, node->listno, node->word_name);
    }
    else {
        newsym->level = scopeDisplay[depth];
        newsym->depth = depth;
        newsym->action = 1;
        scopeDisplay[depth] = newsym;
        //添加到散列表
        if(oldsym == NULL) {
            Add(newsym);
            //PrintHash(h);
        }
        else {
            Delete(oldsym);
            Add(newsym);
        }
        newsym->var = oldsym;
    }
    return newsym;
}

int GetStructNum(/*struct Node *structlink,*/ char *name) {
    struct Symbol *tmp;
    tmp = structlink;
    while(tmp) {
        if(controller) printf("GetStructNum : %s  structlinkname : %s action : %d\n", name, tmp->name, tmp->action);
        if(!strcmp(tmp->name, name) && tmp->action) {
            return tmp->structNum;
        }
        tmp = tmp->structnext;
    }
    return -1;
}

int FindSTID(int STID, char *name) {
    int elemtype = -1;
    struct Symbol *symbol;
    struct Node *node;
    symbol = structlink;
    while(symbol) {
        if(symbol->structNum == STID) {
            node = symbol->varlist;
            ST(node, name, -1, &elemtype);
            break;
        }
        symbol = symbol->structnext;
    }
    return elemtype; 
}

//--ST--
int ST(struct Node *node, char *name, int s_type, int *findtype) {
    int spe_type;
    struct Node *tmp;
    tmp = node;
    if(node) {
        switch(node->name) {
            case deflist:
                if(controller) printf("qdeflist [%d]\n", tmp->lineno);
                if(tmp->child) {
                    ST(tmp->child, name, -1, findtype);
                    ST(tmp->child->brother,name, -1, findtype);
                }
                break;
            case def:
                if(controller) printf("qdef [%d]\n", tmp->lineno);
                spe_type = ST(tmp->child,name, -1, findtype);
                ST(tmp->child->brother, name, spe_type, findtype);
                break;
            case declist:
                if(controller) printf("qdeclist [%d]\n", tmp->lineno);
                if(tmp->child) {
                    ST(tmp->child, name, s_type, findtype);
                    ST(tmp->child->brother, name, s_type, findtype);
                }
            break;
            case vardec:
                if(controller) printf("vardec [%d]\n", tmp->lineno);
                switch(tmp->type) {
                    case WORD:
                        if(!strcmp(tmp->word_name, name)) {
                            *findtype = tmp->v.value_type;
                        }
                        break;
                    case array:
                        node = tmp;
                        while(node->child) node = node->child;
                        if(!strcmp(node->word_name, name)) {
                            *findtype = node->v.value_type;
                        }
                        break;
                }
                break;
            case dec:
                if(controller) printf("qdec [%d]\n", tmp->lineno);
                    ST(tmp->child, name, s_type, findtype);
                    break;
        }
    }
    return spe_type;
}

/* --RecursionTreePrint-- */
void RecursionTreePrint(struct Node* root, int spaceNum) {
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
        if(tmp->child) {
            RecursionTreePrint(tmp->child, spaceNum+2);
        }
        if(tmp->brother != NULL){
            RecursionTreePrint(tmp->brother, spaceNum);
        }
    }
}

/* --TreePrint-- */
void TreePrint(struct Node* root) {
    RecursionTreePrint(root, 0);
}

/* --ReturnSymbol-- */
struct Symbol* ReturnSymbol(char *name) {
    // 返回当前可见域的第一个可见符号
    struct Hash *sym;
    struct Symbol *tmp;
    sym = GetHashTable(name);
    tmp = sym->symbol;
    while(tmp != NULL) {
        if(!strcmp(tmp->name, name)) {
            return tmp;
        }
        tmp = tmp->hash;
    }
    return NULL;
}

/* --GetHashTable-- */
struct Hash *GetHashTable(char *name) {
    int i = (int)(*name) % H_NUM;
    switch(i) {
        case 0:
            return &(h[0]);
        case 1:
            return &(h[1]);
        case 2:
            return &(h[2]);
        case 3:
            return &(h[3]);
        case 4:
            return &(h[4]);
    }
    return NULL;
}

/* --Add-- */
void Add(struct Symbol *symbol) {
    struct Hash *tmp;
    tmp = GetHashTable(symbol->name);
    symbol->hash = tmp->symbol;
    tmp->symbol = symbol;
}

/* --Delete-- */
void Delete(struct Symbol *symbol) {
    struct Hash *tmp;
    struct Symbol *star;
    struct Symbol *current;
    tmp = GetHashTable(symbol->name);
    star = tmp->symbol;
    if(!strcmp(star->name, symbol->name)) {
        tmp->symbol = symbol->hash;
        symbol->action = 0;
        return;
    }
    while(star != NULL) {
        current = star->hash; 
        if(current == NULL) {
            printf("Delete failed !\n");
            return;
        }
        if(!strcmp(current->name, symbol->name)) {
            star->hash = current->hash;
            current->action = 0;
            return;
       }
       star = star->hash;
    }
}

/* --OpenScope-- */
void OpenScope() {
    depth = depth + 1; // 嵌套深度加1
    //scopeDisplay[depth] = NULL; // 新作用域表项置空
}

/* --CloseScope-- */
void CloseScope() {
    struct Symbol *prevsym;
    struct Symbol *sym;
    for(sym = scopeDisplay[depth]; sym != NULL; sym = sym->level) {
        prevsym = sym->var;
        if(sym->action) {
            //PrintHash(h);
            Delete(sym);
        }
        if(prevsym != NULL) {
            Add(prevsym);
        }
    }
    depth = depth - 1;
}

/* --PrintScopeDisplay-- */
void PrintScopeDisplay(struct Symbol **scopedisplay) {
    struct Symbol *tmp;
    int i = 0;
    printf("fundec\tarray\tint\tfloat\tchar\n");
    printf("%d\t%d\t%d\t%d\t%d\n", fundec, array, INT, FLOAT, CHAR);
    printf("name\t\t\ttype\t\t\tdepth\t\t\taction\t\t\telemtype\t\t\t\n");
    for(i = 0; i < 7; i++) {
        tmp = scopedisplay[i];
        while(tmp) {
            printf("%s\t\t\t%d\t\t\t%d\t\t\t%d\t\t\t%d\t\t\t\n", tmp->name, tmp->type, tmp->depth, tmp->action, tmp->elemtype);
            tmp = tmp->level;
        }
    }
}

/* --PrintHash-- */
void PrintHash(struct Hash *hash) {
    printf("Hash\t\tname\t\ttype\t\t\n");
}

int DeclaredLocally(/*struct Symbol **scopeDisplay, */char *name) {
    struct Symbol *symbol;
    symbol = scopeDisplay[depth];
    if(symbol) {
        while(symbol) {
            if(!strcmp(symbol->name, name) && symbol->action) return 1;
            symbol = symbol->level;
        }
    }
    return 0;
}

void MatchFundecArgs(struct Symbol *symbol, struct Node *args) {
    struct Node *tmp;
    int scount = 0, acount = 0;
    tmp = args;
    while(tmp && tmp->child) {
        acount++;
        tmp = tmp->child->brother;
    }
    tmp = symbol->varlist;
    while(tmp && tmp->child) {
        scount++;
        tmp = tmp->child->brother;
    }
    if(scount != acount) {
        printf("Error type at line %d:%d: Args not matched\n", args->lineno, args->listno);
    }
}
