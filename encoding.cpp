#include <iostream>
#include "stack.h"

using namespace std;

int main(){
    stack s;
    s.push(create_node('a',0.1250,false));
    s.push(create_node('b',0.125,false));
    s.push(create_node('c',0.25,false));
    s.push(create_node('d',0.50,false));
    s.print();
    s.sort();
    s.print();
    return 0;
}