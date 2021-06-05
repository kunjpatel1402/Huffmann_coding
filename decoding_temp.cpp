#include <iostream>
#include<fstream>
#include <bitset>
#include<bits/stdc++.h>

using namespace std;

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
    ofstream MyFile("decoded.txt");
    cout<<"Please enter the name of compressed file: (with .dat extention)"<<endl;
    string inp;
    //cin>>inp;
    ifstream fin("compressed.dat",ios::binary);
    //Myfile will write the decoded data in the file whereas comressed file is the file from where we get the encoded data
    unsigned int u;
    /*now we will traverse the tree iteratively untill we read the whole file in each traversal whenever we read 1 we will move to the left child and 
    we move to the right child if we read 0 and if we reach at some leaf node we write it's char data to our decompressed file and again start traversing
    from the root*/
    /*while(1)
    {
        fin.read((char *)&u,sizeof(u));
        cout<<u<<endl;
        if(fin.eof())
            break;
        else
        {
           bitset<32> x(u);
           for(int i=1;i<=32;i++)
          {
            if(x[i]==1)
           {
              auto it=adj[v].begin() ;
              v=*it;
           }
           else if(x[i]==0)
            {
             auto it=adj[v].begin();
             it++;
             v = *it;
            }
            if(adj[v].begin()==adj[v].end())
            {
              MyFile<<node_data[v];
               v=1;
            }
         }

        }
    }*/
    if (!fin){
        cout<<"cannot open file";
        return ;
    }
    else{
        unsigned int u,pause;
        while(!fin.eof()){
            fin.read((char*) &u,sizeof(u));
            //cout<<u<<endl;
            //cout<<":";cin>>pause;
            bitset<32> x(u);
            cout<<x;
            for(int i=1;i<=32;i++)
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
                    cout<<node_data[v]<<" "<<v<<endl;;
                    v=1;
                }
            }
        }
    }
    MyFile.close();
    fin.close();

}



int main()
{
    string s;

    cout<<"Please enter the file name: "<<endl;
    //cin>>s;
    ifstream readfile("compressed_tree.dat",ios::binary);
    //this will start reading the file which contains data of nodes,edges and  char each node has
    int n;
    readfile >> n ;
    cout<<n<<endl;
    Graph g;
     node_data = new char[n+1];
 // ane aiya '\0' thi init pan kari de
    node_data[0]='*';
    for (int i = 0; i < n+1; i++){
        node_data[0]='\0';
    }
    int t,sym;
    while(!readfile.eof()){
        for(int i=1;(i<=n)&&(!readfile.eof());i++)
        {
            readfile >> t;
        // aiya ek if muk jo dummy na hoy to j symbol read thay baki nai
            readfile >>sym;
            cout<<t<<" "<<(char)sym<<endl;
            node_data[t] = (char)sym;

        }
        for(int i=0;(i<n-1)&&(!readfile.eof());i++)
        {
            int a,b;
            readfile >> a;
            readfile >> b;
            g.addEdge(a,b);//making tree using edge data
            //cout<<a<<" "<<b<<endl;
        }
    }
    readfile.close();
    /*string es;
    es = g.input();*/

    g.decoding();
    cout<<"Decomressed file is ready! please check it out"<<"\n";
    cout<<"Thank you for using our software"<<"\n";
    return 0;
}
