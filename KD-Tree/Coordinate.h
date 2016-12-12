#ifndef KD_TREE_COORDINATE_H
#define KD_TREE_COORDINATE_H

#include <iostream>
#include <vector>

using namespace std;

class cCoordinate {
	private:
		vector<float> mCoordinates;

	public:
		cCoordinate(vector<float>);
        unsigned long mGetDimension();
		void print();
		cCoordinate operator=(cCoordinate coord);
		bool operator==(cCoordinate coord);
		float operator[](int pos);
};

#endif //KDTREE2_COORDINATE_H
