
template <typename T>
class cNode<T>{
	public:
		
		T mData;
		cNode<T>* mChild[2];
		int mMediana;

		cNode(T data, int mediana){
			mData = data;
			mMediana = mediana;
		}

};
