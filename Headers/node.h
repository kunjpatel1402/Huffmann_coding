#include <iostream>

using namespace std;

struct node{
    node* parent;
    node* left;
    node* right;
    char symbol;
    float probablity;
    bool dummy;
    int node_number;
};

node* create_node(char symbol, float probablity,bool dummy,node* left_node = NULL,node* right_node = NULL,node* parent_node = NULL){
    node* temp = new node;
    temp->symbol = symbol;
    temp->probablity = probablity;
    temp->dummy = dummy;
    temp->left = left_node;
    temp->parent = parent_node;
    temp->right = right_node;
    return temp;
}

void print_node(node* tree_node){
    cout<<"\n\nsymbol:"<<tree_node->symbol;
    cout<<"\nprobablity:"<<tree_node->probablity;
    cout<<"\nparent:"<<tree_node->parent;
    cout<<"\nleft:"<<tree_node->left;
    cout<<"\nright:"<<tree_node->right;
    cout<<"\ndummy:"<<tree_node->dummy;
}
