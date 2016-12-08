#include "Coordinate.hpp"

template <typename T>
class cNode{
	private:
		cCoordinate mCoord;
		cNode<T>* mChild[2];
		int mCutCoordinate;

	public:
		cNode<T> (cCoordinate, int);
		bool mIsLeaf();
		void mSetLeftSon(cNode<T>*);
		void mSetRightSon(cNode<T>*);
		int mGetCutCoordinateVal();
		void mSetCutCoordinate(int);
		float mGetCoordinate(int);
        cCoordinate mGetCoordinate();
        cNode<T>* mGetChild(bool);
        void mPrintCoordinates();
		virtual ~cNode<T> ();

};
