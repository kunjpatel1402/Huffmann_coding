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
    //string input();//remaining
};


void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w);

}
void Graph::decoding()
{

    int v=1;
    ofstream MyFile("decoded.txt");
    cout<<"Please enter the name of compressed file: (with .dat extention)";
    string inp;
    cin>>inp;
    ifstream fin("inp",ios::binary);
    //Myfile will write the decoded data in the file whereas comressed file is the file from where we get the encoded data
    unsigned int u;
    /*now we will traverse the tree iteratively untill we read the whole file in each traversal whenever we read 1 we will move to the left child and 
    we move to the right child if we read 0 and if we reach at some leaf node we write it's char data to our decompressed file and again start traversing
    from the root*/
    while(1)
    {
        fin.read((char *)&u,sizeof(u));
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
    }

    MyFile.close();
    fin.close();

}



int main()
{
    string s;

    cout<<"Please enter the file name: ";
    cin>>s;
    ifstream readfile(s);
    //this will start reading the file which contains data of nodes,edges and  char each node has
    int n;
    readfile >> n ;
    Graph g;
     node_data = new char[n+1];
        node_data[0]='*';
        int t;
        for(int i=1;i<=n;i++)
        {
            readfile >> t;
            readfile >>node_data[t];

        }
    for(int i=0;i<n-1;i++)
    {
        int a,b;
        readfile >> a;
        readfile >> b;
        g.addEdge(a,b);//making tree using edge data

    }
    readfile.close();
    /*string es;
    es = g.input();*/

    g.decoding();
    cout<<"Decomressed file is ready! please check it out"<<"\n";
    cout<<"Thank you for using our software"<<"\n";
    return 0;
}
