#include "vpTree.h"

int LDistance(string, string);

int main(){

	srand(time(NULL));

	string files[1] = {"diccionario.txt"};
	cVPT<string> arbol(files);

	//arbol.print();

	while(true){

		int radius;
		string target;
		cout<<endl<<"Ingrese el elemento a buscar y el radio: "<<endl;
		cin>>target>>radius;

		arbol.search(arbol.mRoot, target, radius);

	}

	return 0;

}
