#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC 
#include <crtdbg.h>  
#endif

#include <stdio.h>
#include <stdbool.h>
#include "file-manager.h"
#include "symbol-table.h"
#include "lexical-analysis.h"
#include "ast-builder.h"
#include "generator.h"

bool compile_flag = false;
bool display_debug_info = false;
char* input_filename = NULL;
char* output_filename = NULL;

void parse_arguments(int argc, char *argv[]);
void display_help();

int main(int argc, char *argv[])
{
	argc == 1 ? display_help() : parse_arguments(argc, argv);

	if (compile_flag)
	{
		if (!input_filename || !output_filename)
		{
			printf("Invalid -c usage, type -h for more information.");
			return;
		}

		printf("Starting compilation %s...\n", input_filename);
		printf("--------------------------------------------------------------\n");

		const char* source = file_load(input_filename);
		if (source)
		{
			vector symbol_table;
			vector_init(&symbol_table);

			vector* tokens = lexical_gettokens(source);
			if (display_debug_info) lexical_dump(tokens);

			ast_node* ast = ast_build(tokens, &symbol_table);
			if (display_debug_info) ast_dump(ast);
			if (display_debug_info) symboltable_dump(&symbol_table);

			string* asm_code = generator_build(ast, &symbol_table);
			file_save(output_filename, asm_code->data, asm_code->count);

			string_clean(asm_code);
			ast_clean(ast);
			symboltable_clean(&symbol_table);
			lexical_clean(tokens);

			free(asm_code);
			free(ast);
			free(tokens);
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

				case 'd':
				{
					display_debug_info = true;
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
	printf(" -d - display debug info.\n");
}