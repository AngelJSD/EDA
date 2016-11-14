#include "qtree.hpp"

main(){

	cData<int> d1(10, coord(2, 2));
	cData<int> d2(11, coord(5, 5));
	cData<int> d3(12, coord(1, 1));
	cData<int> d4(13, coord(1, 3));
	cData<int> d5(14, coord(4, 1));

	vector<cData<int>> elements;
	elements.push_back(d1);
	elements.push_back(d2);


	cQTree<int> arbol(elements, 4);
	cout<<"--------"<<endl;
	arbol.print(arbol.mRoot);
	cout<<"--------"<<endl;
	arbol.mInsert(d3);
	cout<<"--------"<<endl;
	arbol.print(arbol.mRoot);
	cout<<"--------"<<endl;
	arbol.mInsert(d4);
	cout<<"--------"<<endl;
	arbol.print(arbol.mRoot);
	cout<<"--------"<<endl;
	arbol.mInsert(d5);
	cout<<"--------"<<endl;
	arbol.print(arbol.mRoot);
	cout<<"--------"<<endl;
}
