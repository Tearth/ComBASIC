#pragma once
#include "string.h"
#include "vector.h"
#include "ast-node.h"
#include "generator-block.h"

void generator_if_build(string* code, ast_node* root, vector* symbol_table);