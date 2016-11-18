#include "Options.h"
#include "MidiFile.h"
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <iostream>
#include <vector>
#include <math.h>
#include <stack>

#include "bkt.h"

using namespace std;

int main(int argc, char const *argv[]) {

	if( argc < 3 ){
		printf("** Error. Usage: ./main.o image1 radio\n");
		return -1;
	}

	string files[1] = {"sound.txt"};
	bkt<string> arbol(files,argc);

	//cout<<arbol.root->hijos.size()<<endl;
	//cout<<arbol.my_find("hla")<<endl;
	// cout<<"ojo1 "<<endl;
	arbol.my_print();

	cout<<endl<<endl;
	int radio = atoi(argv[2]);
	arbol.my_search(arbol.root, argv[1], radio);
	printf( "Done \n" );

	//waitKey(0);
	return 0;
}
