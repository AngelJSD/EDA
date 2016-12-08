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

#endif //KD_TREE_NODE_H