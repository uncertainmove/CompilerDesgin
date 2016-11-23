/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_SYNTAX_TAB_H_INCLUDED
# define YY_YY_SYNTAX_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    POUND = 258,
    INCLUDE = 259,
    VOID = 260,
    INT = 261,
    FLOAT = 262,
    CHAR = 263,
    INT_DIGIT = 264,
    CHAR_DIGIT = 265,
    FLOAT_DIGIT = 266,
    WORD = 267,
    DOUBLE = 268,
    OCTAL = 269,
    HEXADECIMAL = 270,
    SHORT = 271,
    UNSIGNED = 272,
    UNSIGNED_DIGIT = 273,
    PLUS = 274,
    SUB = 275,
    MUL = 276,
    DIV = 277,
    MOD = 278,
    ASSIGNOP = 279,
    COMMA = 280,
    SEMICOLON = 281,
    POINT = 282,
    SINGLE_QUOTE = 283,
    DOUBLE_QUOTE = 284,
    JUDGE_BiGGER = 285,
    JUDGE_SMALLER = 286,
    JUDGE_BIGGER_EQUAL = 287,
    JUDGE_SMALLER_EQUAL = 288,
    JUDGE_EQUAL = 289,
    JUDGE_NOT_EQUAL = 290,
    NOT = 291,
    FOR = 292,
    WHILE = 293,
    IF = 294,
    ELSE = 295,
    RETURN = 296,
    BREAK = 297,
    STRUCT = 298,
    LP = 299,
    RP = 300,
    LC = 301,
    RC = 302,
    LB = 303,
    RB = 304,
    LEFT_ANGLE_BRA = 305,
    RIGHT_ANGLE_BRA = 306,
    OR = 307,
    AND = 308,
    ANNOTATION_LINE = 309,
    ANNOTATION_BLOCK_START = 310,
    ANNOTATION_BLOCK_STOP = 311,
    STRING = 312,
    JUDGE_BIGGER = 313,
    LOWER_THAN_ELSE = 314
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 16 "syntax.y" /* yacc.c:1909  */

    int type_int;
    char type_char;
    float type_float;
    char *type_string;
    struct Node *token_p;

#line 122 "syntax.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SYNTAX_TAB_H_INCLUDED  */
