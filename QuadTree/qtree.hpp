#include "node.hpp"

template <typename T>
class cQTree{


	public:
		cNode<T>* mRoot;
		int mOVF;
		int mGreatX;
		int mLessX;
		int mGreatY;
		int mLessY;

		void mInsert(cData<T>);
		bool find(coord, coord);
		cQTree(vector< cData< T > >, int);
		~cQTree();

};

template <typename T>
cQTree<T>::cQTree(vector< cData< T > > elements, int OVF){

	mGreatX = elements[0].mCoord.x;
	mLessX = elements[0].mCoord.x;
	mGreatY = elements[0].mCoord.x;
	mLessY = elements[0].mCoord.y;
	for (uint i = 0; i < elements.size(); ++i) {
		mLessX =  elements[i].mCoord.x < mLessX ? elements[i].mCoord.x : mLessX;
		mGreatX =  elements[i].mCoord.x > mGreatX ? elements[i].mCoord.x : mGreatX;

		mLessY =  elements[i].mCoord.y < mLessY ? elements[i].mCoord.y : mLessY;
		mGreatY =  elements[i].mCoord.y > mGreatY ? elements[i].mCoord.y : mGreatY;
	}

	mRoot = new cNode<T>(coord(mLessX, mLessY), coord(mGreatX, mGreatY), elements);
	mOVF = OVF;

	if ( mRoot->mOverflow(mOVF) ) {
		mRoot->mCreateQuad();
		mRoot->mAssignData();
	}
}

template <typename T>
bool cQTree<T>::find(coord c1, coord c2){

}

template <typename T>
void cQTree<T>::mInsert(cData<T> data){

	cNode<T>* tmp = mRoot;
	while( !(tmp->mIsLeaf()) ){
		if( data.mCoord.x < tmp->mX && data.mCoord.y > tmp->mY ){
			tmp = tmp->mChild[0];
		}
		else if( data.mCoord.x > tmp->mX && data.mCoord.y > tmp->mY ){
			tmp = tmp->mChild[1];
		}
		else if( data.mCoord.x < tmp->mX && data.mCoord.y < tmp->mY ){
			tmp = tmp->mChild[2];
		}
		else if( data.mCoord.x > tmp->mX && data.mCoord.y < tmp->mY ){
			tmp = tmp->mChild[3];
		}
	}
	tmp->mElements.push_back(data);
	if ( tmp->mOverflow(mOVF) ) {
		tmp->mCreateQuad();
		tmp->mAssignData();
	}
}

template <typename T>
cQTree<T>::~cQTree(){

}
