#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "autocompleter.h"
#include "utils.h"

// The split_data function splits the large file of all phrases into smaller chunks of 1000 lines each and creates new files.
// Arguments: The file argument stands for the file to be parsed.
// Arguments: The total argument stands for the total number of files created.
// Returns: None
void split_data(char* file, int *total) {
    FILE *fp, *fp1;
    char line[32767];

     if ((fp = fopen(file,"r")) == NULL)
      {
      printf("Exiting to system.");
      exit(EXIT_FAILURE);
      }

  int fid=1, linecount=0;
  char newfile[2048]="";
  strncpy(newfile,file,strlen(file));
  newfile[strlen(newfile)-4]='\0';
  char str[15];
  sprintf(str, "%d", fid);
  strcat(newfile,str);
  strcat(newfile,".txt");
  fp1=fopen(newfile,"w");
  while (fscanf(fp, "%s", line) != EOF) {
     linecount++;
     fprintf(fp1,"%s\n",line);
     if (!(linecount%CHUNK) && (linecount>1)) {
        fclose(fp1);
        printf("FILE WAS %s\n", newfile);
        fid+=1;
        memset(&newfile[0], 0, sizeof(newfile));
        strncpy(newfile,file,strlen(file));
        newfile[strlen(newfile)-4]='\0';
        memset(&str[0], 0, sizeof(str));
        sprintf(str, "%d", fid);
        strcat(newfile,str);
        strcat(newfile,".txt");
        fp1=fopen(newfile,"w");
     }
  }
  fclose(fp1);
  fclose(fp);
  *total=fid-1;
}

// The read_data function reads all of the files created by split_data above, one at a time, and builds the ternary tree.
// Arguments: The root argument stands for the root of the ternary tree.
// Arguments: The file argument stands for the file containing the list of reference phrases to be parsed.
// Arguments: The total argument stands for the total number of files created using split_data above.
// Returns: None
void read_data(struct Node** root, char* file, int *total) {

  int fid=1;
  char newfile[2048]="";

  while (fid<=*total) {
       memset(&newfile[0], 0, sizeof(newfile));
       strncpy(newfile,file,strlen(file));
       newfile[strlen(newfile)-4]='\0';
       char str[15];
       sprintf(str, "%d", fid);
       strcat(newfile,str);
       strcat(newfile,".txt");
       fileparse(newfile,root);
       fid+=1;
  }
}

// The fileparse function parses each file and builds the ternary tree by using the insert helper function for each Node object.
// Arguments: The file argument stands for the file to be parsed.
// Arguments: The root argument stands for the node which will be created.
// Returns: None
void fileparse(char *file, struct Node** root) {

    FILE *fp;
    char line[32767];
     printf("Reading file %s\n", file);
     if ((fp = fopen(file,"r")) == NULL)
      {
      printf("Exiting to system.");
      exit(EXIT_FAILURE);
      }

    while (fscanf(fp, "%s", line) != EOF) {
             if (strlen(line)>32767) {
               printf("Current phrase longer than 32767 characters, skipping it ...\n");
               continue;
             }
             strtok(line,"\r\n");
             line[strlen(line)+1]='\0';
             insert(root, line);
    }
    fclose(fp);
}

// The cleanup function removes the files created by split_data above.
// Arguments: The file argument stands for the filename containing the list of reference phrases to be parsed.
// Arguments: The total argument stands for the total number of files created using split_data above.
// Returns: None.
void cleanup(char *file, int* total) {

  int fid=1;
  char newfile[2048]="";

  while (fid<=*total+1) {
       memset(&newfile[0], 0, sizeof(newfile));
       strncpy(newfile,file,strlen(file));
       newfile[strlen(newfile)-4]='\0';
       char str[15];
       sprintf(str, "%d", fid);
       strcat(newfile,str);
       strcat(newfile,".txt");
       int status = remove(newfile);
       if( status == 0 )
           printf("%s file deleted successfully.\n",newfile);
       else
      {
          printf("Unable to delete the file %s\n", newfile);
          perror("Error");
      }
       fid+=1;
  }
}


