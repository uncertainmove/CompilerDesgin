/*************************************************************************
	> File Name: semant.c
	> Author: 
	> Mail: 
	> Created Time: 2016年12月01日 星期四 07时39分25秒
 ************************************************************************/

#include"semant.h"

#define controller 0
#define H_NUM 5

extern struct Node *p;
struct Symbol *structlink;
struct Hash h[H_NUM];  //Hash表
struct Symbol *scopeDisplay[7]; //符号表 
int depth = 0;  // 指示当前嵌套深度
int address = 0; // 记录当前函数已分配的空间

void RTprogram(struct Node *root) {
    if(controller) printf("program \n");
    RTextdeflist(root->child);
}
void RTextdeflist(struct Node *root) {
    if(controller) printf("extdeflist\n");
    if(root->child) {
        RTextdef(root->child);
        if(root->child->brother) RTextdeflist(root->child->brother);
    }
}
void RTextdef(struct Node *root) {
    int spe_type;
    if(controller) printf("extdef\n");
    spe_type = RTspecifier(root->child);
    switch(root->type) {
        case extdeclist:
            RTextdeclist(root->child->brother, spe_type);
            break;
        case fundec:
            RTfundec(root->child->brother, spe_type);
            RTcompst(root->child->brother->brother, spe_type);
            CloseScope();
            break;
    }
}
int RTspecifier(struct Node *root) {
    int spe_type = -1;
    if(controller) printf("specifier\n");
    switch(root->type) {
        case type:
            spe_type =  root->child->type;
            break;
        case structspecifier:
            spe_type = RTstructspecifier(root->child);
            break;
    }
    // printf("RTspecifier:(spe_type=%d)\n", spe_type);
    return spe_type;
}

void RTdef(struct Node *root) {
    int spe_type;
    if(controller) printf("def\n");
    spe_type = RTspecifier(root->child);
    RTdeclist(root->child->brother, spe_type);
}

void RTdeclist(struct Node *root, int s_type) {
    if(controller) printf("declist\n");
    if(root->child) {
        RTdec(root->child, s_type);
        if(root->child->brother) RTdeclist(root->child->brother, s_type);
    }
}
void RTvardec(struct Node *root, int s_type) {
    struct Node *node;
    struct Symbol *symbol;
    int old_addr;
    if(controller) printf("vardec\n");
    printf("fix : vardec(array)\n");
    switch(root->type) {
        case WORD:
            if(DeclaredLocally(root->word_name)) {
            printf("Error type ay line %d:%d: ID \"%s\" defined\n", root->lineno, root->listno, root->word_name);
            }
            else {
                symbol = EnterSymbol(root, s_type); // 加入符号表 
                symbol->address = address;
                old_addr = address;
                ChangeAddr(&address, symbol); // 为当前变量分配空间
                symbol->size = address - old_addr;
                root->v.value_type = s_type; 
                root->symbol = symbol; // 将符号记录挂载到语法树
            }
            break;
        case array:
            node = root;
            while(node->child) node = node->child;
            if(DeclaredLocally(node->word_name)) {
            printf("Error type ay line %d:%d: ID \"%s\" defined\n", node->lineno, node->listno, node->word_name);
            }
            else {
                symbol = EnterSymbol(node, array);
                symbol->address = address;
                symbol->elemtype = s_type;
                symbol->varlist = root;
                root->v.value_type = s_type;
                old_addr = address;
                ChangeAddr(&address, symbol);
                symbol->size = address - old_addr;
                root->symbol = symbol; // 将符号记录挂载到语法树
            }
            break;
    }
}
void RTdec(struct Node *root, int s_type) {
    switch(root->type) {
        case vardec:
            RTvardec(root->child, s_type);
            break;
        case ASSIGNOP:
            RTvardec(root->child, s_type);
            if(!CheckType(s_type, RTexp(root->child->brother, -1))) {
            printf("Error type at line %d:%d: Assign not matched\n", root->lineno, root->listno);
            }
            break;
    }
}
void RTextdeclist(struct Node *root, int s_type) {
    if(root->child) {
        RTvardec(root->child, s_type);
        if(root->child->brother) RTextdeclist(root->child->brother, s_type);
    }
}
void RTfundec(struct Node *root, int s_type) {
    struct Symbol *symbol;
    int old_addr;
    symbol = EnterSymbol(root, fundec);
    symbol->return_type = s_type;
    symbol->varlist = root->child; // 下挂参数列表
    OpenScope();
    if(root->child) {
        RTvarlist(root->child);
    }
    old_addr = address;
    symbol->size = address- old_addr;
}
void RTcompst(struct Node *root, int s_type) {
    // deflist may empty
    if(root->child) {
        RTdeflist(root->child);
        if(root->child->brother) RTstmtlist(root->child->brother, s_type);
    }
}
int RTstructspecifier(struct Node *root) {
    struct Symbol *symbol, *t_symbol;
    int spe_type;
    int old_addr;
    if(controller) printf("structspecifier [%d]\n", root->lineno);
    switch(root->type) {
        case opttag:
            if((spe_type = GetStructNum(root->child->word_name)) != -1) {
                printf("Error type at line %d:%d: Struct \"%s\" already defined\n", root->child->lineno, root->child->listno, root->child->word_name);
            }
            else {
                symbol = EnterSymbol(root->child, STRUCT);
                symbol->varlist = root->child->brother;
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
            RTdeflist(root->child->brother);
            CloseScope();
            break;
        case tag:
            if(!(symbol = ReturnSymbol(root->child->word_name))) {
                printf("Error type at line %d:%d: struct \"%s\" not defined\n", root->child->lineno, root->child->listno, root->child->word_name);
                spe_type = -1;
            }
            else {
                if(symbol->type != STRUCT) {
                    printf("Error type at line %d:%d: \"%s\" not struct\n", root->child->lineno, root->child->listno, root->child->word_name);
                    spe_type = -1;
                }
                else spe_type = symbol->structNum;
            }
            // printf("RTstructspecifier:(spe_type=%d)\n", spe_type);
            break;
    }
    return spe_type;
}
void RTdeflist(struct Node *root) {
    if(controller) printf("deflist [%d]\n", root->lineno);
    if(root->child) {
        RTdef(root->child);
        if(root->child->brother) RTdeflist(root->child->brother);
    }
}

/*
int RTtag(struct Node *root) {
    int spe_type;
    if(controller) printf("tag [%d]\n", root->lineno);
    if(!ReturnSymbol(root->word_name)) {
        printf("Error type at line %d:%d: Undifined struct \"%s\"\n", root->lineno, root->listno, root->word_name);
    }
    spe_type = GetStructNum(root->word_name);
    return spe_type;
}*/

void RTvarlist(struct Node *root) {
    if(controller) printf("varlist [%d]\n", root->lineno);
    if(root->child) {
        RTparamdec(root->child);
        if(root->child->brother) RTvarlist(root->child->brother);
    }
}
int RTparamdec(struct Node *root) {
    int spe_type;
    if(controller) printf("paramdec [%d]\n", root->lineno);
    spe_type = RTspecifier(root->child);
    RTvardec(root->child->brother, spe_type);
    return spe_type;
}
void RTstmtlist(struct Node *root, int s_type) {
    if(controller) printf("stmtlist [%d]\n", root->lineno);
    if(root->child) {
        RTstmt(root->child, s_type);
        if(root->child->brother) RTstmtlist(root->child->brother, s_type);
    }
}
void RTstmt(struct Node *root, int s_type) {
    if(controller) printf("stmt [%d]\n", root->lineno);
    switch(root->type) {
        case exp:
            RTexp(root->child, -1);
            break;
        case compst:
            OpenScope();
            RTcompst(root->child, s_type);
            CloseScope();
            break;
        case RETURN:
            if(root->child) {
                if(!CheckType(s_type, RTexp(root->child, -1))) {
                    printf("Error type at line %d:%d: Function return not matched\n", root->lineno, root->listno);
                }
            }
            else {
                if(!CheckType(s_type, VOID)) {
                    printf("Error type at line %d:%d: Function return not matched\n", root->lineno, root->listno);
                }
            }
            break;
        case IF:
            if(!CheckType(INT, RTexp(root->child, -1))) {
                printf("Error type at line %d:%d: IF need INT\n", root->lineno, root->listno);
            }
            if(root->child->brother) {
                RTstmt(root->child->brother, s_type);
                if(root->child->brother->brother) RTstmt(root->child->brother->brother, s_type);
            }
            break;
        case WHILE:
            if(!CheckType(INT, RTexp(root->child, -1))) {
                printf("Error type at line %d:%d: WHILE need INT\n", root->lineno, root->listno);
            }
            RTstmt(root->child->brother, -1);
            break;
    }
}
int RTexp(struct Node *root, int s_type) {
    struct Symbol *symbol;
    int spe_type, STID;
    if(controller) printf("exp [%d]\n", root->lineno);
    switch(root->type) {
        case ASSIGNOP:
            if(root->child->type == fundec) {
                printf("Error type at line %d:%d: \"%s\" is left operate\n", root->lineno, root->listno, root->child->word_name);
            } 
            else if(root->child->type == constant) {
                printf("Error type at line %d:%d: \"%d\" is left operate\n", root->lineno, root->listno, root->child->child->v.int_value);
            }
            if(!CheckType(spe_type = RTexp(root->child, -1), RTexp(root->child->brother, -1))) {
                printf("Error type at line %d:%d: ASSIGN not matched\n", root->lineno, root->listno);
            }
            break;
        case AND:
            if(!CheckType(RTexp(root->child, -1), RTexp(root->child->brother, -1))) {
                printf("Error type at line %d:%d: AND not matched\n", root->lineno, root->listno);
            }
            spe_type = INT;
            break;
        case OR:
            if(!CheckType(RTexp(root->child, -1), RTexp(root->child->brother, -1))) {
                printf("Error type at line %d:%d: OR not matched\n", root->lineno, root->listno);
            }
            spe_type = INT;
            break;
        case JUDGE_BIGGER:
            if(!CheckType(RTexp(root->child, -1), RTexp(root->child->brother, -1))) {
                printf("Error type at line %d:%d: JUDGE_BIGGER not matched\n", root->lineno, root->listno);
            }
            spe_type = INT;
            break;
        case JUDGE_SMALLER:
            if(!CheckType(RTexp(root->child, -1), RTexp(root->child->brother, -1))) {
                printf("Error type at line %d:%d: JUDGE_SMALLER not matched\n", root->lineno, root->listno);
            }
            spe_type = INT;
            break;
        case JUDGE_BIGGER_EQUAL:
            if(!CheckType(RTexp(root->child, -1), RTexp(root->child->brother, -1))) {
                printf("Error type at line %d:%d: JUDGE_BIGGER_EQUAL not matched\n", root->lineno, root->listno);
            }
            spe_type = INT;
            break;
        case JUDGE_SMALLER_EQUAL:
            if(!CheckType(RTexp(root->child, -1), RTexp(root->child->brother, -1))) {
                printf("Error type at line %d:%d: JUDGE_SMALLER_EQUAL not matched\n", root->lineno, root->listno);
            }
            spe_type = INT;
            break;
        case JUDGE_NOT_EQUAL:
            if(!CheckType(RTexp(root->child, -1), RTexp(root->child->brother, -1))) {
                printf("Error type at line %d:%d: '<=' not matched\n", root->lineno, root->listno);
            }
            spe_type = INT;
            break;
        case JUDGE_EQUAL:
            if(!CheckType(RTexp(root->child, -1), RTexp(root->child->brother, -1))) {
                //printf("Error type at line %d:%d: '==' not matched\n", root->lineno, root->listno);
            }
            spe_type = INT;
            break;
        case PLUS:
            if(!CheckType(spe_type = RTexp(root->child, -1), RTexp(root->child->brother, -1))) {
                printf("Error type at line %d:%d: '+' not matched\n", root->lineno, root->listno);
            }
            break;
        case SUB:
            if(!CheckType(spe_type = RTexp(root->child, -1), RTexp(root->child->brother, -1))) {
                printf("Error type at line %d:%d: '-' not matched\n", root->lineno, root->listno);
            }
            break;
        case MUL:
            // need to compelt star
            if(!CheckType(spe_type = RTexp(root->child, -1), RTexp(root->child->brother, -1))) {
                printf("Error type at line %d:%d: '*' not matched\n", root->lineno, root->listno);
            }
            break;
        case DIV:
            if(!CheckType(spe_type = RTexp(root->child, -1), RTexp(root->child->brother, -1))) {
                printf("Error type at line %d:%d: '/' not matched\n", root->lineno, root->listno);
            }
            break;
        case exp:
            spe_type = RTexp(root->child, -1);
            break;
        case NOT:
            if(!CheckType(INT, RTexp(root->child, -1))) {
                printf("Error type at line %d:%d: '!' not matched\n", root->lineno, root->listno);
            }
            spe_type = INT;
            break;
        case fundec:
            symbol = ReturnSymbol(root->word_name);
            if(symbol) {
                spe_type = symbol->return_type;
                if(symbol->type != fundec) {
                    printf("Error type at line %d:%d: \"%s\" not function\n", root->lineno, root->listno, root->word_name);
                }
                else if(root->child) {
                    if(RTargs(root->child, symbol->varlist)) {
                        printf("Error type at line %d:%d: \"%s\" parameter not matched\n", root->lineno, root->listno, root->word_name);
                    }
                }
                root->symbol = symbol;
            }
            else {
                printf("Error type at line %d:%d: Function \"%s\" not defined\n", root->lineno, root->listno, root->word_name);
                spe_type = -1;
            }
            break;
        case array:
            spe_type = RTexp(root->child, array);
            if(!CheckType(INT, RTexp(root->child->brother, -1))) {
                printf("Error type at line %d:%d: array need int\n", root->lineno, root->listno);
            }
            break;
        case POINT:
            if((STID = RTexp(root->child, STRUCT)) == -1) {
                printf("Error type at line %d:%d: Illegal use of \".\"\n", root->lineno, root->listno);
            }
            else {
                // 返回元素类型
                spe_type = FindSTID(STID, root->word_name); // 查找对应结构是否存在该元素
                if(spe_type == -1) {
                    printf("Error type at line %d:%d: \"%s\" not struct member\n", root->lineno, root->listno, root->word_name);
                }
            }
            break;
        case WORD:
            spe_type = -1;
                symbol = ReturnSymbol(root->word_name);
                if(symbol) {
                    spe_type = symbol->type;
                }
                else {
                    printf("Error type at line %d:%d: \"%s\" not defined\n", root->lineno, root->listno, root->word_name);
                    spe_type = -1;
                }
            root->symbol = symbol; // 绑定到符号表
            break;
        case constant:
            spe_type = root->child->type;
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

/* --FindSTID-- */
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

/* --ReturnSymbol-- */
struct Symbol* ReturnSymbol(char *name) {
    // 返回当前可见域的第一个可见符号
    struct Hash *sym;
    struct Symbol *tmp;
    if(controller) printf("returnsymbol\n");
    sym = GetHashTable(name);
    tmp = sym->symbol;
    while(tmp != NULL) {
        //printf("tmp name: %s name: %s\n", tmp->name, name);
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
    printf("name\t\ttype\t\tdepth\t\taction\t\telemtype\tsize\t\taddress\n");
    for(i = 0; i < 7; i++) {
        tmp = scopedisplay[i];
        while(tmp) {
            printf("%s\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", tmp->name, tmp->type, tmp->depth, tmp->action, tmp->elemtype, tmp->size, tmp->address);
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

int RTargs(struct Node *args, struct Node *var) {
    int type_1, type_2;
    struct Node *tmp;
    tmp = args;
    if(args) {
        if(args->child) {
            type_1 = RTexp(args->child, -1);
            type_2 = RTspecifier(var->child->child);
            if(type_1 != type_2) {
                printf("Error type at line %d:%d: \"%s\" not matched\n", args->lineno, args->listno, var->child->child->brother->word_name);
            }
            else {
                if(!(args->child->brother) && !(var->child->brother)) return 0;
                else if(args->child->brother && var->child->brother) RTargs(args->child->brother, var->child->brother);
                else return 1;
            }
        }
    }
}

int ChangeAddr(int *_address, struct Symbol *symbol) {
    int old_addr = *_address;
    int number = 1;
    struct Node *node;
    struct Symbol *t_symbol;
    switch(symbol->type) {
        case INT:
            *_address = *_address + 4; // int分配４个字节
            break;
        case FLOAT:
            *_address = *_address + 8; // float分配8个字节
            break;
        case CHAR:
            *_address = *_address + 1; // char分配1个字节
            break;
        case array:
            node = symbol->varlist;
            while(node && node->type == array) {
                number *= node->capacity;
                node = node->child;
            }
            switch(symbol->elemtype) {
                case INT:
                    *_address = *_address + number * 4;
                    break;
                case FLOAT:
                    *_address = *_address + number * 8;
                    break;
                case CHAR:
                    *_address = *_address + number * 1;
                    break;
                default:
                    printf("ChangeAddr: not found(symbol->elemtype)\n");
                    break;
            }
            break;
        // default : struct
        default:
         // 默认为结构体
            t_symbol = structlink;
            while(t_symbol) {
                // printf("ChangeAddr:(symbol->type=%d,t_symbol->structNum=%d,t_symbol->size=%d)\n", symbol->type, t_symbol->structNum, t_symbol->size);
                if(t_symbol->structNum == symbol->type) {
                    *_address = *_address + t_symbol->size;
                    break;
                }
                t_symbol = t_symbol->structnext;
            }
            break;
    }
    if(old_addr == *_address) {
    // 未分配空间
        printf("ChangeAddr: 未对(type=%d)分配空间(name:%s)\n", symbol->type, symbol->name);
    }
    return *_address;
}
