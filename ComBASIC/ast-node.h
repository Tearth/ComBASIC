#pragma once
#include "string.h"
#include "vector.h"

typedef enum node_type
{
	N_ROOT,
	N_LINENUMBER,
	N_VARIABLE,
	N_CLS,
	N_PRINT,
	N_REM
} node_type;

typedef struct node
{
	node_type node_type;
	string node_value;
	vector children;
} node;

void astnode_init(node* node);