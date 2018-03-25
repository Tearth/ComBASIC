#pragma once
#include <stdlib.h>
#include <stdio.h>

typedef struct vector
{
	void** data;
	int size;
	int count;
} vector;

void vector_init(vector* vector);
int vector_size(vector* vector);
int vector_count(vector* vector);
void vector_add(vector* vector, void* data);
void* vector_get(vector* vector, int index);
void vector_set(vector* vector, int index, void* data);
void vector_remove(vector* vector, int index);
void vector_free(vector* vector);
void vector_dump(vector* vector);