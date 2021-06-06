#include <iostream>
#include<fstream>
#include <bitset>
#include<bits/stdc++.h>

using namespace std;

void progress_bar(int completed){
    for (int i = 0; i < completed;i++){
        cout<<"|";
    }
    for (int i = completed; i < 30; i++){
        cout<<" ";
    }
    cout<<"|";
    cout<<" decompressing file";
    //for(int i =0 ; i < 1000000; i++);
    cout<<"\r";
}

void clear(){
    cout<<"\r";
    for (int i = 0; i < 50; i++){
        cout<<" ";
    }
    cout<<"\n->file decompressed"<<endl;
}

 char *node_data;
class Graph
{
public:
   // map<int, bool> visited;
    map<int, list<int>> adj;
    void addEdge(int v, int w);
    void decoding();
    
};
void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w);

}
void Graph::decoding()
{

    int v=1;
    string inp;
    cout<<"\n\n enter name for decompressed file(with .txt extention):\n";
    cin>>inp;
    ofstream MyFile(inp);
    cout<<"Please enter the name of compressed file: (with .dat extention)"<<endl;
    cin>>inp;
    ifstream fin(inp,ios::binary);
    unsigned int u;
    if (!fin){
        cout<<"cannot open file";
        return ;
    }
    else{
        int progress = 0;
        unsigned int u,pause;
        while(true){
            fin.read((char*) &u,sizeof(u));
            if (fin.eof())  break;
            bitset<32> x(u);
            for(int i=31;i>=0;i--)
            {
                if(x[i]==1)
                {
                    auto it = adj[v].begin();
                    v=*it;
                }
                else if(x[i]==0)
                {
                    auto it = adj[v].begin();
                    it++;
                    v = *it;
                }
                if(adj[v].begin()==adj[v].end())
                {
                    MyFile<<node_data[v];
                    v=1;
                }
            }
            progress = ++progress%30;
            progress_bar(progress);
        }
    }
    clear();
    MyFile.close();
    fin.close();
}



int main()
{
    string s;

    cout<<"Please enter the tree file name: "<<endl;
    cin>>s;
    ifstream readfile(s,ios::binary);
    int n;
    readfile >> n ;
    Graph g;
     node_data = new char[n+1];
    for (int i = 0; i < n+1; i++){
        node_data[0]='\0';
    }
    int t,sym;
    cout<<"\n->creating character tree";
    while(!readfile.eof()){
        for(int i=1;(i<=n)&&(!readfile.eof());i++)
        {
            readfile >> t;
            readfile >>sym;
            node_data[t] = (char)sym;

        }
        for(int i=0;(i<n-1)&&(!readfile.eof());i++)
        {
            int a,b;
            readfile >> a;
            readfile >> b;
            g.addEdge(a,b);
        }
    }
    readfile.close();
    g.decoding();
    cout<<"\nDecomressed file is ready! please check it out"<<"\n";
    cout<<"Thank you for using our software"<<"\n";
    return 0;
}
