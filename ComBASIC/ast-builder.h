#pragma once
#include "string.h"
#include "vector.h"
#include "ast-node.h"
#include "parser-linenumber.h"
#include "parser-keyword.h"
#include "parser-cls.h"

node* ast_build(vector* tokens);

void ast_parsearguments(vector* tokens, node* keyword, int* index);
void ast_dump(node* node);
void ast_dump_r(node* node, int level);