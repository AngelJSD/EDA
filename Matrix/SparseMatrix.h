#include <iostream>
#include "colors.h"
#include "CNode.h"

using namespace std;

struct Cless{
	inline bool operator()(int a, int b){
		return a <= b;
	}
};

struct Cgreater{
	inline bool operator()(int a, int b){
		return a >= b;
	}
};

template <class T>
class SparseMatrix{
	public:
		CNODE<T>* m_root;

		SparseMatrix(int x, int y, T a){
			m_root = new CNODE<T>(x,y,a);
		}

		void m_findy(int y, CNODE<T>** &p){

			// cout<<"buscando Y "<<(*p)->m_y<<endl;
			//nodo donde se va a insertar verticalmente
			if( y > (*p)->m_y ){

				Cgreater cmp;
				for( ; (*p) && y != (*p)->m_y && ( (*p)->m_vertical[ y > (*p)->m_y] ) &&                              cmp(y, (*p)->m_vertical[ y > (*p)->m_y ]->m_y) ; p = &(*p)->m_vertical[ y > (*p)->m_y]){
				}
			}
			else{
				Cless cmp;
				for( ; (*p) && y != (*p)->m_y && ( (*p)->m_vertical[ y > (*p)->m_y] ) &&                                cmp( y, (*p)->m_vertical[ y > (*p)->m_y]->m_y ) ; p = &(*p)->m_vertical[ y > (*p)->m_y]);
			}
		}

		void m_findx(int x, CNODE<T>** &q){
			// cout<<"buscando X"<<endl;
			//nodo donde se va a insertar horizontalmente
			if( x > (*q)->m_x ){
				Cgreater cmp;
				for( ; (*q) && x != (*q)->m_x && (*q)->m_horizontal[ x > (*q)->m_x ] &&                                 cmp( x, (*q)->m_horizontal[ x > (*q)->m_x ]->m_x ) ; q = &(*q)->m_horizontal[ x > (*q)->m_x ] );
			}
			else{
				Cless cmp;
				for( ; (*q) && x != (*q)->m_x && (*q)->m_horizontal[ x > (*q)->m_x ] &&                                 cmp( x, (*q)->m_horizontal[ x > (*q)->m_x ]->m_x ) ; q = &(*q)->m_horizontal[ x > (*q)->m_x ] );
			}
		}

		bool m_find(int x, int y, CNODE<T>** &p, CNODE<T>** &q){
			// cout<<"buscando"<<endl;

			p = q = &m_root;

			m_findy(y, p);
			m_findx(x, q);

			/*m_findy(y, p);
				if ( (*p) != m_root ){
					m_findx(x, p);
				}

				m_findx(x, q);
				if ( (*q) != m_root ){
					m_findy(y, q);
				}*/
				
			if( (*p) == (*q) && (*p)->m_y == y && (*p)->m_x == x ){
				return true;
			}
			return false;
		}

		bool m_insert(int x,int y, T a, T aux){

			CNODE<T>	**p,			//Movimiento en Y
						**q;			//Movimiento en X
			if( m_find(x, y, p, q) ){	//si lo encuentra solo modifica el valor
				(*q)->m_data = a;
				return 0;
			}
			CNODE<T>* tmp = new CNODE<T> (x, y, a);

			/*s*/if( (*p)->m_y == y && (*p)->m_x != x && (*p) == (*q) ){
				/*1 - Inserción horizontal -> (5, 3)

						(3, 3)<------------>(5, 3)

				*/

				tmp->m_horizontal[ x > (*p)->m_x ] = (*p)->m_horizontal[ x > (*p)->m_x ];
				if( tmp->m_horizontal[ x > (*p)->m_x ] ){
					tmp->m_horizontal[ x > (*p)->m_x ]->m_horizontal[ x < (*p)->m_x ] = tmp;
				}
				(*p)->m_horizontal[ x > (*p)->m_x ] = tmp;
				tmp->m_horizontal[ x < (*p)->m_x ] = (*p);


			}
			else if( (*p)->m_y == y && (*p)->m_x != x && (*q)->m_y == y && (*q)->m_x != x && (*p) != (*q) ){
				/*	Inserción horizontal -> (5, 3) - Caso 2
				(q)(3, 3)<---->(p)(4, 3)
				----------------------------------
				(3, 3)<---->(4, 3)<---->(5, 3)
				*/
				tmp->m_horizontal[ x > (*q)->m_x ] = (*q)->m_horizontal[ x > (*q)->m_x ];
				if( tmp->m_horizontal[ x > (*q)->m_x ] ){
					tmp->m_horizontal[ x > (*q)->m_x ]->m_horizontal[ x < (*q)->m_x ] = tmp;
				}
				(*q)->m_horizontal[ x > (*q)->m_x ] = tmp;
				tmp->m_horizontal[ x < (*q)->m_x ] = (*q);
			}
			else if( (*p)->m_y != y && (*p)->m_x == x && (*p) == (*q) ){
				/* 2 - Inserción vertical -> (3, 5)

						(3, 3)
						   ^
						   |
						   v
						(5, 3)

				*/
				tmp->m_vertical[ y > (*q)->m_y ] = (*q)->m_vertical[ y > (*q)->m_y ];
				if( tmp->m_vertical[ y > (*q)->m_y ] ){
					tmp->m_vertical[ y > (*q)->m_y ]->m_vertical[ y < (*q)->m_y ] = tmp;
				}
				(*q)->m_vertical[ y > (*q)->m_y ] = tmp;
				tmp->m_vertical[ y < (*q)->m_y ] = (*q);
			}
			else if( (*p)->m_y != y && (*p)->m_x == x && (*q)->m_y != y && (*q)->m_x == x && (*p) != (*q) ){
				/* 2 - Inserción vertical -> (3, 5) - Caso 2
						(3, 3)
						   ^
						   |
						   v
						(3, 4)
					----------------
					 (q)(3, 3)
						   ^
						   |
						   v
					 (p)(3, 4)
   						   ^
   						   |
   						   v
   						(3, 5)

				*/
				tmp->m_vertical[ y > (*p)->m_y ] = (*p)->m_vertical[ y > (*p)->m_y ];
				if( tmp->m_vertical[ y > (*p)->m_y ] ){
					tmp->m_vertical[ y > (*p)->m_y ]->m_vertical[ y < (*p)->m_y ] = tmp;
				}
				(*p)->m_vertical[ y > (*p)->m_y ] = tmp;
				tmp->m_vertical[ y < (*p)->m_y ] = (*p);
			}
			/*s*/else if( (*p)->m_y != y && (*p)->m_x != x && (*q)->m_y != y && (*q)->m_x == x && (*p) != (*q) ){
				/* Inserción cuando solo se tiene en 'X' y no en 'Y' -> (5, 5)
							(3, 3)<------->(5, 3)
				----------------------------------
							(3, 3)<------->(5, 3)
							   ^
							   |
							   v
							(3, 5)
				----------------------------------
							(3, 3)<------->(5, 3)
							   ^			  ^
							   |			  |
							   v			  v
							(3, 5)<------->(5, 5)
				*/

				CNODE<T>* tmp_y = new CNODE<T>( (*p)->m_x, y, aux);

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

				tmp->m_vertical[ y > (*q)->m_y ] = (*q)->m_vertical[ y > (*q)->m_y ];
				if( tmp->m_vertical[ y > (*q)->m_y ] ){
					tmp->m_vertical[ y > (*q)->m_y ]->m_vertical[ y < (*q)->m_y ] = tmp;
				}
				(*q)->m_vertical[ y > (*q)->m_y ] = tmp;
				tmp->m_vertical[ y < (*q)->m_y ] = (*q);

			}
			/*s*/else if( (*p)->m_y == y && (*p)->m_x != x && (*q)->m_y != y && (*q)->m_x !=x && (*p) != (*q) ){
				/* Inserción cuando solo se tiene en 'Y' y no en 'X' -> (5, 5)
							(3, 3)
							   ^
							   |
							   v
							(3, 5)
				----------------------------------
							(3, 3)<------->(5, 3)
							   ^
							   |
							   v
							(3, 5)
				----------------------------------
							(3, 3)<------->(5, 3)
							   ^			  ^
							   |			  |
							   v			  v
							(3, 5)<------->(5, 5)
				*/
				//Temporal en x
				CNODE<T>* tmp_x = new CNODE<T>( x, (*q)->m_y, aux);

				tmp_x->m_horizontal[ x > (*q)->m_x ] = (*q)->m_horizontal[ x > (*q)->m_x ];
				if( tmp_x->m_horizontal[ x > (*q)->m_x ] ){
					tmp_x->m_horizontal[ x > (*q)->m_x ]->m_horizontal[ x < (*q)->m_x ] = tmp_x;
				}
				(*q)->m_horizontal[ x > (*q)->m_x ] = tmp_x;
				tmp->m_horizontal[ x < (*q)->m_x ] = (*q);

				q = &(*q)->m_horizontal[ x > (*q)->m_x ];

				tmp->m_horizontal[ x > (*p)->m_x ] = (*p)->m_horizontal[ x > (*p)->m_x ];
				if( tmp->m_horizontal[ x > (*p)->m_x ] ){
					tmp->m_horizontal[ x > (*p)->m_x ]->m_horizontal[ x < (*p)->m_x ] = tmp;
				}
				(*p)->m_horizontal[ x > (*p)->m_x ] = tmp;
				tmp->m_horizontal[ x < (*p)->m_x ] = (*p);

				tmp->m_vertical[ y > (*q)->m_y ] = (*q)->m_vertical[ y > (*q)->m_y ];
				if( tmp->m_vertical[ y > (*q)->m_y ] ){
					tmp->m_vertical[ y > (*q)->m_y ]->m_vertical[ y < (*q)->m_y ] = tmp;
				}
				(*q)->m_vertical[ y > (*q)->m_y ] = tmp;
				tmp->m_vertical[ y < (*q)->m_y ] = (*q);

			}
			/*s*/else if( (*p)->m_y == y && (*p)->m_x != x && (*q)->m_y != y && (*q)->m_x == x && (*p) != (*q) ){
				/* Inserción solo del nodo -> (5, 5)
				----------------------------------
							(3, 3)<------->(5, 3)
							   ^
							   |
							   v
							(3, 5)
				----------------------------------
							(3, 3)<------->(5, 3)
							   ^			  ^
							   |			  |
							   v			  v
							(3, 5)<------->(5, 5)

				*/

				tmp->m_horizontal[ x > (*p)->m_x ] = (*p)->m_horizontal[ x > (*p)->m_x ];
				if( tmp->m_horizontal[ x > (*p)->m_x ] ){
					tmp->m_horizontal[ x > (*p)->m_x ]->m_horizontal[ x < (*p)->m_x ] = tmp;
				}
				(*p)->m_horizontal[ x > (*p)->m_x ] = tmp;
				tmp->m_horizontal[ x < (*p)->m_x ] = (*p);

				tmp->m_vertical[ y > (*q)->m_y ] = (*q)->m_vertical[ y > (*q)->m_y ];
				if( tmp->m_vertical[ y > (*q)->m_y ] ){
					tmp->m_vertical[ y > (*q)->m_y ]->m_vertical[ y < (*q)->m_y ] = tmp;
				}
				(*q)->m_vertical[ y > (*q)->m_y ] = tmp;
				tmp->m_vertical[ y < (*q)->m_y ] = (*q);
			}
			/*s*/else if( (*p)->m_y != y && (*p)->m_x != x && (*p) == (*q) ){
				/*Inserción de "esquina" -> (5, 5)
					(3, 3)
					-------------------
					(3, 3)
					  ^
					  |
					  |
					  v
					(3, 5)
					--------------------
					(3, 3)<---------->(5, 3)
					  ^
					  |
					  |
					  v
					(3, 5)
					--------------------
					(3, 3)<---------->(5, 3)
					  ^					^
					  |					|
					  |					|
					  v					v
					(3, 5)<---------->(5, 5)
				*/

				CNODE<T>* tmp_y = new CNODE<T>( (*p)->m_x, y, aux);


				tmp_y->m_vertical[ y > (*p)->m_y ] = (*p)->m_vertical[ y > (*p)->m_y ];
				if( tmp_y->m_vertical[ y > (*p)->m_y ] ){
					tmp_y->m_vertical[ y > (*p)->m_y ]->m_vertical[ y < (*p)->m_y ] = tmp_y;
				}
				(*p)->m_vertical[ y > (*p)->m_y ] = tmp_y;
				tmp_y->m_vertical[ y < (*p)->m_y ] = (*p);

				p = &(*p)->m_vertical[ y > (*p)->m_y ];

				CNODE<T>* tmp_x = new CNODE<T>( x, (*q)->m_y, aux);

				tmp_x->m_horizontal[ x > (*q)->m_x ] = (*q)->m_horizontal[ x > (*q)->m_x ];
				if( tmp_x->m_horizontal[ x > (*q)->m_x ] ){
					tmp_x->m_horizontal[ x > (*q)->m_x ]->m_horizontal[ x < (*q)->m_x ] = tmp_x;
				}
				(*q)->m_horizontal[ x > (*q)->m_x ] = tmp_x;
				tmp->m_horizontal[ x < (*q)->m_x ] = (*q);

				q = &(*q)->m_horizontal[ x > (*q)->m_x ];

				tmp->m_horizontal[ x > (*p)->m_x ] = (*p)->m_horizontal[ x > (*p)->m_x ];
				if( tmp->m_horizontal[ x > (*p)->m_x ] ){
					tmp->m_horizontal[ x > (*p)->m_x ]->m_horizontal[ x < (*p)->m_x ] = tmp;
				}
				(*p)->m_horizontal[ x > (*p)->m_x ] = tmp;
				tmp->m_horizontal[ x < (*p)->m_x ] = (*p);

				tmp->m_vertical[ y > (*q)->m_y ] = (*q)->m_vertical[ y > (*q)->m_y ];
				if( tmp->m_vertical[ y > (*q)->m_y ] ){
					tmp->m_vertical[ y > (*q)->m_y ]->m_vertical[ y < (*q)->m_y ] = tmp;
				}
				(*q)->m_vertical[ y > (*q)->m_y ] = tmp;
				tmp->m_vertical[ y < (*q)->m_y ] = (*q);
			}

		}

		void print(){

			CNODE<T>	*tmp,
						*tmp1;

			tmp = m_root;

			cout<<bold<<underline<<yellow<<"SUPERIOR"<<reset<<endl;

			while( tmp ){
				cout<<red<<tmp->m_data<<reset<<bold<<"->"<<reset;
				tmp1 = tmp->m_horizontal[1];
				while( tmp1 ){
					cout<<green<<tmp1->m_data<<reset<<bold<<"->"<<reset;
					tmp1 = tmp1->m_horizontal[1];
				}
				tmp1 = tmp;
				cout<<endl;
				cout<<red<<tmp->m_data<<reset<<bold<<"<-"<<reset;;
				tmp1 = tmp->m_horizontal[0];
				while( tmp1 ){
					cout<<green<<tmp1->m_data<<reset<<bold<<"<-"<<reset;
					tmp1 = tmp1->m_horizontal[0];
				}
				tmp = tmp->m_vertical[0];
				cout<<endl;
			}
			tmp = m_root;
			cout<<bold<<underline<<yellow<<"INFERIOR"<<reset<<endl;

			while( tmp ){
				cout<<red<<tmp->m_data<<reset<<bold<<"->"<<reset;;
				tmp1 = tmp->m_horizontal[1];
				while( tmp1 ){
					cout<<green<<tmp1->m_data<<reset<<bold<<"->"<<reset;
					tmp1 = tmp1->m_horizontal[1];
				}
				tmp1 = tmp;
				cout<<endl;
				cout<<red<<tmp->m_data<<reset<<bold<<"<-"<<reset;;
				tmp1 = tmp1->m_horizontal[0];
				while( tmp1 ){
					cout<<green<<tmp1->m_data<<reset<<bold<<"<-"<<reset;
					tmp1 = tmp1->m_horizontal[0];
				}
				tmp = tmp->m_vertical[1];
				cout<<endl;
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
