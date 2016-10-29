#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <cmath>
#include <iostream>
#include <cstdio>

using namespace std;
using namespace cv;

int main(int argc, char*argv[]){

	if(argc!=3){
		cout<<"usage: ./ms main.png match.png"<<endl;
		return 1;
	}

	Mat src = imread(argv[1]);
	Mat match = imread(argv[2]);

	Mat srcGray;
	Mat matchGray;

	cvtColor(src, srcGray, CV_BGR2GRAY);
	cvtColor(match, matchGray, CV_BGR2GRAY);

	Mat src_th, match_th;
	threshold(srcGray, src_th, 125, 255, THRESH_BINARY_INV);
	threshold(matchGray, match_th, 125, 255, THRESH_BINARY_INV);

	vector<vector<Point> > src_contours;
	vector<Vec4i> src_hierarchy;
	findContours(src_th, src_contours, src_hierarchy, CV_RETR_TREE,  CV_CHAIN_APPROX_SIMPLE);

	vector<vector<Point> > match_contours;
	vector<Vec4i> match_hierarchy;

	findContours(match_th, match_contours, match_hierarchy, CV_RETR_TREE,  CV_CHAIN_APPROX_SIMPLE);

	double matchR;

	for(int i=0;i<src_contours.size();++i){
		matchR += matchShapes(src_contours[i], match_contours[1], CV_CONTOURS_MATCH_I1,0);
	}

	cout<<"matchR: "<<float(matchR/src_contours.size())<<endl;
	printf( "Done \n" );

}
