#include "Coordinate.hpp"

cCoordinate::cCoordinate (vector<float> coord){
	mCoordinates = coord;
};

int cCoordinate::mGetDimension(){
	return mCoordinates.size();
}

cCoordinate cCoordinate::operator=(cCoordinate coord){
	mCoordinates = coord.mCoordinates;
	return *this;
};

float cCoordinate::operator[](int pos){
	return mCoordinates[pos];
};
