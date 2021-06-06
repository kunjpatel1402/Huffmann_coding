#include <iostream>
#include <fstream>
#include <math.h>
#include "table.h"
#include "queue.h"

using namespace std;

void progress_bar(int completed){
    //cout<<completed<<endl;
    //int pause;
    //cout<<":";cin>>completed;
    for (int i = 0; i < completed;i++){
        cout<<"|";
    }
    for (int i = completed; i < 100; i++){
        cout<<" ";
    }
    cout<<"|";
    cout<<" compressing file\r";
    //for(int i =0 ; i < 1000; i++);
    //cout<<"\r";
    //cout<<":";cin>>completed;
}

void clear(){
    cout<<"\r";
    for (int i = 0; i < 170; i++){
        cout<<" ";
    }
    cout<<"\n->file compressed"<<endl;
}

void printPreorder(node* root,string s,string* binary_code_for_the_character,int* nodes_in_tree){
    if (root == NULL)
        return;
    if(root->symbol!='\0')
        binary_code_for_the_character[root->symbol] = s;
    (*nodes_in_tree)++;
    root->node_number = *nodes_in_tree;
    printPreorder(root->left,(s + "1"),binary_code_for_the_character,nodes_in_tree);
    printPreorder(root->right,(s + "0"),binary_code_for_the_character,nodes_in_tree);
}

node* create_tree(table* s){
    int pause = 0;
    //(*s) = (*s).sort_table();
    (*s).sort();
    while(true){
        if ((*s).get_size() < 2){
            cout<<"\nERROR"<<endl;
        }
        node* c1 = (*s).pop();
        node* c2 = (*s).pop();
        node* p = new node;
        pause += 2;
        p = create_node('\0',c1->probablity+c2->probablity,true,c1,c2,nullptr);
        p->left = c1;
        p->right = c2;
        c1->parent = p;
        c2->parent = p;
        (*s).push(p);
        //(*s) = (*s).sort_table();
        (*s).sort();
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
            //cout<<1;
        }
        else{
            q->enqueue(0);
            //cout<<0;
        }
    }
}

unsigned int bin2uint(intqueue* q){
    unsigned int ret = 0;
    for(int i = 31; i >= 0 && !(*q).empty(); i--){
        ret += ((*q).dequeue())*pow(2,i);
    }
    return ret;
}

void count_character_frequencies(string filename, unsigned long long int* freq_of_character,unsigned long long int* total_frequency, int* total_lines){
    ifstream fin;
    fin.open(filename,ios::binary);
    string s;
    while (true){
        getline(fin,s);
        (*total_lines)++;
        (*total_frequency)++;
        if (fin.eof()) break;
        for ( unsigned long long int i = 0; i < s.length(); i++){
            freq_of_character[s[i]]++;
            (*total_frequency)++;
        }
    }   
    fin.close();
}

void compress_file_to(string original_file_name, string compressed_file_name,string* binary_code_for_character, int* total_lines){
    ifstream fin(original_file_name,ios::binary);
    ofstream fout(compressed_file_name,ios::binary);
    string s;
    unsigned int d;
    int lines_read=0;
    intqueue q;
    int progress = 0;
    while(!fin.eof()){
        getline(fin,s);
        lines_read++;
        //cout<<lines_read<<" "<<*total_lines;
        for (unsigned long long int i = 0; i < s.length();i++){
            add_to_queue(&q,binary_code_for_character[s[i]]);
            if (q.get_size() >= 32){
                d = bin2uint(&q);
                fout.write((char*)&d,sizeof(d));
                //cout<<"\n"<<d<<endl;
                //cout<<lines_read/(*total_lines)<<" "<<lines_read<<" "<<*total_lines;
            }
        }
        add_to_queue(&q,binary_code_for_character['\n']);
        if (q.get_size() >= 32){
                d = bin2uint(&q);
                fout.write((char*)&d,sizeof(d));
                //cout<<"\n"<<d<<endl;
        }
        progress_bar((lines_read*100)/(*total_lines));
    }
    do{
        d = bin2uint(&q);
        fout.write((char*)&d,sizeof(d));
        //cout<<"\n"<<d<<endl;
    }while(!q.empty());
    clear();
    fout.close();
    fin.close();
}

void write_symbols(fstream& fout,node* n){
    fout.seekg(0,ios::end);
    if (n != NULL){
        fout<<n->node_number<<" ";
        if (!n->dummy){
            int ascii_code = n->symbol;
            fout<<ascii_code<<endl;
        }
        else{
            int not_dummy = 0;
            fout<<not_dummy<<endl;
        }
        write_symbols(fout,n->left);
        write_symbols(fout,n->right);
    }
    else{
        return;
    }
}
void write_edges(fstream& fout,node* n){
    if ((n->right != NULL)&&(n->left!=NULL)){
        fout<<n->node_number<<" "<<n->left->node_number<<endl;
        fout<<n->node_number<<" "<<n->right->node_number<<endl;
        write_edges(fout,n->left);
        write_edges(fout,n->right);
    }
    else{
        return;
    }
}

void write_tree_to(fstream& fout,node* n,int* nodes_written){
    int no = *nodes_written;
    fout<<no<<endl;
    write_symbols(fout,n);
    write_edges(fout,n);
}

int main(){
    string binary_code_for_character[256]={""};
    unsigned long long int freq_of_character[256] = {0},total_frequency = 0;
    int total_lines = 0;
    string inputFile;
    cout<<"\n Please enter name for the input file(file should be in same folder as program):\n";
    cin>>inputFile;
    count_character_frequencies(inputFile,freq_of_character,&total_frequency,&total_lines);
    cout<<"\n->calculated probablities for the characters";
    table s;
    for (unsigned long long int i = 1; i < 256; i++){
        if (freq_of_character[i]){
            s.push(create_node((char)i,freq_of_character[i]*1.0/total_frequency,false,nullptr,nullptr,nullptr));
        }
    }
    cout<<"\n->pushed them into table";
    node* root_of_tree = create_tree(&s);
    int nodes_in_tree = 0;
    printPreorder(root_of_tree,"",binary_code_for_character,&nodes_in_tree);
    cout<<"\n->created binary tree"<<endl;
    string compressedFile;
    cout<<"\n Please enter name for the compressed file :\n";
    cin>>compressedFile;
    compress_file_to(inputFile,compressedFile,binary_code_for_character,&total_lines);
    string compressedFileTree;
    cout<<"\n Please enter name for the file where you want to write tree for decoding:\n";
    cin>>compressedFileTree;
    fstream fout(compressedFileTree,ios::out|ios::binary);
    cout<<"\nwriting data for tree in file";
    write_tree_to(fout,root_of_tree,&nodes_in_tree);
    fout.close();
    cout<<"\nprocess complete";
    return 0;
}
