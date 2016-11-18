#include "node.hpp"
#include<stack>

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
		void mExplosion(cNode<T>*);
		bool mFindElement(cData<T>);
		bool mFindByRange(coord, coord, cNode<T>*);
		bool mDeleteElement(cData<T>);
		void print(cNode<T>*);
		bool mInsideQuad(coord, coord, coord);
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

	mExplosion(mRoot);
}

template <typename T>
bool cQTree<T>::mFindElement(cData<T> data){

	cNode<T>* tmp = mRoot;
	while( tmp->mInside(data) && !(tmp->mIsLeaf()) ){
		if(tmp->mChild[0]->mInside(data) ){
			tmp = tmp->mChild[0];
		}
		else if(tmp->mChild[1]->mInside(data) ){
			tmp = tmp->mChild[1];
		}
		else if(tmp->mChild[2]->mInside(data) ){
			tmp = tmp->mChild[2];
		}
		else if(tmp->mChild[3]->mInside(data) ){
			tmp = tmp->mChild[3];
		}
	}
	for (uint i = 0; tmp && i < tmp->mElements.size(); ++i) {
		if (tmp->mElements[i] == data) {
			return true;
		}
	}
	return false;
}

template <typename T>
void cQTree<T>::mInsert(cData<T> data){

	if ( mFindElement(data) ) {
		return;
	}
	cNode<T>* tmp = mRoot;
	// cout<<"Insertion"<<endl;
	while( tmp && !(tmp->mIsLeaf()) ){
		if(tmp->mChild[0]->mInside(data) ){
			tmp = tmp->mChild[0];
		}
		else if(tmp->mChild[1]->mInside(data) ){
			tmp = tmp->mChild[1];
		}
		else if(tmp->mChild[2]->mInside(data) ){
			tmp = tmp->mChild[2];
		}
		else if(tmp->mChild[3]->mInside(data) ){
			tmp = tmp->mChild[3];
		}
	}

	tmp->mElements.push_back(data);

	mExplosion(tmp);

}


template <typename T>
void cQTree<T>::mExplosion(cNode<T>* tmp){

	if( !tmp ){
		return;
	}

	if ( tmp->mOverflow(mOVF) ) {
		// cout<<"Split"<<endl;
		tmp->mCreateQuad();
		// cout<<"Assign"<<endl;
		tmp->mAssignData();
	}
	for (int i = 0; i < 4; ++i) {

		if( tmp->mChild[i] && tmp->mChild[i]->mOverflow(mOVF) ){
			// cout<<"Verify Sons"<<endl;
			mExplosion(tmp->mChild[i]);
		}
	}
}


template <typename T>
void cQTree<T>::print(cNode<T>* tmp){
	cout<<"Bordes: "<<tmp->mCoord1.x<<"-"<<tmp->mCoord1.y<<endl;
	cout<<"Bordes: "<<tmp->mCoord2.x<<"-"<<tmp->mCoord2.y<<endl;
	if ( !(tmp) ) {
		return;
	}
	if ( tmp->mIsLeaf() ) {
		cout<<"("<<tmp->mX<<"-"<<tmp->mY<<"): ";
		for (uint i = 0; i < tmp->mElements.size(); ++i) {
			cout<<tmp->mElements[i].mData<<"("<<tmp->mElements[i].mCoord.x<<","<<tmp->mElements[i].mCoord.y<<")"<<"-";
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
bool cQTree<T>::mDeleteElement(cData<T> data){

	cNode<T>* tmp = mRoot;
	cNode<T>* parent;
	cout<<tmp->mInside(data)<<endl;
	while( !(tmp->mIsLeaf()) ){
		parent = tmp;
		if(tmp->mChild[0]->mInside(data) ){
			tmp = tmp->mChild[0];
		}
		else if(tmp->mChild[1]->mInside(data) ){
			tmp = tmp->mChild[1];
		}
		else if(tmp->mChild[2]->mInside(data) ){
			tmp = tmp->mChild[2];
		}
		else if(tmp->mChild[3]->mInside(data) ){
			tmp = tmp->mChild[3];
		}
	}
	for (uint i = 0; tmp && i < tmp->mElements.size(); ++i) {
		if (tmp->mElements[i] == data) {
			tmp->mElements.erase(tmp->mElements.begin() + i);
			//return true;
		}
	}
	int elements;
	vector< cData< T > > new_data;
	for (int i=0; i<4; i++)
	{
		elements+=parent->mChild[i]->mElements.size()
		for (int j=0; j<mChild[i].mElements.size();j++)
		{
			new_data.push_back(mChild[j].mElements[j])
		}
	}
	if (elements == mOVF)
	{
		parent->mElements = new_data;
		parent->mChild.clear()
	}
	return true;
}
template <typename T>

bool cQTree<T>::mFindByRange(coord c1, coord c2, cNode<T>* tmp){

	if( tmp->mIsLeaf() ){
		// cout<<"Is leaf"<<endl;

		for (uint i = 0; i < tmp->mElements.size(); ++i) {
			if( mInsideQuad(tmp->mElements[i].mCoord, c1, c2) ){
				cout<<tmp->mElements[i].mData<<"("<<tmp->mElements[i].mCoord.x<<","<<tmp->mElements[i].mCoord.y<<")"<<"-";
			}
		}
		return true;
	}

	if ( tmp->mInside(c1, c2) ) {
		for (int i = 0; i < 4; ++i) {
			mFindByRange(c1, c2, tmp->mChild[i]);
		}
	}
}

template <typename T>
bool cQTree<T>::mInsideQuad(coord c1, coord c2, coord c3){
	return c1.x >= c2.x && c1.y >= c2.y && c1.x <= c3.x && c1.y <= c3.y;
}

template <typename T>
cQTree<T>::~cQTree(){

}
