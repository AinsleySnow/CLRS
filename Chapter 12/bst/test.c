#include "BinarySearchTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main(void)
{
    int data[] = {2, 3, 4, 6, 7, 13, 9, 15, 18, 20, 17};
    node* root = calloc(1, sizeof(node));
    
    tree_build(root, data, 11);
    printf("Result of inorder_tree_walk:\n");
    inorder_tree_walk(root);

    tree_insert(root, 200);
    tree_insert(root, 57);
    tree_insert(root, 38);
    tree_insert(root, INT_MAX);

    printf("Tree Max: %d\n", tree_max(root)->key);
    printf("Tree Min: %d\n", tree_min(root)->key);

    node* search_result = tree_search(root, 4);
    printf("Search result for 4: %d\n", search_result->key);

    search_result = iterative_tree_search(root, -1);
    if(search_result)
        printf("This line should not emerge: %d\n");
    
    search_result = tree_search(root, 38);
    tree_delete(search_result);
    free(search_result);
    search_result = NULL;
    printf("What the tree like after the node with key 38 was deleted:\n");
    inorder_tree_walk(root);

    search_result = iterative_tree_search(root, INT_MAX);
    tree_delete(search_result);
    free(search_result);
    search_result = NULL;
    printf("What the tree like after the node with key INT_MAX was deleted:\n");
    inorder_tree_walk(root);

    delete_the_tree(&root);

    return 0;
}