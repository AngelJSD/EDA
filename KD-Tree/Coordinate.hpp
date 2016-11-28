#include <iostream>
#include <vector>

using namespace std;

class cCoordinate {

	private:

		vector<float> mCoordinates;

	public:

		cCoordinate (vector<float> coord){
			mCoordinates = coord;
		};

		virtual ~cCoordinate (){
			mCoordinates.clear();
		};

		cCoordinate operator=(cCoordinate coord){
			mCoordinates = coord.mCoordinates;
		};

		float operator[](int pos){
			return mCoordinates[pos];
		};

};
