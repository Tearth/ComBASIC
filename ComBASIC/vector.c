#include "vector.h"

void vector_init(vector* vector)
{
	vector->data = NULL;
	vector->size = 0;
	vector->count = 0;
}

int vector_size(vector* vector)
{
	return vector->size;
}

int vector_count(vector* vector)
{
	return vector->count;
}

void vector_add(vector* vector, void* data)
{
	if (vector->size == 0)
	{
		vector->size = 8;
		vector->data = malloc(sizeof(void*) * vector->size);
	}

	if (vector->count + 1 > vector->size)
	{
		vector->size *= 2;
		vector->data = realloc(vector->data, sizeof(void*) * vector->size);
	}

	vector->data[vector->count] = data;
	vector->count++;
}

void* vector_get(vector* vector, int index)
{
	if (index >= vector->count)
	{
		return NULL;
	}

	return vector->data[index];
}

void vector_set(vector* vector, int index, void* data)
{
	if (index >= vector->count)
	{
		return;
	}

	vector->data[index] = data;
}

void vector_remove(vector* vector, int index)
{
	if (index >= vector->count)
	{
		return;
	}

	for (int i = index; i < vector->count - 1; i++)
	{
		vector->data[i] = vector->data[i + 1];
	}

	vector->count--;
}

void vector_free(vector* vector)
{
	if (vector->size > 0)
	{
		vector->size = 0;
		vector->count = 0;
		free(vector->data);
	}
}

void vector_dump(vector* vector)
{
	for (int i = 0; i < vector->count; i++)
	{
		printf("[%d] %s\n", i, vector->data[i]);
	}
}