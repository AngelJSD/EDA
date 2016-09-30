#include "SparseMatrix.h"


int main(){

	cout << "Hello world!" << endl;
	SparseMatrix<char> Matriz(1, 2, 'a');
	cout<<"z"<<endl;
	Matriz.m_insert(1, 1, 'z');
	cout<<"z"<<endl;
	Matriz.m_insert(3, 5, 'z');
	cout<<"a"<<endl;
	Matriz.m_insert(2, 3, 's');
	Matriz.print();
	return 0;

}
