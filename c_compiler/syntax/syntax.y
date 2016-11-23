%{

#include"../token_scanner/lex.yy.c"
#include"../token_scanner/Node.h"
#include<string.h>
#include"Scope.h"
#define H_NUM 5
struct Node *p;
struct Hash h[H_NUM];  //Hash表
struct Symbol *scopeDisplay[5]; //符号表 
int depth = 0;  // 指示当前嵌套深度
void RecursionTypeAssign(struct Node *p);  // 语义分析
void CreateSymbolList(struct Node *p);  // 语义分析
char *TypeGet(struct Node *p);
void TypeAssign(struct Node *p, char *type);
void TypeInsert(struct Node* parent, struct Node* child);
void InsertSymbol(struct Node *p);
void StarToString(char **type, const char *s);
void RecursionTreePrint(struct Node* root, int spaceNum);
void TreePrint(struct Node* root);
int yyerror(const char *msg);
void RecursionInsertSymbol(struct Node *p);

%}

%error-verbose

%union {
    struct Node *token_p;
}

/* token */
%token<token_p> POUND INCLUDE VOID
%token<token_p> INT WORD INT_DIGIT
%token<token_p> FLOAT FLOAT_DIGIT
%token<token_p> DOUBLE OCTAL HEXADECIMAL
%token<token_p> SHORT
%token<token_p> UNSIGNED UNSIGNED_DIGIT
%token<token_p> CHAR CHAR_DIGIT
%token<token_p> PLUS SUB MUL DIV MOD 
%token<token_p> ASSIGNOP
%token<token_p> COMMA SEMICOLON POINT SINGLE_QUOTE DOUBLE_QUOTE
%token<token_p> JUDGE_BIGER JUDGE_SMALLER JUDGE_BIGER_EQUAL JUDGE_SMALLER_EQUAL JUDGE_EQUAL JUDGE_NOT_EQUAL
%token<token_p> NOT
%token<token_p> FOR WHILE IF ELSE RETURN BREAK STRUCT
%token<token_p> LP RP LC RC LB RB LEFT_ANGLE_BRA RIGHT_ANGLE_BRA
%token<token_p> OR AND
%token<token_p> ANNOTATION_LINE ANNOTATION_BLOCK_START ANNOTATION_BLOCK_STOP
%token<token_p> STRING

/* type */
%type<token_p> program extdeflist extdef specifier def declist vardec dec extdeclist fundec compst type structspecifier opttag deflist tag varlist paramdec stmtlist stmt exp args constant 

/* priority */
%right ASSIGNOP
%left OR
%left AND
%left JUDGE_SMALLER JUDGE_SMALLER_EQUAL JUDGE_BIGER JUDGE_BIGER_EQUAL JUDGE_EQUAL JUDGE_NOT_EQUAL 
%left PLUS SUB
%left MUL DIV
%right NOT
%left POINT
%left LB RB 
%left LP RP

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%start program

%%

/* --program-- */
program : extdeflist {
            p = NewNode("program", $1->No_Line, 0);
            insert(p, $1);
            $$ = p;
        }
        ;

/* --extdeflist-- */
extdeflist : extdef extdeflist {
                p = NewNode("extdeflist", $1->No_Line, 0);
                insert(p, $1);
                insert(p, $2);
                $$ = p;
           }
           | {
                p = NewNode("NULL", 0, 0);
                $$ = p;
           }
           ;

/* --extdef-- */
extdef : specifier extdeclist SEMICOLON {
            p = NewNode("extdef", $1->No_Line, 0);
            StarToString(&($2->type), $1->type);
            insert(p, $1);
            insert(p, $2);
            insert(p, $3);
            $$ = p;
       }
       | specifier extdeclist error SEMICOLON
       | specifier SEMICOLON {
            p = NewNode("extdef", $1->No_Line, 0);
            insert(p, $1);
            insert(p, $2);
            $$ = p;
       }
       | specifier fundec compst {
            p = NewNode("extdef", $1->No_Line, 0);
            StarToString(&($2->type), $1->type);
            insert(p, $1);
            insert(p, $2);
            insert(p, $3);
            $$ = p;
       }
       ;

/* --extdeclist-- */
extdeclist : vardec {
                p = NewNode("extdeclist", $1->No_Line, 0);
                insert(p, $1);
                $$ = p;
           }
           | vardec COMMA extdeclist {
                p = NewNode("extdeclist", $1->No_Line, 0);
                insert(p, $1);
                insert(p, $2);
                insert(p, $3);
                $$ = p;
           }
           ;

/* --specifier-- */
specifier : type {
                p = NewNode("specifier", $1->No_Line, 0);
                insert(p, $1);
                StarToString(&(p->type), $1->type);
                $$ = p;
          }
          | structspecifier {
                p = NewNode("specifier", $1->No_Line, 0);
                insert(p, $1);
                StarToString(&(p->type), $1->type);
                $$ = p;
          }
          ;

/* --structspecifier-- */
structspecifier : STRUCT opttag LC deflist RC {
                    p = NewNode("structspecifier", $1->No_Line, 0);
                    insert(p, $1);
                    insert(p, $2);
                    insert(p, $3);
                    insert(p, $4);
                    insert(p, $5);
                    StarToString(&(p->type), $2->type);
                    $$ = p;
                }
                | STRUCT opttag LC deflist error RC
                | STRUCT tag {
                    p = NewNode("structspecifier", $1->No_Line, 0);
                    insert(p, $1);
                    insert(p, $2);
                    StarToString(&(p->type), $2->type);
                    $$ = p;
                }
                ;

/* --opttag-- */
opttag : WORD {
            p = NewNode("opttag", $1->No_Line, 0);
            insert(p, $1);
            StarToString(&(p->type), $1->name);
            StarToString(&($1->type), "struct");
            $$ = p;
       }
       | {
            p = NewNode("NULL", 0, 0);
            StarToString(&(p->type), "NULL");
            $$ = p;
       }
       ;

/* --tag-- */
tag : WORD{
        p = NewNode("tag", $1->No_Line, 0);
        insert(p, $1);
        StarToString(&(p->type), $1->name);
        StarToString(&($1->type), "struct");
        $$ = p;
    }
    ;

/* --vardec-- */
vardec : WORD {
            p = NewNode("vardec", $1->No_Line, 0);
            insert(p, $1);
            $$ = p;
       }
       | vardec LB INT RB {
            p = NewNode("vardec", $1->No_Line, 0);
            insert(p, $1);
            insert(p, $2);
            insert(p, $3);
            insert(p, $4);
            $$ = p;
       }
       | vardec LB INT_DIGIT RB {
            p = NewNode("vardec", $1->No_Line, 0);
            insert(p, $1);
            insert(p, $2);
            insert(p, $3);
            insert(p, $4);
            $$ = p;
       }
       ;

/* --fundec-- */
fundec : WORD LP error RP 
       | WORD LP RP {
            p = NewNode("fundec", $1->No_Line, 0);
            insert(p, $1);
            insert(p, $2);
            insert(p, $3);
            $$ = p;
       }
       | WORD LP varlist RP
       ;

/* --varlist-- */
varlist : paramdec COMMA varlist {
            p = NewNode("varlist", $1->No_Line, 0);
            insert(p, $1);
            insert(p, $2);
            insert(p, $3);
            $$ = p;
        }
        | paramdec {
            p = NewNode("varlist", $1->No_Line, 0);
            insert(p, $1);
            $$ = p;
        }
        ;

/* --paramdec-- */
paramdec : specifier vardec {
            p = NewNode("paramdec", $1->No_Line, 0);
            insert(p, $1);
            insert(p, $2);
            $$ = p; 
         }
         ;

/* --compst-- */
compst : LC deflist stmtlist RC {
            p = NewNode("compst", $1->No_Line, 0);
            insert(p, $1);
            insert(p, $2);
            insert(p, $3);
            insert(p, $4);
            $$ = p; 
       }
       | LC deflist stmtlist error RC
       ;

/* --stmtlist-- */
stmtlist : stmt stmtlist {
            p = NewNode("stmtlist", $1->No_Line, 0);
            insert(p, $1);
            insert(p, $2);
            $$ = p; 
         }
         | {
            p = NewNode("NULL", 0, 0);
            $$ = p; 
         }
         ;

/* --stmt-- */
stmt : exp SEMICOLON {
            p = NewNode("stmt", $1->No_Line, 0);
            insert(p, $1);
            insert(p, $2);
            $$ = p;
     }
     | exp error SEMICOLON
     | compst {
            p = NewNode("stmt", $1->No_Line, 0);
            insert(p, $1);
            $$ = p;
     }
     | RETURN exp SEMICOLON {
            p = NewNode("stmt", $1->No_Line, 0);
            insert(p, $1);
            insert(p, $2);
            insert(p, $3);
            $$ = p;
     }
     | RETURN SEMICOLON {
            p = NewNode("stmt", $1->No_Line, 0);
            insert(p, $1);
            insert(p, $2);
            $$ = p;
     }
     | IF LP exp RP stmt %prec LOWER_THAN_ELSE {
            p = NewNode("stmt", $1->No_Line, 0);
            insert(p, $1);
            insert(p, $2);
            insert(p, $3);
            insert(p, $4);
            insert(p, $5);
            $$ = p;
     }
     | IF LP exp RP stmt ELSE stmt {
            p = NewNode("stmt", $1->No_Line, 0);
            insert(p, $1);
            insert(p, $2);
            insert(p, $3);
            insert(p, $4);
            insert(p, $5);
            insert(p, $6);
            insert(p, $7);
            $$ = p;
     }
     | WHILE LP exp RP stmt {
            p = NewNode("stmt", $1->No_Line, 0);
            insert(p, $1);
            insert(p, $2);
            insert(p, $3);
            insert(p, $4);
            insert(p, $5);
            $$ = p;
     }
     ;

/* --deflist-- */
deflist : def deflist {
            p = NewNode("deflist", $1->No_Line, 0);
            insert(p, $1);
            insert(p, $2);
            $$ = p;
        }
        | {
            p = NewNode("NULL", 0, 0);
            $$ = p;
        }

        ;

/* --def-- */
def : specifier declist SEMICOLON {
            p = NewNode("def", $1->No_Line, 0);
            insert(p, $1);
            insert(p, $2);
            insert(p, $3);
            $$ = p;
    }
    | specifier declist error SEMICOLON 
    ;

/* --declist-- */
declist : dec {
            p = NewNode("declist", $1->No_Line, 0);
            insert(p, $1);
            $$  = p;
        }
        | dec COMMA declist {
            p = NewNode("declist", $1->No_Line, 0);
            insert(p, $1);
            insert(p, $2);
            insert(p, $3);
            $$ = p;
        }
        ;

/* --dec-- */
dec : vardec {
            p = NewNode("dec", $1->No_Line, 0);
            insert(p, $1);
            $$ = p;
    }
    | vardec ASSIGNOP exp {
            p = NewNode("dec", $1->No_Line, 0);
            insert(p, $1);
            insert(p, $2);
            insert(p, $3);
            $$ = p;
    }
    ;

/* --exp-- */
exp : exp ASSIGNOP exp {
            p = NewNode("exp", $1->No_Line, 0);
            insert(p, $1);
            insert(p, $2);
            insert(p, $3);
            $$ = p;
    }
    | exp AND exp {
            p = NewNode("exp", $1->No_Line, 0);
            insert(p, $1);
            insert(p, $2);
            insert(p, $3);
            $$ = p;
    }
    | exp OR exp {
            p = NewNode("exp", $1->No_Line, 0);
            insert(p, $1);
            insert(p, $2);
            insert(p, $3);
            $$ = p;
    }
    | exp JUDGE_BIGER exp {
            p = NewNode("exp", $1->No_Line, 0);
            insert(p, $1);
            insert(p, $2);
            insert(p, $3);
            $$ = p;
    }
    | exp JUDGE_SMALLER exp {
            p = NewNode("exp", $1->No_Line, 0);
            insert(p, $1);
            insert(p, $2);
            insert(p, $3);
            $$ = p;
    }
    | exp JUDGE_BIGER_EQUAL exp {
            p = NewNode("exp", $1->No_Line, 0);
            insert(p, $1);
            insert(p, $2);
            insert(p, $3);
            $$ = p;
    }
    | exp JUDGE_SMALLER_EQUAL exp {
            p = NewNode("exp", $1->No_Line, 0);
            insert(p, $1);
            insert(p, $2);
            insert(p, $3);
            $$ = p;
    }
    | exp JUDGE_NOT_EQUAL exp {
            p = NewNode("exp", $1->No_Line, 0);
            insert(p, $1);
            insert(p, $2);
            insert(p, $3);
            $$ = p;
    }
    | exp JUDGE_EQUAL exp {
            p = NewNode("exp", $1->No_Line, 0);
            insert(p, $1);
            insert(p, $2);
            insert(p, $3);
            $$ = p;
    }
    | exp PLUS exp {
            p = NewNode("exp", $1->No_Line, 0);
            insert(p, $1);
            insert(p, $2);
            insert(p, $3);
            $$ = p;
    }
    | exp SUB exp {
            p = NewNode("exp", $1->No_Line, 0);
            insert(p, $1);
            insert(p, $2);
            insert(p, $3);
            $$ = p;
    }
    | exp MUL exp {
            p = NewNode("exp", $1->No_Line, 0);
            insert(p, $1);
            insert(p, $2);
            insert(p, $3);
            $$ = p;
    }
    | exp DIV exp {
            p = NewNode("exp", $1->No_Line, 0);
            insert(p, $1);
            insert(p, $2);
            insert(p, $3);
            $$ = p;
    }
    | LP exp RP {
            p = NewNode("exp", $1->No_Line, 0);
            insert(p, $1);
            insert(p, $2);
            insert(p, $3);
            $$ = p;
    }
    | MUL exp {
            p = NewNode("exp", $1->No_Line, 0);
            insert(p, $1);
            insert(p, $2);
            $$ = p;
    }
    | NOT exp {
            p = NewNode("exp", $1->No_Line, 0);
            insert(p, $1);
            insert(p, $2);
            $$ = p;
    }
    | WORD LP args RP {
            p = NewNode("exp", $1->No_Line, 0);
            insert(p, $1);
            insert(p, $2);
            insert(p, $3);
            insert(p, $4);
            $$ = p; 
    }
    | WORD LP RP {
            p = NewNode("exp", $1->No_Line, 0);
            insert(p, $1);
            insert(p, $2);
            insert(p, $3);
            $$ = p;
    }
    | exp LB exp RB {
            p = NewNode("exp", $1->No_Line, 0);
            insert(p, $1);
            insert(p, $2);
            insert(p, $3);
            insert(p, $4);
            $$ = p;
    }
    | exp POINT WORD {
            p = NewNode("exp", $1->No_Line, 0);
            insert(p, $1);
            insert(p, $2);
            insert(p, $3);
            $$ = p;
    }
    | WORD {
            p = NewNode("exp", $1->No_Line, 0);
            insert(p, $1);
            $$ =  p;
    }
    | constant {
            p = NewNode("exp", $1->No_Line, 0);
            insert(p, $1);
            $$ =  p;
    }
    ;

/* --constant-- */
constant : INT_DIGIT {
            p = NewNode("constant", $1->No_Line, 0);
            insert(p, $1);
            $$ =  p; 
         }
         | CHAR_DIGIT {
            p = NewNode("constant", $1->No_Line, 0);
            insert(p, $1);
            $$ =  p;
         }
         | FLOAT_DIGIT {
            p = NewNode("constant", $1->No_Line, 0);
            insert(p, $1);
            $$ =  p;
         }
         ;

/* --args-- */
args : exp COMMA args {
            p = NewNode("args", $1->No_Line, 0);
            insert(p, $1);
            insert(p, $2);
            insert(p, $3);
            $$ =  p;
     }
     | exp {
            p = NewNode("args", $1->No_Line, 0);
            insert(p, $1);
            $$ = p;
     }
     ;

/*
relop : JUDGE_BIGER {
            p = NewNode("relop", $1->No_Line, 0);
            insert(p, $1);
            $$ = p;
      }
      | JUDGE_SMALLER {
            p = NewNode("relop", $1->No_Line, 0);
            insert(p, $1);
            $$ = p;
      }
      | JUDGE_BIGER_EQUAL {
            p = NewNode("relop", $1->No_Line, 0);
            insert(p, $1);
            $$ = p;
      }
      | JUDGE_SMALLER_EQUAL {
            p = NewNode("relop", $1->No_Line, 0);
            insert(p, $1);
            $$ = p;
      }
      | JUDGE_EQUAL {
            p = NewNode("relop", $1->No_Line, 0);
            insert(p, $1);
            $$ = p;
      }
      | JUDGE_NOT_EQUAL {
            p = NewNode("relop", $1->No_Line, 0);
            insert(p, $1);
            $$ = p;
      }
      ;
*/

/* --type-- */
type : INT {
            p = NewNode("type", $1->No_Line, 0);
            insert(p, $1);
            StarToString(&(p->type), "int");
            $$ = p;
     }
     | FLOAT {
            p = NewNode("type", $1->No_Line, 0);
            insert(p, $1);
            StarToString(&(p->type), "int");
            $$ = p;
     }
     | SHORT {
            p = NewNode("type", $1->No_Line, 0);
            insert(p, $1);
            StarToString(&(p->type), "int");
            $$ = p;
     }
     | DOUBLE {
            p = NewNode("type", $1->No_Line, 0);
            insert(p, $1);
            StarToString(&(p->type), "int");
            $$ = p;
     }
     ;

%%

/* --main-- */
int main(int argc, char** argv) {
    if(argc <= 1) return 1;
    FILE* f = fopen(argv[1], "r");
    if(!f){
        perror(argv[1]);
        return 1;
    }
    yydebug = 1;
    yyrestart(f);
    yyparse();
    //h.hash = 0;
    //h.next = NULL;
    h[0].symbol = NULL;
    h[1].symbol = NULL;
    h[2].symbol = NULL;
    h[3].symbol = NULL;
    h[4].symbol = NULL;
    for(int i = 1; i < 5; i++) {
        scopeDisplay[i] = NULL;
    }
    CreateSymbolList(p);
    //PrintScopeDisplay(scopeDisplay);
    //PrintHash(h);
    //TreePrint(p);
    return 0;
}

/* --yyerror-- */
int yyerror(const char* msg) {
    fprintf(stderr, "Error type B in line %d:%d: \"%s\"\n",yylineno,yycolumn, msg);
    return 1;
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

/* --RecursionTreePrint-- */
void RecursionTreePrint(struct Node* root, int spaceNum) {
    int i;
    struct Node *tmp;
    struct Node *brother;
    tmp = root;
    if(tmp) {
        if(tmp->No_Line != 0) printf("%s\n", tmp->name);   
        if(tmp->No_Child != 0) {
            i = spaceNum;
            while(i > 0) {
                printf(" ");
                i--;
            }
            RecursionTreePrint(tmp->child, spaceNum);
        }
        if(tmp->brother != NULL){
            brother = tmp->brother; 
            RecursionTreePrint(brother, spaceNum);
        }
    }
}

/* --TreePrint-- */
void TreePrint(struct Node* root) {
    RecursionTreePrint(root, 0);
}

/* --CreateSymbolList-- */
void CreateSymbolList(struct Node *p) {
    RecursionTypeAssign(p);
    InsertSymbol(p);
}

/* --InsertSymbol-- */
void InsertSymbol(struct Node* root) {
    struct Node *tmp;
    struct Node *brother;
    tmp = root;
    // check the whole tree and insert specifier's brother node
    // fixed : structspecifier should be added
    if(tmp) {
        //if(tmp->child == NULL) printf("%s ", tmp->name);
        if(tmp->group == LC) {
            OpenScope();
        }
        if(tmp->group == RC) {
            CloseScope();
        }
        if(!strcmp(tmp->name, "specifier")) {
            RecursionInsertSymbol(tmp->brother->child);
        }
        if(!strcmp(tmp->name, "structspecifier")) {
            RecursionInsertSymbol(tmp->child->brother->child);
        }
        if(tmp->group == WORD) {
           if(!ReturnSymbol(tmp->name)) {
                fprintf(stderr, "Error type B in line %d:%d: \"%s\" is not declared\n", tmp->No_Line, 0, tmp->name);
            }
        }
        if(tmp->No_Child != 0) {
            InsertSymbol(tmp->child);
        }
        if(tmp->brother != NULL){
            brother = tmp->brother; 
            InsertSymbol(brother);
        }
    }
}

/* --RecursionInsertSymbol-- */
void RecursionInsertSymbol(struct Node *p) {
    struct Node *tmp;
    tmp = p; 
    if(tmp) {
        if(tmp->group == WORD) {
            EnterSymbol(tmp->name, tmp->type);
        }
        if(tmp->No_Child != 0) {
            RecursionInsertSymbol(tmp->child);
        }
        if(tmp->brother != NULL) {
            RecursionInsertSymbol(tmp->brother);
        }
    }
}

/* --CreateNewSymbol-- */
struct Symbol* CreateNewSymbol(char *name, char *type) {
    struct Symbol *s;
    s = (struct Symbol*)malloc(sizeof(struct Symbol));
    s->name = (char *)malloc(sizeof(char) * (strlen(name) + 1));
    strcpy(s->name, name);
    s->type= (char *)malloc(sizeof(char) * strlen(type));
    strcpy(s->type, type);
    s->action = 1;  // 符号作用于当前域
    return s; 
}

/* --ReturnSymbol-- */
struct Symbol* ReturnSymbol(char *name) {
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

/* --EnterSymbol-- */
void EnterSymbol(char *name, char *type) {
    struct Symbol *oldsym;
    struct Symbol *newsym;
    oldsym = ReturnSymbol(name);
    if(oldsym != NULL && oldsym->depth == depth) {
        printf("Duplicate definition of %s\n", name);
    }
    else {
        newsym = CreateNewSymbol(name, type);
        newsym->level = scopeDisplay[depth];
        newsym->depth = depth;
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
}

/* --RecursionTypeAssign-- */
void RecursionTypeAssign(struct Node *p) {
    struct Node *tmp;    
    //char *ex_type = NULL;  // 用于标识符的类型赋值
    tmp = p;
    if(tmp) {  
        if(!strcmp(tmp->name, "specifier"))  {
        // 检查到类型声明节点
            //ex_type = TypeGet(tmp->child);
            //printf("%s %s\n", ex_type, tmp->brother->name);
            TypeAssign(tmp->brother, tmp->type); // 进行类型赋值
        }
        if(tmp->child) {
            RecursionTypeAssign(tmp->child);
        }
        if(tmp->brother) {
            RecursionTypeAssign(p->brother);
        }
    }
}

/* --TypeAssign-- */
void TypeAssign(struct Node *p, char *type) {
    if(p->group == WORD) {
    // 当前为标识符
        p->type = (char *)malloc(sizeof(char) * (strlen(type) + 1));
        strcpy(p->type, type);
    }
    else if(!strcmp(p->name, "fundec")) {
    // 当前为函数标识符节点
        p->child->type = (char *)malloc(sizeof(char) * (strlen("function") + 1));
        strcpy(p->child->type, "function");
    }
    else if(!strcmp(p->name, "extdeclist")) {
    // 当前为全局标识符节点
        TypeAssign(p->child, type);
    }
    else if(!strcmp(p->name, "vardec")) {
    // 当前为单个全局标识符节点
        TypeAssign(p->child, type);
        if(p->brother) TypeAssign(p->brother, type);
    }
    else if(!strcmp(p->name, "declist")) {
    // 当前为局部标识符节点
        TypeAssign(p->child, type);
    }
    else if(!strcmp(p->name, "dec")) {
    // 当前为单个局部标识符节点
        TypeAssign(p->child, type);
        if(p->brother) TypeAssign(p->brother, type);
    }
    else if(!strcmp(p->name, ",")) {
    // 当前为分隔符逗号
        TypeAssign(p->brother, type);
    }
}

/* --TypeGet-- */
char* TypeGet(struct Node* p) {
//    struct Node *brother;
//    struct Node *child;
    if(!strcmp(p->name, "type")) {
    // 普通类型声明节点
        return p->child->name;
    }
    if(!strcmp(p->name, "structspecifier")) {
    // 结构类型声明节点
        p->child->brother->child->type = (char *)malloc(sizeof(char) * strlen(p->child->name));
        strcpy(p->child->brother->child->type, p->child->name);
        if(!strcmp(p->child->brother->name, "tag")) {
        // 不带结构体的结构类型声明
           return p->child->brother->child->name; 
        }
        if(!strcmp(p->child->brother->name, "opttag")) {
        // 带结构体的结构类型声明
            if(!strcmp(p->child->brother->child->name, "NULL")) {
            // 匿名的结构类型
                return p->child->brother->child->name;
            }
            else {
            // 带名字的结构类型声明
                return p->child->brother->child->name;
            }
        }
    }
    return NULL;
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
    int dep = 0;
    printf("scopeDisplay\t\tname\t\ttype\t\taction\t\t\n");
    while(scopedisplay[dep] != NULL) {
        tmp = scopedisplay[dep];
        while(tmp != NULL) {
            printf("scopeDisplay[%d]\t\t%s\t\t%s\t\t%d\t\t\n", dep, tmp->name, tmp->type, tmp->action);
            tmp = tmp->level; 
        }
        dep = dep + 1;
    }
}

/* --PrintHash-- */
void PrintHash(struct Hash *hash) {
    struct Symbol *current;
    int i = 0;
    printf("Hash\t\tname\t\ttype\t\t\n");
    while(i < H_NUM) {
        current = hash[i].symbol;
        while(current != NULL) {
            printf("%d\t\t%s\t\t%s\t\t\n", i, current->name, current->type);
            current = current->hash;
        }
        i = i + 1;
    }
}

/* --StarToString-- */
void StarToString(char **type, const char *s) {
    if(s == NULL) {
        printf("s is NULL !");
        return;
    }
    *type = (char *)malloc(sizeof(char) * (strlen(s) + 1));
    strcpy(*type, s);
}

