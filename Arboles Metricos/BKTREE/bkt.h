#ifndef BKT_H
#define BKT_H

#include <fstream>
#include <string>

using namespace std;

template<typename T>

class Node{

    public:
        Node(){
        }

        vector<pair<int,Node*> >hijos;
        T dato;
};

template<typename T>

class bkt
{
    public:
        bkt(T files[]){

            root=new Node<T>();
            generation(files);

        }

        Node<T> *root;

        int distancia(T, T);
        bool my_insert(T);
        bool my_find(T);
        void my_search(Node<T>*, T, int);
        void my_print();

        void generation(T files[]){

            bool r=true;
            string file=files[0];
            ifstream myfile(file);
            string palabra;

            if ( myfile.is_open() ) {

                while ( getline( myfile, palabra) ) {
                    if(r) {
                        root->dato="hola";
                        r=false;
                    }
                    else my_insert(palabra);
                }

                myfile.close();
            }
            return;
        }
};

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
}

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

	    //cout<<"ojo1 "<<i<<endl;
	    if(distancia((*p)->dato,s)==(*p)->hijos[i].first){
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

    if(d<radius)
        cout<<n->dato<<d<<endl;

    for(int i=0; i<n->hijos.size(); ++i)
        if(n->hijos[i].first>=d-radius && n->hijos[i].first<=d+radius)
            my_search(n->hijos[i].second, s, radius);

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
