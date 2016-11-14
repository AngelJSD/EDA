#include "qtree.hpp"

int main(int argc, char const *argv[]) {

	srand(time(NULL));

	vector< cData< int > > elements;

	for(int i = 0; i < 100; ++i) {
		for(int j = 0; j < 100; ++j) {
			elements.push_back(cData<int>( i+j, coord(i, j)));
		}
	}


	cQTree<int> arbol(elements, 100);
	cout<<"--------"<<endl;
	//arbol.print(arbol.mRoot);
	cout<<"--------"<<endl;


	cout<<"Búsqueda"<<endl;
	//arbol.mFindElement(cData< string >)
	arbol.mFindByRange(coord(0, 0), coord(20, 20), arbol.mRoot);
	return 0;

}
