
#include "node.h"

template<typename T>
class cVPT{


	public:
		cNode<T>* mRoot;
		int cont=0;

		cVPT(T files[]){
			mRoot == nullptr;
			Generation(files);
		};

		vector<pair<T, pair<int,int> > > distancias;

		/*void Distances(vector<pair<string, pair<int> > > &plbs, string rnd){
			for (int i = 0; i < plbs.size(); ++i) {
				plbs[i].second = lDistance(rnd, plbs[i].first);
			}
		}*/

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

		vector<pair<T, pair<int,int> > > getWords(string file){

			ifstream myfile(file);
			string palabra;
			vector< pair< string, pair< int, int > > > palabras;

			if ( myfile.is_open() ) {

				while ( getline( myfile, palabra) ) {
					palabras.push_back( make_pair(palabra, make_pair(-1,-1)) );
				}

				myfile.close();
			}
			return palabras;
		}

		void Generation(T files[]){

			int i,f,mediana,izq,der;
			cNode<T>* p;
			mRoot= new cNode<T>();
			distancias = getWords(files[0]);
			vector<pair<T,pair<int,int> > > l,r;
			p=mRoot;
			stack<pair<cNode<T>*,vector<pair<T,pair<int, int> > > > > pila;
			T a;
			pila.push(make_pair(p,distancias));
			while(!pila.empty()){
				// cout<<"--------------"<<endl;
				l.clear();
				r.clear();
				p = pila.top().first;
					//cout<<"holi"<<endl;
				distancias = pila.top().second;

				//cout<<endl;
				//cout<<"holi2"<<endl;
				pila.pop();
					//cout<<"holi3"<<endl;
				if(distancias.size()==0){
					continue;
				}

				izq = rand() % distancias.size();
				der = rand() % distancias.size();
				//cout<<distancias.size()<<endl;
				while(izq==der && distancias.size()!=1){
					der = rand() % distancias.size();
				}
				// cout<<"IZQ: "<<izq<<"\t"<<"DER: "<<der<<endl;
				// for(int i=0; i<distancias.size(); ++i){
				// 	cout<<distancias[i].first<<"-";
				// }
				// cout<<endl;
				p->mData.first = distancias[izq].first;
				// cout<<distancias[izq].first<<endl;
				p->mData.second = distancias[der].first;
				// cout<<distancias[der].first<<endl;
				if ( izq < der ){
					der--;
				}
				if(distancias.size()>0){
					distancias.erase( distancias.begin() + izq );
				}
				if(distancias.size()>0){
					distancias.erase( distancias.begin() + der );
				}
				// for(int i=0; i<distancias.size(); ++i){
				// 	cout<<distancias[i].first<<"-";
				// }
				// cout<<endl;

				for (int i = 0; i < distancias.size(); ++i) {
					distancias[i].second.first = lDistance(p->mData.first, distancias[i].first);
					distancias[i].second.second = lDistance(p->mData.second, distancias[i].first);
				}
					//cout<<"holi6"<<endl;
				if(distancias.size()!=0){

					for (int k = 0; k < distancias.size(); k++) {

						if(distancias[k].second.first < distancias[k].second.second){
							l.push_back(distancias[k]);
						}
						else{
							r.push_back(distancias[k]);
						}
						//cout<<"holi7"<<endl;
						if(l.size()!=0) {
							p->mChild[0]=new cNode<T>();
							pila.push(make_pair(p->mChild[0],l));
						}
						if(r.size()!=0) {
							p->mChild[1]=new cNode<T>();
							pila.push(make_pair(p->mChild[1],r));
						}

					}
					// cout<<"L: ";
					// for(int i=0; i<l.size(); ++i){
					// 	cout<<l[i].first<<"-";
					// }
					// cout<<endl;
					// cout<<"R: ";
					// for(int i=0; i<r.size(); ++i){
					// 	cout<<r[i].first<<"-";
					// }
					// cout<<endl;
					int m = -1;
					for (int i = 0; i <l.size(); i++) {
						if(l[i].second.first > m){
							m = l[i].second.first;
						}
					}
					p->radios.first = m;
					m = -1;
					for (int i = 0; i <r.size(); i++) {
						if(r[i].second.second > m){
							m = r[i].second.second;
						}
					}
					p->radios.second = m;

				}
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
				cout<<aux->mData.first<<" "<<aux->mData.second<<" en nivel "<<nivel<<" con padre "<<padre<<" "<<hijo<<endl;
				cola.pop();

				if(aux->mChild[0]!=nullptr){

cola.push(make_pair(make_pair(aux->mChild[0],0),make_pair(nivel+1,aux->mData.first+" "+aux->mData.second)));
				}
				if(aux->mChild[1]!=nullptr){

cola.push(make_pair(make_pair(aux->mChild[1],1),make_pair(nivel+1,aux->mData.first+" "+aux->mData.second)));
				}
			}
			cout<<endl;
		};

		void search(cNode<T>* n, T target, int radius){

			cont++;
			if(n==nullptr) return;
			int dist1=lDistance(n->mData.first, target);
			int dist2=lDistance(n->mData.second, target);
			// cout<<dist1<<"-"<<dist2<<endl;
			if(dist1<=radius)
				cout<<n->mData.first<<" "<<dist1<<endl;
			if(dist2<=radius)
				cout<<n->mData.second<<" "<<dist2<<endl;

            if ( dist1 - radius <= n->radios.first ) {
                search( n->mChild[0], target, radius );
            }

            if ( dist2 - radius <= n->radios.second ) {
                search( n->mChild[1], target, radius );
            }

		};


};
