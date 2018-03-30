#include "file-manager.h"

const char* file_load(const char* filename)
{
	FILE* source = NULL;
	char* buffer = NULL;
	int length = 0;

	if (fopen_s(&source, filename, "r") != 0)
	{
		printf("ERROR: Unable to load file %s.\n", filename);
		exit(-1);
	}

	fseek(source, 0, SEEK_END);
	length = ftell(source);
	fseek(source, 0, SEEK_SET);

	buffer = (char*)calloc(length, sizeof(char));
	fread(buffer, sizeof(char), length, source);

	fclose(source);

	return buffer;
}

void file_save(const char* filename, const char* content, int length)
{
	FILE* file = NULL;
	if (fopen_s(&file, filename, "w+") != 0)
	{
		printf("ERROR: Unable to save file %s.\n", filename);
		exit(-1);
	}

	fwrite(content, sizeof(char), length, file);
	fclose(file);
}