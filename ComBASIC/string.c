#include "string.h"

void string_init(string* string)
{
	string->data = NULL;
	string->size = 0;
	string->count = 0;
}

string* string_clone(string* original)
{
	string* clone = (string*)malloc(sizeof(string));
	string_init(clone);

	string_append_s(clone, original->data);
	return clone;
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
	string->data[string->count + 1] = 0;
	string->count++;
}

void string_append_s(string* string, const char* str)
{
	while (*str != 0)
	{
		string_append_c(string, *str);
		str++;
	}
}

void string_removelast(string* string)
{
	string->data[string->count - 1] = 0;
	string->count--;
}

void string_removeall(string* string)
{
	string->data[0] = 0;
	string->count = 0;
}

void string_clear(string* string)
{
	if (string->size > 0)
	{
		free(string->data);
		string->size = 0;
		string->count = 0;
	}
}