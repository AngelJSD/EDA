#include "node.h"

template<typename T>
class cVPT<T>{
	public:
		cNode<T>* mRoot;

		cVPT(){
			mRoot == nullptr;
		};

		vector<pair<string, int> > mDistances;

		void generateDistances();
		int Distance(string, string);
		int Distance(mus, mus);
		int Mediana(int, int);

		void Generation(T files[], int n){

					int i,f,mediana,j;
					cNode<T>* p;
					vector<pair<T,int> > distancias=getWords(files[0]);
					vector<pair<T,int> > l,r;
					p=mRoot;
					stack<pair<cNode<T>*,vector<pair<T,int> > > > pila;
					T a;
					pila.push(make_pair(p,distancias);
					i=0;
					while(!pila.empty()){
									p=pila.top().first;
									distancias=pila.top().second;
									pila.pop();
									j=rand()%distancias.size();
									p->mData=distancias[j].first;
									distancias.erase(distancias[j]);
									i=0;
									f=palabras.size()-1;
									efe();
									p->mediana=Mediana(i,f);
									int k;

									for(k=0; distancias[k]<=mediana; ++k)
													l.push_back(distancias[k]);

									for(; k<distancias.size(); ++k)
													r.push_back(distancias[k]);

									pila.push(make_pair(p->mChild[0],l));
									pila.push(make_pair(p->mChild[1],r));
					}
		};

};

int cpalabrasPT::Mediana(int i, int f){

				int med;

				if((f-i)%2 != 0)  //es par
								med=(palabras[(i + f)/2] + palabras[(i + f)/2 + 1])/2;
				else
								med=palabras[(i + f)/2];

				return med;
}

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
