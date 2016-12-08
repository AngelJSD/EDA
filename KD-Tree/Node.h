#ifndef KD_TREE_NODE_H
#define KD_TREE_NODE_H
#include "Coordinate.h"

class cNode{
	private:
		cCoordinate mCoord;
		int mCutCoordinate;

	public:
		cNode* mChild[2];
		cNode(cCoordinate, int);
		bool mIsLeaf();
		void mSetLeftSon(cNode*);
		void mSetRightSon(cNode*);
		int mGetCutCoordinateVal();
		void mSetCutCoordinate(int);
		float mGetCoordinate(int);
		cCoordinate mGetCoordinate();
		cNode** mGetChildDir(bool);
		cNode* mGetChild(bool);
		void mPrintCoordinates();
		virtual ~cNode ();
};

cNode::cNode(cCoordinate coor, int cutCoordinate): mCoord(coor)
{
	mChild[0] = mChild[1] = nullptr;
	mCutCoordinate = cutCoordinate;
};

cNode::~cNode(){

};

bool cNode::mIsLeaf(){
	return (mChild[0] || mChild[1]);
};


void cNode::mSetLeftSon(cNode* son){
	mChild[0] = son;
};


void cNode::mSetRightSon(cNode* son){
	mChild[1] = son;
};


int cNode::mGetCutCoordinateVal(){
	return mCutCoordinate;
};


void cNode::mSetCutCoordinate(int cutCoordinate){
	mCutCoordinate = cutCoordinate;
};


float cNode::mGetCoordinate(int dimension){
	return mCoord[dimension];
};


cCoordinate cNode::mGetCoordinate(){
	return mCoord;
}


cNode** cNode::mGetChildDir(bool child){
	return &(mChild[child]);
}

cNode* cNode::mGetChild(bool child){
	return (mChild[child]);
}

void cNode::mPrintCoordinates(){
	mCoord.print();
}


#endif //KD_TREE_NODE_H