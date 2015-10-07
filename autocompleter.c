#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "autocompleter.h"

// The newNode function acts like the default constructor for a Node object.
// Arguments: The data argument represents the character to be added.
// Returns: A Node pointer to the newly created node object
struct Node* newNode(char data)
{
    struct Node* temp = (struct Node*) malloc(sizeof( struct Node ));
    if (!temp) {
      printf("[ERROR]: Unable to allocate memory properly... Exiting!\n");
      exit(EXIT_FAILURE);
    }
    temp->data = data;
    temp->flag = 0;
    temp->left = NULL;
    temp->center = NULL;
    temp->right = NULL;
    return temp;
}

// The insert function recursively adds a string to the ternary tree.
// Arguments: The root argument represents the node in the tree to which the addition is performed (left or right)
// Arguments: The word argument stands for the string which will be added.
// Returns: A Node double pointer to the node on which insertion was performed.
struct Node** insert(struct Node** root, char *word)
{
        // Base Case: Tree is empty
    if (!(*root))
        *root = newNode(*word);

    // If current character of word is smaller than root's character,
    // then insert this word in left subtree of root
    if ((*word) < (*root)->data)
        root=insert(&( (*root)->left ), word);

    // If current character of word is greate than root's character,
    // then insert this word in right subtree of root
    else if ((*word) > (*root)->data)
        root=insert(&( (*root)->right ), word);

    // If current character of word is same as root's character,
    else
    {
        if (*(word+1))
            root=insert(&( (*root)->center ), word+1);

        // the last character of the word
        else
            (*root)->flag = 1;
    }
    return root;
}


// The dfs function performs a recursive depth first search on the ternary tree.
// Arguments: The root argument represents the root node from which depth-first search is performed.
// Arguments: The buffer argument stands for the suffix to be searched for string completion.
// Arguments: The depth argument stands for the length of the suffix to be searched for string completion.
// Arguments: The input argument stands for the prefix input by the user.
// Returns: None
void dfs(struct Node* root, char* buffer, int depth, char* input)
{
     // printf("IN DFS BUFFER %s\n", buffer);
     if (root)
    {
        // First traverse the left subtree
        dfs(root->left, buffer, depth, input);

        // Store the character of this node
        buffer[depth] = root->data;
        if (root->flag)
        {
            char outstr[65536]="";
            buffer[depth+1]='\0';
            strncat(outstr, input, strlen(input));
            strncat(outstr, buffer, strlen(buffer));
            printf( "%s\n", outstr);
        }

        // Traverse the subtree using equal pointer (middle subtree)
        dfs(root->center, buffer, depth+1, input);

        // Finally Traverse the right subtree
        dfs(root->right, buffer, depth, input);
    }
}

// The searchTST function recursively searches the TST for all possible completions.
// Arguments: The root argument represents the root node from which the search is performed.
// Arguments: The word argument stands for the prefix input by the user.
// Arguments: The match argument stores the suffix to be searched for string completion.
// Arguments: The input argument stands for the prefix input by the user.
// Returns: Integer (1 for success, 0 for failure)
int searchTST(struct Node *root, char *word, char* match, char* input)
{

if (!root)
        return 0;

    if (*word < (root)->data) {
          if (root->left==NULL) {
            printf("No match found\n");
            return 0;
          }
        return searchTST(root->left, word, match, input);
    }

    else if (*word > (root)->data) {
         if (root->right==NULL) {
            printf("No match found\n");
            return 0;
          }
        return searchTST(root->right, word, match, input);
    }

    else
    {
        if (strlen(word)==1) {
          if (root->center) {
            char buf[256]="";
            strcat(buf, match);
            strcat(buf,&(root->data));
            strcat(buf,&(root->center->data));
            dfs(root->center, buf,0, input);
          }
            return 1;
        }
        char buf[256]="";
        strcat(buf, match);
        strcat(buf,word);
        return searchTST(root->center, word+1, buf, input);
    }
 }

// The freeTST function recursively deallocates memory for the TST.
// Arguments: The root node represents the node from the recursive deallocation takes place.
// Returns: None.
void freeTST(struct Node* root)
{
        if (root->center ==  NULL && root->left == NULL && root->right == NULL) free(root);

        if (root->center != NULL) {
            freeTST(root->center);
        }

        if (root->right != NULL){
            freeTST(root->right);
        }

      if (root->left != NULL){
            freeTST(root->left);
        }

}
