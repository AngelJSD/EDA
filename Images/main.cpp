#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;

/*Esta es la función si decides tomar el primer caso
 *Si decides escoger otro caso cambia en esta linea el 0 por el caso que tomes:
 *	double comparison = compareHist( hist_base, hist_test1, 0 );
 *															^
 */

double compare(string, string);

int main( int argc, char** argv ){

	Mat src_base, hsv_base;
	Mat src_test1, hsv_test1;

	/// Load three images with different environment settings
	if( argc < 3 )
	{
	    printf("** Error. Usage: ./main.o image1 image2\n");
	    return -1;
	}

	src_base = imread( argv[1], IMREAD_COLOR );
	src_test1 = imread( argv[2], IMREAD_COLOR );

	if (src_base.empty() || src_test1.empty() ){
	  cout << "Can't read one of the images" << endl;
	  return -1;
	}

	/// Convert to HSV
	cvtColor( src_base, hsv_base, COLOR_BGR2HSV );
	cvtColor( src_test1, hsv_test1, COLOR_BGR2HSV );

	int h_bins = 50; int s_bins = 60;
	int histSize[] = { h_bins, s_bins };

	float h_ranges[] = { 0, 180 };
	float s_ranges[] = { 0, 256 };

	const float* ranges[] = { h_ranges, s_ranges };

	int channels[] = { 0, 1 };


	MatND hist_base;
	MatND hist_test1;

	calcHist( &hsv_base, 1, channels, Mat(), hist_base, 2, histSize, ranges, true, false );
	calcHist( &hsv_test1, 1, channels, Mat(), hist_test1, 2, histSize, ranges, true, false );

	normalize( hist_base, hist_base, 0, 1, NORM_MINMAX, -1, Mat() );
	normalize( hist_test1, hist_test1, 0, 1, NORM_MINMAX, -1, Mat() );

	for( int i = 0; i < 4; i++ )
	{
	    int compare_method = i;
	    double base_test1 = compareHist( hist_base, hist_test1, compare_method );

	    printf( " Method [%d] - Similarity: %f \n", i, base_test1 );
	}

	printf("%f\n", compare("m3.jpg", "pd2.jpg"));

	namedWindow( argv[1], WINDOW_AUTOSIZE );
		imshow( argv[1], src_base );

	namedWindow( argv[2], WINDOW_AUTOSIZE );
		imshow( argv[2], src_test1 );

	printf( "Done \n" );

	waitKey(0);
	return 0;
}

double compare(string img1, string img2){

	Mat src1, hsv_base;
	Mat src2, hsv_test1;

	/// Load three images with different environment settings

	src1 = imread( img1, IMREAD_COLOR );
	src2 = imread( img2, IMREAD_COLOR );

	if (src1.empty() || src2.empty() ){
		cout << "Can't read one of the images" << endl;
		return -1;
	}

	/// Convert to HSV
	cvtColor( src1, hsv_base, COLOR_BGR2HSV );
	cvtColor( src2, hsv_test1, COLOR_BGR2HSV );

	int h_bins = 50; int s_bins = 60;
	int histSize[] = { h_bins, s_bins };

	float h_ranges[] = { 0, 180 };
	float s_ranges[] = { 0, 256 };

	const float* ranges[] = { h_ranges, s_ranges };

	int channels[] = { 0, 1 };

	MatND hist_base;
	MatND hist_test1;

	calcHist( &hsv_base, 1, channels, Mat(), hist_base, 2, histSize, ranges, true, false );
	calcHist( &hsv_test1, 1, channels, Mat(), hist_test1, 2, histSize, ranges, true, false );

	normalize( hist_base, hist_base, 0, 1, NORM_MINMAX, -1, Mat() );
	normalize( hist_test1, hist_test1, 0, 1, NORM_MINMAX, -1, Mat() );

	double comparison = compareHist( hist_base, hist_test1, 0 );

	return comparison;
}
