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
		bool find(cNode<T>&);
		void print(cNode<T>*);
		cQTree(vector< cData< T > >, int);
		~cQTree();

};

template <typename T>
cQTree<T>::cQTree(vector< cData< T > > elements, int OVF){

	if (elements.empty()) {
		cout<<"Two elements required."<<endl;
		return;
	}
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
	cout<<"Boundaries: "<<mGreatX<<"-"<<mGreatY<<"--"<<mLessX<<"-"<<mLessY<<endl;

	mRoot = new cNode<T>(coord(mLessX, mLessY), coord(mGreatX, mGreatY), elements);
	mOVF = OVF;

	if ( mRoot->mOverflow(mOVF) ) {
		// cout<<"Overflow"<<endl;
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
	// cout<<"Insertion"<<endl;
	while( tmp && !(tmp->mIsLeaf()) ){
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
		// cout<<"Iteration"<<endl;
	}
	tmp->mElements.push_back(data);
	if ( tmp->mOverflow(mOVF) ) {
		// cout<<"Split"<<endl;
		tmp->mCreateQuad();
		// cout<<"Assign"<<endl;
		tmp->mAssignData();
	}

}

template <typename T>
void cQTree<T>::print(cNode<T>* tmp){
	// cout<<"Bordes: "<<mRoot->mCoord1.x<<"-"<<mRoot->mCoord1.y<<endl;
	// cout<<"Bordes: "<<mRoot->mCoord2.x<<"-"<<mRoot->mCoord2.y<<endl;
	if ( !(tmp) ) {
		return;
	}
	if ( tmp->mIsLeaf() ) {
		cout<<"("<<tmp->mX<<"-"<<tmp->mY<<"): ";
		for (uint i = 0; i < tmp->mElements.size(); ++i) {
			cout<<tmp->mElements[i].mData<<"-";
		}
		cout<<endl;
	}
	else{
		cout<<"("<<tmp->mX<<"-"<<tmp->mY<<")\n";
		for (uint i = 0; i < tmp->mChild.size(); i++) {
			print(tmp->mChild[i]);
		}
	}

}

template <typename T>

bool cQTree<T>::mVerify(cNode<T> &tmp){
	if ( !(tmp) || tmp->mIsLeaf() ) {
		return;
	}
	else{
		for (uint i = 0; i < tmp->mChild.size(); i++) {

		}
	}

}

template <typename T>
cQTree<T>::~cQTree(){

}
