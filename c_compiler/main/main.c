/*************************************************************************
	> File Name: main.c
	> Author: 
	> Mail: 
	> Created Time: 2016年11月10日 星期四 06时01分57秒
 ************************************************************************/

#include"main.h"

#undef YYDEBUG
#define YYDEBUG 1
extern struct Symbol *structlink;
extern struct Hash h[5];  //Hash表
extern struct Symbol *scopeDisplay[7]; //符号表 
extern struct Taclist *taclist;

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
    // TreePrint(p, 4);
    RTprogram(p);
    tac_start(p);
    _print_taclist(taclist);
    target_start(argv[1], taclist);
    return 0;
}
