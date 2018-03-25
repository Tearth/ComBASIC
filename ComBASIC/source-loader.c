#include "source-loader.h"

const char* source_load(const char* filename)
{
	char* buffer = NULL;
	int length = 0;

	FILE* source = fopen(filename, "r");
	if (source == NULL)
	{
		return NULL;
	}

	fseek(source, 0, SEEK_END);
	length = ftell(source);
	fseek(source, 0, SEEK_SET);

	buffer = (char*)calloc(length, sizeof(char));
	fread(buffer, sizeof(char), length, source);
	buffer[length] = '\0';

	fclose(source);

	return buffer;
}