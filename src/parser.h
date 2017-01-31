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

#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 56 "parser.bison" /* yacc.c:1909  */

	#include <stdio.h>
	#include <stdlib.h>
	#include "ast.h"

	extern int yylex();
	extern int yyline;
	extern int linha;
	extern int cmdCount;
	extern int boolCount;
	extern int intCount;
	extern int varCount;
	extern int opCount;
	extern int compCount;
	extern char* yytext;
	extern FILE* yyin;
	extern void yyerror(const char* msg);
	CmdList* root;

#line 64 "parser.h" /* yacc.c:1909  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    INT = 258,
    VARIAVEL = 259,
    PTVIRG = 260,
    DOISPONTOS = 261,
    COMENTARIO = 262,
    PARENTESQ = 263,
    PARENTDIR = 264,
    MAIS = 265,
    MENOS = 266,
    MULT = 267,
    DIV = 268,
    VERDADE = 269,
    FALSO = 270,
    MAIOR = 271,
    MENOR = 272,
    MENOR_IGUAL = 273,
    MAIOR_IGUAL = 274,
    IGUAL_IGUAL = 275,
    DIFERENTE = 276,
    IGUAL = 277,
    IF = 278,
    ELSEIF = 279,
    ELSE = 280,
    END = 281,
    FOR = 282,
    WHILE = 283,
    DISP = 284,
    INPUT = 285
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 41 "parser.bison" /* yacc.c:1909  */

	int intValue;
	char var[30];
	Expr* exprValue;
	CmdList* cmdListValue;
	Cmd* cmdValue;

#line 115 "parser.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */
