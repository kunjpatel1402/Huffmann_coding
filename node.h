struct node{
    node* parent;
    node* left;
    node* right;
    char symbol;
    float probablity;
    bool dummy;
};

node* create_node(char symbol, float probablity,bool dummy){
    node* temp = new node;
    temp->symbol = symbol;
    temp->probablity = probablity;
    temp->dummy = dummy;
    temp->left = nullptr;
    temp->parent = nullptr;
    temp->right = nullptr;
    return temp;
}