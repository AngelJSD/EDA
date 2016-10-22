
template <typename T>
class cNode{
	public:

		T mData;
		cNode<T>* mChild[2];
		int mMediana=0;

		cNode(){
			mChild[0]=nullptr;
			mChild[1]=nullptr;
		}

};
