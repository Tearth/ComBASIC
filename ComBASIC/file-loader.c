#include "file-loader.h"

const char* file_load(const char* filename)
{
	char* buffer = NULL;
	int length = 0;

	FILE* source = fopen(filename, "r");
	if (!source)
	{
		printf("Unable to load file.\n");
		return NULL;
	}

	fseek(source, 0, SEEK_END);
	length = ftell(source);
	fseek(source, 0, SEEK_SET);

	buffer = (char*)calloc(length, sizeof(char));
	fread(buffer, sizeof(char), length, source);

	fclose(source);

	return buffer;
}