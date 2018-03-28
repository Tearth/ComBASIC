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
string* string_clone(string* original);
void string_append_c(string* string, char c);
void string_append_s(string* string, const char* str);
void string_removelast(string* string);
void string_clean(string* string);