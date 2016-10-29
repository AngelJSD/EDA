#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
<<<<<<< Updated upstream
#include <stack>
#include <queue>
=======
>>>>>>> Stashed changes
#include "node.h"

using namespace std;

template<typename T>
class cVPT{

	private:

<<<<<<< Updated upstream
		bool static mySort(pair<string, int> i, pair<string, int> j) {
=======
		bool mySort(pair<string, int> i, pair<string, int> j) {
>>>>>>> Stashed changes
			return (i.second < j.second);
		}

	public:
		cNode<T>* mRoot;

		cVPT(T files[]){
			mRoot == nullptr;
			Generation(files);
		};

<<<<<<< Updated upstream
		vector<pair<T, int>> distancias;
=======
		vector<pair<T, int>> mDistances;
>>>>>>> Stashed changes

		void Distances(vector<pair<string, int> > &plbs, string rnd){
			for (int i = 0; i < plbs.size(); ++i) {
				plbs[i].second = lDistance(rnd, plbs[i].first);
			}
			sort(plbs.begin(), plbs.end(), mySort);
		}
<<<<<<< Updated upstream

		int lDistance(string s1, string s2){
			int N1 = s1.size();
			int N2 = s2.size();
			int i, j;
			vector<int> vec(N2+1);

			for ( i = 0; i <= N2; i++ ){
				vec[i] = i;
			}

			for ( i = 0; i < N1; i++ ){
				vec[0] = i+1;
				int corner = i;
				for ( j = 0; j < N2; j++ )
				{
					int upper = vec[j+1];
					if ( s1[i] == s2[j] ){
						vec[j+1] = corner;
					}
					else{
						vec[j+1] = min(vec[j], min(upper, corner)) + 1;
					}
				corner = upper;
				}
			}
			return vec[N2];
		}

		int Mediana(int i, int f){
			int med;
			if((f-i)%2 != 0){  //es par
				med=(distancias[(i + f)/2].second + distancias[(i + f)/2 + 1].second)/2;
			}
			else{
				med=distancias[(i + f)/2].second;
			}
			return med;
		}
		vector<pair<string, int>> getWords(string file){

			ifstream myfile(file);
			string palabra;
=======

		int lDistance(string s1, string s2){
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

		vector<pair<string, int>> getWords(string file){

			string palabra;
			ifstream myfile(file);

>>>>>>> Stashed changes
			vector<pair<string, int>> palabras;

			if ( myfile.is_open() ) {

				while ( getline( myfile, palabra) ) {
<<<<<<< Updated upstream
					palabras.push_back( make_pair(palabra, -1) );
				}

				myfile.close();
			}
			return palabras;
		}

		void Generation(T files[]){

			int i,f,mediana,j;
			cNode<T>* p;
			mRoot= new cNode<T>();
			distancias = getWords(files[0]);
			vector<pair<T,int> > l,r;
			p=mRoot;
			stack<pair<cNode<T>*,vector<pair<T,int> > > > pila;
			T a;
			pila.push(make_pair(p,distancias));
			i=0;
			while(!pila.empty()){
				l.clear();
				r.clear();
				p = pila.top().first;
				// cout<<"holi"<<endl;
					// cout<<"holi1"<<endl;
				distancias = pila.top().second;
					// cout<<"holi2"<<endl;
				pila.pop();
					// cout<<"holi3"<<endl;
				if(distancias.size()==0) continue;
				j = rand() % distancias.size();
					//cout<<"aleatorio:"<<distancias[j].first<<endl;
				p->mData = distancias[j].first;
					// cout<<"holi4"<<endl;
				distancias.erase( distancias.begin() + j );
					// cout<<"holi5"<<endl;
				i = 0;
				f = distancias.size()-1;
				Distances(distancias, p->mData);
					// cout<<"holi6"<<endl;
				p->mMediana = Mediana(i,f);
					// cout<<"holi7"<<endl;

				/*for(int z=0; z < distancias.size(); ++z)
				{
					cout<<distancias[z].first<<" , "<<distancias[z].second<<endl;
				}*/
				if(distancias.size()!=0){
					int k;
					for(k = 0; k<distancias.size() && distancias[k].second <= p->mMediana; k++)
						l.push_back(distancias[k]);
					// cout<<"holi8"<<endl;
					for(; k < distancias.size(); k++)
						r.push_back(distancias[k]);
					// cout<<"holi9"<<endl;
					// cout<<"l"<<endl;
					// for(int z=0; z < l.size(); ++z)
					// {
					// 	cout<<l[z].first<<" , "<<l[z].second<<endl;
					// }
					// cout<<"r"<<endl;
					// for(int z=0; z < r.size(); ++z)
					// {
					// 	cout<<r[z].first<<" , "<<r[z].second<<endl;
					// }
					
					// cout<<"holi10"<<endl;
					if(l.size()!=0) {
						p->mChild[0]=new cNode<T>();
						pila.push(make_pair(p->mChild[0],l));
					}
					if(r.size()!=0) {
						p->mChild[1]=new cNode<T>();
						pila.push(make_pair(p->mChild[1],r));
					}
				}
				int w;
				//cin>>w;
			}

		};
		void print(){

			int nivel;
			T padre;
			bool hijo;
			queue<pair<pair<cNode<T>*,bool> ,pair<int,T> > > cola;
			cNode<T>* aux;

			cola.push(make_pair(make_pair(mRoot,0),make_pair(0," ")));

			while(!cola.empty()){

				aux = cola.front().first.first;
				hijo = cola.front().first.second;
				nivel = cola.front().second.first;
				padre = cola.front().second.second;

				//DATO<<NIVEL EN EL QUE ESTA<<PADRE<<SI ESTA A LA IZQUIERDA O DERECHA
				cout<<aux->mData<<" en nivel "<<nivel<<" con padre "<<padre<<" "<<hijo<<endl;
				cola.pop();

				if(aux->mChild[0]!=nullptr){
					cola.push(make_pair(make_pair(aux->mChild[0],0),make_pair(nivel+1,aux->mData)));
				}
				if(aux->mChild[1]!=nullptr){
					cola.push(make_pair(make_pair(aux->mChild[1],1),make_pair(nivel+1,aux->mData)));
				}
			}
			cout<<endl;
		};

		void search(cNode<T>* n, T target, int radius){

			if(n==nullptr) return;
			int dist=lDistance(n->mData, target);
			if(dist<radius)
				cout<<n->mData<<" "<<dist<<endl;

            if ( dist - radius <= n->mMediana ) {
                search( n->mChild[0], target, radius );
            }

            if ( dist + radius > n->mMediana ) {
                search( n->mChild[1], target, radius );
            }

		};


=======
					palabras.push_back( mk_pair(palabra, (-1)) );
				}

				myfile.close();
				palabras.pop_back();
			}
			return palabras;
		}

		void Generation(T files[], int n){



		};

>>>>>>> Stashed changes
};
