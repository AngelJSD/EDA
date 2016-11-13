#include "coord.h"
#include "node.h"

template <typename T>
class cQTree{
    

    public:
        cNode<T>* mRoot;
        int mOVF;

        void insert(T, coord);
        bool find(coord, coord);
        cQTree(coord, coord, int);
        ~cQTree();
    
};

template <typename T>
bool cQTree<T>::find(coord c1, coord c2){
    
}

template <typename T>
void cQTree<T>::insert(T data, coord c1){
    
    cNode<T>* wen = new cNode<T>(c1, data);
    cNode<T>* tmp = mRoot;

    while( tmp && tmp->isLeaf() ){
        cout<<"holi\n";
        if( c1.x < tmp->mX && c1.y > tmp->mY){
            cout<<"holi1\n";
            tmp = tmp->mChild[0];
        }
        else if( c1.x > tmp->mX && c1.y > tmp->mY){
            cout<<"holi2\n";
            tmp = tmp->mChild[1];
        }
        else if( c1.x < tmp->mX && c1.y < tmp->mY){
            cout<<"holi3\n";
            tmp = tmp->mChild[2];
        }
        else if( c1.x > tmp->mX && c1.y < tmp->mY){
            cout<<"holi4\n";
            tmp = tmp->mChild[3];
        }
    }
    tmp->mElements.push_back(wen);

}

template <typename T>
cQTree<T>::cQTree(coord c1, coord c2, int OVF){

    mRoot = new cNode<T>(c1, c2);
    mOVF = OVF;
    cout<<"holi\n";
    mRoot->createSons();
    
}

template <typename T>
cQTree<T>::~cQTree(){

}