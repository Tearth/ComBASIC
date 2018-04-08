#pragma once
#include "string.h"
#include "vector.h"
#include "ast-node.h"
#include "generator-cls.h"
#include "generator-end.h"
#include "generator-for.h"
#include "generator-goto.h"
#include "generator-if.h"
#include "generator-input.h"
#include "generator-let.h"
#include "generator-linenumber.h"
#include "generator-print.h"
#include "generator-rem.h"
#include "generator-while.h"

void generator_block_build(string* code, ast_node* root, vector* symbol_table);