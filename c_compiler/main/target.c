/*************************************************************************
	> File Name: target.c
	> Author: 
	> Mail: 
	> Created Time: 2016年12月13日 星期二 16时56分30秒
 ************************************************************************/

#include "target.h"

void target_start(char *filename, _Taclist taclist) {
    FILE *f;
    int para_sign = 0, args_sign = 0; // 标志当前处理的参数序号
    _Tac tac_current;
    _contrl_print("target_start\n");
    if(!taclist) {
        printf("null : target_start(taclist)");
        exit(0);
    }
    else {
        tac_current = taclist->front;
        f = fopen("test.s", "w+");
        // fprintf(f, "\t.file\t\"%s\"\n", filename);
        while(tac_current->op == _GLOBLE) {
            fprintf(f, "\t.common\t%s,%d,%d\n", tac_current->temp[2]->value._w, 4, 4);
            tac_current = tac_current->next;
        }
        fprintf(f, "\t.text\n");
        while(tac_current && tac_current->op == _FUNCTION) {
            para_sign = 0;
            fprintf(f, "\t.globl\t%s\n", tac_current->lable->name);
            // fprintf(f, "\t.type\t%s, @function\n", tac_current->lable->name);
            fprintf(f, "%s:\n", tac_current->lable->name);
            // fprintf(f, ".LFB%d:\n", LFB++);
            // fprintf(f, "\t.cfi_startproc\n");
            fprintf(f, "\tpushq\t%%rbp\n");
            // fprintf(f, "\t.cfi_def_cfa_offset %d\n", 16);
            // fprintf(f, "\t.cfi_offset %d, %d\n", 6, -16);
            fprintf(f, "\tmovq\t%%rsp, %%rbp\n");
            // fprintf(f, "\t.cfi_def_cfa_register %d\n", 6);
            fprintf(f, "\tsubq\t$%d, %%rsp\n", tac_current->lable->frame->f_size);
            tac_current = tac_current->next;
            while(tac_current && tac_current->op != _FUNCTION) {
                if(tac_current->op != _ARG) args_sign = 0;
                switch(tac_current->op) {
                    case _PLUS:
                        if(tac_current->temp[0]->sign == __t || tac_current->temp[0]->sign == __v) {
                            movl(f, -1, tac_current->temp[0]->offset, "%ecx", NULL, 3);
                        }
                        else if(tac_current->temp[0]->sign == __int) {
                            movl(f, tac_current->temp[0]->value._int, -1, "%ecx", NULL, 0);
                        }
                        else {
                            movl(f, -1, -1, "%ecx", tac_current->temp[0]->value._w, 4);
                        }
                        if(tac_current->temp[1]->sign == __t || tac_current->temp[1]->sign == __v) {
                            movl(f, -1, tac_current->temp[1]->offset, "%eax", NULL, 3);
                            fprintf(f, "\taddl\t%s, %s\n", "%eax", "%ecx");
                        }
                        else if(tac_current->temp[1]->sign == __int) {
                            fprintf(f, "\taddl\t$%d, %s\n", tac_current->temp[1]->value._int, "%ecx");
                        }
                        else {
                            fprintf(f, "\taddl\t%s(%%rbp), %s\n", tac_current->temp[1]->value._w, "%ecx");
                        }
                        movl(f, -1, tac_current->temp[2]->offset, "%ecx", NULL, 2);
                    break;
                    case _SUB:
                        if(tac_current->temp[0]->sign == __t || tac_current->temp[0]->sign == __v) {
                            movl(f, -1, tac_current->temp[0]->offset, "%ecx", NULL, 3);
                        }
                        else if(tac_current->temp[0]->sign == __int) {
                            movl(f, tac_current->temp[0]->value._int, -1, "%ecx", NULL, 0);
                        }
                        else {
                            movl(f, -1, -1, "%ecx", tac_current->temp[0]->value._w, 4);
                        }
                        if(tac_current->temp[1]->sign == __t || tac_current->temp[1]->sign == __v) {
                            movl(f, -1, tac_current->temp[1]->offset, "%eax", NULL, 3);
                            fprintf(f, "\tsubl\t%s, %s\n", "%eax", "%ecx");
                        }
                        else if(tac_current->temp[1]->sign == __int) {
                            fprintf(f, "\tsubl\t$%d, %s\n", tac_current->temp[1]->value._int, "%ecx");
                        }
                        else {
                            fprintf(f, "\tsubl\t%s(%%rbp), %s\n", tac_current->temp[1]->value._w, "%ecx");
                        }
                        movl(f, -1, tac_current->temp[2]->offset, "%ecx", NULL, 2);
                    break;
                    case _MUL:
                        if(tac_current->temp[0]->sign == __t || tac_current->temp[0]->sign == __v) {
                            movl(f, -1, tac_current->temp[0]->offset, "%ecx", NULL, 3);
                        }
                        else if(tac_current->temp[0]->sign == __int) {
                            movl(f, tac_current->temp[0]->value._int, -1, "%ecx", NULL, 0);
                        }
                        else {
                            movl(f, -1, -1, "%ecx", tac_current->temp[0]->value._w, 4);
                        }
                        if(tac_current->temp[1]->sign == __t || tac_current->temp[1]->sign == __v) {
                            movl(f, -1, tac_current->temp[1]->offset, "%eax", NULL, 3);
                            fprintf(f, "\timull\t%s, %s\n", "%eax", "%ecx");
                        }
                        else if(tac_current->temp[1]->sign == __int) {
                            fprintf(f, "\timull\t$%d, %s\n", tac_current->temp[1]->value._int, "%ecx");
                        }
                        else {
                            fprintf(f, "\timull\t%s(%%rbp), %s\n", tac_current->temp[1]->value._w, "%ecx");
                        }
                        movl(f, -1, tac_current->temp[2]->offset, "%ecx", NULL, 2);
                    break;
                    case _DIV:
                        if(tac_current->temp[0]->sign == __t || tac_current->temp[0]->sign == __v) {
                            movl(f, -1, tac_current->temp[0]->offset, "%eax", NULL, 3);
                        }
                        else if(tac_current->temp[0]->sign == __int) {
                            movl(f, tac_current->temp[0]->value._int, -1, "%eax", NULL, 0);
                        }
                        else {
                            movl(f, -1, -1, "%eax", tac_current->temp[0]->value._w, 4);
                        }
                        if(tac_current->temp[1]->sign == __t || tac_current->temp[1]->sign == __v) {
                            movl(f, -1, tac_current->temp[1]->offset, "%ecx", NULL, 3);
                            fprintf(f, "\tcltd\n");
                            fprintf(f, "\tidivl\t%s\n", "%ecx");
                        }
                        else if(tac_current->temp[1]->sign == __int) {
                            fprintf(f, "\tcltd\n");
                            fprintf(f, "\tidivl\t$%d\n", tac_current->temp[1]->value._int);
                        }
                        else {
                            fprintf(f, "\tcltd\n");
                            fprintf(f, "\tidivl\t%s(%%rbp)\n", tac_current->temp[1]->value._w);
                        }
                        movl(f, -1, tac_current->temp[2]->offset, "%eax", NULL, 2);
                    break;
                    case _ASSIGN:
                        if(tac_current->temp[0]->sign == __t || tac_current->temp[0]->sign == __v) {
                            movl(f, -1, tac_current->temp[0]->offset, "%ecx", NULL, 3);
                            if(tac_current->temp[2]->sign == __t || tac_current->temp[2]->sign == __v)
                                movl(f, -1, tac_current->temp[2]->offset, "%ecx", NULL, 2);
                            else if(tac_current->temp[2]->sign == __w) {
                                movl(f, -1, tac_current->temp[2]->offset, "%ecx", tac_current->temp[2]->value._w, 5);
                            }
                        }
                        else if(tac_current->temp[0]->sign == __int) {
                            if(tac_current->temp[2]->sign == __t || tac_current->temp[2]->sign == __v)
                                movl(f, tac_current->temp[0]->value._int, tac_current->temp[2]->offset, NULL, NULL, 1);
                            else if(tac_current->temp[2]->sign == __w) {
                                movl(f, tac_current->temp[0]->value._int, -1, NULL, tac_current->temp[2]->value._w, 6);
                            }
                        }
                    break;
                    case _JUDGE_E:
                        if(tac_current->temp[0]->sign == __t || tac_current->temp[0]->sign == __v) {
                            movl(f, -1, tac_current->temp[0]->offset, "%ecx", NULL, 3);
                        }
                        else if(tac_current->temp[0]->sign == __int) {
                            movl(f, tac_current->temp[0]->value._int, -1, "%ecx", NULL, 0);
                        }
                        else {
                            movl(f, -1, -1, "%ecx", tac_current->temp[0]->value._w, 4);
                        }
                        if(tac_current->temp[1]->sign == __t || tac_current->temp[1]->sign == __v) {
                            movl(f, -1, tac_current->temp[1]->offset, "%eax", NULL, 3);
                            fprintf(f, "\tcmpl\t%s, %s\n", "%eax", "%ecx");
                        }
                        else if(tac_current->temp[1]->sign == __int || tac_current->temp[1]->sign == __v) {
                            fprintf(f, "\tcmpl\t$%d, %s\n", tac_current->temp[1]->value._int, "%ecx");
                        }
                        else {
                            fprintf(f, "\tcmpl\t%s(%%rip), %s\n", tac_current->temp[1]->value._w, "%ecx");
                        }
                        fprintf(f, "\tsete\t%%al\n");
                        fprintf(f, "\tmovzbl\t%%al, %%eax\n");
                        movl(f, -1, tac_current->temp[2]->offset, "%eax", NULL, 2);
                    break;
                    case _JUDGE_NE:
                        if(tac_current->temp[0]->sign == __t || tac_current->temp[0]->sign == __v) {
                            movl(f, -1, tac_current->temp[0]->offset, "%ecx", NULL, 3);
                        }
                        else if(tac_current->temp[0]->sign == __int) {
                            movl(f, tac_current->temp[0]->value._int, -1, "%ecx", NULL, 0);
                        }
                        else {
                            movl(f, -1, -1, "%ecx", tac_current->temp[0]->value._w, 4);
                        }
                        if(tac_current->temp[1]->sign == __t || tac_current->temp[1]->sign == __v) {
                            movl(f, -1, tac_current->temp[1]->offset, "%eax", NULL, 3);
                            fprintf(f, "\tcmpl\t%s, %s\n", "%eax", "%ecx");
                        }
                        else if(tac_current->temp[1]->sign == __int) {
                            fprintf(f, "\tcmpl\t$%d, %s\n", tac_current->temp[1]->value._int, "%ecx");
                        }
                        else {
                            fprintf(f, "\tcmpl\t%s(%%rip), %s\n", tac_current->temp[1]->value._w, "%ecx");
                        }
                        fprintf(f, "\tsetne\t%%al\n");
                        fprintf(f, "\tmovzbl\t%%al, %%eax\n");
                        movl(f, -1, tac_current->temp[2]->offset, "%eax", NULL, 2);
                    break;
                    case _JUDGE_BE:
                        if(tac_current->temp[0]->sign == __t || tac_current->temp[0]->sign == __v) {
                            movl(f, -1, tac_current->temp[0]->offset, "%ecx", NULL, 3);
                        }
                        else if(tac_current->temp[0]->sign == __int) {
                            movl(f, tac_current->temp[0]->value._int, -1, "%ecx", NULL, 0);
                        }
                        else {
                            movl(f, -1, -1, "%ecx", tac_current->temp[0]->value._w, 4);
                        }
                        if(tac_current->temp[1]->sign == __t || tac_current->temp[1]->sign == __v) {
                            movl(f, -1, tac_current->temp[1]->offset, "%eax", NULL, 3);
                            fprintf(f, "\tcmpl\t%s, %s\n", "%eax", "%ecx");
                        }
                        else if(tac_current->temp[1]->sign == __int) {
                            fprintf(f, "\tcmpl\t$%d, %s\n", tac_current->temp[1]->value._int, "%ecx");
                        }
                        else {
                            fprintf(f, "\tcmpl\t%s(%%rip), %s\n", tac_current->temp[1]->value._w, "%ecx");
                        }
                        fprintf(f, "\tsetge\t%%al\n");
                        fprintf(f, "\tmovzbl\t%%al, %%eax\n");
                        movl(f, -1, tac_current->temp[2]->offset, "%eax", NULL, 2);
                    break;
                    case _JUDGE_SE:
                        if(tac_current->temp[0]->sign == __t || tac_current->temp[0]->sign == __v) {
                            movl(f, -1, tac_current->temp[0]->offset, "%ecx", NULL, 3);
                        }
                        else if(tac_current->temp[0]->sign == __int) {
                            movl(f, tac_current->temp[0]->value._int, -1, "%ecx", NULL, 0);
                        }
                        else {
                            movl(f, -1, -1, "%ecx", tac_current->temp[0]->value._w, 4);
                        }
                        if(tac_current->temp[1]->sign == __t || tac_current->temp[1]->sign == __v) {
                            movl(f, -1, tac_current->temp[1]->offset, "%eax", NULL, 3);
                            fprintf(f, "\tcmpl\t%s, %s\n", "%eax", "%ecx");
                        }
                        else if(tac_current->temp[1]->sign == __int) {
                            fprintf(f, "\tcmpl\t$%d, %s\n", tac_current->temp[1]->value._int, "%ecx");
                        }
                        else {
                            fprintf(f, "\tcmpl\t%s(%%rip), %s\n", tac_current->temp[1]->value._w, "%ecx");
                        }
                        fprintf(f, "\tsetle\t%%al\n");
                        fprintf(f, "\tmovzbl\t%%al, %%eax\n");
                        movl(f, -1, tac_current->temp[2]->offset, "%eax", NULL, 2);
                    break;
                    case _JUDGE_B:
                        if(tac_current->temp[0]->sign == __t || tac_current->temp[0]->sign == __v) {
                            movl(f, -1, tac_current->temp[0]->offset, "%ecx", NULL, 3);
                        }
                        else if(tac_current->temp[0]->sign == __int) {
                            movl(f, tac_current->temp[0]->value._int, -1, "%ecx", NULL, 0);
                        }
                        else {
                            movl(f, -1, -1, "%ecx", tac_current->temp[0]->value._w, 4);
                        }
                        if(tac_current->temp[1]->sign == __t || tac_current->temp[1]->sign == __v) {
                            movl(f, -1, tac_current->temp[1]->offset, "%eax", NULL, 3);
                            fprintf(f, "\tcmpl\t%s, %s\n", "%eax", "%ecx");
                        }
                        else if(tac_current->temp[1]->sign == __int) {
                            fprintf(f, "\tcmpl\t$%d, %s\n", tac_current->temp[1]->value._int, "%ecx");
                        }
                        else {
                            fprintf(f, "\tcmpl\t%s(%%rip), %s\n", tac_current->temp[1]->value._w, "%ecx");
                        }
                        fprintf(f, "\tsetg\t%%al\n");
                        fprintf(f, "\tmovzbl\t%%al, %%eax\n");
                        movl(f, -1, tac_current->temp[2]->offset, "%eax", NULL, 2);
                    break;
                    case _JUDGE_S:
                        if(tac_current->temp[0]->sign == __t || tac_current->temp[0]->sign == __v) {
                            movl(f, -1, tac_current->temp[0]->offset, "%ecx", NULL, 3);
                        }
                        else if(tac_current->temp[0]->sign == __int) {
                            movl(f, tac_current->temp[0]->value._int, -1, "%ecx", NULL, 0);
                        }
                        else {
                            movl(f, -1, -1, "%ecx", tac_current->temp[0]->value._w, 4);
                        }
                        if(tac_current->temp[1]->sign == __t || tac_current->temp[1]->sign == __v) {
                            movl(f, -1, tac_current->temp[1]->offset, "%eax", NULL, 3);
                            fprintf(f, "\tcmpl\t%s, %s\n", "%eax", "%ecx");
                        }
                        else if(tac_current->temp[1]->sign == __int) {
                            fprintf(f, "\tcmpl\t$%d, %s\n", tac_current->temp[1]->value._int, "%ecx");
                        }
                        else {
                            fprintf(f, "\tcmpl\t%s(%%rip), %s\n", tac_current->temp[1]->value._w, "%ecx");
                        }
                        fprintf(f, "\tsetl\t%%al\n");
                        fprintf(f, "\tmovzbl\t%%al, %%eax\n");
                        movl(f, -1, tac_current->temp[2]->offset, "%eax", NULL, 2);
                    break;
                    case _RETURN:
                        if(tac_current->temp[2]->sign == __t || tac_current->temp[2]->sign == __v) {
                            movl(f, -1, tac_current->temp[2]->offset, "%eax", NULL, 3);
                        }
                        else if(tac_current->temp[2]->sign == __int) {
                            movl(f, tac_current->temp[2]->value._int, -1, "%eax", NULL, 0);

                        }
                        else {
                            movl(f, -1, -1, "%eax", tac_current->temp[2]->value._w, 4);
                        }
                        fprintf(f, "\tleave\n");
                        fprintf(f, "\tret\n");
                    break;
                    case _PARAMETER:
                        switch(para_sign) {
                            case 0:
                                fprintf(f, "\tmovl\t%%edi, -%d(%%rbp)\n", tac_current->temp[2]->offset);
                                para_sign = 1;
                            break;
                            case 1:
                                fprintf(f, "\tmovl\t%%esi, -%d(%%rbp)\n", tac_current->temp[2]->offset);
                                para_sign = 2;
                            break;
                            case 2:
                                fprintf(f, "\tmovl\t%%edx, -%d(%%rbp)\n", tac_current->temp[2]->offset);
                                para_sign = 3;
                            break;
                            default:
                                printf("default : target_start(_PARAMETER)\n");
                        }
                    break;
                    case _LABLE:
                        fprintf(f, ".lable%d:\n", tac_current->lable->_l_num);
                    break;
                    case _IF:
                        if(tac_current->temp[2]->sign == __t || tac_current->temp[2]->sign == __v) {
                            movl(f, -1, tac_current->temp[2]->offset, "%ecx", NULL, 3);
                        }
                        else if(tac_current->temp[2]->sign == __w) {
                            movl(f, -1, -1, "%ecx", tac_current->temp[2]->value._w, 4);
                        }
                        else {
                            movl(f, 1, -1, "ecx", NULL, 0);
                        }
                        fprintf(f, "\tcmpl\t$1, %s\n", "%ecx");
                        if(tac_current->next->op == _GOTO) {
                            tac_current = tac_current->next;
                            fprintf(f, "\tje\t.lable%d\n", tac_current->lable->_l_num);
                        }
                    break;
                    case _GOTO:
                        fprintf(f, "\tjmp\t.lable%d\n", tac_current->lable->_l_num);
                    break;
                    case _ARG:
                        switch(args_sign) {
                            case 0:
                                if(tac_current->temp[2]->sign == __t || tac_current->temp[2]->sign == __v) {
                                    fprintf(f, "\tmovl\t-%d(%%rbp), %%edi\n", tac_current->temp[2]->offset);
                                }
                                else if(tac_current->temp[2]->sign == __int) {
                                    fprintf(f, "\tmovl\t%s(%%rip), %%edi\n", tac_current->temp[2]->value._w);
                                }
                                else {
                                    fprintf(f, "\tmovl\t%d, %%edi\n", tac_current->temp[2]->value._int);
                                }
                                args_sign = 1;
                            break;
                            case 1:
                                if(tac_current->temp[2]->sign == __t || tac_current->temp[2]->sign == __v) {
                                    fprintf(f, "\tmovl\t-%d(%%rbp), %%esi\n", tac_current->temp[2]->offset);
                                }
                                else if(tac_current->temp[2]->sign == __int) {
                                    fprintf(f, "\tmovl\t%s(%%rip), %%esi\n", tac_current->temp[2]->value._w);
                                }
                                else {
                                    fprintf(f, "\tmovl\t%d, %%esi\n", tac_current->temp[2]->value._int);
                                }
                                args_sign = 2;
                            break;
                            case 2:
                                if(tac_current->temp[2]->sign == __t || tac_current->temp[2]->sign == __v) {
                                    fprintf(f, "\tmovl\t-%d(%%rbp), %%edx\n", tac_current->temp[2]->offset);
                                }
                                else if(tac_current->temp[2]->sign == __int) {
                                    fprintf(f, "\tmovl\t%s(%%rip), %%edx\n", tac_current->temp[2]->value._w);
                                }
                                else {
                                    fprintf(f, "\tmovl\t%d, %%edx\n", tac_current->temp[2]->value._int);
                                }
                                args_sign = 3;
                            break;
                            default:
                                printf("default : target_start(_ARG)\n");
                        }
                    break;
                    case _CALL:
                        fprintf(f, "\tcall\t%s\n", tac_current->lable->name);
                        if(tac_current->temp[2]->sign == __t || tac_current->temp[2]->sign == __v) {
                            fprintf(f, "\tmovl\t%%eax, -%d(%%rbp)\n", tac_current->temp[2]->offset);
                        }
                        else {
                            fprintf(f, "\tmovl\t%%eax, %s(%%rip)\n", tac_current->temp[2]->value._w);
                        }
                    break;
                    default:
                        printf("default : target_start(op=%d)\n", tac_current->op);
                }
                tac_current = tac_current->next;
            }
        }
    }
    fclose(f);
}

void movl(FILE *f, int constant, int offset, const char *reg, const char *glb, int sign) {
    // sign = 0 : movl $-, %reg
    // sign = 1 : movl $-, --(%rbp)
    // sign = 2 : movl %reg, --(%rbp)
    // sign = 3 : movl --(%rbp), %reg 
    // sign = 4 : movl glb, %reg 
    // sign = 5 : movl %reg,glb 
    // sign = 6 : movl $-,glb 
    switch(sign) {
        case 0:
            fprintf(f, "\tmovl\t$%d, %s\n", constant, reg);
        break;
        case 1:
            fprintf(f, "\tmovl\t$%d, -%d(%%rbp)\n", constant, offset);
        break;
        case 2:
            fprintf(f, "\tmovl\t%s, -%d(%%rbp)\n", reg, offset);
        break;
        case 3:
            fprintf(f, "\tmovl\t-%d(%%rbp), %s\n", offset, reg);
        break;
        case 4:
            fprintf(f, "\tmovl\t%s(%%rip), %s\n", glb, reg);
        break;
        case 5:
            fprintf(f, "\tmovl\t%s, %s(%%rip)\n", reg, glb);
        break;
        case 6:
            fprintf(f, "\tmovl\t$%d, %s(%%rip)\n", constant, glb);
        break;
        default:
            printf("default : movl()\n");
    }
}
