#include<bits/stdc++.h>
#include "./Headers/encoding.cpp"
#include "./Headers/decoding.cpp"
using namespace std;
int main()
{

    cout<<"Which operation you want to perform?: "<<endl;
    cout<<"Enter \n1. for compression of file\n2. to decompress file\n0. to exit"<<endl;
    int n;
    get_input:{;}
    cout<<":";
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
    case 0:
        {
            break;
        }
    default:
        {
            cout<<"Please enter a valid digit"<<endl;
            goto get_input;
        }
    }

    return 0;
}
