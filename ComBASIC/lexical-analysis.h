#pragma once
#include <ctype.h>
#include "vector.h"
#include "string.h"

vector* lexical_gettokens(const char* source);
string* lexical_readidentifier(const char* source, int* length);
string* lexical_readnumber(const char* source, int* length);
string* lexical_readoperator(const char* source, int* length);