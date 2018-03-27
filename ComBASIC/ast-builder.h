#pragma once
#include "string.h"
#include "vector.h"

typedef enum node_type
{
	N_ROOT,
	N_LINENUMBER,
	N_STRING,
	N_CLS,
	N_PRINT
} node_type;

typedef struct node
{
	node_type node_type;
	string node_value;

	vector children;
} node;

node* ast_build(vector* tokens);
void ast_initnode(node* node);
void ast_dump(node* node);
void ast_dump_r(node* node, int level);