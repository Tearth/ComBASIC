/**
* @file file-manager.h
* @brief Basic functions to load and save files.
*/

#pragma once
#include <stdlib.h>
#include <stdio.h>

/**
* @brief Loads a content of the specified file and returns it as string array. If file doesn't exists, then error
*		 message is printed and app is closed.
* @param filename Path to the specified file.
* @return The file content.
*/
const char* file_load(const char* filename);

/**
* @brief Saves a content to the specified file. Note that previous data will be erased.
*		 If file doesn't exists, then error message is printed and app is closed.
* @param filename Path to the specified file.
* @param content The content to save.
* @param length The content length.
*/
void file_save(const char* filename, const char* content, int length);