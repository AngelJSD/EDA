#include "Node.h"

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

void cNode::mSetCoordinate(cCoordinate Coordinate){
    mCoord = Coordinate;
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