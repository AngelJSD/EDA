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
		int mGetDimension();
		void print();
		cCoordinate operator=(cCoordinate coord);
		bool operator==(cCoordinate coord);
		float operator[](int pos);
};


cCoordinate::cCoordinate(vector<float> coord){
	mCoordinates = coord;
};


int cCoordinate::mGetDimension(){
	return mCoordinates.size();
}


cCoordinate cCoordinate::operator=(cCoordinate coord){
	mCoordinates = coord.mCoordinates;
	return *this;
};


bool cCoordinate::operator==(cCoordinate coord) {
	return mCoordinates == coord.mCoordinates;
}


void cCoordinate::print()
{
	cout<<"(";
	for (int i=0;i<mCoordinates.size()-1;i++){
		cout<<mCoordinates[i]<<",";
	}
	cout<<mCoordinates[mCoordinates.size()-1]<<")"<<endl;
}


float cCoordinate::operator[](int pos){
	return mCoordinates[pos];
};

#endif //KDTREE2_COORDINATE_H
