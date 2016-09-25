#include <iostream>
#include "CNode.h"

using namespace std;

struct Cless
{
	inline bool operator()(int a, int b){
		return a<b;
	}
};
struct Cgreater
{
	inline bool operator()(int a, int b){
		return a>b;
	}
};


template <class T>
class SparseMatrix
{
	public:
	CNODE<T>* m_root;

	SparseMatrix(int x, int y, T a){
		m_root = new CNODE<T>(x,y,a);
	}

	bool m_findy(int y, CNODE<T>** &p){

		// cout<<"buscando Y "<<(*p)->m_y<<endl;
		//nodo donde se va a insertar verticalmente
		if( y > (*p)->m_y ){

			Cgreater cmp;
			for( ; (*p) && y != (*p)->m_y && ( (*p)->m_vertical[y>(*p)->m_y] ) && cmp(y,(*p)->m_vertical[y>(*p)->m_y]->m_y) ; p = &(*p)->m_vertical[y>(*p)->m_y]){
			}
		}
		else{
			Cless cmp;
			for( ; (*p) && y != (*p)->m_y && ( (*p)->m_vertical[y>(*p)->m_y] ) && cmp(y,(*p)->m_vertical[y>(*p)->m_y]->m_y) ; p = &(*p)->m_vertical[y>(*p)->m_y]);
		}
		if( (*p) && (*p)->m_y == y ){
			return 1;
		}
		return 0;
	}

	bool m_findx(int x, CNODE<T>** &q){
		// cout<<"buscando X"<<endl;
		//nodo donde se va a insertar horizontalmente
		if(x>(*q)->m_x){
			Cgreater cmp;
			for( ; (*q) && x != (*q)->m_x && (*q)->m_horizontal[x>(*q)->m_x] && cmp(x,(*q)->m_horizontal[x>(*q)->m_x]->m_x) ; q = &(*q)->m_horizontal[x>(*q)->m_x]);
		}
		else{
			Cless cmp;
			for( ; (*q) && x != (*q)->m_x && (*q)->m_horizontal[x>(*q)->m_x] && cmp(x,(*q)->m_horizontal[x>(*q)->m_x]->m_x) ; q = &(*q)->m_horizontal[x>(*q)->m_x]);
		}
		if( (*q)->m_x == x ){
			return 1;
		}
		return 0;
	}

	bool m_find(int x, int y, CNODE<T>** &p, CNODE<T>** &q){
		// cout<<"buscando"<<endl;

		p = q = &m_root;
		if( m_findy(y,p) ){
			m_findx(x,p);
			if( m_findx(x,q) ){
				m_findy(y, q);
				return 1;
			}
		}
		return 0;
	}

	bool m_insert(int x,int y, T a){

		CNODE<T>	**p,		//Movimiento en Y
					**q;		//Movimiento en X
		if( m_find(x, y, p, q) ){	//si lo encuentra solo modifica el valor
			(*q)->m_data = a;
			return 0;
		}
		CNODE<T>* tmp = new CNODE<T> (x, y, a);
		// cout<<"insertando"<<endl;
		if( (*p)->m_y == y ){
			tmp->m_horizontal[ x > (*p)->m_x ] = (*p)->m_horizontal[ x > (*p)->m_x ];
			if( tmp->m_horizontal[ x > (*p)->m_x ] ){
				tmp->m_horizontal[ x > (*p)->m_x ]->m_horizontal[ x < (*p)->m_x ] = tmp;
			}
			(*p)->m_horizontal[ x > (*p)->m_x ] = tmp;
			tmp->m_horizontal[ x < (*p)->m_x ] = (*p);

			if ( (*q)->m_x != x ){
				CNODE<T>* tmp_x = new CNODE<T>( x, (*q)->m_y, 0);
				tmp_x->m_horizontal[ x > (*q)->m_x ] = (*q)->m_horizontal[ x > (*q)->m_x ];
				if( tmp_x->m_horizontal[ x > (*q)->m_x ] ){
					tmp->m_horizontal[ x > (*q)->m_x ]->m_horizontal[ x < (*q)->m_x ] = tmp_x;
				}
				(*q)->m_horizontal[ x > (*q)->m_x ] = tmp_x;
				tmp->m_horizontal[ x < (*q)->m_x ] = (*q);

				q = &(*q)->m_horizontal[ x > (*q)->m_x ];

				tmp->m_vertical[ y > (*q)->m_y ] = tmp_x->m_vertical[ y > (*q)->m_y ];
				if( tmp->m_vertical[ y > (*q)->m_y ] ){
					tmp->m_vertical[ y > (*q)->m_y ]->m_vertical[ y < (*q)->m_y ] = tmp;
				}
				(*q)->m_vertical[ y > (*q)->m_y ] = tmp;
				tmp->m_vertical[ y < (*q)->m_y ] = (*q);
				return 1;
			}
			if ( (*q)->m_x == x ){
				tmp->m_vertical[ y > (*q)->m_y ] = (*q)->m_vertical[ y > (*q)->m_y ];
				if( tmp->m_vertical[ y > (*q)->m_y ] ){
					tmp->m_vertical[ y > (*q)->m_y ]->m_vertical[ y < (*q)->m_y ] = tmp;
				}
				(*q)->m_vertical[ y > (*q)->m_y ] = tmp;
				tmp->m_vertical[ y < (*q)->m_y ] = (*q);
				return 1;
			}
		}
		else if( (*p)->m_y != y && (*q)->m_x != x ){


			CNODE<T>* tmp_y = new CNODE<T>( (*p)->m_x, y, '-');

			tmp_y->m_vertical[ y > (*p)->m_y ] = (*p)->m_vertical[ y > (*p)->m_y ];
			if( tmp_y->m_vertical[ y > (*p)->m_y ] ){
				tmp_y->m_vertical[ y > (*p)->m_y ]->m_vertical[ y < (*p)->m_y ] = tmp_y;
			}
			(*p)->m_vertical[ y > (*p)->m_y ] = tmp_y;
			tmp_y->m_vertical[ y < (*p)->m_y ] = (*p);


			CNODE<T>* tmp_x = new CNODE<T>( x, (*q)->m_y, '-');
			tmp_x->m_horizontal[ x > (*q)->m_x ] = (*q)->m_horizontal[ x > (*q)->m_x ];

			if( tmp_x->m_horizontal[ x > (*q)->m_x ] ){
				tmp_x->m_horizontal[ x > (*q)->m_x ]->m_horizontal[ x < (*q)->m_x ] = tmp_x;
			}
			(*q)->m_horizontal[ x > (*q)->m_x ] = tmp_x;
			tmp->m_horizontal[ x < (*q)->m_x ] = (*q);

			p = &(*p)->m_vertical[ y > (*p)->m_y ];

			tmp->m_horizontal[ x > (*p)->m_x ] = (*p)->m_horizontal[ x > (*p)->m_x ];
			if( tmp->m_horizontal[ x > (*p)->m_x ] ){
				tmp->m_horizontal[ x > (*p)->m_x ]->m_horizontal[ x < (*p)->m_x ] = tmp;
			}
			(*p)->m_horizontal[ x > (*p)->m_x ] = tmp;
			tmp->m_horizontal[ x < (*p)->m_x ] = (*p);

			q = &(*q)->m_horizontal[ x > (*q)->m_x ];

			tmp->m_vertical[ y > (*q)->m_y ] = (*q)->m_vertical[ y > (*q)->m_y ];
			if( tmp->m_vertical[ y > (*q)->m_y ] ){
				tmp->m_vertical[ y > (*q)->m_y ]->m_vertical[ y < (*q)->m_y ] = tmp;
			}
			(*q)->m_vertical[ y > (*q)->m_y ] = tmp;
			tmp->m_vertical[ y < (*q)->m_y ] = (*q);
			return 1;

		}
		else if( (*p)->m_y != y && (*q)->m_x == x ){

			tmp->m_vertical[ y > (*q)->m_y ] = (*q)->m_vertical[ y > (*q)->m_y ];
			if( tmp->m_vertical[ y > (*q)->m_y ] ){
				tmp->m_vertical[ y > (*q)->m_y ]->m_vertical[ y < (*q)->m_y ] = tmp;
			}
			(*q)->m_vertical[ y > (*q)->m_y ] = tmp;
			tmp->m_vertical[ y < (*q)->m_y ] = (*q);


			CNODE<T>* tmp_y = new CNODE<T>( (*p)->m_x, y, '-');

			tmp_y->m_vertical[ y > (*p)->m_y ] = (*p)->m_vertical[ y > (*p)->m_y ];
			if( tmp_y->m_vertical[ y > (*p)->m_y ] ){
				tmp_y->m_vertical[ y > (*p)->m_y ]->m_vertical[ y < (*p)->m_y ] = tmp_y;
			}
			(*p)->m_vertical[ y > (*p)->m_y ] = tmp_y;
			tmp_y->m_vertical[ y < (*p)->m_y ] = (*p);

			p = &(*p)->m_vertical[ y > (*p)->m_y ];

			tmp->m_horizontal[ x > (*p)->m_x ] = (*p)->m_horizontal[ x > (*p)->m_x ];
			if( tmp->m_horizontal[ x > (*p)->m_x ] ){
				tmp->m_horizontal[ x > (*p)->m_x ]->m_horizontal[ x < (*p)->m_x ] = tmp;
			}
			(*p)->m_horizontal[ x > (*p)->m_x ] = tmp;
			tmp->m_horizontal[ x < (*p)->m_x ] = (*p);

			return 1;
		}
	}

	void print(){

		CNODE<T>	*tmp,
					*tmp1;
		tmp = m_root;

		while( tmp ){
			tmp1 = tmp;
			cout<<endl<<tmp->m_data<<">";
			while( tmp1 ){
				cout<<tmp1->m_data<<"|";
				tmp1 = tmp1->m_horizontal[1];
			}
			tmp1 = tmp;
			cout<<endl<<tmp->m_data<<"<";
			while( tmp1 ){
				cout<<tmp1->m_data<<"|";
				tmp1 = tmp1->m_horizontal[0];
			}
			tmp = tmp->m_vertical[0];
		}
		tmp = m_root;

		while( tmp ){
			tmp1 = tmp;
			cout<<endl<<tmp->m_data<<">";
			while( tmp1 ){
				cout<<tmp1->m_data<<"|";
				tmp1 = tmp1->m_horizontal[1];
			}
			tmp1 = tmp;
			cout<<endl<<tmp->m_data<<"<";
			while( tmp1 ){
				cout<<tmp1->m_data<<"|";
				tmp1 = tmp1->m_horizontal[0];
			}
			tmp = tmp->m_vertical[1];
		}
	}


	bool m_remove(int x, int y){
		CNODE<T>**p,**q;
		if(!m_find(x,p)) return 0;
		if((*p)->m_right)
		{
		    q=p;
		    (*q)=(*p)->m_right;
		}
		if((*p)->m_down)
		{
		    q=p;
		    (*q)=(*p)->m_down;
		}
		CNODE<T> *temp;
		temp=(*p);
		(*p)=(*p)->m_child[!!(*p)->m_child[1]];
		delete temp;
		return 1;
	}

};
