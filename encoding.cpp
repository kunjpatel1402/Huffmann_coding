#include <iostream>
#include <fstream>
#include "stack.h"

using namespace std;

void printInorder(node* root,string s){
    if (root == NULL)
        return;
    printInorder(root->left,(s + "1"));
    printInorder(root->right,(s + "0"));
    print_node(root);
    cout<<"\n"<<s<<endl;
}

node* create_tree(stack* s){
    int pause;
    (*s).sort();
    (*s).print();
    while(true){
        node* c1 = (*s).pop();
        node* c2 = (*s).pop();
        node* p = new node;
        p = create_node('\0',c1->probablity+c2->probablity,true);
        p->left = c1;
        p->right = c2;
        c1->parent = p;
        c2->parent = p;
        (*s).push(p);
        (*s).sort();
        (*s).print();
        cout<<"\n:";cin>>pause;
        if((*s).get_size() <= 1){
            break;
        }
    }
    return ((*s).pop());
}

int main(){
    stack s;
    s.push(create_node('a',0.125,false));
    s.push(create_node('b',0.125,false));
    s.push(create_node('c',0.25,false));
    s.push(create_node('d',0.50,false));
    printInorder(create_tree(&s),"");
    return 0;
}
