#pragma once
#include "ast-node.h"
#include "lexical-analysis.h"

#include "parser-linenumber.h"
#include "parser-keyword.h"
#include "parser-cls.h"
#include "parser-print.h"
#include "parser-rem.h"
#include "parser-for.h"
#include "parser-goto.h"
#include "parser-if.h"
#include "parser-input.h"
#include "parser-let.h"
#include "parser-while.h"
#include "parser-end.h"
#include "parser-gosub.h"
#include "parser-return.h"

bool parser_block_build(vector* tokens, ast_node* root, vector* symbol_table);
bool ast_parsearguments(vector* tokens, ast_node* keyword, int* index, vector* symbol_table);