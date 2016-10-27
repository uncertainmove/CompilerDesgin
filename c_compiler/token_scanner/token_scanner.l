%{
    #include "token.h"
    struct YYLTYPE yylloc;
    int errorCount = 0;
    int yycolumn = 1;
    #define YY_USER_ACTION yylloc.first_line = yylloc.last_line = yylineno; yylloc.first_column = yycolumn; yylloc.last_column = yycolumn + yyleng - 1; yycolumn += yyleng;
%}
%option yylineno

word [A-Za-z_][A-Za-z0-9_]*
string ["][%A-Za-z0-9_' ]*["]
int_digit ([0-9])+
char_digit ['][A-Za-z][']
float_digit [0-9]+[\.][0-9]*
delim [" "\t]
whitespace {delim}+
enter [\n]+
%%
"int" {return INT;}
"char" {return CHAR;}
"double" {return DOUBLE;}
"float" {return FLOAT;}
"short" {return SHORT;}
"unsigned" {return UNSIGNED;}
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
"struct" {return STRUCT;}
"(" {return LEFT_PAR;}
")" {return RIGHT_PAR;}
"," {return COMMA;}
"." {return POINT;}
";" {return SEMICOLON;}
"{" {return LEFT_BRACE;}
"}" {return RIGHT_BRACE;}
"[" {return LEFT_BRACKET;}
"]" {return RIGHT_BRACKET;}
"&&" {return AND;}
"||" {return OR;}
"//" {char c = input(); while(c != '\n') c = input();}
"/*" {return ANNOTATION_BLOCK_START;}
"*/" {return ANNOTATION_BLOCK_STOP;}
{word} {return WORD;}
{whitespace} {}
{int_digit} {yylval = atoi(yytext); return INT_DIGIT;}
{float_digit} {yylval = atof(yytext); return FLOAT_DIGIT;}
{char_digit} {yylval = yytext[1]; return CHAR_DIGIT;}
{enter} {yycolumn = 1;} /* 行号加1 */
{string} {return STRING;}
. {errorCount++; printf("error(in line %d): %s\n", yylineno, yytext);}
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
    printf("\t%d\t\t\t%s\t\t\t%s\n", yylineno, yytext, s);
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
