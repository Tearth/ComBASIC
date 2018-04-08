#pragma once
#include "string.h"
#include "vector.h"
#include "ast-node.h"
#include "symbol-node.h"

#include "generator-block.h"

string* code_build(ast_node* root, vector* symbol_table);
void code_includesection(string* code, ast_node* root, vector* symbol_table);
void code_datasection(string* code, ast_node* root, vector* symbol_table);
void code_textsection(string* code, ast_node* root, vector* symbol_table);
void code_endsection(string* code, ast_node* root, vector* symbol_table);