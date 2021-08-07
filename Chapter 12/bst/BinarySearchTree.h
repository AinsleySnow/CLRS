#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

typedef struct node
{
    int key;
    struct node* previous;
    struct node* left;
    struct node* right;
} node;

int tree_build(node*, int*, int);
void inorder_tree_walk(node*);
void delete_the_tree(node**);
node* tree_search(node*, int);
node* iterative_tree_search(node*, int);
node* tree_min(node*);
node* tree_max(node*);
node* inorder_tree_successor(node*);
void tree_delete(node*);
int tree_insert(node*, int);

#endif //BINARY_SEARCH_TREE_H