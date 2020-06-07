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

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
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
    IntegerValue = 258,
    Id = 259,
    Comment = 260,
    KW_TRUE = 261,
    KW_FALSE = 262,
    OP_PLUS = 263,
    OP_MINUS = 264,
    OP_MULT = 265,
    OP_DIV = 266,
    KW_AND = 267,
    KW_OR = 268,
    KW_NOT = 269,
    KW_EQUAL = 270,
    KW_APPEND = 271,
    KW_CONCAT = 272,
    KW_SET = 273,
    KW_DEFFUN = 274,
    KW_IF = 275,
    KW_DEFVAR = 276,
    OP_OP = 277,
    OP_APOS = 278,
    OP_CP = 279
  };
#endif
/* Tokens.  */
#define IntegerValue 258
#define Id 259
#define Comment 260
#define KW_TRUE 261
#define KW_FALSE 262
#define OP_PLUS 263
#define OP_MINUS 264
#define OP_MULT 265
#define OP_DIV 266
#define KW_AND 267
#define KW_OR 268
#define KW_NOT 269
#define KW_EQUAL 270
#define KW_APPEND 271
#define KW_CONCAT 272
#define KW_SET 273
#define KW_DEFFUN 274
#define KW_IF 275
#define KW_DEFVAR 276
#define OP_OP 277
#define OP_APOS 278
#define OP_CP 279

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
