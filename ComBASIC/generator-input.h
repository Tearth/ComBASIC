#pragma once
#include "string.h"
#include "vector.h"
#include "ast-node.h"

void generator_input_build(string* code, ast_node* root, vector* symbol_table);