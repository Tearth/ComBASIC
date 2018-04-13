#pragma once
#include "ast-node.h"
#include "lexical-analysis.h"
#include "parser-utils.h"

ast_node* parser_keyword_build(vector* tokens, int* index);