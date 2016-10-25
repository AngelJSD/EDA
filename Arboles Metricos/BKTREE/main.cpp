#include <iostream>
#include <vector>
#include <math.h>
#include <stack>

#include "bkt.h"

using namespace std;

int main()
{
    string files[1] = {"ejemplo.txt"};
    bkt<string> arbol(files);

    //cout<<arbol.root->hijos.size()<<endl;
    //cout<<arbol.my_find("hla")<<endl;

    //arbol.my_print();

    arbol.my_search(arbol.root,"de",3);
    //arbol.my_search(arbol.root,"perro",2);
    return 0;
}
