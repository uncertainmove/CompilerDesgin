%{
    #include<stdio.h>
    #include<stdlib.h>
    #include"token.h"
    #include"../syntax/syntax.tab.h"
    int lineno = 1;
/*    int wordCount = 0; */
%}
word [A-Za-z_][A-Za-z0-9_]*
string ["][%A-Za-z0-9_' ]*["]
digit ([0-9])+
delim [ \t]
whitespace {delim}+
enter [\n]+
%%
"int"|"char"|"double"|"floate"|"short"|"unsigned" {/* Upper(yytext, yyleng); */print("Indentifier");}
"+" {return PLUS;}
"-" {return SUB;}
"*" {return MUL;}
"/" {return DIV;}
"%" {return MOD;}
"=" {return ASSIGNOP;}
">" {return JUDGE_BIGER;}
"<" {return JUDGE_SMALLER;}
">=" {return JUDGE_BIGER_EQUAL;}
"<=" {return JUDGE_SMALLER_EQUAL;}
"==" {return JUDGE_EQUAL;}
"!=" {return JUDGE_NOT_EQUAL;}
"for" {return FOR;}
"while" {return WHILE;}
"if" {return IF;}
"else" {return ELSE;}
"return" {return RETURN;}
"break" {return BREAK;}
"(" {return LEFT_PAR;}
")" {return RIGHT_PAR;}
"," {return COMMA;}
"." {return POINT;}
";" {return SEMICOLON;}
"{" {return LEFT_BRACE;}
"}" {return RIGHT_BRACE;}
"[" {return LEFT_BRACKET;}
"]" {return RIGHT_BRACKET;}
"<" {return LEFT_ANGLE_BRA;}
">" {return RIGHT_ANGLE_BRA;}
"*" {return STAR;}
"&&" {return AND;}
"||" {return OR;}
"//" {return ANNOTATION_LINE;}
"/*" {return ANNOTATION_BLOCK_START;}
"*/" {return ANNOTATION_BLOCK_STOP;}
{word} {return WORD;}
{whitespace} {}
{digit} {return DIGIT;}
{enter} {lineno++;} /* 行号加1 */
{string} {return STRING;}
. {printf("error(in line %d): %s\n", lineno, yytext);}
%%
/*
int main(int argc, char** argv)
{
    if(argc <= 1) return 1;
    FILE* f = fopen(argv[1], "r");
    if(!f) {
        perror(argv[1]);
        return 1;
    }
    yyrestart(f);
    yyparse();
    fclose(yyin);
   system("PAUSE");
    return 0;
}
*/
int yywrap()
{
    return 1;
}

/*
函数功能：打印关键字信息
*/
void print(char *s) {
    printf("\t%d\t\t\t%s\t\t\t%s\n", lineno, yytext, s);
}

/*
函数功能：转换大小写
*/
/* void Upper(char *s, int l) {
    int i;
    for(i = 0; i < l; i++) {
        s[i] = toupper(s[i]);
    }
}
*/
