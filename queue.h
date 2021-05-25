#include <iostream>

using namespace std;

struct queue_node{
    int data;
    queue_node *next;
    queue_node *prev;
};
class intqueue{
    queue_node *head,*last;
    int size;
    public:
    intqueue();
    bool empty();
    void create();
    void enqueue(int val);
    int dequeue();
    int front();
    void print();
    int get_size();
};

intqueue::intqueue(){
    head = NULL;
    last = NULL;
    size = 0;
}
void intqueue::create(){
    head = NULL;
    last = NULL;
    size = 0;
}
bool intqueue::empty(){
    if (head == NULL){
        return true;
    }
    return false;
}
void intqueue::enqueue(int val){
    queue_node* temp = new queue_node;
    temp->data = val;
    temp->next = NULL;
    temp->prev = NULL;
    size++;
    if (head == NULL){
        head = temp;
        last = temp;
    }
    else{
        last->next = temp;
        temp->prev= last;
        last = temp;
    }
}
int intqueue::dequeue(){
    if (empty()){
        return -1;
    }
    else{
        int ret = head->data;
        queue_node* temp = new queue_node;
        temp = head;
        head = head->next;
        size--;
        /*head->prev = NULL;
        temp->next = NULL;*/
        delete temp;
        return ret;
    }
}
int intqueue::front(){
    if (empty()){
        return -1;
    }
    else{
        return head->data;
    }
}
void intqueue::print(){
    queue_node* temp = new queue_node;
    temp = head;
    while(temp){
        cout<<" "<<temp->data;
        temp = temp->next;
    }
    cout<<endl;
}
int intqueue::get_size(){
    return size;
}
