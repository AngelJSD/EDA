#ifndef BKT_H
#define BKT_H

#include <fstream>
#include <string>

using namespace std;
//using namespace cv;

template<typename T>

class Node{

    public:
        Node(){
        }

        //vector<pair<int,Node*> >hijos;
		vector<pair<double,Node*> >hijos;
        T dato;
};

template<typename T>

class bkt
{
    public:
        bkt(T files[], int a){

            root=new Node<T>();
            generation(files);
            argc=a;

        }

        Node<T> *root;

        Options  options;
		int      quarterQ = 0;  // used with -q option: time units in quarter notes.
		int      joinQ    = 0;  // used with -j option: join tracks before printing.
		int      secondsQ = 0;  // used with -s option: print times in seconds.

		int argc;


		void     checkOptions        (Options& opts);
		void     example             (void);
		void     usage               (const string& command);

        //int distancia(T, T);
		//double distancia(string, string);
		int dist(vector<int>, vector<int>);
        bool my_insert(T);
        bool my_find(T);
        void my_search(Node<T>*, T, int);
        void my_print();

        int abs(int a){
    
		    if(a<0)
		      return a*-1;
		    return a;
		}

        void generation(T files[]){

            bool r=true;
            string file=files[0];
            ifstream myfile(file);
            string palabra;

            if ( myfile.is_open() ) {

                while ( getline( myfile, palabra) ) {
					// cout<<"palabra: "<<palabra<<endl;

                    if(r) {
                        root->dato=palabra;

                        r=false;
                    }
                    else my_insert(palabra);
                }

                myfile.close();
            }
            return;
        }

        int distancia(string a, string b) {

        	/*char* argv[2];
			
			char* writable = new char[a.size() + 1];
			std::copy(a.begin(), a.end(), writable);
			writable[a.size()] = '\0';

			char* writable1 = new char[b.size() + 1];
			std::copy(b.begin(), b.end(), writable1);
			writable1[b.size()] = '\0';

		    argv[0]=writable;
			argv[1]=writable1;*/



		   //options.setOptions(argc, argv);

		   //checkOptions(options);
		   //options.define("q|quarter=b", "Display ticks in quarter note units");
		   
		   //options.define("j|join=b",    "Join tracks before printing");
		   //options.define("s|seconds=b", "Display times in seconds");

		   /*options.define("author=b",   "Author of the program");
		   	options.define("version=b",  "Version of the program");
		   //options.define("example=b",  "Example useage of the program");
		   //options.define("h|help=b",   "List of options for the program");
		   
		   //options.process();
		   cout<<"vivo"<<endl;


		   if (options.getBoolean("author")) {
		      cout << "Written by Craig Stuart Sapp, "
		              "craig@ccrma.stanford.edu, February 2015" << endl;
		      exit(0);
		   } else if (options.getBoolean("version")) {
		      cout << "duration, version 1.0 (19 Feb 2015)\n"
		              "compiled: " << __DATE__ << endl;
		      exit(0);
		   }*/

		   //quarterQ  = options.getBoolean("quarter");
		   //joinQ     = options.getBoolean("join");
		   //secondsQ  = options.getBoolean("seconds");

		   if (secondsQ) {
		      quarterQ = 0;
		   }

		   if (options.getArgCount() > 2) {
		      cerr << "Error: One input file or standard input is required." << endl;
		      exit(1);
		   }



		   vector<int> vect1,vect1t,vect2,vect2t;
		   
		   MidiEvent* mev;
		   int duration;
		   int status;
		   MidiFile midifile, midifile1;
		   
		   if (secondsQ) {
		      midifile.doTimeAnalysis();
		   }
		   
		   //if (options.getArgCount()) {
		      status = midifile.read(a);
		   /*} else {
		      status = midifile.read(cin);
		   }*/
		   
		   //if (options.getArgCount()) {
		      status = midifile1.read(b);
		   /*} else {
		      status = midifile1.read(cin);
		   }*/
		   if (status == 0) {
		      cerr << "Error: could not read MIDI file" << endl;
		      exit(1);
		   }
		   
		   int tpq = midifile.getTicksPerQuarterNote();
		   int tpq1 = midifile1.getTicksPerQuarterNote();
		   int cont=0;
		   int cont1=0;
		   midifile.linkNotePairs();
		   midifile1.linkNotePairs();
		   
		   midifile.joinTracks();
		   midifile1.joinTracks();
		   
		   int track = 0;
		   
		   for (int i=0; i<midifile[track].size(); i++) {
		     
		      if (!midifile[track][i].isNoteOn()) {
		         continue;
		      }
		      if (secondsQ) {
		            duration = midifile[track][i].getDurationInSeconds();
		         } else {
		            duration = midifile[track][i].getTickDuration();
		         }

		         if (secondsQ) {
		            vect1t.push_back(duration);
		         } else if (quarterQ) {
		            vect1t.push_back(duration/tpq);
		         } else {
		            vect1t.push_back(duration);
		         }
		      vect1.push_back((int)midifile[track][i][1]);
		      cont++;
		   }
		   
		   track = 0;
		   
		   for (int i=0; i<midifile1[track].size(); i++) {
		     
		      if (!midifile1[track][i].isNoteOn()) {
		         continue;
		      }
		      if (secondsQ) {
		            duration = midifile1[track][i].getDurationInSeconds();
		         } else {
		            duration = midifile1[track][i].getTickDuration();
		         }

		         if (secondsQ) {
		            vect2t.push_back(duration);
		         } else if (quarterQ) {
		            vect2t.push_back(duration/tpq1);
		         } else {
		            vect2t.push_back(duration);
		         }
		      vect2.push_back((int)midifile1[track][i][1]);
		      cont1++;
		   }
		   
		   return ceil((dist(vect1,vect2)+dist(vect1t,vect2t)-(abs(cont-cont1)))*100/(2*(cont+cont1)));
		}
};

template<typename T>

int bkt<T>::dist(vector<int> s1, vector<int> s2){

	int N1 = s1.size();
	int N2 = s2.size();
	int i, j;
	vector<int> T1(N2+1);

	for ( i = 0; i <= N2; i++ ){
		T1[i] = i;
	}

	for ( i = 0; i < N1; i++ ){
		T1[0] = i+1;
		int corner = i;
		for ( j = 0; j < N2; j++ )
	 	{
		  	int upper = T1[j+1];
			if ( s1[i] == s2[j] ){
				T1[j+1] = corner;
			}
			else{
				T1[j+1] = min(T1[j], min(upper, corner)) + 1;
			}
		corner = upper;
		}
	}
	return T1[N2];
}


/*
template<typename T>

int bkt<T>::distancia(T s1, T s2){

	int N1 = s1.size();
	int N2 = s2.size();
	int i, j;
	vector<int> T1(N2+1);

	for ( i = 0; i <= N2; i++ ){
		T1[i] = i;
	}

	for ( i = 0; i < N1; i++ ){
		T1[0] = i+1;
		int corner = i;
		for ( j = 0; j < N2; j++ )
	 	{
		  	int upper = T1[j+1];
			if ( s1[i] == s2[j] ){
				T1[j+1] = corner;
			}
			else{
				T1[j+1] = min(T1[j], min(upper, corner)) + 1;
			}
		corner = upper;
		}
	}
	return T1[N2];
}*/
/*
template<typename T>

double bkt<T>::distancia(string img1, string img2){

	Mat src1, hsv_base;
	Mat src2, hsv_test1;

	/// Load three images with different environment settings

	src1 = imread( img1, IMREAD_COLOR );
	src2 = imread( img2, IMREAD_COLOR );

	if (src1.empty() || src2.empty() ){
		cout<<"Imagen fallida: "<<img1<<endl;
		cout<<"Imagen fallida: "<<img2<<endl;
		cout << "Can't read one of the images" << endl;
		return -1;
	}

	/// Convert to HSV
	cvtColor( src1, hsv_base, COLOR_BGR2HSV );
	cvtColor( src2, hsv_test1, COLOR_BGR2HSV );

	int h_bins = 100;
	int s_bins = 100;
	int histSize[] = { h_bins, s_bins };

	float h_ranges[] = { 0, 256 };
	float s_ranges[] = { 0, 256 };

	const float* ranges[] = { h_ranges, s_ranges };

	int channels[] = { 0, 1 };

	MatND hist_base;
	MatND hist_test1;

	calcHist( &hsv_base, 1, channels, Mat(), hist_base, 2, histSize, ranges, true, false );
	calcHist( &hsv_test1, 1, channels, Mat(), hist_test1, 2, histSize, ranges, true, false );

	normalize( hist_base, hist_base, 0, 1, NORM_MINMAX, -1, Mat() );
	normalize( hist_test1, hist_test1, 0, 1, NORM_MINMAX, -1, Mat() );

	double comparison = ceil( (1 - abs(compareHist( hist_base, hist_test1, 0 ))) * 100 );
	//double comparison = compareHist( hist_base, hist_test1, 1 );

	return comparison;
}
*/
template<typename T>

bool bkt<T>::my_find(T s){

    Node<T> **p=&root;
    Node<T> *aux=nullptr;
    int i=0;

    for(; (*p) && (*p)->dato!=s && i<(*p)->hijos.size(); ++i){
        //cout<<"h"<<endl;
        aux=(*p);
        if(distancia((*p)->dato,s)==(*p)->hijos[i].first){
            //cout<<(*p)->dato<<endl;
            p=&(*p)->hijos[i].second;
            i=0;
        }
    }

    if((*p) && (*p)->dato == s) return 1;
    return 0;

}

template<typename T>

bool bkt<T>::my_insert(T s){

	//cout<<"i"<<s<<endl;
	Node<T> **p = &root;
	Node<T> *n;

	int i = 0;

	if( my_find(s) ) {
		return 0;
	}

	for(; (*p) && i < (*p)->hijos.size(); ++i){

		// cout<<"ojo1 "<<i<<endl;
		if(distancia((*p)->dato,s)==(*p)->hijos[i].first){
		//if(sound(argv)==(*p)->hijos[i].first){
			//cout<<"ojo"<<distancia((*p)->dato,s)<<(*p)->hijos[i].first<<endl;
			p = &(*p)->hijos[i].second;
			i = -1; //***s
		}
	}

	n=new Node<T>();

	n->dato = s;
	(*p)->hijos.push_back(make_pair(distancia((*p)->dato,s),n));

	//cout<<distancia((*p)->dato,s)<<endl;
	return 1;
}

template<typename T>

void bkt<T>::my_search(Node<T>* n, T s, int radius){

	
    int d=distancia(n->dato,s);
	//double d=distancia(n->dato,s);
	//int d=distancia(argv);

    if(d<=radius){
		cout<<n->dato<<' '<<d<<endl;

		/*namedWindow( n->dato, WINDOW_AUTOSIZE );
		imshow( n->dato, imread( n->dato, IMREAD_COLOR ) );*/

	}
    for(int i=0; i<n->hijos.size(); ++i)
        if(n->hijos[i].first>=d-radius && n->hijos[i].first<=d+radius){
            my_search(n->hijos[i].second, s, radius);
		}
    return;
}

template<typename T>

void bkt<T>::my_print(){

    stack<Node<T>*> pila;
    Node<T>* aux;
    cout<<root->dato<<","<<endl;
    pila.push(root);

    while(!pila.empty()){

        aux=pila.top();
        pila.pop();
        cout<<aux->dato<<"->";
        for(int i=0; i<aux->hijos.size(); ++i)
        {
            cout<<aux->hijos[i].first<<"-"<<aux->hijos[i].second->dato<<",";
            pila.push(aux->hijos[i].second);
        }
        cout<<endl;
    }
}


#endif // BKT_H
