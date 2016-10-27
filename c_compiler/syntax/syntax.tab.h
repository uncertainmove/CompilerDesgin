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
    INT = 258,
    FLOATE = 259,
    DOUBLE = 260,
    SHORT = 261,
    PLUS = 262,
    SUB = 263,
    MUL = 264,
    DIV = 265,
    MOD = 266,
    ASSIGNOP = 267,
    COMMA = 268,
    SEMICOLON = 269,
    POINT = 270,
    JUDGE_BIGER = 271,
    JUDGE_SMALLER = 272,
    JUDGE_BIGER_EQUAL = 273,
    JUDGE_SMALLER_EQUAL = 274,
    JUDGE_EQUAL = 275,
    JUDGE_NOT_EQUAL = 276,
    NOT = 277,
    FOR = 278,
    WHILE = 279,
    IF = 280,
    ELSE = 281,
    RETURN = 282,
    BREAK = 283,
    STRUCT = 284,
    LEFT_PAR = 285,
    RIGHT_PAR = 286,
    LEFT_BRACE = 287,
    RIGHT_BRACE = 288,
    LEFT_BRACKET = 289,
    RIGHT_BRACKET = 290,
    LEFT_ANGLE_BRA = 291,
    RIGHT_ANGLE_BRA = 292,
    WORD = 293,
    DIGIT = 294,
    OR = 295,
    AND = 296,
    STAR = 297,
    ANNOTATION_LINE = 298,
    ANNOTATION_BLOCK_START = 299,
    ANNOTATION_BLOCK_STOP = 300,
    STRING = 301
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SYNTAX_TAB_H_INCLUDED  */
