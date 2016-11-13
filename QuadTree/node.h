#include <iostream>
#include <vector>

using namespace std;

template <typename T>
class cNode{

    public:

    //Variables

        float mX;
        float mY;

        coord mCoord1;
        coord mCoord2;

        T mData;
        vector<cNode*> mElements;
        vector<cNode*> mChild;

    //Métodos
        cNode(coord, T);
        cNode(coord, coord);
        bool overflow(int);
        bool isLeaf();
        void createSons();
        ~cNode();

};



//Nodo cuadrante animal.
template <typename T>
cNode<T>::cNode(coord c1, coord c2){

    vector<coord> crd = c1.generate(c1,c2);
    mCoord1 = crd[0];
    mCoord2 = crd[1];

    for (int i = 0; i < 4; i++)
    {
        mChild[i] == nullptr;
    }
    cout<<"constructor"<<endl;

    mX = ( mCoord1.x + mCoord2.x ) / 2.0;
    mY = ( mCoord1.y + mCoord2.y ) / 2.0;

}

//Nodo elemento imbécil.
template <typename T>
cNode<T>::cNode(coord c1, T data){

    mX = c1.x;
    mY = c1.y;

    mData = data;    
}

template <typename T>
cNode<T>::~cNode(){

}

template <typename T>
bool cNode<T>::isLeaf(){
    return (mChild.empty());
}

//no te calmes, estrésate :v.
template <typename T>
bool cNode<T>::overflow(int OVF){
    return mData.size() > OVF;
}

template <typename T>
void cNode<T>::createSons(){
    
    coord c1(mX, mY);

    coord c2(mCoord1.x, mCoord2.y);
    mChild[0] = new cNode<T>(c1, c2);

    mChild[1] = new cNode<T>(c1, mCoord2);

    mChild[2] = new cNode<T>(mCoord1, c1);

    c2 = coord(mCoord2.x, mCoord1.y);
    mChild[3] = new cNode<T>(c1, c2);

}
