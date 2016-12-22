/*************************************************************************
	> File Name: frame.h
	> Author: 
	> Mail: 
	> Created Time: 2016年12月05日 星期一 22时43分17秒
 ************************************************************************/

#ifndef _FRAME_H
#define _FRAME_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"absyn.h"
#include "semant.h"
#include"syntax.tab.h"

// typedef enum {_function, _for, _while, _if, _globle } __lable_value;
typedef enum {__int = 1, __char, __float, __w, __t, __v} __temp_t;
typedef enum {_A_ADD, _JUDGE_E, _JUDGE_NE, _JUDGE_B, _JUDGE_BE, _JUDGE_S, _JUDGE_SE, _PLUS, _SUB, _MUL, _OR, _AND, _DIV, _ASSIGN, _RETURN, _NOT, _PARAMETER, _CALL, _FUNCTION, _LABLE, _GLOBLE, _GOTO, _IF, _ARG, _not_op = -1} __op;
typedef enum {_eax, _ebx, _ecx, _edx, _ebp, _esp, _esi, _edi, _ax, _bx, _cx, _dx, _ah, _bh, _ch, _dh, _al, _bl, _cl, _dl} _register;
typedef struct Temp* _Temp;
typedef struct Taclist* _Taclist;
typedef struct Lable* _Lable;
typedef struct Tac* _Tac;
typedef struct TempValue* _TempValue;

typedef struct Tac {
    __op op; // 操作符
    _Temp temp[3];
    _Lable lable; // function,for,while,if则生成lable
    // __lable_value type; // function:1, for:2, while:3, if:4
    struct Tac *next;
    
}Tac;

typedef struct Lable {
    union {
        int _l_num;
        char *name;
    };
    int _lable_tag; // 0 : 临时标号，1 : 函数标号
    struct Frame *frame; // 标号为函数时指向函数栈帧
}Lable;

typedef struct Taclist {
    struct Tac *front;
    struct Tac *current;
}Taclist;

typedef struct Temp {
    union {
        int _int;
        char _char;
        float _float;
        char *_w;
        int _t;
        int _v;
    }value;
    __temp_t sign; // 1,2,3,4,5,6
    int offset; // 相对ebp的偏移量
    struct Symbol* symbol;
}Temp;

// 栈帧
struct Frame {
    int f_size; // 栈帧大小
};

typedef union tempValue{
    int _int;
    char _char;
    float _float;
    char *_w;
    int _t;
}TempValue;

// contrl print
void _contrl_print(const char *);
void _check_point(struct Node *r, const char *);
void _op_print(__op op);
// 遍历语法树
void tac_start(struct Node *);
void tac_program(struct Node *);
void tac_fundec(struct Node *);
void tac_compst(struct Node *);
void tac_paramdec(struct Node *);
void tac_extdeflist(struct Node *);
void tac_extdef(struct Node *);
void tac_deflist(struct Node *);
void tac_extdeclist(struct Node *);
void tac_def(struct Node *);
void tac_stmtlist(struct Node *);
void tac_declist(struct Node *);
void tac_dec(struct Node *);
_Temp tac_vardec(struct Node *);
_Temp tac_exp(struct Node *);
void tac_globle_vardec(struct Node *);
void tac_varlist(struct Node *);
void tac_stmtlist(struct Node *);
void tac_stmt(struct Node *);
void tac_args(struct Node *);
// found tac
_Tac new_tac(int op, _Temp, _Temp, _Temp, _Lable);
_Temp new_temp(TempValue, __temp_t, int offset);
void insert_tac(_Tac);
_Lable new_lable(char *);
struct Frame *new_frame();
// print Taclist
void _print_taclist(_Taclist);
void temp_print(_Temp temp);
void lable_print(_Lable lable);
#endif
