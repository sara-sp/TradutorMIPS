#include <stdio.h>
#include <string.h>
#include "parser.h"

void printExpr(Expr*);
void printCmd(Cmd*);
void printElseif(CmdList*);
void printTree(CmdList*);

void printExpr(Expr* expr){

  if (expr == 0) 
    yyerror("Expressão nula!!");
  
  else if (expr->kind == E_INTEGER)
	printf("Int(%d) ", expr->attr.value);

  else if (expr->kind == E_INPUT)
	printf("INPUT() ");

  else if (expr->kind == E_BOOL){
	if(expr->attr.booleano==0)
		printf("Bool(falso) ");
	else
		printf("Bool(verdade) ");
  }

  else if (expr->kind == E_STRING)
	printf("Var(%s) ", expr->attr.palavra);
  
  else if (expr->kind == E_OPERATION){
    printExpr(expr->attr.op.left);

	switch (expr->attr.op.operator){
		case MAIS: 
                printf("Op(+) ");
			    break;
		case MENOS: 
				printf("Op(-) ");
				break;
		case MULT: 
				printf("Op(*) ");
				break;
		case DIV: 
				printf("Op(/) ");
				break;  
		case MAIOR: 
				printf("Comp(>) ");
				break;		
		case MENOR: 		
				printf("Comp(<) ");
				break;
		case MENOR_IGUAL: 
				printf("Comp(<=) ");
				break;
		case MAIOR_IGUAL: 
				printf("Comp(>=) ");
				break;		
		case IGUAL_IGUAL: 
				printf("Comp(==) ");
				break;
		case IGUAL: 
				printf("= ");
				break;
        case DIFERENTE:
				printf("Comp(~=) ");
				break;               
		
        default: yyerror("Operador desconhecido");
    }
	
    printExpr(expr->attr.op.right);
  }

  else if (expr->kind == E_PARENTESES){
	printf("( ");
	printExpr(expr->attr.ep);
	printf(") ");
  }
}

void printCmd(Cmd* cmd){

  if(cmd == 0)
	yyerror("Expressão nula!!\n");

  else if (cmd->kindCmd == E_VARIAVEL){
	printf("Var(%s) = ", cmd->tipo.atr.var);
  	printExpr(cmd->tipo.atr.valC);
  }

  else if (cmd->kindCmd == E_IF){
	printf("IF   ");
	printExpr(cmd->tipo.aIf.cond);
	printf("\n");
	printTree(cmd->tipo.aIf.comandos);

	if(cmd->tipo.aIf.elseifs!=NULL && cmd->tipo.aIf.comandos2!=NULL){
		printElseif(cmd->tipo.aIf.elseifs);
		printf("%d.\t",linha++);	
		printf("ELSE\n");
		printTree(cmd->tipo.aIf.comandos2);
	}

	else if(cmd->tipo.aIf.elseifs==NULL && cmd->tipo.aIf.comandos2!=NULL){
		printf("%d.\t",linha++);		
		printf("ELSE\n");
		printTree(cmd->tipo.aIf.comandos2);
	}

	else if(cmd->tipo.aIf.elseifs!=NULL && cmd->tipo.aIf.comandos2==NULL)
		printElseif(cmd->tipo.aIf.elseifs);

	printf("%d.\t",linha++);
	printf("Fim instrução");
  }
  
  else if (cmd->kindCmd == E_WHILE){
	printf("WHILE   ");
	printExpr(cmd->tipo.aWhile.cond);
	printf("\n");
	printTree(cmd->tipo.aWhile.comandos);
	printf("%d.\t",linha++);
	printf("Fim instrução");
  }

  else if (cmd->kindCmd == E_FOR){
	printf("FOR   ");
	printExpr(cmd->tipo.aFor.v1);
	printf(": ");
	printExpr(cmd->tipo.aFor.var);
	printf("\n");
	printTree(cmd->tipo.aFor.comandos);
	printf("%d.\t",linha++);
	printf("Fim instrução");
  }

  else if (cmd->kindCmd == E_DISP){
	printf("DISP( ");
    printExpr(cmd->tipo.aDisp.valor);
	printf(")");
  }
   
}

void printElseif(CmdList* current){
	if(current->kindCmds == E_ELSEIF){
		printf("%d.\t",linha++);
		printf("ELSE IF   ");
		printExpr(current->tipo.aElseIf.cond);
		printf("\n");
		printTree(current->tipo.aElseIf.comandos);
		
		if(current->tipo.aElseIf.elseifs!=NULL)
			printElseif(current->tipo.aElseIf.elseifs);
	}
}

void printTree(CmdList* current){

	if (current != NULL){
		printf("%d.\t",linha++);
		printCmd(current->comando);
		printf("\n");
		current = current->next;
		
		if(current != NULL)
		  printTree(current);
	}

	else
		printf("NULL");

}

//╔ ╗ ╝ ═ ╚ ║
void printGrelha(int tam, int v){
	  
	  if(v==0)
		  printf("\n╔");
	  else
		  printf("╚");
	  for(int i=0; i<tam; i++)
			printf("═");

	  if(v==0)
		  printf("╗");
	  else
		  printf("╝\n");

}
  
int main(int argc, char** argv) {
  --argc; ++argv;

  if (argc != 0) {
    yyin = fopen(*argv, "r");
    if (!yyin) {
      printf("'%s': could not open file\n", *argv);
      return 1;
    }
  } //  yyin = stdin

  int intro = strlen(" ÁRVORE SINTATICA DO FICHEIRO []") + strlen(*argv); 
  int res = strlen(" RESUMO ");

  if (yyparse() == 0){ 
	  printGrelha(intro, 0);
	  printf("\n║ ÁRVORE SINTATICA DO FICHEIRO [%s] ║\n", *argv);
	  printGrelha(intro, 1);

	  printTree(root);
	  
	  printGrelha(res, 0);
      printf("\n║ RESUMO ║\n");
	  printGrelha(res, 1);
	  printf("%d linhas imprimidas num total de %d analizadas.\n", linha-1, yyline);
	  
      if(cmdCount>1)
		  printf("%d chamadas de comandos.\n", cmdCount);

	  if(cmdCount==1)
		  printf("1 chamada de comando.\n");

      if(boolCount>1)
		  printf("%d chamadas de booleanos.\n", boolCount);
	  
      if(boolCount==1)
		  printf("1 chamada de booleano.\n");

      if(intCount>1)
		  printf("%d chamadas de inteiros.\n", intCount);

	  if(intCount==1)
		  printf("1 chamada de inteiro.\n");
	  
      if(varCount>1)
		  printf("%d chamadas de variaveis.\n", varCount);

	  if(varCount==1)
		  printf("1 chamada de variavel.\n");
	  
      if(opCount>1)
		  printf("%d chamadas de operadores.\n", opCount);

	  if(opCount==1)
		  printf("1 chamada de operador.\n");
	  
      if(compCount>1)
		  printf("%d chamadas de comparadores.\n", compCount);

	  if(compCount==1)
		  printf("1 chamada de comparador.\n");
  }
  return 0;
}
