#include <stdio.h>
#include <stdbool.h>
#include "source-loader.h"
#include "lexical-analysis.h"

bool compile = false;
char* input_filename = NULL;
char* output_filename = NULL;

void parse_arguments(int argc, char *argv[]);
void display_help();

int main(int argc, char *argv[])
{
	if (argc == 1)
	{
		display_help();
	}
	else
	{
		parse_arguments(argc, argv);
	}

	if (compile)
	{
		if (input_filename == NULL || output_filename == NULL)
		{
			printf("Invalid -c usage, type -h for more information.");
			return;
		}

		const char* source = source_load(input_filename);
		if (source != NULL)
		{
			vector* tokens = lexical_gettokens(source);
		}
	}

	return 0;
}

void parse_arguments(int argc, char *argv[])
{
	for (int i = 0; i < argc; i++)
	{
		if (argv[i][0] == '-')
		{
			switch (argv[i][1])
			{
				case 'h':
				{
					display_help();
					break;
				}

				case 'c':
				{
					compile = true;
					break;
				}

				case 'i':
				{
					if (i + 1 >= argc)
					{
						printf("Invalid -i usage, type -h for more information.");
						break;
					}

					input_filename = argv[i + 1];
					break;
				}

				case 'o':
				{
					if (i + 1 >= argc)
					{
						printf("Invalid -o usage, type -h for more information.");
						break;
					}

					output_filename = argv[i + 1];
					break;
				}
			}
		}
	}
}

void display_help()
{
	printf("ComBASIC - a BASIC compiler based on Altair dialect\n");
	printf("Available options:\n");
	printf(" -h - display help.\n");
	printf(" -c [-i input_filename -o output_filename] - compile a source file to the specified output.\n");
}