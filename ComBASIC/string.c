#include "string.h"

void string_init(string* string)
{
	string->data = NULL;
	string->size = 0;
	string->count = 0;
}

int string_size(string* string)
{
	return string->size;
}

int string_count(string* string)
{
	return string->count;
}

void string_append_c(string* string, char c)
{
	if (string->size == 0)
	{
		string->size = 8;
		string->data = (char*)malloc(sizeof(char) * string->size);
	}

	if (string->count + 1 >= string->size)
	{
		string->size *= 2;
		string->data = (char*)realloc(string->data, sizeof(char) * string->size);
	}

	string->data[string->count] = c;
	string->data[string->count + 1] = '\0';
	string->count++;
}

void string_append_s(string* string, const char* str)
{
	while (*str != '\0')
	{
		string_append_c(string, *str);
		str++;
	}
}

const char* string_get(string* string)
{
	return string->data;
}

void string_free(string* string)
{
	if (string->size > 0)
	{
		string->size = 0;
		string->count = 0;
		free(string->data);
	}
}