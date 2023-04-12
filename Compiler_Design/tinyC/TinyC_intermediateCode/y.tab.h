/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

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
    NUMBER = 258,
    ID = 259,
    END = 260,
    RETURN = 261,
    VOID = 262,
    IF = 263,
    ELSE = 264,
    UNARY = 265,
    LE = 266,
    GE = 267,
    EQ = 268,
    NE = 269,
    GT = 270,
    LT = 271,
    AAND = 272,
    OOR = 273,
    NNOT = 274,
    SUBTRACT = 275,
    MUL = 276,
    DIVISION = 277,
    MODULUS = 278,
    ADDITION = 279,
    DOUB = 280,
    PRINT = 281,
    INTEGER = 282,
    PRINTALL = 283
  };
#endif
/* Tokens.  */
#define NUMBER 258
#define ID 259
#define END 260
#define RETURN 261
#define VOID 262
#define IF 263
#define ELSE 264
#define UNARY 265
#define LE 266
#define GE 267
#define EQ 268
#define NE 269
#define GT 270
#define LT 271
#define AAND 272
#define OOR 273
#define NNOT 274
#define SUBTRACT 275
#define MUL 276
#define DIVISION 277
#define MODULUS 278
#define ADDITION 279
#define DOUB 280
#define PRINT 281
#define INTEGER 282
#define PRINTALL 283

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 28 "tiny.y"

	Program* pro;
	char ch;
        SymbolTable* sym;
	SymbolTableEntry * ste;
	Function* func;
        char* cval;
	int ival;
	double dval;
	Ast* a;
	list<Ast*> *la;
	DataType dt;
	ExprAst *ea;

#line 128 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
