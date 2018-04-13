#pragma once
#include "ast-node.h"
#include "lexical-analysis.h"
#include "parser-block.h"
#include "parser-utils.h"

bool parser_if_build(vector* tokens, ast_node* keyword, int* index, vector* symbol_table);
vector* parser_if_buildbody(vector* tokens, int* index);
vector* parser_if_buildelse(vector* tokens, int* index);