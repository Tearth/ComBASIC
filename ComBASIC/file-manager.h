#pragma once
#include <stdlib.h>
#include <stdio.h>

const char* file_load(const char* filename);
void file_save(const char* filename, const char* content, int length);