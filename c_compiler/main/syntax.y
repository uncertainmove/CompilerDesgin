%{

#include"lex.yy.c"
#include"Node.h"
#include<string.h>
extern struct Node *p;
void StarToString(char **type, const char *s);
int yyerror(const char *msg);
//yydebug = 1;
enum { array, program, extdeflist, extdef, specifier, def, declist, vardec, dec, extdeclist, fundec, compst, type, structspecifier, opttag, deflist, tag, varlist, paramdec, stmtlist, stmt, exp, args, constant, };

%}

%error-verbose

%union {
    int type_int;
    char type_char;
    float type_float;
    char *type_string;
    struct Node *token_p;
}

/* token */
%token POUND INCLUDE VOID
%token INT FLOAT CHAR 
%token<type_int> INT_DIGIT
%token<type_char> CHAR_DIGIT
%token<type_float> FLOAT_DIGIT
%token<type_string> WORD
%token DOUBLE OCTAL HEXADECIMAL
%token SHORT
%token UNSIGNED UNSIGNED_DIGIT
%token PLUS SUB MUL DIV MOD 
%token ASSIGNOP
%token COMMA SEMICOLON POINT SINGLE_QUOTE DOUBLE_QUOTE
%token JUDGE_BiGGER JUDGE_SMALLER JUDGE_BIGGER_EQUAL JUDGE_SMALLER_EQUAL JUDGE_EQUAL JUDGE_NOT_EQUAL
%token NOT
%token FOR WHILE IF ELSE RETURN BREAK STRUCT
%token LP RP LC RC LB RB LEFT_ANGLE_BRA RIGHT_ANGLE_BRA
/* LC RC is {} - LP RP is () - LB RB is [] */
%token OR AND
%token ANNOTATION_LINE ANNOTATION_BLOCK_START ANNOTATION_BLOCK_STOP
%token STRING

/* type */
%type<token_p> program extdeflist extdef specifier def declist vardec dec extdeclist fundec compst type structspecifier opttag deflist tag varlist paramdec stmtlist stmt exp args constant

/* priority */
%right ASSIGNOP
%left OR
%left AND
%left JUDGE_SMALLER JUDGE_SMALLER_EQUAL JUDGE_BIGGER JUDGE_BIGGER_EQUAL JUDGE_EQUAL JUDGE_NOT_EQUAL 
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
            p = NewNode(program, yylineno, yylloc.first_column, 0);
            insert(p, $1);
            $$ = p;
        }
        ;

/* --extdeflist-- */
extdeflist : extdef extdeflist {
                p = NewNode(extdeflist, yylineno, yylloc.first_column, 0);
                insert(p, $1);
                insert(p, $2);
                $$ = p;
           }
           | {
                p = NULL;
                $$ = p;
           }
           ;

/* --extdef-- */
extdef : specifier extdeclist SEMICOLON {
            p = NewNode(extdef, yylineno, yylloc.first_column, 0);
            insert(p, $1);
            insert(p, $2);
            p->type = extdeclist;
            $$ = p;
       }
       | specifier extdeclist error SEMICOLON
       | specifier SEMICOLON {
            p = NewNode(extdef, yylineno, yylloc.first_column, 0);
            insert(p, $1);
            p->type = -1;
            $$ = p;
       }
       | specifier fundec compst {
            p = NewNode(extdef, yylineno, yylloc.first_column, 0);
            insert(p, $1);
            insert(p, $2);
            insert(p, $3);
            p->type = fundec;
            $$ = p;
       }
       ;

/* --extdeclist-- */
extdeclist : vardec {
                p = NewNode(extdeclist, yylineno, yylloc.first_column, 0);
                insert(p, $1);
                $$ = p;
           }
           | vardec COMMA extdeclist {
                p = NewNode(extdeclist, yylineno, yylloc.first_column, 0);
                insert(p, $1);
                insert(p, $3);
                $$ = p;
           }
           ;

/* --specifier-- */
specifier : type {
                p = NewNode(specifier, yylineno, yylloc.first_column, 0);
                insert(p, $1);
                p->type = type;
                $$ = p;
          }
          | structspecifier {
                p = NewNode(specifier, yylineno, yylloc.first_column, 0);
                insert(p, $1);
                p->type = structspecifier;
                $$ = p;
          }
          ;

/* --structspecifier-- */
structspecifier : STRUCT opttag LC deflist RC {
                    p = NewNode(structspecifier, yylineno, yylloc.first_column, 0);
                    insert(p, $2);
                    insert(p, $4);
                    p->type = opttag;
                    $$ = p;
                }
                | STRUCT opttag LC deflist error RC {
                    p = NewNode(structspecifier, yylineno, yylloc.first_column, 0);
                    p->type = opttag;
                    $$ = p;
                }
                | STRUCT tag {
                    p = NewNode(structspecifier, yylineno, yylloc.first_column, 0);
                    insert(p, $2);
                    p->type = tag;
                    $$ = p;
                }
                ;

/* --opttag-- */
opttag : WORD {
            p = NewNode(opttag, yylineno, yylloc.first_column, 0);
            p->word_name = (char *)malloc(sizeof(char) * strlen($1));
            strcpy(p->word_name, $1);
            p->type = STRUCT;
            $$ = p;
       }
       | {
            p = NewNode(opttag, yylineno, yylloc.first_column, 0);
            p->word_name = (char *)malloc(sizeof(char) * 5);
            strcpy(p->word_name, "NULL");
            p->type = STRUCT;
            $$ = p;
       }
       ;

/* --tag-- */
tag : WORD {
        p = NewNode(tag, yylineno, yylloc.first_column, 0);
        p->word_name = (char *)malloc(sizeof(char) * strlen($1));
        strcpy(p->word_name, $1);
        $$ = p;
    }
    ;

/* --vardec-- */
vardec : WORD {
            p = NewNode(vardec, yylineno, yylloc.first_column, 0);
            p->word_name = (char *)malloc(sizeof(char) * strlen($1));
            strcpy(p->word_name, $1);
            p->type = WORD;
            $$ = p;
       }
       | vardec LB INT_DIGIT RB {
            p = NewNode(vardec, yylineno, yylloc.first_column, 0);
            insert(p, $1);
            p->capacity = $3;
            p->type = array;
            $$ = p;
       }
       ;

/* --fundec-- */
fundec : WORD LP error RP {
            p = NewNode(fundec, yylineno, yylloc.first_column, 0);
            $$ = p;
       }
       | WORD LP RP {
            p = NewNode(fundec, yylineno, yylloc.first_column, 0);
            p->word_name = (char *)malloc(sizeof(char) * strlen($1));
            strcpy(p->word_name, $1);
            $$ = p;
       }
       | WORD LP varlist RP {
            p = NewNode(fundec, yylineno, yylloc.first_column, 0);
            p->word_name = (char *)malloc(sizeof(char) * strlen($1));
            strcpy(p->word_name, $1);
            insert(p, $3);
            $$ = p;
        }
       ;

/* --varlist-- */
varlist : paramdec COMMA varlist {
            p = NewNode(varlist, yylineno, yylloc.first_column, 0);
            insert(p, $1);
            insert(p, $3);
            $$ = p;
        }
        | paramdec {
            p = NewNode(varlist, yylineno, yylloc.first_column, 0);
            insert(p, $1);
            $$ = p;
        }
        ;

/* --paramdec-- */
paramdec : specifier vardec {
            p = NewNode(paramdec, yylineno, yylloc.first_column, 0);
            insert(p, $1);
            insert(p, $2);
            $$ = p; 
         }
         ;

/* --compst-- */
compst : LC deflist stmtlist RC {
            p = NewNode(compst, yylineno, yylloc.first_column, 0);
            insert(p, $2);
            insert(p, $3);
            $$ = p; 
       }
       | LC deflist stmtlist error RC {
            p = NewNode(compst, yylineno, yylloc.first_column, 0);
            $$ = p;
       }
       ;

/* --stmtlist-- */
stmtlist : stmt stmtlist {
            p = NewNode(stmtlist, yylineno, yylloc.first_column, 0);
            insert(p, $1);
            insert(p, $2);
            $$ = p; 
         }
         | {
            p = NULL; 
            $$ = p; 
         }
         ;

/* --stmt-- */
stmt : exp SEMICOLON {
            p = NewNode(stmt, yylineno, yylloc.first_column, 0);
            insert(p, $1);
            p->type = exp;
            $$ = p;
     }
     | exp error SEMICOLON
     | compst {
            p = NewNode(stmt, yylineno, yylloc.first_column, 0);
            insert(p, $1);
            p->type = compst;
            $$ = p;
     }
     | RETURN exp SEMICOLON {
            p = NewNode(stmt, yylineno, yylloc.first_column, 0);
            insert(p, $2);
            p->type = RETURN;
            $$ = p;
     }
     | RETURN SEMICOLON {
            p = NewNode(stmt, yylineno, yylloc.first_column, 0);
            p->type = RETURN;
            $$ = p;
     }
     | IF LP exp RP stmt %prec LOWER_THAN_ELSE {
            p = NewNode(stmt, yylineno, yylloc.first_column, 0);
            insert(p, $3);
            insert(p, $5);
            p->type = IF;
            $$ = p;
     }
     | IF LP exp RP stmt ELSE stmt {
            p = NewNode(stmt, yylineno, yylloc.first_column, 0);
            insert(p, $3);
            insert(p, $5);
            insert(p, $7);
            p->type = IF;
            $$ = p;
     }
     | WHILE LP exp RP stmt {
            p = NewNode(stmt, yylineno, yylloc.first_column, 0);
            insert(p, $3);
            insert(p, $5);
            p->type = WHILE;
            $$ = p;
     }
     ;

/* --deflist-- */
deflist : def deflist {
            p = NewNode(deflist, yylineno, yylloc.first_column, 0);
            insert(p, $1);
            insert(p, $2);
            $$ = p;
        }
        | {
            p = NULL; 
            $$ = p;
        }

        ;

/* --def-- */
def : specifier declist SEMICOLON {
            p = NewNode(def, yylineno, yylloc.first_column, 0);
            insert(p, $1);
            insert(p, $2);
            $$ = p;
    }
    | specifier declist error SEMICOLON 
    ;

/* --declist-- */
declist : dec {
            p = NewNode(declist, yylineno, yylloc.first_column, 0);
            insert(p, $1);
            $$  = p;
        }
        | dec COMMA declist {
            p = NewNode(declist, yylineno, yylloc.first_column, 0);
            insert(p, $1);
            insert(p, $3);
            $$ = p;
        }
        ;

/* --dec-- */
dec : vardec {
            p = NewNode(dec, yylineno, yylloc.first_column, 0);
            insert(p, $1);
            p->type = vardec;
            $$ = p;
    }
    | vardec ASSIGNOP exp {
            p = NewNode(dec, yylineno, yylloc.first_column, 0);
            insert(p, $1);
            insert(p, $3);
            p->type = ASSIGNOP;
            $$ = p;
    }
    ;

/* --exp-- */
exp : exp ASSIGNOP exp {
            p = NewNode(exp, yylineno, yylloc.first_column, 0);
            insert(p, $1);
            insert(p, $3);
            p->type = ASSIGNOP;
            $$ = p;
    }
    | exp AND exp {
            p = NewNode(exp, yylineno, yylloc.first_column, 0);
            insert(p, $1);
            insert(p, $3);
            p->type = AND;
            $$ = p;
    }
    | exp OR exp {
            p = NewNode(exp, yylineno, yylloc.first_column, 0);
            insert(p, $1);
            insert(p, $3);
            p->type = OR;
            $$ = p;
    }
    | exp JUDGE_BIGGER exp {
            p = NewNode(exp, yylineno, yylloc.first_column, 0);
            insert(p, $1);
            insert(p, $3);
            p->type = JUDGE_BIGGER;
            $$ = p;
    }
    | exp JUDGE_SMALLER exp {
            p = NewNode(exp, yylineno, yylloc.first_column, 0);
            insert(p, $1);
            insert(p, $3);
            p->type = JUDGE_SMALLER;
            $$ = p;
    }
    | exp JUDGE_BIGGER_EQUAL exp {
            p = NewNode(exp, yylineno, yylloc.first_column, 0);
            insert(p, $1);
            insert(p, $3);
            p->type = JUDGE_BIGGER_EQUAL;
            $$ = p;
    }
    | exp JUDGE_SMALLER_EQUAL exp {
            p = NewNode(exp, yylineno, yylloc.first_column, 0);
            insert(p, $1);
            insert(p, $3);
            p->type = JUDGE_SMALLER_EQUAL;
            $$ = p;
    }
    | exp JUDGE_NOT_EQUAL exp {
            p = NewNode(exp, yylineno, yylloc.first_column, 0);
            insert(p, $1);
            insert(p, $3);
            p->type = JUDGE_NOT_EQUAL;
            $$ = p;
    }
    | exp JUDGE_EQUAL exp {
            p = NewNode(exp, yylineno, yylloc.first_column, 0);
            insert(p, $1);
            insert(p, $3);
            p->type = JUDGE_EQUAL;
            $$ = p;
    }
    | exp PLUS exp {
            p = NewNode(exp, yylineno, yylloc.first_column, 0);
            insert(p, $1);
            insert(p, $3);
            p->type = PLUS;
            $$ = p;
    }
    | exp SUB exp {
            p = NewNode(exp, yylineno, yylloc.first_column, 0);
            insert(p, $1);
            insert(p, $3);
            p->type = SUB;
            $$ = p;
    }
    | exp MUL exp {
            p = NewNode(exp, yylineno, yylloc.first_column, 0);
            insert(p, $1);
            insert(p, $3);
            p->type = MUL;
            $$ = p;
    }
    | exp DIV exp {
            p = NewNode(exp, yylineno, yylloc.first_column, 0);
            insert(p, $1);
            insert(p, $3);
            p->type = DIV;
            $$ = p;
    }
    | LP exp RP {
            p = NewNode(exp, yylineno, yylloc.first_column, 0);
            insert(p, $2);
            p->type = exp;
            $$ = p;
    }
    | MUL exp {
            p = NewNode(exp, yylineno, yylloc.first_column, 0);
            insert(p, $2);
            p->type = MUL;
            $$ = p;
    }
    | NOT exp {
            p = NewNode(exp, yylineno, yylloc.first_column, 0);
            insert(p, $2);
            p->type = NOT;
            $$ = p;
    }
    | WORD LP args RP {
            p = NewNode(exp, yylineno, yylloc.first_column, 0);
            insert(p, $3);
            p->word_name = (char *)malloc(sizeof(char) * strlen($1));
            strcpy(p->word_name, $1);
            p->type = fundec;
            $$ = p; 
    }
    | WORD LP RP {
            p = NewNode(exp, yylineno, yylloc.first_column, 0);
            p->word_name = (char *)malloc(sizeof(char) * strlen($1));
            strcpy(p->word_name, $1);
            p->type = fundec;
            $$ = p;
    }
    | exp LB exp RB {
            p = NewNode(exp, yylineno, yylloc.first_column, 0);
            insert(p, $1);
            insert(p, $3);
            p->type = array;  // 代表节点下为数组
            $$ = p;
    }
    | exp POINT WORD {
            p = NewNode(exp, yylineno, yylloc.first_column, 0);
            insert(p, $1);
            p->word_name = (char *)malloc(sizeof(char) * strlen($3));
            strcpy(p->word_name, $3);
            p->type = POINT;
            $$ = p;
    }
    | WORD {
            p = NewNode(exp, yylineno, yylloc.first_column, 0);
            p->type = WORD;
            p->word_name = (char *)malloc(sizeof(char) * strlen($1));
            strcpy(p->word_name, $1);
            $$ =  p;
    }
    | constant {
            p = NewNode(exp, yylineno, yylloc.first_column, 0);
            insert(p, $1);
            p->type = constant;
            $$ =  p;
    }
    ;

/* --constant-- */
constant : INT_DIGIT {
            p = NewNode(constant, yylineno, yylloc.first_column, 0);
            p->type = INT;
            p->v.int_value = $1;
            $$ = p; 
         }
         | CHAR_DIGIT {
            p = NewNode(constant, yylineno, yylloc.first_column, 0);
            p->type = CHAR;
            p->v.char_value = $1;
            $$ = p;
         }
         | FLOAT_DIGIT {
            p = NewNode(constant, yylineno, yylloc.first_column, 0);
            p->type = FLOAT;
            p->v.float_value = $1;
            $$ = p;
         }
         ;

/* --args-- */
args : exp COMMA args {
            p = NewNode(args, yylineno, yylloc.first_column, 0);
            insert(p, $1);
            insert(p, $3);
            $$ = p;
     }
     | exp {
            p = NewNode(args, yylineno, yylloc.first_column, 0);
            insert(p, $1);
            $$ = p;
     }
     ;

/*
relop : JUDGE_BIGGER {
            p = NewNode("relop", yylineno, yylloc.first_column, 0);
            insert(p, $1);
            $$ = p;
      }
      | JUDGE_SMALLER {
            p = NewNode("relop", yylineno, yylloc.first_column, 0);
            insert(p, $1);
            $$ = p;
      }
      | JUDGE_BIGGER_EQUAL {
            p = NewNode("relop", yylineno, yylloc.first_column, 0);
            insert(p, $1);
            $$ = p;
      }
      | JUDGE_SMALLER_EQUAL {
            p = NewNode("relop", yylineno, yylloc.first_column, 0);
            insert(p, $1);
            $$ = p;
      }
      | JUDGE_EQUAL {
            p = NewNode("relop", yylineno, yylloc.first_column, 0);
            insert(p, $1);
            $$ = p;
      }
      | JUDGE_NOT_EQUAL {
            p = NewNode("relop", yylineno, yylloc.first_column, 0);
            insert(p, $1);
            $$ = p;
      }
      ;
*/

/* --type-- */
type : INT {
            p = NewNode(type, yylineno, yylloc.first_column, 0);
            p->type = INT;
            $$ = p;
     }
     | FLOAT {
            p = NewNode(type, yylineno, yylloc.first_column, 0);
            p->type = FLOAT;
            $$ = p;
     }
     | SHORT {
            p = NewNode(type, yylineno, yylloc.first_column, 0);
            p->type = SHORT;
            $$ = p;
     }
     | DOUBLE {
            p = NewNode(type, yylineno, yylloc.first_column, 0);
            p->type = DOUBLE;
            $$ = p;
     }
     ;

%%

/* --yyerror-- */
int yyerror(const char* msg) {
    fprintf(stderr, "Error type B in line %d:%d: \"%s\"\n",yylineno,yylloc.first_column, msg);
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


