%{

    #include "../syntax/syntax.tab.h"
    #include"token.h"
    #include"Node.h"
    #include<string.h>
    #include<stdlib.h>
    #include<stdio.h>
    struct YYLTYPE yylloc;
    int yycolumn = 1;
    int errorCount = 0;
    #define YY_USER_ACTION yylloc.first_line = yylloc.last_line = yylineno; yylloc.first_column = yycolumn; yylloc.last_column = yycolumn + yyleng - 1; yycolumn += yyleng;
    struct Node* NewNode(char *node_name, int lineno, int group);

%}

%option yylineno
%option nounput

word [A-Za-z_][A-Za-z0-9_]*

octal [0][0-7]+

err_octal [0][0-7]*[89][0-9]*

hexadecimal [0][xX][0-9A-Fa-f]+

err_hexadecimal [0][xX][0-9A-Fa-f]*[G-Zg-z][0-9A-Za-z]*

int_digit ([0]|([1-9][0-9]*))

char_digit ['][0-9A-Za-z][']

float_digit (([0-9]+[\.][0-9]+)|([0-9]*[.][0-9]+[Ee][+-]?[0-9]+))

delim [" "\t]

whitespace {delim}+

enter [\n]+

%%

"#" {
    print("#"); 
    yylval.token_p = NewNode(yytext, yylineno, POUND); 
    return POUND;
}

"include" {
    print("include"); 
    yylval.token_p = NewNode(yytext, yylineno, INCLUDE); 
    return INCLUDE;
}

"void" {
    print("void"); 
    yylval.token_p = NewNode(yytext, yylineno, VOID); 
    return VOID;
}

"int" {
    print("int"); 
    yylval.token_p = NewNode(yytext, yylineno, INT); 
    return INT;
}

"char" {
    print("char"); 
    yylval.token_p = NewNode(yytext, yylineno, CHAR);  
    return CHAR;
}

"double" {
    print("double"); 
    yylval.token_p = NewNode(yytext, yylineno, DOUBLE); 
    return DOUBLE;
}

"float" {
    print("float"); 
    yylval.token_p = NewNode(yytext, yylineno, FLOAT); 
    return FLOAT;
}

"short" {
    print("short"); 
    yylval.token_p = NewNode(yytext, yylineno, SHORT); 
    return SHORT;
}

"unsigned" {
    print("unsigned"); 
    yylval.token_p = NewNode(yytext, yylineno, UNSIGNED); 
    return UNSIGNED;
}

"+" {
    print("+"); 
    yylval.token_p = NewNode(yytext, yylineno, PLUS); 
    return PLUS;
}

"-" {
    print("-"); 
    yylval.token_p = NewNode(yytext, yylineno, SUB); 
    return SUB;
}

"*" {
    print("*"); 
    yylval.token_p = NewNode(yytext, yylineno, MUL); 
    return MUL;
}

"/" {
    print("/"); 
    yylval.token_p = NewNode(yytext, yylineno, DIV); 
    return DIV;
}

"%" {
    print("%"); 
    yylval.token_p = NewNode(yytext, yylineno, MOD); 
    return MOD;
}

"=" {
    print("="); 
    yylval.token_p = NewNode(yytext, yylineno, ASSIGNOP); 
    return ASSIGNOP;
}

">" {
    print(">"); 
    yylval.token_p = NewNode(yytext, yylineno, JUDGE_BIGER); 
    return JUDGE_BIGER;
}

"<" {
    print("<"); 
    yylval.token_p = NewNode(yytext, yylineno, JUDGE_SMALLER); 
    return JUDGE_SMALLER;
}

">=" {
    print(">="); 
    yylval.token_p = NewNode(yytext, yylineno, JUDGE_BIGER_EQUAL); 
    return JUDGE_BIGER_EQUAL;
}

"<=" {
    print("<="); 
    yylval.token_p = NewNode(yytext, yylineno, JUDGE_SMALLER_EQUAL); 
    return JUDGE_SMALLER_EQUAL;
}

"==" {
    print("=="); 
    yylval.token_p = NewNode(yytext, yylineno,  JUDGE_EQUAL); 
    return JUDGE_EQUAL;
}

"!=" {
    print("!="); 
    yylval.token_p = NewNode(yytext, yylineno, JUDGE_NOT_EQUAL); 
    return JUDGE_NOT_EQUAL;
}

"\"" {
    print("\""); 
    yylval.token_p = NewNode(yytext, yylineno, DOUBLE_QUOTE); 
    return DOUBLE_QUOTE;
}

"\'" {
    print("\'"); 
    yylval.token_p = NewNode(yytext, yylineno, SINGLE_QUOTE); 
    return SINGLE_QUOTE;
}

"for" {
    print("for"); 
    yylval.token_p = NewNode(yytext, yylineno, FOR); 
    return FOR;
}

"while" {
    print("while"); 
    yylval.token_p = NewNode(yytext, yylineno, WHILE); 
    return WHILE;
}

"if" {
    print("if"); 
    yylval.token_p = NewNode(yytext, yylineno, IF); 
    return IF;
}

"else" {
    print("else"); 
    yylval.token_p = NewNode(yytext, yylineno, ELSE); 
    return ELSE;
}

"return" {
    print("return"); 
    yylval.token_p = NewNode(yytext, yylineno, RETURN); 
    return RETURN;
}

"break" {
    print("break"); 
    yylval.token_p = NewNode(yytext, yylineno, BREAK); 
    return BREAK;
}

"struct" {
    print("struct"); 
    yylval.token_p = NewNode(yytext, yylineno, STRUCT); 
    return STRUCT;
}

"(" {
    print("("); 
    yylval.token_p = NewNode(yytext, yylineno, LP); 
    return LP;
}

")" {
    print(")"); 
    yylval.token_p = NewNode(yytext, yylineno, RP); 
    return RP;
}

"," {
    print(","); 
    yylval.token_p = NewNode(yytext, yylineno, COMMA); 
    return COMMA;
}

"." {
    print("."); 
    yylval.token_p = NewNode(yytext, yylineno, POINT); 
    return POINT;
}

";" {
    print(";"); 
    yylval.token_p = NewNode(yytext, yylineno, SEMICOLON); 
    return SEMICOLON;
}

"{" {
    print("{"); 
    yylval.token_p = NewNode(yytext, yylineno, LC); 
    return LC;
}

"}" {
    print("}"); 
    yylval.token_p = NewNode(yytext, yylineno, RC); 
    return RC;
}

"[" {
    print("["); 
    yylval.token_p = NewNode(yytext, yylineno, LB); 
    return LB;
}

"]" {
    print("]"); 
    yylval.token_p = NewNode(yytext, yylineno, RB); 
    return RB;
}

"&&" {
    print("AND"); 
    yylval.token_p = NewNode(yytext, yylineno, AND); 
    return AND;
}

"||" {
    print("OR"); 
    yylval.token_p = NewNode(yytext, yylineno, OR); 
    return OR;
}

"//" {
    print("\n"); 
    char c = input(); 
    while(c != '\n') c = input(); 
    yycolumn = 1;
}

"/*" {
    CommentMatch();
}

"*/" {
    print("*/"); 
    printf("Error type A at line %d:%d: Miss match \"%s\"\n", yylineno, yylloc.first_column, yytext);
}

{word} {
    print("word"); 
    yylval.token_p = NewNode(yytext, yylineno, WORD); 
    return WORD;
}

{whitespace} {
    print(" ");
}

{octal} {
    print("octal"); 
    yylval.token_p = NewNode(yytext, yylineno, OCTAL); 
    return OCTAL;
}

{err_octal} {
    errorCount++; 
    print("err_octal"); 
    printf("Error type A at line %d:%d: Mysterious charactor \"%s\"\n", yylineno, yylloc.first_column, yytext);
}

{err_hexadecimal} {
    errorCount++; 
    print("err_hexadecimal"); 
    printf("Error type A at line %d:%d: Mysterious charactor \"%s\"\n", yylineno, yylloc.first_column, yytext);
}

{hexadecimal} {
    print("hexadecimal"); 
    yylval.token_p = NewNode(yytext, yylineno, HEXADECIMAL); 
    return HEXADECIMAL;
}

{int_digit} {
    print("int_digit"); 
    yylval.token_p = NewNode(yytext, yylineno, INT_DIGIT); 
    return INT_DIGIT;
}

{float_digit} {
    print("float_digit"); 
    yylval.token_p = NewNode(yytext, yylineno, FLOAT_DIGIT); 
    return FLOAT_DIGIT;
}

{char_digit} {
    print("char_digit"); 
    yylval.token_p = NewNode(yytext, yylineno, CHAR_DIGIT);  
    return CHAR_DIGIT;
}

{enter} {
    print("\n"); 
    yycolumn = 1;
} /* 行号加1 */

. {
    errorCount++; 
    printf("Error type A at line %d:%d: Mysterious charactor \"%s\"\n", yylineno, yylloc.first_column, yytext);
}

%%
#if 0
int main(int argc, char** argv)
{
    if(argc <= 1) return 1;
    if(!(yyin = fopen(argv[1], "r"))) {
        perror(argv[1]);
        return 1;
    }
    while (yylex() != 0);
    fclose(yyin);
    fclose(g);
    return 0;
}
#endif
int yywrap()
{
    return 1;
}

/*
函数功能：打印关键字信息
*/
void print(const char* s) {
    FILE *g = fopen("result.txt", "w+");
    fputs(s, g);
}

void CommentMatch() {
    char c;
    int sign = 0;
    while((c = input()) != EOF) {
        if(c == '*') {
            sign = 1;
        }
        else if(c == '/' && sign == 1) {
            break;
        }
        else {
            sign = 0;
        }
    }
}

struct Node* NewNode(char *node_name, int lineno, int group) {
    struct Node *p = (struct Node*)malloc(sizeof(struct Node));
    if(p == NULL) {
        printf("Error: out of memory.\n");
        exit(1);
    }
    p->name = (char *)malloc(sizeof(char) * (strlen(node_name) + 1));
    strcpy(p->name, node_name);
    p->group = group;
    p->type = NULL;    //语义分析时赋值
    p->brother = NULL;
    p->child = NULL;
    p->No_Line = lineno;
    p->No_Child = 0;
    p->IsBegin = 0;
    return p;
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
