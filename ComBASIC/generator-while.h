#pragma once
#include "string.h"
#include "vector.h"
#include "ast-node.h"
#include "generator-expression.h"

void generator_while_build(string* code, ast_node* root, vector* symbol_table);