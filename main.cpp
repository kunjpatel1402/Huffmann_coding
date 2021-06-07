#include<bits/stdc++.h>
#include "encoding.cpp"
#include "decoding.cpp"
using namespace std;
int main()
{

    cout<<"Which operation you want to perform!: "<<endl;
    cout<<"Enter \n1. for compression of file\n2 to decompress file"<<endl;
    cout<<":";
    int n;
    cin>>n;
    switch(n)
    {
    case 1:
        {
            encoding();
            break;
        }
    case 2:
        {
            decoding();
            break;
        }
    default:
        {
            cout<<"Please enter a valid digit"<<endl;
        }
    }

    return 0;
}