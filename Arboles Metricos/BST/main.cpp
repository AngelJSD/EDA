#include "bst.h"

int LDistance(string, string);

int main(int argc, char const *argv[]) {

	srand(time(NULL));

	string files[1] = {argv[1]};
	cVPT<string> arbol(files);

	arbol.print();

	while(true){

		int radius;
		string target;
		cout<<endl<<"Ingrese el elemento a buscar y el radio: "<<endl;
		cin>>target>>radius;
		arbol.search(arbol.mRoot, target, radius);
		cout<<arbol.cont;
		arbol.cont=0;

	}

	return 0;

}
