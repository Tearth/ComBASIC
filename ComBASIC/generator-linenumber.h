#pragma once
#include "string.h"
#include "vector.h"
#include "ast-node.h"

string* generator_linenumber_build(string* code, ast_node* root, vector* symbol_table);