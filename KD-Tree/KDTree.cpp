
#include "KDTree.hpp"

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

float cKDTree::distance(cCoordinate A, cCoordinate B){
    float dist=0;
    for(int i=0; i<mDimensions;i++)
    {
        dist+=pow(A[i]-B[i],2.0);
    }
    dist=sqrt(dist);
    return dist;
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

cNode* cKDTree::mMinimum(cNode *A, cNode *B, cNode *C, int dim){

    float min;
    if(A && B && C){
        if(A->mGetCoordinate(dim)<B->mGetCoordinate(dim) && A->mGetCoordinate(dim)<C->mGetCoordinate(dim))
            return A;
        if(B->mGetCoordinate(dim)<A->mGetCoordinate(dim) && B->mGetCoordinate(dim)<C->mGetCoordinate(dim))
            return B;
        if(C->mGetCoordinate(dim)<A->mGetCoordinate(dim) && C->mGetCoordinate(dim)<B->mGetCoordinate(dim))
            return C;
    }
    else if(A && B){
        if(A->mGetCoordinate(dim)<B->mGetCoordinate(dim))
            return A;
        return B;
    }
    else if(B && C){
        if(B->mGetCoordinate(dim)<C->mGetCoordinate(dim))
            return B;
        return C;
    }
    else if(A && C){
        if(A->mGetCoordinate(dim)<C->mGetCoordinate(dim))
            return A;
        return C;
    }
    else if(A){
        return A;
    }
    else if(B){
        return B;
    }
    else if(C){
        return C;
    }
}

cNode* cKDTree::mFindMin(cNode *T, int dim, int cd){

    if(T==NULL) return NULL;

    if(cd==dim){

        if(T->mGetChild(0)==NULL)
            return T;
        else
            return mFindMin(T->mGetChild(0), dim, (cd+1)%mDimensions);

    }
    else{

        return mMinimum(mFindMin(T->mGetChild(0), dim, (cd+1)%mDimensions),
                        mFindMin(T->mGetChild(1), dim, (cd+1)%mDimensions),
                        T, dim);

    }
}
cNode* cKDTree::mFindNearestNeighborAux(cCoordinate coord, cNode** t,cNode* cb,int cd, float dcb){

    if (coord == (*t)->mGetCoordinate())
    {
        return *t;
    }
    float d=distance(coord, (*t)->mGetCoordinate());
    if(dcb== -1 || d<dcb)
    {
        dcb=d;
        cb=*t;
    }

    bool c=(coord[cd] >= (*t)->mGetCoordinate(cd));
    cNode** p=(*t)->mGetChildDir(c);
    if (*p==NULL)
    {
        return cb;
    }
    return mFindNearestNeighborAux(coord, p, cb, (cd+1) % mDimensions, dcb);
}
cNode* cKDTree::MFindNearestNeighbor(cCoordinate coord){

    cNode* FNN=   mFindNearestNeighborAux(coord,&mRoot, mRoot,0,-1);
    return FNN;
}


cNode* cKDTree::mDelete(cCoordinate x, cNode * T, int cd){

    if(T==NULL){
        cout<<"Error: Punto no encontrado"<<endl;
		return NULL;
	}

    int next_cd=(cd+1)%mDimensions;

    if( x==T->mGetCoordinate() ){

        if(T->mGetChild(1) != NULL){

            T->mSetCoordinate(mFindMin(T->mGetChild(1),cd, next_cd)->mGetCoordinate());
            T->mSetRightSon(mDelete(T->mGetCoordinate(),T->mGetChild(1),next_cd));
        }
        else if(T->mGetChild(0) != NULL){
            T->mSetCoordinate(mFindMin(T->mGetChild(0),cd, next_cd)->mGetCoordinate());
            T->mSetRightSon(mDelete(T->mGetCoordinate(),T->mGetChild(0),next_cd));
            T->mSetLeftSon(NULL);
            cout<<(bool)T->mGetChild(0)<<endl;
        }
        else{

            T = NULL;
        }
    }
    else if(x[cd] < T->mGetCoordinate(cd)){

        T->mSetLeftSon(mDelete(x,T->mGetChild(0),next_cd));
    }
    else{

        T->mSetRightSon(mDelete(x,T->mGetChild(1),next_cd));
    }

    return T;

}
