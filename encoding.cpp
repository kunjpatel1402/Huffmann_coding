#include <iostream>
#include <fstream>
#include <math.h>
#include "stack.h"
#include "queue.h"

using namespace std;

void printInorder(node* root,string s,string* binary_code_for_the_character){
    if (root == NULL)
        return;
    printInorder(root->left,(s + "1"),binary_code_for_the_character);
    printInorder(root->right,(s + "0"),binary_code_for_the_character);
    //print_node(root);
    //cout<<"\n"<<s<<endl;
    binary_code_for_the_character[root->symbol] = s;
}

node* create_tree(stack* s){
    int pause;
    (*s).sort();
    //(*s).print();
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
        //(*s).print();
        //cout<<"\n:";
        //cin>>pause;
        if((*s).get_size() <= 1){
            break;
        }
    }
    return ((*s).pop());
}

void add_to_queue(intqueue* q,string str){
    for (unsigned long long i = 0;i < str.length();i++){
        if (str[i]=='1'){
            q->enqueue(1);
        }
        else{
            q->enqueue(0);
        }
    }
}

unsigned int bin2uint(intqueue* q){
    unsigned int ret = 0;
    for(int i = 31; i >= 0 && !(*q).empty(); i--){
        ret += ((*q).dequeue())*pow(2,i);
        //cout<<ret<<endl;
        //(*q).print();
    }
    //(*q).print();
    //cout<<"\n function returned"<<endl;
    return ret;
}

void count_character_frequencies(string filename, unsigned long long int* freq_of_character, unsigned long long int* freq_of_next_line,unsigned long long int* total_frequency){
    ifstream fin(filename);
    string s;
    while (true){
        getline(fin,s);
        (*freq_of_next_line)++;
        (*total_frequency)++;
        if (fin.eof()) break;
        for ( unsigned long long int i = 0; i < s.length(); i++){
            freq_of_character[s[i]]++;
            (*total_frequency)++;
        }
    }
    fin.close();
}

int main(){
    string binary_code_for_character[256]={""};
    unsigned long long int freq_of_character[256] = {0},freq_of_next_line = 0,total_frequency = 0;
    count_character_frequencies("test.txt",freq_of_character,&freq_of_next_line,&total_frequency);
    for (unsigned long long int i = 0; i < 256; i++){
        cout<<(char)i<<" "<<freq_of_character[i]<<endl;
    }
    cout<<freq_of_next_line<<endl;
    cout<<total_frequency<<endl;
    return 0;
}
