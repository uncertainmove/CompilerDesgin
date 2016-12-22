/*************************************************************************
	> File Name: frame.c
	> Author: 
	> Mail: 
	> Created Time: 2016年12月05日 星期一 22时43分10秒
 ************************************************************************/

#include"frame.h"

#define controller 0

_Taclist taclist = NULL;
struct Frame *frame; // 指向当前正在分析的函数栈帧，分析结束手动跳转
int _t_buffer = 0;
int _l_buffer = 0;
int _v_buffer = 0;
int _reg_sign[4];

void tac_start(struct Node *r) {
    int i;
    _contrl_print("tac_start\n");
    // 寄存器使用初始化
    for(i = 0; i < 4; i++) {
        _reg_sign[i] = 0;
    }
    tac_program(r);
}

void tac_program(struct Node *r) {
    _contrl_print("tac_program\n");
    tac_extdeflist(r->child);
}
void tac_extdeflist(struct Node *r) {
    _contrl_print("tac_extdeflist\n");
    if(r->child) {
        tac_extdef(r->child);
        if(r->child->brother) tac_extdeflist(r->child->brother);
    }
}
void tac_extdef(struct Node *r) {
    _contrl_print("tac_extdef\n");
    switch(r->type) {
        case extdeclist:
            tac_extdeclist(r->child->brother);
            break;
        case fundec:
            tac_fundec(r->child->brother);
            tac_compst(r->child->brother->brother);
            break;
        default:
            if(controller) 
                printf("tac_extdef(specifier SEMICOLON)\n");
            break;
    }
}
void tac_fundec(struct Node *r) {
    _Lable lable;
    _Tac tac;
    _contrl_print("tac_fundec\n");
    frame = new_frame();
    lable = new_lable(r->word_name);
    lable->frame = frame; // 栈帧绑定到lable
    tac = new_tac(_FUNCTION, NULL, NULL, NULL, lable);
    insert_tac(tac);
    if(r->child) {
        tac_varlist(r->child);
    }
    if(r->brother) {
        tac_compst(r->brother);
    }
}
void tac_varlist(struct Node *r) {
    _contrl_print("tac_varlist\n");
    if(r->child) {
        tac_paramdec(r->child);
        if(r->child->brother) tac_varlist(r->child->brother);
    }
}
void tac_paramdec(struct Node *r) {
    _Temp t;
    _Tac tac;
    TempValue value;
    struct Node *node, *tmp;
    _contrl_print("tac_paramdec\n");
    _check_point(r, "tac_paramdec");
    tmp = node = r->child->brother;
    switch(r->child->brother->type) {
        case WORD:
            // value._w = r->child->brother->word_name;
            switch(node->symbol->type) {
                case INT:
                break;
                case CHAR:
                break;
                case FLOAT:
                break;
            }
            t = new_temp(value, __v, -1);
            tac = new_tac(_PARAMETER, NULL, NULL, t, NULL);
            insert_tac(tac);
            node->symbol->_temp = t;
        break;
        case array:
            printf("tac_paramdec(offset wait to fix)\n");
            while(tmp && tmp->child) {
                tmp = tmp->child;
            }
            // value._w = tmp->word_name;
            t = new_temp(value, __t, -1);
            // Temp绑定到符号表中
            node->symbol->_temp = t;
            t->symbol = node->symbol;
        break;
        default:
            printf("default : tac_paramdec\n");
    }
}
void tac_compst(struct Node *r) {
    _contrl_print("tac_compst\n");
    if(r->child) tac_deflist(r->child);
}
void tac_deflist(struct Node *r) {
    _contrl_print("tac_deflist\n");
    if(r->child) tac_def(r->child);
    if(r->brother) tac_stmtlist(r->brother);
}
void tac_def(struct Node *r) {
    _contrl_print("tac_def\n");
    _check_point(r->child, "tac_def(r->child)\n");
    if(r->child) {
        if(r->child->brother)
            tac_declist(r->child->brother);
    }
}
void tac_declist(struct Node *r) {
    _contrl_print("tac_declist\n");
    if(r->child) tac_dec(r->child);
}
void tac_dec(struct Node *r) {
    _Temp t1, t2;
    _Tac tac;
    _contrl_print("tac_dec\n");
    switch(r->type) {
        case ASSIGNOP:
            t1 = tac_vardec(r->child);
            t2 = tac_exp(r->child->brother);
            tac = new_tac(_ASSIGN, t2, NULL, t1, NULL);
            insert_tac(tac);
        break;
        case vardec:
            tac_vardec(r->child);
        break;
    }
    if(r->brother) tac_declist(r->brother);
}
void tac_extdeclist(struct Node *r) {
    _contrl_print("tac_extdeclist\n");
    if(r->child) {
        tac_globle_vardec(r->child);
        if(r->child->brother) tac_extdeclist(r->child->brother);
    }
}
void tac_globle_vardec(struct Node *r) {
    struct Node *tmp;
    TempValue value;
    _Tac tac;
    _Temp t;
    _contrl_print("tac_globle_vardec\n");
    tmp = r;
    switch(r->type) {
        case WORD:
            printf("fix : tac_globle_vardec(offset)\n");
            value._w = r->word_name;
            t = new_temp(value, __w, -1);
            tac = new_tac(_GLOBLE, NULL, NULL, t, NULL);
            insert_tac(tac);
            r->symbol->_temp = t;
            t->symbol = r->symbol;
        break;
        case array:
            printf("fix : tac_globle_vardec(offset)\n");
            while(tmp && tmp->child) {
                tmp = tmp->child;
            }
            value._w = tmp->word_name;
            t = new_temp(value, __w, -1);
            tac = new_tac(_GLOBLE, NULL, NULL, t, NULL);
            insert_tac(tac);
            // Temp绑定到符号表中
            r->symbol->_temp = t;
            t->symbol = r->symbol;
        break;
        default:
            printf("default : tac_globle_vardec\n");
    }
}
_Temp tac_vardec(struct Node *r) {
    struct Node *tmp;
    TempValue value;
    _Temp t;
    _contrl_print("tac_vardec\n");
    tmp = r;
    switch(r->type) {
        case WORD:
            t = new_temp(value, __t, -1);
            r->symbol->_temp = t;
        break;
        case array:
            while(tmp && tmp->child) {
                tmp = tmp->child;
            }
            t = new_temp(value, __t, -1);
            // Temp绑定到符号表中
            r->symbol->_temp = t;
            t->symbol = r->symbol;
        break;
    }
    return t;
}
_Temp tac_exp(struct Node *r) {
    _Temp t, t1, t2;
    _Tac tac;
    TempValue value;
    _Lable lable;
    _contrl_print("tac_exp\n");
    switch(r->type) {
        case ASSIGNOP:
            t = tac_exp(r->child);
            t1 = tac_exp(r->child->brother);
            tac = new_tac(_ASSIGN, t1, NULL, t, NULL);
            insert_tac(tac);
        break;
        case AND: 
            printf("fix : tac_exp(offset)\n");
            t = new_temp(value, __t, -1);
            t1 = tac_exp(r->child);
            t2 = tac_exp(r->child->brother);
            tac = new_tac(_AND, t1, t2, t, NULL);
            insert_tac(tac);
        break;
        case OR:
            printf("fix : tac_exp(offset)\n");
            t = new_temp(value, __t, -1);
            t1 = tac_exp(r->child);
            t2 = tac_exp(r->child->brother);
            tac = new_tac(_OR, t1, t2, t, NULL);
            insert_tac(tac);
        break;
        case JUDGE_BIGGER:
            printf("fix : tac_exp(offset)\n");
            t = new_temp(value, __t, -1);
            t1 = tac_exp(r->child);
            t2 = tac_exp(r->child->brother);
            tac = new_tac(_JUDGE_B, t1, t2, t, NULL);
            insert_tac(tac);
        break;
        case JUDGE_SMALLER:
            printf("fix : tac_exp(offset)\n");
            t = new_temp(value, __t, -1);
            t1 = tac_exp(r->child);
            t2 = tac_exp(r->child->brother);
            tac = new_tac(_JUDGE_S, t1, t2, t, NULL);
            insert_tac(tac);
        break;
        case JUDGE_BIGGER_EQUAL:
            printf("fix : tac_exp(offset)\n");
            t = new_temp(value, __t, -1);
            t1 = tac_exp(r->child);
            t2 = tac_exp(r->child->brother);
            tac = new_tac(_JUDGE_BE, t1, t2, t, NULL);
            insert_tac(tac);
        break;
        case JUDGE_SMALLER_EQUAL:
            printf("fix : tac_exp(offset)\n");
            t = new_temp(value, __t, -1);
            t1 = tac_exp(r->child);
            t2 = tac_exp(r->child->brother);
            tac = new_tac(_JUDGE_SE, t1, t2, t, NULL);
            insert_tac(tac);
        break;
        case JUDGE_NOT_EQUAL:
            printf("fix : tac_exp(offset)\n");
            t = new_temp(value, __t, -1);
            t1 = tac_exp(r->child);
            t2 = tac_exp(r->child->brother);
            tac = new_tac(_JUDGE_NE, t1, t2, t, NULL);
            insert_tac(tac);
        break;
        case JUDGE_EQUAL:
            printf("fix : tac_exp(offset)\n");
            t = new_temp(value, __t, -1);
            t1 = tac_exp(r->child);
            t2 = tac_exp(r->child->brother);
            tac = new_tac(_JUDGE_E, t1, t2, t, NULL);
            insert_tac(tac);
        break;
        case PLUS:
            printf("fix : tac_exp(offset)\n");
            t = new_temp(value, __t, -1);
            t1 = tac_exp(r->child);
            t2 = tac_exp(r->child->brother);
            tac = new_tac(_PLUS, t1, t2, t, NULL);
            insert_tac(tac);
        break;
        case SUB:
            printf("fix : tac_exp(offset)\n");
            t = new_temp(value, __t, -1);
            t1 = tac_exp(r->child);
            t2 = tac_exp(r->child->brother);
            tac = new_tac(_SUB, t1, t2, t, NULL);
            insert_tac(tac);
        break;
        case MUL:
            printf("fix : tac_exp(offset)\n");
            t = new_temp(value, __t, -1);
            t1 = tac_exp(r->child);
            t2 = tac_exp(r->child->brother);
            tac = new_tac(_MUL, t1, t2, t, NULL);
            insert_tac(tac);
        break;
        case DIV:
            printf("fix : tac_exp(offset)\n");
            t = new_temp(value, __t, -1);
            t1 = tac_exp(r->child);
            t2 = tac_exp(r->child->brother);
            tac = new_tac(_DIV, t1, t2, t, NULL);
            insert_tac(tac);
        break;
        case exp:
            printf("fix : tac_exp(offset)\n");
            t = new_temp(value, __t, -1);
            t1 = tac_exp(r->child);
            tac = new_tac(_ASSIGN, t1, NULL, t, NULL);
            insert_tac(tac);
        break;
        case NOT:
            printf("fix : tac_exp(offset)\n");
            t = new_temp(value, __t, -1);
            t1 = tac_exp(r->child);
            tac = new_tac(_NOT, t1, NULL, t, NULL);
            insert_tac(tac);
        break;
        case fundec:
            printf("fix : tac_exp(offset)\n");
            tac_args(r->child);
            lable = new_lable(r->word_name);
            t = new_temp(value, __t, -1);
            tac = new_tac(_CALL, NULL, NULL, t, lable);
            insert_tac(tac);
        break;
        case array:
            printf("fix : tac_exp(offset)\n");
            t = new_temp(value, __t, -1);
            t1 = tac_exp(r->child);
            t2 = tac_exp(r->child->brother);
            printf("%d\n", t1->symbol->elemtype);
            switch(t1->symbol->elemtype) {
                case INT:
                    value._int = 4;
                break;
                case CHAR:
                    value._int = 1;
                break;
                case FLOAT:
                    value._int = 4;
                break;
            }
            tac = new_tac(_MUL, t2, NULL, t, NULL);
            insert_tac(tac);
            tac = new_tac(_A_ADD, t1, t2, t, NULL);
            insert_tac(tac);
        break;
        case POINT:
            printf("fix : tac_exp(offset)\n");
            printf("fix : tac_exp(case POINT)\n");
        break;
        case WORD:
            if(!(r->symbol)) {
                printf("tac_exp : %s(no symbol)\n", r->word_name);
                exit(0);
            }
            t = r->symbol->_temp;
            if(!t) printf("error : tac_exp(t=NULL)\n");
        break;
        case constant:
            switch(r->child->type) {
                case INT:
                    value._int = r->child->v.int_value;
                    t = new_temp(value, __int, -1);
                break;
                case CHAR:
                    value._char= r->child->v.char_value;
                    t = new_temp(value, __char, -1);
                break;
                case FLOAT:
                    value._float = r->child->v.float_value;
                    t = new_temp(value, __float, -1);
                break;
                default:
                    printf("default(type=%d)\n", r->child->type);
                    printf("default : tac_exp(constant)\n");
                break;
            }
        break;
    }
    return t;
}
void tac_args(struct Node *r) {
    _Tac tac;
    _Temp t;
    _contrl_print("tac_args\n");
    if(r->child->brother) {
        tac_args(r->child->brother);
    }
    if(r->child) {
        t = tac_exp(r->child);
        tac = new_tac(_ARG, NULL, NULL, t, NULL);
        insert_tac(tac);
    }
}
void tac_stmtlist(struct Node *r) {
    _contrl_print("tac_stmtlist\n");
    if(r->child) tac_stmt(r->child);
    if(r->child->brother) tac_stmtlist(r->child->brother);
}

void tac_stmt(struct Node *r) {
    _Temp t;
    _Lable lable, true_lable, false_lable, while_lable;
    _Tac tac;
    _contrl_print("tac_stmt\n");
    printf("fix : tac_stmt()\n");
    switch(r->type) {
        case exp:
            tac_exp(r->child);
        break;
        case compst:
            tac_compst(r->child);
        break;
        case RETURN:
            if(r->child) {
                t = tac_exp(r->child);
                tac = new_tac(_RETURN, NULL, NULL, t, NULL);
                insert_tac(tac);
            }
            else {
                tac = new_tac(_RETURN, NULL, NULL, NULL, NULL);
                insert_tac(tac);
            }
        break;
        case IF:
            lable = new_lable(NULL);
            false_lable = new_lable(NULL);
            true_lable = new_lable(NULL);
            t = tac_exp(r->child);
            tac = new_tac(_IF, NULL, NULL, t, NULL);
            insert_tac(tac);
            tac = new_tac(_GOTO, NULL, NULL, NULL, true_lable);
            insert_tac(tac);
            tac = new_tac(_GOTO, NULL, NULL, NULL, false_lable);
            insert_tac(tac);
            tac = new_tac(_LABLE, NULL, NULL, NULL, true_lable);
            insert_tac(tac);
            tac_stmt(r->child->brother);
            tac = new_tac(_GOTO, NULL, NULL, NULL, lable);
            insert_tac(tac);
            tac = new_tac(_LABLE, NULL, NULL, NULL, false_lable);
            insert_tac(tac);
            tac_stmt(r->child->brother->brother);
            tac = new_tac(_LABLE, NULL, NULL, NULL, lable);
            insert_tac(tac);
        break;
        case WHILE:
            lable = new_lable(NULL);
            while_lable = new_lable(NULL);
            true_lable = new_lable(NULL);
            tac = new_tac(_LABLE, NULL, NULL, NULL, while_lable);
            t = tac_exp(r->child);
            insert_tac(tac);
            tac = new_tac(_IF, NULL, NULL, t, NULL);
            insert_tac(tac);
            tac = new_tac(_GOTO, NULL, NULL, NULL, true_lable);
            insert_tac(tac);
            tac = new_tac(_GOTO, NULL, NULL, NULL, lable);
            insert_tac(tac);
            tac = new_tac(_LABLE, NULL, NULL, NULL, true_lable);
            insert_tac(tac);
            tac_stmt(r->child->brother);
            tac = new_tac(_GOTO, NULL, NULL, NULL, while_lable);
            insert_tac(tac);
        break;
        default:
            printf("check : tac_stmt(default)\n");
        break;
    }
}
// -insert_tac
void insert_tac(_Tac tac) {
    _contrl_print("insert_tac\n");
    if(!taclist) {
        _contrl_print("first : insert_tac\n");
        taclist = (_Taclist)malloc(sizeof(Taclist));
        taclist->front = tac;
        taclist->current = tac;
    }
    else {
        _contrl_print("behind : insert_tac\n");
        taclist->current->next = tac;
        taclist->current = tac;
    }
    // if(taclist->current->op == _PARAMETER) printf("_PARAMETER is insert\n");
}

// -_contrl_print && _check_point
void _contrl_print(const char *msg) {
    if(controller) {
        printf("%s", msg);
    }
}
void _check_point(struct Node *node, const char *msg) {
    if(!node) {
        printf("%s\n", msg);
    }
}

// -new_temp
_Temp new_temp(TempValue value, __temp_t type, int _offset) {
    _Temp t;
    t = (_Temp)malloc(sizeof(Temp));
    t->sign = type;
    t->offset = _offset;
    switch(type) {
        case __int:
            t->value._int = value._int;
        break;
        case __char:
            t->value._char = value._char;
        break;
        case __float:
            t->value._float= value._float;
        break;
        case __w:
            t->value._w = (char *)malloc(sizeof(char) * strlen(value._w));
            strcpy(t->value._w, value._w);
        break;
        case __t:
            t->value._t = _t_buffer++;
            frame->f_size += 4;
            t->offset = frame->f_size - 4;
        break;
        case __v:
            t->value._v = _v_buffer++;
            frame->f_size += 4;
            t->offset = frame->f_size - 4;
        break;
        break;
        default:
            printf("default : new_temp(type)");
        break;
    }
    return t;
}

// -new_frame
struct Frame *new_frame() {
    struct Frame *frame;
    frame = (struct Frame *)malloc(sizeof(struct Frame));
    frame->f_size = 4;
    return frame;
}

// -new_tac
_Tac new_tac(int op, _Temp t1, _Temp t2, _Temp t3, _Lable lable) {
    _Tac tac;
    tac = (_Tac)malloc(sizeof(Tac));
    tac->op = op;
    tac->temp[0]= t1;
    tac->temp[1]= t2;
    tac->temp[2]= t3;
    tac->lable = lable;
    tac->next = NULL;
    return tac;
}

// -new_lable
_Lable new_lable(char *name) {
    _Lable lable;
    lable = (_Lable)malloc(sizeof(Lable));
    if(!name) {
        // 临时生成标号
        lable->_lable_tag = 0;
        lable->_l_num = _l_buffer++;
    }
    else {
        lable->_lable_tag = 1;
        lable->name = (char *)malloc(sizeof(char) * strlen(name));
        strcpy(lable->name, name);
    }
    return lable;
}

// -_print_taclist && -_op_print
void _print_taclist(_Taclist list) {
    _Tac rlist = list->front;
    if(!rlist) printf("_print_taclist : rlist(null)\n");
    while(rlist) {
    switch(rlist->op) {
        case _not_op:
            printf("-1, \n");
        break;
        case _A_ADD:
            printf("A_ADD, ");
            temp_print(rlist->temp[2]);
            printf(" = ");
            temp_print(rlist->temp[0]);
            printf(" + ");
            temp_print(rlist->temp[1]);
            printf("\n");
        break;
        case _NOT:
            temp_print(rlist->temp[2]);
            printf(" = ");
            printf("!");
            temp_print(rlist->temp[0]);
            printf("\n");
        break;
        case _PARAMETER:
            printf("parameter ");
            temp_print(rlist->temp[2]);
            printf("\n");
        break;
        case _CALL:
            if(rlist->temp[2]) {
                temp_print(rlist->temp[2]);
                printf(" = ");
            }
            printf("call ");
            lable_print(rlist->lable);
            printf("\n");
        break;
        case _PLUS:
            temp_print(rlist->temp[2]);
            printf(" = ");
            temp_print(rlist->temp[0]);
            printf(" + ");
            temp_print(rlist->temp[1]);
            printf("\n");
        break;
        case _SUB:
            temp_print(rlist->temp[2]);
            printf(" = ");
            temp_print(rlist->temp[0]);
            printf(" - ");
            temp_print(rlist->temp[1]);
            printf("\n");
        break;
        case _MUL:
            temp_print(rlist->temp[2]);
            printf(" = ");
            temp_print(rlist->temp[0]);
            printf(" * ");
            temp_print(rlist->temp[1]);
            printf("\n");
        break;
        case _OR:
            temp_print(rlist->temp[2]);
            printf(" = ");
            temp_print(rlist->temp[0]);
            printf(" | ");
            temp_print(rlist->temp[1]);
            printf("\n");
        break;
        case _AND:
            temp_print(rlist->temp[2]);
            printf(" = ");
            temp_print(rlist->temp[0]);
            printf(" & ");
            temp_print(rlist->temp[1]);
            printf("\n");
        break;
        case _DIV:
            temp_print(rlist->temp[2]);
            printf(" = ");
            temp_print(rlist->temp[0]);
            printf(" / ");
            temp_print(rlist->temp[1]);
            printf("\n");
        break;
        case _ASSIGN:
            temp_print(rlist->temp[2]);
            printf(" = ");
            temp_print(rlist->temp[0]);
            printf("\n");
        break;
        case _RETURN:
            printf("return ");
            temp_print(rlist->temp[2]);
            printf("\n");
        break;
        case _JUDGE_E:
            temp_print(rlist->temp[2]);
            printf(" = ");
            temp_print(rlist->temp[0]);
            printf(" == ");
            temp_print(rlist->temp[1]);
            printf("\n");
        break;
        case _JUDGE_NE:
            temp_print(rlist->temp[2]);
            printf(" = ");
            temp_print(rlist->temp[0]);
            printf(" != ");
            temp_print(rlist->temp[1]);
            printf("\n");
        break;
        case _JUDGE_B:
            temp_print(rlist->temp[2]);
            printf(" = ");
            temp_print(rlist->temp[0]);
            printf(" > ");
            temp_print(rlist->temp[1]);
            printf("\n");
        break;
        case _JUDGE_BE:
            temp_print(rlist->temp[2]);
            printf(" = ");
            temp_print(rlist->temp[0]);
            printf(" >= ");
            temp_print(rlist->temp[1]);
            printf("\n");
        break;
        case _JUDGE_S:
            temp_print(rlist->temp[2]);
            printf(" = ");
            temp_print(rlist->temp[0]);
            printf(" < ");
            temp_print(rlist->temp[1]);
            printf("\n");
        break;
        case _JUDGE_SE:
            temp_print(rlist->temp[2]);
            printf(" = ");
            temp_print(rlist->temp[0]);
            printf(" <= ");
            temp_print(rlist->temp[1]);
            printf("\n");
        break;
        case _FUNCTION:
            printf("function(frame(%d)) ", rlist->lable->frame->f_size);
            lable_print(rlist->lable);
            printf(":\n");
        break;
        case _GLOBLE:
            printf("globle ");
            temp_print(rlist->temp[2]);
            printf("\n");
        break;
        case _LABLE:
            printf("lable ");
            lable_print(rlist->lable);
            printf(":\n");
        break;
        case _GOTO:
            printf("goto ");
            lable_print(rlist->lable);
            printf("\n");
        break;
        case _IF:
            printf("if ");
            temp_print(rlist->temp[2]);
            printf(" ");
        break;
        case _ARG:
            printf("arg ");
            temp_print(rlist->temp[2]);
            printf("\n");
        break;
        default:
            printf("default : _print_taclist(op=%d)\n", rlist->op);
    }
    rlist = rlist->next;
    }
}

void temp_print(_Temp temp) {
    switch(temp->sign) {
        case __int:
            printf("%d", temp->value._int);
        break;
        case __char:
            printf("%d", temp->value._char);
        break;
        case __float:
            printf("%f", temp->value._float);
        break;
        case __w:
            printf("%s", temp->value._w);
        break;
        case __t:
            printf("t%d(offset=%d)", temp->value._t, temp->offset);
        break;
        case __v:
            printf("v%d(offset=%d)", temp->value._v, temp->offset);
        break;
        default:
            printf("default : temp_print()\n");
        break;
    }
}

void lable_print(_Lable lable) {
    switch(lable->_lable_tag) {
        case 0:
            printf("lable%d", lable->_l_num);
        break;
        case 1:
            printf("%s", lable->name);
        break;
    }
}
