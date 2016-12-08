#include "Node.hpp"

template <typename T>
class cKDTree {
private:
	cNode<T>* mRoot;

public:
    int mDimensions;
	cKDTree<T> (int);
	void mInsert(cCoordinate);
    bool mInsertAux(cCoordinate,cNode<T>*,int);
	virtual ~cKDTree ();
    void print();
    void print2(cNode<T>* t, int nivel);

};
