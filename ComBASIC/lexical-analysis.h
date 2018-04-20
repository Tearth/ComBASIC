/**
* @file lexical-analysis.h
* @brief Lexical analysis is the first phase of compilation. It takes a input file and splits it to a set of
*		 tokens which contains type and value. These tokens are grouped into vector and passend next to the syntax
*		 analysis.
*
* @code
* 10 PRINT "Hello", x
* @endcode
* is translated to
* @code
* [line_number, 10] [keyword PRINT] [string Hello] [comma] [identifier x] [end_of_instruction]
* @endcode
*/

#pragma once

/**
* @brief The max keywords count in the array.
*/
#define MAX_KEYWORDS_TOKENS_COUNT 64

#include <ctype.h>
#include <string.h>
#include "lexical-token.h"
#include "vector.h"
#include "string.h"

/**
* @brief Converts an input file into the vector of tokens.
* @param source The BASIC source code.
* @return Vector of tokens.
*/
vector* lexical_gettokens(const char* source);

/**
* @brief Tries to read a word and shifts source pointor to the next unparsed char.
* @param source The BASIC source code.
* @param length The source code length.
* @return The pointer to the read lexical token.
*/
lexical_token* lexical_readword(const char* source, int* length);

/**
* @brief Tries to read a number and shifts source pointor to the next unparsed char.
* @param source The BASIC source code.
* @param length The source code length.
* @return The pointer to the read lexical token.
*/
lexical_token* lexical_readnumber(const char* source, int* length);

/**
* @brief Tries to read an operator and shifts source pointor to the next unparsed char.
* @param source The BASIC source code.
* @param length The source code length.
* @return The pointer to the read lexical token.
*/
lexical_token* lexical_readoperator(const char* source, int* length);

/**
* @brief Checks if there is end_of_instruction token at the end of the vector of tokens. If not, then it's added.
* @param tokens_vector The vector of tokens.
*/
void lexical_checklasttoken(vector* tokens_vector);

/**
* @brief Checks if the keyword exists.
* @param keyword The keyword to check.
* @return True if the keyword exists, otherwise false.
*/
bool lexical_keywordexists(const char* keyword);

/**
* @brief Checks if the operator exists.
* @param operator The operator to check.
* @return True if the operator exists, otherwise false.
*/
bool lexical_operatorexists(const char* operator);

/**
* @brief Checks if the unary operator exists.
* @param operator The unary operator to check.
* @return True if the unary operator exists, otherwise false.
*/
bool lexical_isunaryoperator(const char* operator);

/**
* @brief Loops over vector of tokens and merges keywords if possible (e.g. END, IF is merged to one ENDIF).
* @param tokens_vector The vector of tokens.
*/
void lexical_mergekeywords(vector* tokens_vector);

/**
* @brief Loops over vector of tokens and merges operators if possible (e.g. =, > is merged to one =>).
* @param tokens_vector The vector of tokens.
*/
void lexical_mergeoperators(vector* tokens_vector);

/**
* @brief Loops over vector of tokens and converts unary operators to normal (e.g. -5 is converted to (0 - 5)).
* @param tokens_vector The vector of tokens.
*/
void lexical_fixunaryoperators(vector* tokens_vector);

/**
* @brief Prints all tokens contained in the passed vector
* @param tokens The vector of tokens to dump.
*/
void lexical_dump(vector* tokens);

/**
* @brief Clears the vector of tokens.
* @param tokens The vector to clear
*/
void lexical_clear(vector* tokens);