/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_SRC_Y_TAB_H_INCLUDED
# define YY_YY_SRC_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    WRITE = 258,                   /* WRITE  */
    DECL = 259,                    /* DECL  */
    ENDDECL = 260,                 /* ENDDECL  */
    T_INT = 261,                   /* T_INT  */
    T_BOOL = 262,                  /* T_BOOL  */
    VAR = 263,                     /* VAR  */
    NUM = 264,                     /* NUM  */
    b_NUM = 265,                   /* b_NUM  */
    T = 266,                       /* T  */
    F = 267,                       /* F  */
    BEG = 268,                     /* BEG  */
    END = 269,                     /* END  */
    IF = 270,                      /* IF  */
    THEN = 271,                    /* THEN  */
    ELSE = 272,                    /* ELSE  */
    ENDIF = 273,                   /* ENDIF  */
    LOGICAL_AND = 274,             /* LOGICAL_AND  */
    LOGICAL_NOT = 275,             /* LOGICAL_NOT  */
    LOGICAL_OR = 276,              /* LOGICAL_OR  */
    EQUALEQUAL = 277,              /* EQUALEQUAL  */
    LESSTHANOREQUAL = 278,         /* LESSTHANOREQUAL  */
    GREATERTHANOREQUAL = 279,      /* GREATERTHANOREQUAL  */
    NOTEQUAL = 280,                /* NOTEQUAL  */
    FOR = 281                      /* FOR  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define WRITE 258
#define DECL 259
#define ENDDECL 260
#define T_INT 261
#define T_BOOL 262
#define VAR 263
#define NUM 264
#define b_NUM 265
#define T 266
#define F 267
#define BEG 268
#define END 269
#define IF 270
#define THEN 271
#define ELSE 272
#define ENDIF 273
#define LOGICAL_AND 274
#define LOGICAL_NOT 275
#define LOGICAL_OR 276
#define EQUALEQUAL 277
#define LESSTHANOREQUAL 278
#define GREATERTHANOREQUAL 279
#define NOTEQUAL 280
#define FOR 281

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 33 "src/compiler.y"

	int var;
	bool b_var;
	node*  treeNode;
	symbltblentry* entry;

#line 126 "src/y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_SRC_Y_TAB_H_INCLUDED  */
