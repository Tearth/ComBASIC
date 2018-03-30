#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "string.h"
#include "vector.h"
#include "ast-node.h"
#include "symbol-node.h"

string* code_build(ast_node* root, vector* symbol_table);
void code_datasection(string* code, ast_node* root, vector* symbol_table);
void code_textsection(string* code, ast_node* root, vector* symbol_table);