#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <iostream>
#include <vector>
#include <math.h>
#include <stack>

#include "bkt.h"

using namespace std;

int main()
{
    string files[1] = {"imagenes.txt"};
    bkt<string> arbol(files);

    //cout<<arbol.root->hijos.size()<<endl;
    //cout<<arbol.my_find("hla")<<endl;
	// cout<<"ojo1 "<<endl;
    arbol.my_print();

	cout<<endl<<endl;

    arbol.my_search(arbol.root, "bb1.jpg", 100);
    //arbol.my_search(arbol.root,"perro",2);
    return 0;
}
