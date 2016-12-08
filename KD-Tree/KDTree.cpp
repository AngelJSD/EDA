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


template<typename T>
void cKDTree<T>::print() {
    print2(mRoot,0);
}


template <typename T>
void cKDTree<T>::print2(cNode<T>* t, int level) {
    if (t!=NULL)
    {
        print2(t->mGetChild(0), level+1);
        for (int k = 0; k < level; k++)
        {
            cout << "   ";
        }
        t->mPrintCoordinates();
        print2(t->mGetChild(1), level+1);
    }
}


template <typename T>
bool cKDTree<T>::mInsertAux(cCoordinate coord, cNode<T>* t,int cd)
{
    if (t==NULL)
    {
        t = new cNode<T>(coord,cd);
        return 1;
    }
    /*if (coord == t->mGetCoordinate())
    {
        return 0;
    }
    bool c=(coord[cd] < t->mGetCoordinate(cd));
    return mInsertAux(coord,t->mGetChild(!c),(cd+1) % mDimensions);
*/
}


template <typename T>
void cKDTree<T>::mInsert(cCoordinate coord){
	if ( mDimensions != coord.mGetDimension() ) {
		cout << "Dimensión inválida. Asigne coordenadas de la dimensión: "<< mDimensions << endl;
		return;
	}
	if(mInsertAux(coord,mRoot,0)){
        cout<<"Insertado correctamente"<<endl;
    }
    else{
        cout<<"La coordenada ya esta en el arbol"<<endl;
    }
}
