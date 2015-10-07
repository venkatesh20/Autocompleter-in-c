// This code implements an auto-completer using the ternary tree data structure.
// For more information, please check out: http://en.wikipedia.org/wiki/Ternary_search_tree

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "autocompleter.h"
#include "utils.h"

int main()
{
    char file[1024], input[32768];
    int total=0;
    struct Node *root = NULL;

    printf("Welcome to the autocomplete program.\nPlease enter the full path to the database file containing the list of reference phrases, and press ENTER:\n");
    fgets(file, 1024, stdin);
    printf("[INFO]: Loading database file %s containing list of phrases into memory ...\n", file);
    strtok(file,"\r\n");
    split_data(file, &total);
    read_data(&root,file, &total);

    printf("[INFO]: Finished loading database file.\n");

    printf("Please type the prefix of a word (more than one character) and press ENTER:\n");
    fgets(input, 32768, stdin);
    if (strlen(input)> 32768) {
      printf("Prefix size is limited to 32768 characters only. Please reduce accordingly. Exiting ..!\n");
      exit(EXIT_FAILURE);
    }
    while(strcmp(input,"")>0) {
     if (strcmp(input,"quit\n")!=0) {
        //printf("You entered %s\n", input);
        strtok(input,"\r\n");
        char buffer[32767]="";
        strncpy(buffer, input, strlen(input));
        printf("\nSuggestions:\n");
        searchTST(root,input,"", buffer);
        printf("\nPlease type the prefix of a word (more than one character and no more than 32768 characters) :\n");
        fgets(input, 32768, stdin);
      }  else {
       printf("Exiting the program\n");
       break;
      }
    }

    printf("Freeing memory ...\n");
    freeTST(root);
    cleanup(file,&total);
    printf("Freeing memory done\n");

    return 0;
}
