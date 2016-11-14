#include "coord.hpp"

template <typename T>
struct cData{
	public:
		T mData;
		coord mCoord;
		cData(T data, coord c1){
			mData = data;
			mCoord = c1;
		}

		bool operator==(cData<T> data){
			return mData == data.mData && mCoord == data.mCoord;
		}
};
