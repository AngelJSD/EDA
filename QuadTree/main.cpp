#include "qtree.hpp"

main(){

	cData<int> d1(10, coord(2, 2));
	cData<int> d2(11, coord(5, 5));

	vector<cData<int>> elements;
	elements.push_back(d1);
	elements.push_back(d2);

	cData<int> d3(12, coord(1, 1));

	cQTree<int> arbol(elements, 400);

	cout<<elements.empty()<<endl;
	if (elements.empty()) {
		cout<<"Vacío si"<<endl;
	}
	else{
		cout<<"Vacío no"<<endl;
	}
	// arbol.insert(98734, c3);

}
