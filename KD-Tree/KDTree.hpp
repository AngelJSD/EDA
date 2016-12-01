#include "Node.hpp"

template <typename T>
class cKDTree {
private:
	cNode<T>* mRoot;
	int mDimensions;
public:
	cKDTree<T> (int);
	void mInsert(cCoordinate);
	virtual ~cKDTree ();

};
