#include <iostream>
#include <fstream>
#include <math.h>
#include "stack.h"
#include "queue.h"

using namespace std;

void printPreorder(node* root,string s,string* binary_code_for_the_character,int* nodes_in_tree){
    if (root == NULL)
        return;
    if(root->symbol!='\0')
        binary_code_for_the_character[root->symbol] = s;
    (*nodes_in_tree)++;
    //cout<<*nodes_in_tree<<endl;
    root->node_number = *nodes_in_tree;
    //print_node(root);
    printPreorder(root->left,(s + "1"),binary_code_for_the_character,nodes_in_tree);
    printPreorder(root->right,(s + "0"),binary_code_for_the_character,nodes_in_tree);
    //cout<<"\n"<<s<<endl;
}

node* create_tree(stack* s){
    int pause = 0;
    (*s).sort();
    //(*s).print();
    while(true){
        if ((*s).get_size() < 2){
            cout<<"ERROR"<<endl;
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
        (*s).sort();
        //(*s).print();
        //cout<<"\n:";
        //cin>>pause;
        if((*s).get_size() <= 1){
            break;
        }
    }
    cout<<pause<<endl;
    return ((*s).pop());
}

void add_to_queue(intqueue* q,string str){
    for (unsigned long long i = 0;i < str.length();i++){
        if (str[i]=='1'){
            q->enqueue(1);
            cout<<1;
        }
        else{
            q->enqueue(0);
            cout<<0;
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
    ifstream fin;
    fin.open(filename,ios::binary);
    string s;
    while (true){
        getline(fin,s);
        cout<<s<<endl;
        (*freq_of_next_line)++;
        (*total_frequency)++;
        if (fin.eof()) break;
        for ( unsigned long long int i = 0; i < s.length(); i++){
            freq_of_character[s[i]]++;
            (*total_frequency)++;
        }
        //cout<<s<<endl;
    }
    cout<<fin.eof();
    fin.close();
}

void compress_file_to(string original_file_name, string compressed_file_name,string* binary_code_for_character){
    ifstream fin(original_file_name,ios::binary);
    ofstream fout(compressed_file_name,ios::binary);
    string s;
    unsigned int d;
    intqueue q;
    while(!fin.eof()){
        getline(fin,s);
        //if (fin.eof()) break;
        //cout<<s<<endl;
        for (unsigned long long int i = 0; i < s.length();i++){
            add_to_queue(&q,binary_code_for_character[s[i]]);
            if (q.get_size() >= 32){
                d = bin2uint(&q);
                //fout<<d<<endl;
                fout.write((char*)&d,sizeof(d));
                cout<<"\n"<<d<<endl;
            }
        }
        add_to_queue(&q,binary_code_for_character['\n']);
        if (q.get_size() >= 32){
                d = bin2uint(&q);
                //fout<<d<<endl;
                fout.write((char*)&d,sizeof(d));
                cout<<"\n"<<d<<endl;
        }
    }
    //q.print();
    do{
        d = bin2uint(&q);
        //fout<<d<<endl;
        fout.write((char*)&d,sizeof(d));
        cout<<"\n"<<d<<endl;
    }while(!q.empty());
    fout.close();
    fin.close();
    cout<<q.empty()<<endl;
}

void write_symbols(fstream& fout,node* n){
    fout.seekg(0,ios::end);
    if (n != NULL){
        //fout.write((char*) &(n->node_number),sizeof(n->node_number));
        fout<<n->node_number<<" ";
        if (!n->dummy){
            //fout.write((char*) &(not_dummy),sizeof(not_dummy));
            int ascii_code = n->symbol;
            fout<<ascii_code<<endl;
            //fout.write((char*) &(ascii_code),sizeof(ascii_code));
        }
        else{
            int not_dummy = 0;
            //fout.write((char*) &(not_dummy),sizeof(not_dummy));
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
        /*int num = n->node_number;
        fout.write((char*) &(num),sizeof(num));
        cout<<num<<" ";
        num = n->left->node_number;
        fout.write((char*) &(num),sizeof(num));
        cout<<num<<endl;
        num = n->node_number;
        fout.write((char*) &(num),sizeof(num));
        cout<<num<<" ";
        num = n->right->node_number;
        fout.write((char*) &(num),sizeof(num));
        cout<<num<<endl;*/
        fout<<n->node_number<<" "<<n->left->node_number<<endl;
        fout<<n->node_number<<" "<<n->right->node_number<<endl;
        write_edges(fout,n->left);
        write_edges(fout,n->right);
    }
    else{
        //cout<<"node number:"<<n->node_number<<" "<<n->symbol<<"|"<<endl;
        return;
    }
}

void write_tree_to(fstream& fout,node* n,int* nodes_written){
    //fout<<(*nodes_written)<<endl;
    int no = *nodes_written;
    //fout.write((char*) &no,sizeof(int));
    fout<<no<<endl;
    //fout<<"symbols"<<endl;
    write_symbols(fout,n);
    //fout<<"edges"<<endl;
    cout<<"file"<<endl;
    write_edges(fout,n);
}

int main(){
    cout<<"\n started";
    string binary_code_for_character[256]={""};
    unsigned long long int freq_of_character[256] = {0},freq_of_next_line = 0,total_frequency = 0;
    //cout<<"1"<<endl;
    count_character_frequencies("C:\\Users\\Kunj R. Patel\\Desktop\\codes\\c++\\assignment\\huffmann coding\\test.txt",freq_of_character,&freq_of_next_line,&total_frequency);
    //cout<<"2"<<endl;
    stack s;
    for (unsigned long long int i = 1; i < 256; i++){
        //cout<<(char)i<<" "<<freq_of_character[i]<<endl;
        if (freq_of_character[i]){
            s.push(create_node((char)i,freq_of_character[i]*1.0/total_frequency,false,nullptr,nullptr,nullptr));
        }
    }
    //s.push(create_node('\n',freq_of_next_line*1.0/total_frequency,false));
   //cout<<total_frequency<<endl;
    node* root_of_tree = create_tree(&s);
    int nodes_in_tree = 0;
    printPreorder(root_of_tree,"",binary_code_for_character,&nodes_in_tree);
    for (int i = 0; i < 256; i++){
        if (binary_code_for_character[i]!= ""){
            cout<<i<<" "<<binary_code_for_character[i]<<endl;
        }
    }
    compress_file_to("C:\\Users\\Kunj R. Patel\\Desktop\\codes\\c++\\assignment\\huffmann coding\\test.txt","compressed.dat",binary_code_for_character);
    /*ifstream fin("compressed.dat",ios::binary);
    unsigned int u;
    //bool t;
    while(true){
        fin.read((char*) &u, sizeof(u));
        if (fin.eof()) break;
        bitset<32> x(u);
        cout<<x;
    }*/
    cout<<nodes_in_tree<<endl;
    cout<<root_of_tree->probablity<<endl;
    fstream fout("compressed_tree.dat",ios::out);
    write_tree_to(fout,root_of_tree,&nodes_in_tree);
    fout.close();
    /*int pause;
    ifstream fin("compressed.dat",ios::binary);
    unsigned int n;
    while(!fin.eof()){
        fin.read((char*) &n,sizeof(n));
        cout<<n<<endl;
        //cout<<":";cin>>pause;
    }
    fin.close();*/
    return 0;
}
