#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "autocompleter.h"
#define CHUNK 1000

// Function prototypes
void fileparse(char *file, struct Node** root);
void split_data(char* file, int* total);
void read_data(struct Node** root, char* file, int* total);
void cleanup(char *file, int* total);




#endif // UTILS_H_INCLUDED
