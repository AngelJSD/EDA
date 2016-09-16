#ifndef C_BSTREE_H
#define C_BSTREE_H

#include <iostream>
#include <queue>
#include "node.h"

using namespace std;

static bool* flag;
static int insertados;
static int repetidos;

struct arg_struct {
	void* arg1;
	void* arg2;
	void* arg3;
};

template <class T>

class c_BSTree{

	public:

		c_BSTree(){
			root=nullptr;
		}

		c_Node<T>* root;
		pthread_mutex_t mMutex;
		void* my_delete(void* mdata);
		void my_insert(T data, int rank);
		void print(c_Node<T>* it);
		void print_bfs();
		void transform();
		c_Node<T>** my_find(T data, c_Node<T>*&ant);

};

template<typename T>
c_Node<T>** c_BSTree<T>::my_find(T data, c_Node<T>*& ant){

	c_Node<T>** it = &root;

	for(; *it != nullptr && (*it)->data != data; ant = *it, it = &(*it)->hijos[(*it)->data < data] ){

		while( (*it)->lock );		//Buclea mientras el nodo está ocupado :v

	}
	if(ant){
		ant->lock = true;
	}
	return it;
}

template <class T>
void c_BSTree<T>::my_insert(T data, int rank){

	flag[rank] = false;

	c_Node<T>* ant = nullptr;
	c_Node<T>** it;

	it = my_find(data, ant);

	if ( (*it) && (*it)->data == data){
		++repetidos;
	}
	if(!(*it)){
		*it = new c_Node<T>(data);
		++insertados;
	}

	if(ant) {
		ant->lock = false;
	}

}

template <class T>
void c_BSTree<T>::print(c_Node<T>* it){

	if(!it) return;
	print(it->hijos[0]);
	cout<<it->data<<endl;
	print(it->hijos[1]);
}

template <class T>
void c_BSTree<T>::print_bfs(){

	int nivel;
	queue<pair<c_Node<T>* ,int> > cola;
	c_Node<T>* aux;

	cola.push(make_pair(root,0));

	while(!cola.empty()){

		aux = cola.front().first;
		nivel = cola.front().second;

		cout<<aux->data<<" en nivel "<<nivel<<endl;
		cola.pop();

		if(aux->hijos[0]!=nullptr){
			cola.push(make_pair(aux->hijos[0],nivel+1));
		}
		if(aux->hijos[1]!=nullptr){
			cola.push(make_pair(aux->hijos[1],nivel+1));
		}
	}
	cout<<endl;
}

template<class T>
void* c_BSTree<T>::my_delete(void* mdata){

	c_Node<T>** p;
	c_Node<T>* temp;
	c_Node<T>* ant = nullptr;

	T data;

	data = *((T *)mdata);
	p = my_find(data, ant);

	if( !(*p) ){
		return 0;
	}

	temp = (*p);

	if( (*p)->hijos[0] && (*p)->hijos[1] ){
		for(p = &((*p)->hijos[0]); (*p)->hijos[1]; p = &((*p)->hijos[1]));		//Hacia el hijo más izquierdo del subárbol derecho
		swap((*p)->data,temp->data);		//Los cambia
	}

	temp = (*p);
	(*p) = (*p)->hijos[!!(*p)->hijos[1]];

	if(ant) {
		ant->lock = false;
	}
}

template <class T>
void c_BSTree<T>::transform(){

	c_Node<T> *it, *next;

	it=root;
	while(it!=nullptr){

		if(it->hijos[0]!=nullptr){

			if(it->hijos[1]!=nullptr){

				next=it->hijos[0];
				while (next->hijos[1] != nullptr) next = next->hijos[1];
				next->hijos[1] = it->hijos[1];
			}
			it->hijos[1] = it->hijos[0];
			it->hijos[0] = nullptr;
		}
	it = it->hijos[1];
	}
}

#endif // C_BSTREE_H
