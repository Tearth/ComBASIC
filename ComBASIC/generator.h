#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "string.h"
#include "vector.h"
#include "ast-node.h"
#include "symbol-node.h"

string* generator_build(ast_node* root, vector* symbol_table);
void generator_datasection(string* code, ast_node* root, vector* symbol_table);