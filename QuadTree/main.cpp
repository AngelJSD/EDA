#include "qtree.hpp"

int main(int argc, char const *argv[]) {

	srand(time(NULL));

	vector< cData< int > > elements;

	for(int i = 0; i < 10; ++i) {
		for(int j = 0; j < 10; ++j) {
			elements.push_back(cData<int>( i+j, coord(i, j)));
		}
	}


	cQTree<int> arbol(elements, 10);
	cout<<"--------"<<endl;
	arbol.print(arbol.mRoot);
	cout<<"--------"<<endl;


	cout<<"Búsqueda"<<endl;
	//arbol.mFindElement(cData< string >)
	arbol.mFindByRange(coord(0, 0), coord(20, 20), arbol.mRoot);

	arbol.mDeleteElement(elements[3]);
	cout<<"--------Eliminando: "<<elements[3].mData<<endl;
	arbol.print(arbol.mRoot);
	cout<<"--------"<<endl;
	return 0;

}
