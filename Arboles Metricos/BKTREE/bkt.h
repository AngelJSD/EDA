#ifndef BKT_H
#define BKT_H



using namespace std;

class Node{

    public:
        Node(){
        }

        vector<pair<int,Node*> >hijos;
        string dato;
};




class bkt
{
    public:
        bkt(){

            root=new Node();
            root->dato="hola";

        }

        Node *root;

        int distancia(string, string);
        bool my_insert(string);
        bool my_find(string);
        void my_print();
};

int bkt::distancia(const string a, const string b){

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

bool bkt::my_find(string s){

    Node **p=&root;
    Node *aux=nullptr;
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


bool bkt::my_insert(string s){

	//cout<<"i"<<s<<endl;
	Node **p = &root;
	Node *n;

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

	n=new Node();

	n->dato = s;
	(*p)->hijos.push_back(make_pair(distancia((*p)->dato,s),n));

	//cout<<distancia((*p)->dato,s)<<endl;
	return 1;
}

void bkt::my_print(){

    stack<Node*> pila;
    Node* aux;
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
