#include "SparseMatrix.h"


int main(){

	SparseMatrix<string> Matriz(3, 3, "(3, 3)");
	Matriz.m_insert(1, 2, "(1, 2)", "1-2");
	Matriz.m_insert(1, 1, "(1, 1)", "1-1");
	Matriz.m_insert(2, 2, "(2, 2)", "2-2");
	Matriz.m_insert(5, 5, "(5, 5)", "5-5");
	Matriz.m_insert(7, 10, "(7, 10)", "7-10");
	Matriz.print();

	return 0;

}
