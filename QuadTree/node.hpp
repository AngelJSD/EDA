#include <iostream>
#include <vector>
#include "datos.hpp"

using namespace std;

template <typename T>
class cNode{

	public:

	//Variables

		float mX;
		float mY;

		coord mCoord1;
		coord mCoord2;

		vector< cData< T > > mElements;
		vector< cNode* > mChild;

	//Métodos
		cNode(coord, coord, vector<cData<T> >);
		cNode(coord, coord);
		bool mInside(cData<T>);
		bool mInside(coord);
		bool mInside(coord, coord);
		bool mOverflow(int);
		bool mUnderflow();
		bool mIsLeaf();
		void mCreateQuad();
		void mAssignData();
		~cNode();

};

//Root
template <typename T>
cNode<T>::cNode(coord c1, coord c2, vector<cData<T> > elements){

	vector<coord> crd = c1.generate(c1,c2);
	mCoord1 = crd[0];
	mCoord2 = crd[1];

	// cout<<"constructor"<<endl;

	mX = ( mCoord1.x + mCoord2.x ) / 2.0;
	mY = ( mCoord1.y + mCoord2.y ) / 2.0;

	for (uint i = 0; i < elements.size(); ++i) {
		mElements.push_back(elements[i]);
		// cout<<mElements[i].mData<<"-";
	}
	cout<<endl;

	// cout<<"child resize"<<endl;
	mChild.resize(4);
}

template <typename T>
cNode<T>::cNode(coord c1, coord c2){

	vector<coord> crd = c1.generate(c1,c2);
	mCoord1 = crd[0];
	mCoord2 = crd[1];

	mX = ( mCoord1.x + mCoord2.x ) / 2.0;
	mY = ( mCoord1.y + mCoord2.y ) / 2.0;

	// cout<<"child resize"<<endl;
	mChild.resize(4);
}
template <typename T>
cNode<T>::~cNode(){

}

template <typename T>
bool cNode<T>::mIsLeaf(){
	return mChild[0] == nullptr;
}

template <typename T>
bool cNode<T>::mOverflow(int OVF){
	return mElements.size() > OVF;
}

template <typename T>
bool cNode<T>::mUnderflow(){
	return mElements.size() == 0;
}

template <typename T>
void cNode<T>::mCreateQuad(){

	coord c1(mX, mY);

	coord c2(mCoord1.x, mCoord2.y);
	mChild[0] = new cNode<T>(c1, c2);

	mChild[1] = new cNode<T>(c1, mCoord2);

	mChild[2] = new cNode<T>(mCoord1, c1);

	c2 = coord(mCoord2.x, mCoord1.y);
	mChild[3] = new cNode<T>(c1, c2);

}


template <typename T>
bool cNode<T>::mInside(coord c1){
	return c1.x >= mCoord1.x && c1.y >= mCoord1.y && c1.x <= mCoord2.x && c1.y <= mCoord2.y;
}


template <typename T>
bool cNode<T>::mInside(coord c1, coord c2){
	//cout<<"Evaluando nodo ("<<mCoord1.x<<" , "<<mCoord1.y<<") ("<<mCoord2.x<<" , "<<mCoord2.y<<")"<<endl;
	if(( (mCoord1.x >= c1.x && mCoord1.x <= c2.x) || (mCoord2.x >= c1.x && mCoord2.x <= c2.x) ) && ( (mCoord1.y >= c1.y && mCoord1.y <= c2.y) || (mCoord2.y >= c1.y && mCoord2.y <= c2.y) )){
		//cout<<"Entre si otra vez :v"<<endl;
	}
	return ( (mCoord1.x >= c1.x && mCoord1.x <= c2.x) || (mCoord2.x >= c1.x && mCoord2.x <= c2.x) ) && ( (mCoord1.y >= c1.y && mCoord1.y <= c2.y) || (mCoord2.y >= c1.y && mCoord2.y <= c2.y) );
}

template <typename T>
bool cNode<T>::mInside(cData<T> data){
	// cout<<"Data: "<<data.mCoord.x<<"-"<<data.mCoord.y<<" ---- nodo: "<<mCoord1.x<<"-"<<mCoord1.y<<"--"<<mCoord2.x<<"-"<<mCoord2.y<<endl;
	if( data.mCoord.x <= mCoord2.x && data.mCoord.x >= mCoord1.x && data.mCoord.y <= mCoord2.y && data.mCoord.y >= mCoord1.y ){
		return true;
	}
	return false;
}

template <typename T>
void cNode<T>::mAssignData(){
	for (uint i = 0; i < mElements.size(); ++i) {
		// cout<<mElements[i].mData<<endl;
		if( mChild[0]->mInside(mElements[i]) ){
			mChild[0]->mElements.push_back(mElements[i]);
		}
		else if( mChild[1]->mInside(mElements[i]) ){
			mChild[1]->mElements.push_back(mElements[i]);
		}
		else if( mChild[2]->mInside(mElements[i]) ){
			mChild[2]->mElements.push_back(mElements[i]);
		}
		else if( mChild[3]->mInside(mElements[i]) ){
			mChild[3]->mElements.push_back(mElements[i]);
		}
	}
	mElements.clear();

}
