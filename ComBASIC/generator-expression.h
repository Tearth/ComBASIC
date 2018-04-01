#pragma once
#include "string.h"
#include "vector.h"
#include "ast-node.h"
#include "generator-expression.h"

void generator_expression_build(string* code, ast_node* root, vector* symbol_table);
void generator_expression_build_r(string* code, ast_node* root, int* stack_pointer, vector* symbol_table);