#include<fstream>
#include <bitset>
#include<bits/stdc++.h>

using namespace std;

void progress_Bar(int completed){
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

void Clear(){
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
    take_comp_file_input:{;}
    cout<<"Please enter the name of compressed file: (with .bin extention)"<<endl;
    cin>>inp;
    ifstream fin(inp,ios::binary);
    //Myfile will write the decoded data in the file whereas comressed file is the file from where we get the encoded data
    unsigned int u;
    /*now we will traverse the tree iteratively untill we read the whole file in each traversal whenever we read 1 we will move to the left child and
    we move to the right child if we read 0 and if we reach at some leaf node we write it's char data to our decompressed file and again start traversing
    from the root*/

    if (!fin){
        cout<<"cannot open file!!!";
        cout<<"\n would you like to try again(non-zero for yes/ 0 for no):";
        int c;
        cin>>c;
        if (c){
            goto take_comp_file_input;
        }
        else{
            return;
        }
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
            progress_Bar(progress);
        }
    }
    Clear();
    MyFile.close();
    fin.close();
}



int decoding()
{
    string s;
    take_file_name_input:{;}
    cout<<"Please enter the tree file name: "<<endl;
    cin>>s;
    ifstream readfile(s,ios::binary);
    //this will start reading the file which contains data of nodes,edges and  char each node has
    int n;
    if (!readfile){
        cout<<"\n unable to open file!!!!"<<"\n";
        int choice;
        cout<<"\n would you like to try again(non-zero for yes/ 0 for no):";
        cin>>choice;
        if (choice){
            goto take_file_name_input;
        }
        else{
            ;
        }
    }
    else{
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
                g.addEdge(a,b);//making tree using edge data
            }
        }
        readfile.close();
        g.decoding();
        cout<<"Thank you for using our software"<<"\n";
    }
    return 0;
}
