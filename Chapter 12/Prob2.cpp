#include <iostream>
#include <string>

using namespace std;

struct radix_node
{
    bool hasValue;
    radix_node* left;
    radix_node* right;
};

void build_radix_tree(radix_node* head, string value[], int size)
{
    if(head == nullptr)
        return;

    for(int k = 0; k < size; ++k)
    {
        radix_node* current = head;
        for(int i = 0; i < value[k].length(); ++i)
        {
            if(value[k][i] == '0')
            {
                if(current->left == nullptr)
                    current->left = new radix_node{false, nullptr, nullptr};
                current = current->left;
            }  
            else if(value[k][i] == '1')
            {
                if(current->right == nullptr)
                    current->right = new radix_node{false, nullptr, nullptr};
                current = current->right;
            }
            else
                throw "ValueError!";
        }
        current->hasValue = true;
    }
}

void delete_radix_tree(radix_node** head)
{
    if(*head != nullptr)
    {
        delete_radix_tree(&((*head)->left));
        delete_radix_tree(&((*head)->right));
        delete *head;
        *head = nullptr;
    }
}

void sort_radix_tree(radix_node* head, string value)
{
    if(head != nullptr)
    {
        if(head->hasValue)
            cout << value << endl; 
        sort_radix_tree(head->left, value + "0");
        sort_radix_tree(head->right, value + "1");
    }
}

int main()
{
    radix_node* head = new radix_node{false,nullptr,nullptr};
    string values[] = {"0", "011", "10", "100", "1011"};
    build_radix_tree(head, values, 5);
    sort_radix_tree(head, "");
    delete_radix_tree(&head);
    return 0;
}