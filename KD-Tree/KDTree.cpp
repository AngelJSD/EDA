#include "KDTree.hpp"

template <typename T>
cKDTree<T>::cKDTree(int dimensions){
	mRoot = nullptr;
	mDimensions = dimensions;
}

template <typename T>
cKDTree<T>::~cKDTree(){
	mRoot = nullptr;
}

template <typename T>
void cKDTree<T>::mInsert(cCoordinate coord){
	if ( mDimensions != coord.mGetDimension() ) {
		cout << "Dimensión inválida. Asigne coordenadas de la dimensión: "<< mDimensions << endl;
		return;
	}
	/*
	 *Continúa la inserción
	 *cNode(coordinadas, coordinadaDeCorte);
	 *
	 */
}
