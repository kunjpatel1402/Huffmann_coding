#include <iostream>
#include<fstream>
#include<bits/stdc++.h>

using namespace std;
class Graph
{
public:
   // map<int, bool> visited;
    map<int, list<int>> adj;

    char *node_data;


    Graph(int n){

        node_data = new char[n+1];
        node_data[0]='*';
        int t;
        for(int i=1;i<=n;i++)
        {
            readfile >> t >>"\n";
            readfile >>node_data[t];

        }
    }
    void addEdge(int v, int w);
    void decoding(string es);
    string input();//remaining
};


void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w);

}
void Graph::decoding(string &es)
{
    string ds="";
    int v=1;
    for(int i=0;i<es.length();i++)
    {
        if(es[i]=='1')
        {
          auto it=adj[v].begin() ;
          v=*it;
        }
        else if(es[i]=='0')
        {
            auto it=adj[v].end()-1;
            v = *it;
        }
        if(adj[v].begin()==adj[v].end())
        {
            ds = ds + node_data[v];
            v=1;

        }

    }
}



int main()
{
    string s;

    cout<<"Please enter the file name: ";
    cin>>s;
    ifstream readfile(s);
    int n;
    readfile >> n >>"\n";
    Graph g(n);
    for(int i=0;i<n-1;i++)
    {
        int a,b;
        readfile >> a;
        readfile >> b>>"\n";
        g.addEdge(a,b);

    }
    string es;
    es = g.input();

    g.decoding(es)

    return 0;
}
