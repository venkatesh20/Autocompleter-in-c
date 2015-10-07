#ifndef AUTOCOMPLETER_H_INCLUDED
#define AUTOCOMPLETER_H_INCLUDED

// The Node class implements the standard node in a ternary tree.
// A ternary tree is similar to a binary tree, except each node has 3 children instead of two.
// The left child is alphabetically lower in order than the center and right children.
// Each Node consist of the center, left and right pointers.
// node->data => contains the character.
// node->flag => Flag to Check whether the node is an end character of a valid string.
// node->left, node->right => Links to the next nodes.
// node->center => Link to the next valid character.

struct Node
{
    char data;
    unsigned flag;
    struct Node *left, *center, *right;
};

// Function prototypes
struct Node* newNode(char data);
struct Node** insert(struct Node** root, char *word);
void dfs(struct Node* root, char* buffer, int depth, char* input);
void traverseTST(struct Node* root);
int searchTST(struct Node *root, char *word, char *match, char* input);
void freeTST(struct Node* root);



#endif // AUTOCOMPLETER_H_INCLUDED
