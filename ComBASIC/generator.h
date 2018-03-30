#pragma once
#include "string.h"
#include "vector.h"
#include "ast-node.h"

string* generator_build(ast_node* root, vector* symbol_table);