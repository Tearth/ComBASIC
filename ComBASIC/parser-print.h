#pragma once
#include "ast-node.h"
#include "lexical-analysis.h"

bool parser_print_build(vector* tokens, node* keyword, int* index, vector* symbol_table);