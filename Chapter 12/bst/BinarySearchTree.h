#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

struct node
{
    int key;
    node* previous;
    node* left;
    node* right;
}typedef node node;

int tree_build(node*, int*, int);
void inorder_tree_walk(node*);
node* tree_search(node*, int);
node* iterative_tree_search(node*, int);
node* tree_min(node*);
node* tree_max(node*);
node* inorder_tree_successor(node*);
int tree_insert(node*, int);

#endif //BINARY_SEARCH_TREE_H