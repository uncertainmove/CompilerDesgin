%{
    #include<stdio.h>
%}
/* token */
%token INT FLOATE DOUBLE SHORT
%token PLUS SUB MUL DIV MOD 
%token ASSIGNOP
%token COMMA SEMICOLON POINT
%token JUDGE_BIGER JUDGE_SMALLER JUDGE_BIGER_EQUAL JUDGE_SMALLER_EQUAL JUDGE_EQUAL JUDGE_NOT_EQUAL
%token NOT
%token FOR WHILE IF ELSE RETURN BREAK STRUCT
%token LEFT_PAR RIGHT_PAR LEFT_BRACE RIGHT_BRACE LEFT_BRACKET RIGHT_BRACKET LEFT_ANGLE_BRA RIGHT_ANGLE_BRA
%token WORD
%token DIGIT
%token OR AND STAR
%token ANNOTATION_LINE ANNOTATION_BLOCK_START ANNOTATION_BLOCK_STOP
%token STRING

/* */
%left LEFT_PAR RIGHT_PAR COMMA
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
OptTag : STRING
       |
       ;
Tag : STRING
    ;
/* */
VarDec : STRING
       | VarDec LEFT_BRACKET INT RIGHT_BRACKET
       ;
FunDec : STRING LEFT_PAR VarList RIGHT_PAR
       | STRING LEFT_PAR RIGHT_PAR
       ;
VarList : ParamDec COMMA VarList
        |ParamDec
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
     | IF LEFT_PAR Exp RIGHT_PAR
     | IF LEFT_PAR Exp RIGHT_PAR ELSE Stmt
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
    | Exp STAR Exp
    | Exp DIV Exp
    | LEFT_PAR Exp RIGHT_PAR
    | SUB Exp
    | NOT Exp
    | STRING LEFT_PAR Args RIGHT_PAR
    | STRING LEFT_PAR RIGHT_PAR
    | Exp POINT STRING
    | STRING
    | INT
    | DOUBLE
    | FLOATE
    | SHORT
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
     | FLOATE
     | SHORT
     | DOUBLE
     ;
%%
#include"../token_scanner/lex.yy.c"
int main() {
    yyparse();
}

yyerror(char* msg) {
    fprintf(stderr, "error: %s\n", msg);
}
