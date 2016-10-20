#include <iostream>
#include <vector>
#include <math.h>
#include <stack>

#include "bkt.h"

using namespace std;

int main()
{
    bkt arbol;

    arbol.my_insert("hol");
    arbol.my_insert("hla");
    arbol.my_insert("nola");
    arbol.my_insert("vaca");
    arbol.my_insert("sol");
    arbol.my_insert("sal");
    arbol.my_insert("como");
    arbol.my_insert("altar");
    arbol.my_insert("angel");

    cout<<arbol.root->hijos.size()<<endl;
    cout<<arbol.my_find("hla")<<endl;

    arbol.my_print();

    return 0;
}
