#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC 
#include <crtdbg.h>  
#endif

#include <stdio.h>
#include <stdbool.h>
#include "file-loader.h"
#include "grammar-loader.h"
#include "lexical-analysis.h"

bool compile_flag = false;
bool display_tokens_flag = false;
bool display_grammar_tokens_flag = false;
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

	if (compile_flag)
	{
		if (input_filename == NULL || output_filename == NULL)
		{
			printf("Invalid -c usage, type -h for more information.");
			return;
		}

		printf("Starting compilation %s...\n", input_filename);
		printf("--------------------------------------------------------------\n");

		const char* source = file_load(input_filename);
		vector* grammar_tokens = grammar_load("grammar.txt");

		if (source != NULL)
		{
			//vector* tokens = lexical_gettokens(source);
			//if (display_tokens_flag) lexical_dump(tokens);
			//if (display_grammar_tokens_flag) grammar_dump(grammar_tokens);

			grammar_free(grammar_tokens);

			free(grammar_tokens);
			free((char*)source);
		}
	}

#ifdef _DEBUG
	_CrtDumpMemoryLeaks();
#endif

	system("pause");
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
					compile_flag = true;
					break;
				}

				case 't':
				{
					display_tokens_flag = true;
					break;
				}

				case 'g':
				{
					display_grammar_tokens_flag = true;
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
	printf(" -t - displays tokens.\n");
	printf(" -g - displays grammar tokens.\n");
}