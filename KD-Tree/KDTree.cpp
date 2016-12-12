#include "KDTree.h"

cKDTree::cKDTree(int dimensions){
    mRoot = nullptr;
    mDimensions = dimensions;
}


cKDTree::~cKDTree(){
    mRoot = nullptr;
}

void cKDTree::print() {
    print2(mRoot,0);
}


void cKDTree::print2(cNode* t, int level) {
    if (t!=NULL)
    {
        print2(t->mGetChild(1), level+1);
        for (int k = 0; k < mDimensions*level; k++)
        {
            cout << "   ";
        }
        cout<<vocabulary[t->mGetCutCoordinateVal()]<<endl;
        for (int k = 0; k < mDimensions*level; k++)
        {
            cout << "   ";
        }
        t->mPrintCoordinates();
        print2(t->mGetChild(0), level+1);
    }
}


bool cKDTree::mInsertAux(cCoordinate coord, cNode** t,int cd){
    if (*t==NULL)
    {
        cNode* aux = new cNode(coord,cd);
        *t = aux;
        return 1;
    }
    if (coord == (*t)->mGetCoordinate())
    {
        return 0;
    }
    bool c=(coord[cd] >= (*t)->mGetCoordinate(cd));
    cNode** p=(*t)->mGetChildDir(c);
    return mInsertAux(coord,p,(cd+1) % mDimensions);
}


void cKDTree::mInsert(cCoordinate coord){
    if ( mDimensions != coord.mGetDimension() ) {
        cout << "Dimensión inválida. Asigne coordenadas de la dimensión: "<< mDimensions << endl;
        return;
    }
    if(!mInsertAux(coord,&mRoot,0)){
        cout<<"Insertado correctamente"<<endl;
    }
    else{
        cout<<"La coordenada ya esta en el árbol"<<endl;
    }
}
