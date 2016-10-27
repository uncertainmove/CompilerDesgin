%{
#define YYSTYPE int
%}
%union {
    int type_int;
    double type_double;
    float type_float;
    unsigned type_unsigned;
    char type_char;
}
/* token */
%token <type_int> INT WORD INT_DIGIT
%token <type_float> FLOAT FLOAT_DIGIT
%token <type_double> DOUBLE
%token <type_short> SHORT
%token <type_unsigned> UNSIGNED UNSIGNED_DIGIT
%token <type_char> CHAR CHAR_DIGIT
%token PLUS SUB MUL DIV MOD 
%token ASSIGNOP
%token COMMA SEMICOLON POINT
%token JUDGE_BIGER JUDGE_SMALLER JUDGE_BIGER_EQUAL JUDGE_SMALLER_EQUAL JUDGE_EQUAL JUDGE_NOT_EQUAL
%token NOT
%token FOR WHILE IF ELSE RETURN BREAK STRUCT
%token LEFT_PAR RIGHT_PAR LEFT_BRACE RIGHT_BRACE LEFT_BRACKET RIGHT_BRACKET LEFT_ANGLE_BRA RIGHT_ANGLE_BRA
%token OR AND
%token ANNOTATION_LINE ANNOTATION_BLOCK_START ANNOTATION_BLOCK_STOP
%token STRING

%type <type_int> Exp

/* */
%left LEFT_PAR COMMA RIGHT_PAR
%left LEFT_BRACKET RIGHT_BRACKET 
%left POINT
%right NOT
%left MUL DIV
%left PLUS SUB
%left JUDGE_SMALLER JUDGE_SMALLER_EQUAL JUDGE_BIGER JUDGE_BIGER_EQUAL JUDGE_EQUAL JUDGE_NOT_EQUAL 
%left AND
%left OR
%right ASSIGNOP
%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%start Program
%%
Program : ExtDefList
        ;
ExtDefList : ExtDef ExtDefList
           | 
           ;
ExtDef : Specifier ExtDecList SEMICOLON
       | Specifier SEMICOLON
       |Specifier FunDec CompSt
       ;
ExtDecList : VarDec
           | VarDec COMMA ExtDecList
           ;
Specifier : TYPE
          | StructSpecifier
          ;
StructSpecifier : STRUCT OptTag LEFT_BRACE DefList RIGHT_BRACE
                | STRUCT Tag
                ;
OptTag : WORD
       |
       ;
Tag : WORD
    ;
/* */
VarDec : WORD
       | VarDec LEFT_BRACKET INT RIGHT_BRACKET
       ;
FunDec : WORD LEFT_PAR VarList RIGHT_PAR
       | WORD LEFT_PAR RIGHT_PAR
       ;
VarList : ParamDec COMMA VarList
        | ParamDec
        ;
ParamDec : Specifier VarDec
         ;
CompSt : LEFT_BRACE DefList StmtList RIGHT_BRACE
       ;
StmtList : Stmt StmtList
         |
         ;
Stmt : Exp SEMICOLON
     | CompSt
     | RETURN Exp SEMICOLON
     | IF LEFT_PAR Exp RIGHT_PAR Stmt %prec LOWER_THAN_ELSE
     | IF LEFT_PAR Exp RIGHT_PAR Stmt ELSE Stmt
     | WHILE LEFT_PAR Exp RIGHT_PAR Stmt
     ;
DefList : Def DefList
        |
        ;
Def : Specifier DecList SEMICOLON
    ;
DecList : Dec
        | Dec COMMA DecList
        ;
Dec : VarDec
    | VarDec ASSIGNOP Exp
    ;
Exp : Exp ASSIGNOP Exp
    | Exp AND Exp
    | Exp OR Exp
    | Exp RELOP Exp
    | Exp PLUS Exp
    | Exp SUB Exp
    | Exp MUL Exp
    | Exp DIV Exp
    | LEFT_PAR Exp RIGHT_PAR
    | SUB Exp
    | NOT Exp
    | WORD LEFT_PAR Args RIGHT_PAR
    | WORD LEFT_PAR RIGHT_PAR
    | Exp LEFT_BRACKET Exp RIGHT_BRACKET
    | Exp POINT WORD
    | WORD
    | INT
    | DOUBLE
    | FLOAT
    | SHORT
    | CONSTANT
    ;
CONSTANT : INT_DIGIT
         | CHAR_DIGIT
         | FLOAT_DIGIT
         ;
Args : Exp COMMA Args
     | Exp
     ;
RELOP : JUDGE_BIGER
      | JUDGE_SMALLER
      | JUDGE_BIGER_EQUAL
      | JUDGE_SMALLER_EQUAL
      | JUDGE_EQUAL
      | JUDGE_NOT_EQUAL
      ;
TYPE : INT
     | FLOAT
     | SHORT
     | DOUBLE
     ;
%%
#include"../token_scanner/token.h"
#include"../token_scanner/lex.yy.c"
int main(int argc, char** argv) {
    if(argc <= 1) return 1;
    FILE* f = fopen(argv[1], "r");
    if(!f){
        perror(argv[1]);
        return 1;
    }
//    yydebug = 1;
    yyrestart(f);
    yyparse();
    return 0;
}

yyerror(char* msg) {
    fprintf(stderr, "error(in line %d : %d): %s\n\n\n",yylineno,yycolumn, msg);
}
