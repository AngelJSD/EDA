#ifndef KD_TREE_KDTREE_H
#define KD_TREE_KDTREE_H
#include <math.h>
#include "Node.h"

class cKDTree {
	public:
		cNode* mRoot;
		int mDimensions;
		cKDTree(int);
		void mInsert(cCoordinate);
		bool mInsertAux(cCoordinate,cNode**,int);
		virtual ~cKDTree ();
		void print();
		void print2(cNode* t, int nivel);
        float distance(cCoordinate , cCoordinate );
        string vocabulary="xyz";
        cNode* mFindMin(cNode*, int, int);
        cNode* mMinimum(cNode*, cNode*, cNode*, int);
        cNode* mDelete(cCoordinate, cNode *, int);
        cNode* mFindNearestNeighborAux(cCoordinate , cNode**,cNode* ,int, float);
        cNode* MFindNearestNeighbor(cCoordinate);
};

#endif //KD_TREE_KDTREE_H
