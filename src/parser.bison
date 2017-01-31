// Tokens
%token 
  <intValue> INT  
  <var> VARIAVEL
  PTVIRG	
  DOISPONTOS	
  COMENTARIO
  PARENTESQ		
  PARENTDIR	
  MAIS			
  MENOS			
  MULT			
  DIV	
  VERDADE		
  FALSO			
  MAIOR			
  MENOR			
  MENOR_IGUAL	
  MAIOR_IGUAL	
  IGUAL_IGUAL	
  DIFERENTE		
  IGUAL
  IF			
  ELSEIF		  
  ELSE			
  END			
  FOR			
  WHILE			
  DISP			
  INPUT	

// Operator associativity & precedence
%left MAIS MENOS MULT DIV
%left MAIOR	MENOR MENOR_IGUAL MAIOR_IGUAL IGUAL_IGUAL DIFERENTE	
%left IGUAL

// Root-level grammar symbol
%start program;

// Types/values in association to grammar symbols.
%union {
	int intValue;
	char var[30];
	Expr* exprValue;
	CmdList* cmdListValue;
	Cmd* cmdValue;
}

%type <exprValue> expr
%type <cmdListValue> cmd_list
%type <cmdValue> cmd
%type <cmdListValue> elseif

// Use "%code requires" to make declarations go
// into both parser.c and parser.h
%code requires {
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
}

%%

program:   cmd_list								{ root = $1; } 
;

cmd_list:  cmd cmd_list					 		{ $$ = ast_cmd($1, $2);}
		 | 										{ $$ = NULL; } //empty
;

elseif:   ELSEIF expr cmd_list			{ cmdCount++; $$ = ast_elseif($2, $3, NULL); }
		| ELSEIF expr cmd_list elseif	{ cmdCount++; $$ = ast_elseif($2, $3, $4); }
;

cmd: VARIAVEL IGUAL expr PTVIRG					{ varCount++; cmdCount++; $$ = ast_variavel($1, $3); }
   | IF expr cmd_list END 			 		    { cmdCount++; $$ = ast_if($2, $3, NULL, NULL); }
   | IF expr cmd_list ELSE cmd_list END 		{ cmdCount+=2; $$ = ast_if($2, $3, NULL, $5); }
   | IF expr cmd_list elseif END  				{ cmdCount++; $$ = ast_if($2, $3, $4, NULL); }
   | IF expr cmd_list elseif ELSE cmd_list END 	{ cmdCount+=2; $$ = ast_if($2, $3, $4, $6); }
   | WHILE expr cmd_list END 					{ cmdCount++; $$ = ast_while($2, $3); }
   | FOR expr DOISPONTOS expr cmd_list END      { cmdCount++; $$ = ast_for($2, $4, $5); }
   | DISP PARENTESQ expr PARENTDIR PTVIRG 	    { cmdCount++; $$ = ast_disp($3); }
;

expr:	   INT 							{ intCount++; $$ = ast_integer($1); }
		 | INPUT						{ varCount++; $$ = ast_input(); }
		 | FALSO						{ boolCount++; $$ = ast_bool(0); }
		 | VERDADE						{ boolCount++; $$ = ast_bool(1); }
		 | VARIAVEL						{ varCount++; $$ = ast_string($1); }
         | PARENTESQ expr PARENTDIR 	{ $$ = ast_parenteses($2); }
		 | expr MAIS expr 				{ opCount++; $$ = ast_operation(MAIS, $1, $3); } 
		 | expr MENOS expr 				{ opCount++; $$ = ast_operation(MENOS, $1, $3); } 
		 | expr MULT expr 				{ opCount++; $$ = ast_operation(MULT, $1, $3); } 
 		 | expr DIV expr 				{ opCount++; $$ = ast_operation(DIV, $1, $3); } 
		 | expr MAIOR expr 				{ compCount++; $$ = ast_operation(MAIOR, $1, $3); }
		 | expr MENOR expr 				{ compCount++; $$ = ast_operation(MENOR, $1, $3); }
		 | expr MENOR_IGUAL expr 		{ compCount++; $$ = ast_operation(MENOR_IGUAL, $1, $3); }
		 | expr MAIOR_IGUAL expr 		{ compCount++; $$ = ast_operation(MAIOR_IGUAL, $1, $3); }
		 | expr IGUAL_IGUAL expr 		{ compCount++; $$ = ast_operation(IGUAL_IGUAL, $1, $3); }
		 | expr IGUAL expr				{ $$ = ast_operation(IGUAL, $1, $3); }
		 | expr DIFERENTE expr 			{ compCount++; $$ = ast_operation(DIFERENTE, $1, $3); }
;

%%

void yyerror(const char* err) {
  printf("Line %d: %s - '%s'\n", yyline, err, yytext);
}

