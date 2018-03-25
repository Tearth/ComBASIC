#pragma once
#include <stdlib.h>
#include <stdbool.h>

typedef struct string
{
	char* data;
	int size;
	int count;
} string;

void string_init(string* string);
int string_size(string* string);
int string_count(string* string);
void string_append_c(string* string, char c);
void string_append_s(string* string, const char* str);
const char* string_get(string* string);
void string_free(string* string);