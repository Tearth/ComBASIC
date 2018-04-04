#pragma once
#define MAX_KEYWORDS_TOKENS_COUNT 64

#include <ctype.h>
#include <string.h>
#include "lexical-token.h"
#include "vector.h"
#include "string.h"

vector* lexical_gettokens(const char* source);
lexical_token* lexical_readword(const char* source, int* length);
lexical_token* lexical_readnumber(const char* source, int* length);
lexical_token* lexical_readoperator(const char* source, int* length);

void lexical_checklasttoken(vector* tokens_vector);
bool lexical_keywordexists(const char* keyword);
bool lexical_operatorexists(const char* operator);
bool lexical_isunaryoperator(const char* operator);
void lexical_mergekeywords(vector* tokens_vector);
void lexical_mergeoperators(vector* tokens_vector);
void lexical_fixunaryoperators(vector* tokens_vector);
void lexical_dump(vector* tokens);
void lexical_clean(vector* tokens);