#pragma once

#include "symbol-node.h"
#include "vector.h"
#include "string.h"

void symboltable_add(vector* symbol_table, symbol_node* symbol);
void symboltable_dump(vector* symbol_table);
void symboltable_clean(vector* symbol_table);