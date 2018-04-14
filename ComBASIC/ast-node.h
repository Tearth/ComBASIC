#pragma once
#include "string.h"
#include "vector.h"

typedef enum ast_node_type
{
	N_ADD,
	N_AND,
	N_CLS,
	N_COMMA,
	N_DIV,
	N_ELSE,
	N_END,
	N_ENDIF,
	N_EQUAL,
	N_EQUAL_GREATERTHAN,
	N_EQUAL_LESSTHAN,
	N_EXPRESSION,
	N_FOR,
	N_GOTO,
	N_GOSUB,
	N_GREATERTHAN,
	N_IF,
	N_INPUT,
	N_LESSTHAN,
	N_LET,
	N_LINENUMBER,
	N_MOD,
	N_MUL,
	N_NONEWLINE,
	N_NOTEQUAL,
	N_NUMBER,
	N_OR,
	N_PRINT,
	N_REM,
	N_RETURN,
	N_SUB,
	N_VARIABLE,
	N_WEND,
	N_WHILE,
	N_ROOT
} ast_node_type;

typedef struct ast_node
{
	ast_node_type type;
	string value;
	vector children;
} ast_node;

void astnode_init(ast_node* node, ast_node_type type, const char* value);
void astnode_clear(ast_node* node);