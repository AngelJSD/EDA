#include "node.h"

template<typename T>
class cVPT<T>{
	public:
		cNode<T>* mRoot;

		cVPT(){
			mRoot == nullptr;
		};

		vector<pair<string, int>> mDistances;

		void generateDistances();
		int Distance(string, string);
		int Distance(mus, mus);

		void Generation(T files[], int n){



		};

};

void cVPT::generateDistances(string file){

	ifstream myfile(file);

	if (myfile.is_open()) {

		while (getline(myfile, palabra)) {
			palabras.push_back(make_pair(palabra, num));
			num = num - 1;
		}
		myfile.close();
		palabras.pop_back();
	}

}

int cVPT::Distance(string s1, string s2){
	int N1 = s1.size();
	int N2 = s2.size();
	int i, j;
	vector<int> T(N2+1);

	for ( i = 0; i <= N2; i++ ){
		T[i] = i;
	}

	for ( i = 0; i < N1; i++ ){
		T[0] = i+1;
		int corner = i;
		for ( j = 0; j < N2; j++ )
		{
			int upper = T[j+1];
			if ( s1[i] == s2[j] ){
				T[j+1] = corner;
			}
			else{
				T[j+1] = min(T[j], min(upper, corner)) + 1;
			}
		corner = upper;
		}
	}
	return T[N2];
}
