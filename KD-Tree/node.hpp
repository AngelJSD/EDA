#include "Coordinate.hpp"

template <typename T>
class cNode{
	private:

		cCoordinate mCoord;
		cNode<T> mChild[2];
		int mCutCoordinate;

	public:

		cNode<T> (cCoordinate coord, int cutCoordinate){
			mCoord = coord;
			mChild[0] = mChild[1] = nullptr;
			mCutCoordinate = cutCoordinate;
		};

		bool mIsLeaf(){
			return (mChild[0] || mChild[1]);
		};

		int mGetCutCoordinate(){
			return mCoord[mCutCoordinate];
		};

		float mGetCoordinate(int dimension){
			return mCoord[dimension];
		};

		virtual ~cNode<T> ();

};
