#include <iostream>
#include <vector>

using namespace std;

class cCoordinate {

	private:

		vector<float> mCoordinates;

	public:
		cCoordinate (vector<float> coord);
		int mGetDimension();
		cCoordinate operator=(cCoordinate coord);
		float operator[](int pos);

};
