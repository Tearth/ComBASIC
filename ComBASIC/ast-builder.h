#pragma once
#include "string.h"
#include "vector.h"
#include "ast-node.h"
#include "parser-linenumber.h"
#include "parser-keyword.h"

node* ast_build(vector* tokens);
void ast_dump(node* node);
void ast_dump_r(node* node, int level);