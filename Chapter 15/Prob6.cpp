#include <cstdio>
#include <map>
#include <vector>

using namespace std;

struct node
{
    int id;
    int conviviality;
    node* child;
    node* sibling;
};

void planning_party(map<int, int>& saved, vector<int>& list, node* root)
{
    if (root && root->child)
    {
        planning_party(saved, list, root->child);

        int selected = root->conviviality, unselected = 0;
        if (root->child->child)
        {
            node* current = root->child->child;
            while (current)
            {
                selected += saved[current->id];
                current = current->sibling;
            }
        }

        node* current = root->child;
        while (current)
        {
            unselected += saved[current->id];
            current = current->sibling;
        }

        saved[root->id] = unselected > selected ? unselected : selected;
        if (unselected <= selected)
            list.push_back(current->id);

        planning_party(saved, list, root->sibling);        
    }
    else if (root)
    {
        if (root->conviviality >= 0)
            saved[root->id] = root->conviviality;
        else
            saved[root->id] = 0;
    }   
}

node* build_tree()
{
    node* current = nullptr;

    node* root = new node;
    root->id = 0;
    root->conviviality = 40;
    root->child = new node;
    root->sibling = nullptr;

// rather dull contents
#pragma region
    current = root->child;
    current->id = 1;
    current->conviviality = -30;
    current->child = new node;
    current->sibling = new node;

    current = current->sibling;
    current->id = 47;
    current->conviviality = 4;
    current->child = new node;
    current->sibling = new node;

    current = current->sibling;
    current->id = 99;
    current->conviviality = 49;
    current->child = new node;
    current->sibling = nullptr;

    current = current->child;
    current->id = 30;
    current->conviviality = 28;
    current->child = nullptr;
    current->sibling = nullptr;

    current = root->child->child;
    current->id = 56;
    current->conviviality = 77;
    current->child = nullptr;
    current->sibling = new node;

    current = current->sibling;
    current->id = 90;
    current->conviviality = -4;
    current->child = new node;
    current->sibling = nullptr;

    current = current->child;
    current->id = 4000;
    current->conviviality = 68;
    current->child = nullptr;
    current->sibling = nullptr;

    current = root->child->sibling->child;
    current->id = 8;
    current->conviviality = 10;
    current->child = nullptr;
    current->sibling = new node;

    current = current->sibling;
    current->id = 5;
    current->conviviality = 1;
    current->child = nullptr;
    current->sibling = new node;

    current = current->sibling;
    current->id = 2;
    current->conviviality = 37;
    current->child = new node;
    current->sibling = new node;

    current = current->sibling;
    current->id = 66;
    current->conviviality = 48;
    current->child = nullptr;
    current->sibling = nullptr;

    current = root->child->sibling->child->sibling->sibling;
    current->id = 25;
    current->conviviality = 73;
    current->child = nullptr;
    current->sibling = new node;

    current = current->sibling;
    current->id = 23;
    current->conviviality = 33;
    current->child = nullptr;
    current->sibling = nullptr;
#pragma endregion

    return root;
}

void free_tree(node* root)
{
    if (root)
    {
        free_tree(root->child);
        free_tree(root->sibling);
        delete root;
    }
}

int main()
{
    map<int, int> saved;
    vector<int> list;

    node* root = build_tree();
    planning_party(saved, list, root);

    printf("%d\n", saved[root->id]);
    for (int i : list)
        printf("%d ", i);
    
    free_tree(root);
    return 0;
}