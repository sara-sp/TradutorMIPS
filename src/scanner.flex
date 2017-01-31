%{
// HEADERS
#include <stdlib.h>
#include "parser.h"
#include <string.h>
// variables maintained by the lexical analyser
int yyline = 1;
int linha = 1;
int cmdCount = 0;
int boolCount = 0;
int intCount = 0;
int varCount = 0;
int opCount = 0;
int compCount = 0;
%}

%option noyywrap

%%
[ \t]+ 						{  }
#.*\n 						{ yyline++; }
\n 							{ yyline++; }
\-?[0-9]+ 					{ yylval.intValue = atoi(yytext); return INT; }
";" 						{ return PTVIRG; }
":" 						{ return DOISPONTOS; }
"#" 						{ return COMENTARIO; }
"(" 						{ return PARENTESQ;	}
")" 						{ return PARENTDIR;	}
"+" 						{ return MAIS; }
"-" 						{ return MENOS; }
"*" 						{ return MULT; }
"/" 						{ return DIV; }
"=" 						{ return IGUAL; }
">" 						{ return MAIOR; }
"<" 						{ return MENOR; }
"<=" 						{ strcpy(yylval.var, yytext); return MENOR_IGUAL; }
">=" 						{ strcpy(yylval.var, yytext); return MAIOR_IGUAL; }
"==" 						{ strcpy(yylval.var, yytext); return IGUAL_IGUAL; }
"~=" 						{ strcpy(yylval.var, yytext); return DIFERENTE; }
"input()" 					{ strcpy(yylval.var, yytext); return INPUT; }
"true" 						{ strcpy(yylval.var, yytext); return VERDADE; }
"false" 					{ strcpy(yylval.var, yytext); return FALSO; }
"if" 						{ strcpy(yylval.var, yytext); return IF; }
"elseif" 					{ strcpy(yylval.var, yytext); return ELSEIF; }
"else" 						{ strcpy(yylval.var, yytext); return ELSE; }
"for" 						{ strcpy(yylval.var, yytext); return FOR; }
"while" 					{ strcpy(yylval.var, yytext); return WHILE; }
"end" 						{ strcpy(yylval.var, yytext); return END; }
"disp" 						{ strcpy(yylval.var, yytext); return DISP; }
[a-zA-Z_][a-zA-Z_0-9]* 		{ strcpy(yylval.var, yytext); return VARIAVEL; }
.  							{ yyerror("unexpected character"); }
%%
