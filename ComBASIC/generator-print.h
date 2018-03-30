#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "string.h"
#include "vector.h"
#include "ast-node.h"

void generator_print_build(string* code, ast_node* root, vector* symbol_table);