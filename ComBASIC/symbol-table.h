#pragma once
#include <string.h>
#include "symbol-node.h"
#include "vector.h"
#include "string.h"

symbol_node* symboltable_add(vector* symbol_table, symbol_node_type type, const char* name, const char* value);
void symboltable_dump(vector* symbol_table);
void symboltable_clear(vector* symbol_table);
