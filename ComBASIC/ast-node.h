#pragma once
#include "string.h"
#include "vector.h"

typedef enum ast_node_type
{
	N_ROOT,
	N_LINENUMBER,
	N_VARIABLE,
	N_CLS,
	N_PRINT,
	N_REM,
	N_NONEWLINE,
	N_EXPRESSION,
	N_ADD,
	N_SUB,
	N_MUL,
	N_DIV,
	N_MOD,
	N_EQUAL,
	N_NOTEQUAL,
	N_GREATERTHAN,
	N_EQUAL_GREATERTHAN,
	N_LESSTHAN,
	N_EQUAL_LESSTHAN,
	N_NUMBER,
	N_LET,
	N_IF,
	N_ELSE,
	N_ENDIF,
	N_END,
	N_GOTO,
	N_WHILE,
	N_WEND
} ast_node_type;

typedef struct ast_node
{
	ast_node_type type;
	string value;
	vector children;
} ast_node;

void astnode_init(ast_node* node, ast_node_type type, const char* value);
void astnode_clean(ast_node* node);