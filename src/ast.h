
// AST definitions
#ifndef __ast_h__
#define __ast_h__
#define MAX_SIZE 50

typedef struct _Expr Expr; // Convenience typedef
typedef struct _Cmd Cmd;
typedef struct _CmdList CmdList;

// AST for expressions
struct _Expr {
  
  enum { 
    E_INTEGER,
	E_STRING,
    E_OPERATION,
    E_INPUT,
	E_BOOL,
	E_PARENTESES
  } kind;

  union {
    int value; // for integer values
    char* palavra;
	int booleano;
	Expr* ep;

    struct { 
      int operator; // PLUS, MINUS, etc 
      Expr* left;
      Expr* right;
    } op; // for binary expressions

  } attr;
};

struct _Cmd {
  
  enum { 
	E_VARIAVEL,
    E_IF,
    E_WHILE,
    E_FOR,
    E_DISP
  } kindCmd;

  union {

	struct { 
      char* var;
      Expr* valC;
    } atr;

	struct { 
		Expr* cond; 
		Expr* cond2; 
		CmdList* elseifs;
        CmdList* comandos; 
		CmdList* comandos2;   
    } aIf;

    struct { 
        Expr* cond;  
        CmdList* comandos;
    } aWhile;

	struct { 
        Expr* v1;  
        Expr* var;
        CmdList* comandos;
    } aFor;

	struct { 
        Expr* valor;
    } aDisp;
	
  } tipo;
};

struct _CmdList {
  Cmd* comando;
  CmdList* next;

  enum { 
    E_ELSEIF,
  } kindCmds;

  union {
	struct { 
		Expr* cond; 
		CmdList* elseifs;
        CmdList* comandos; 
    } aElseIf;
  }tipo;
};



// Constructor functions (see implementation in ast.c)
Expr* ast_integer(int v);
Expr* ast_string(char* v);
Expr* ast_bool(int v);
Expr* ast_input();
Expr* ast_parenteses(Expr* ep);
Expr* ast_operation(int operator, Expr* left, Expr* right);
CmdList* ast_cmd(Cmd* atual, CmdList* next);
CmdList* ast_elseif(Expr* cond, CmdList* comandos, CmdList* elseifs);
Cmd* ast_variavel(char* v, Expr* val);
Cmd* ast_if(Expr* cond, CmdList* comandos, CmdList* elseif, CmdList* comandos2);
Cmd* ast_while(Expr* cond, CmdList* comandos);
Cmd* ast_for(Expr* v1, Expr* var, CmdList* comandos);
Cmd* ast_disp(Expr* v);
#endif
