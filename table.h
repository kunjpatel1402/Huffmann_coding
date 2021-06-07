#include <iostream>
#include "node.h"

using namespace std;

struct table_node{
    node* tree_node;
    table_node* next;
};

class table{
    table_node* head;
    int size;
    public:
    table(){
        head = NULL;
        size = 0;
    }
    //push elements at the end
    void push(node* new_node){
        table_node* temp = new table_node;
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
    //pop elements from the end
    node* pop(){
        if (head == NULL){
            return NULL;
        }
        else{
            table_node* temp = new table_node;
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
        table_node* parser = new table_node;
        parser = head;
        while(parser!=NULL){
            print_node(parser->tree_node);
            parser = parser->next;
        }
        cout<<"\n";
    }
    /*sorting data present in the table */
    void sort(){
        table_node* secondary_parser = new table_node;
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
    bool empty(){
        if (head == NULL) return true;
        else return false;
    }
    float top(){
        return head->tree_node->probablity;
    }
    int get_size(){
        return size;
    }
};


