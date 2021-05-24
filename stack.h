#include <iostream>
#include "node.h"

using namespace std;

struct stack_node{
    node* tree_node;
    stack_node* next;
};

class stack{
    stack_node* head;
    int size;
    public:
    stack(){
        head = NULL;
        size = 0;
    }
    void push(node* new_node){
        stack_node* temp = new stack_node;
        temp->tree_node = new_node;
        temp->next = NULL;
        size++;
        if (head == NULL){
            head = temp;
        }
        else{
            temp->next = head;
            head = temp;
        }
    }
    node* pop(){
        if (head == NULL){
            return NULL;
        }
        else{
            stack_node* temp = new stack_node;
            temp = head;
            node* return_node = new node;
            return_node = temp->tree_node;
            temp = head;
            head = head->next;
            delete temp;
            size--;
            return return_node;
        }
    }
    void clear(){
        head = NULL;
        size = 0;
    }
    void print(){
        stack_node* parser = new stack_node;
        parser = head;
        while(parser!=NULL){
            print_node(parser->tree_node);
            parser = parser->next;
        }
        cout<<"\n";
    }
    void sort(){
        stack_node* secondary_parser = new stack_node;
        while(true){
            secondary_parser = head;
            bool flag = true;
            while(secondary_parser->next!=NULL){
                if ((secondary_parser->tree_node->probablity) > (secondary_parser->next->tree_node->probablity)){
                    node* temp_parent = secondary_parser->tree_node->parent;
                    node* temp_left = secondary_parser->tree_node->left;
                    node* temp_right = secondary_parser->tree_node->right;
                    char temp_symbol = secondary_parser->tree_node->symbol;
                    float temp_probablity = secondary_parser->tree_node->probablity;
                    bool temp_dummy = secondary_parser->tree_node->dummy;
                    
                    secondary_parser->tree_node->parent = secondary_parser->next->tree_node->parent;
                    secondary_parser->tree_node->left = secondary_parser->next->tree_node->left;
                    secondary_parser->tree_node->right = secondary_parser->next->tree_node->right;
                    secondary_parser->tree_node->symbol = secondary_parser->next->tree_node->symbol;
                    secondary_parser->tree_node->probablity = secondary_parser->next->tree_node->probablity;
                    secondary_parser->tree_node->dummy = secondary_parser->next->tree_node->dummy;

                    secondary_parser->next->tree_node->parent = temp_parent;
                    secondary_parser->next->tree_node->left = temp_left;
                    secondary_parser->next->tree_node->right = temp_right;
                    secondary_parser->next->tree_node->symbol = temp_symbol;
                    secondary_parser->next->tree_node->probablity = temp_probablity;
                    secondary_parser->next->tree_node->dummy = temp_dummy;
                    flag = false;
                };
                secondary_parser = secondary_parser->next;
            }
            if (flag){
                break;
            }
        }
    }
    int get_size(){
        return size;
    }
};



