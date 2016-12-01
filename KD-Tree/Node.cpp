#include "Node.hpp"


template <typename T>
cNode<T>::cNode (cCoordinate coord, int cutCoordinate){
	mCoord = coord;
	mChild[0] = mChild[1] = nullptr;
	mCutCoordinate = cutCoordinate;
};

template <typename T>
cNode<T>::~cNode<T>(){

};

template <typename T>
bool cNode<T>::mIsLeaf(){
	return (mChild[0] || mChild[1]);
};

template <typename T>
void cNode<T>::mSetLeftSon(cNode<T>* son){
	mChild[0] = son;
};

template <typename T>
void cNode<T>::mSetRightSon(cNode<T>* son){
	mChild[1] = son;
};

template <typename T>
int cNode<T>::mGetCutCoordinateVal(){
	return mCutCoordinate;
};

template <typename T>
void cNode<T>::mSetCutCoordinate(int cutCoordinate){
	mCutCoordinate = cutCoordinate;
};

template <typename T>
float cNode<T>::mGetCoordinate(int dimension){
	return mCoord[dimension];
};
