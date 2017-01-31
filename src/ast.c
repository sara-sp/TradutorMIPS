// AST constructor functions
#include <stdio.h>
#include <string.h>
#include <stdlib.h> // for malloc
#include "ast.h" // AST header

//Inteiros
Expr* ast_integer(int v) {
  Expr* node = malloc(sizeof(Expr));
  node->kind = E_INTEGER;
  node->attr.value = v;
  return node;
}

//Booleanos V/F
Expr* ast_bool(int v){
  Expr* node = malloc(sizeof(Expr));
  node->kind = E_BOOL;
  node->attr.booleano = v;
  return node;
}

//Strings
Expr* ast_string(char* v) {
  Expr* node = malloc(sizeof(Expr));
  char* buffer = malloc(strlen(v)+1);
  strcpy(buffer,v); 
  node->kind = E_STRING;
  node->attr.palavra = buffer;
  return node;
}

Expr* ast_parenteses(Expr* ep){
  Expr* node = malloc(sizeof(Expr));
  node->kind = E_PARENTESES;
  node->attr.ep = ep;
  return node;
}

//comando input(ler)
Expr* ast_input(){
  Expr* node = malloc(sizeof(Expr));
  node->kind = E_INPUT;
  return node;
}

//Operadores
Expr* ast_operation(int operator, Expr* left, Expr* right) {
  Expr* node = malloc(sizeof(Expr));
  node->kind = E_OPERATION;
  node->attr.op.operator = operator;
  node->attr.op.left = left;
  node->attr.op.right = right;
  return node;
}

//Lê comando 
CmdList* ast_cmd(Cmd* comando, CmdList* next) {
  CmdList* node = malloc(sizeof(CmdList));
  node->comando = comando;
  node->next=next;
  return node;
}

//Atribuicoes de variaveis
Cmd* ast_variavel(char* v, Expr* val) {
  Cmd* node = malloc(sizeof(Cmd));
  char* buffer = malloc(strlen(v)+1);
  strcpy(buffer,v); 
  node->kindCmd = E_VARIAVEL;
  node->tipo.atr.var = buffer;
  node->tipo.atr.valC = val;
  return node;
}

//comando if
Cmd* ast_if(Expr* cond, CmdList* comandos, CmdList* elseifs, CmdList* comandos2){
  Cmd* node = malloc(sizeof(Cmd));
  node->kindCmd = E_IF;
  node->tipo.aIf.cond = cond;
  node->tipo.aIf.comandos = comandos;
  node->tipo.aIf.elseifs = elseifs;
  node->tipo.aIf.comandos2 = comandos2;
  return node;  
}

//comando elseif
CmdList* ast_elseif(Expr* cond, CmdList* comandos, CmdList* elseifs){
  CmdList* node = malloc(sizeof(CmdList));
  node->kindCmds = E_ELSEIF;
  node->tipo.aElseIf.cond = cond;
  node->tipo.aElseIf.comandos = comandos;
  node->tipo.aElseIf.elseifs = elseifs;
  return node;  
}

//comando while
Cmd* ast_while(Expr* cond, CmdList* comandos){
  Cmd* node = malloc(sizeof(Cmd));
  node->kindCmd = E_WHILE;
  node->tipo.aWhile.cond = cond;
  node->tipo.aWhile.comandos = comandos;
  return node;
}

//comando for
Cmd* ast_for(Expr* v1, Expr* var, CmdList* comandos){
  Cmd* node = malloc(sizeof(Cmd));
  node->kindCmd = E_FOR;
  node->tipo.aFor.v1 = v1;
  node->tipo.aFor.var = var;
  node->tipo.aFor.comandos = comandos;
  return node; 
}

//comando disp(imprimir)
Cmd* ast_disp(Expr* v){
  Cmd* node = malloc(sizeof(Cmd));
  node->kindCmd = E_DISP;
  node->tipo.aDisp.valor = v;
  return node; 
}
