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
};
