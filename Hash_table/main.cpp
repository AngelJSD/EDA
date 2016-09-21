#include <iostream>
#include <list>
#include <sstream>
#include <random>
#include <time.h>

#include "c_hash_table.h"

#define N 997


using namespace std;

template <class A>

struct ListAdaptor{

    list<A> lista;
    void insert(A x){

        //cout<<"h"<<endl;
        lista.push_back(x);
        //cout<<"h"<<endl;
        return;
    }
    bool find(A x){

        //cout<<"h"<<endl;
        typename list<A>::iterator i;
        for(i=lista.begin(); i!=lista.end(); i++) if(*i==x) return 1;
        return 0;
    }
    void print(){

        //cout<<"h"<<endl;
        typename list<A>::iterator i;
        for(i=lista.begin(); i!=lista.end(); i++) cout<<*i<<",";
        cout<<"tamaño: "<<lista.size()<<endl;
    }
    int get_col(){

        return lista.size();
    }
};

template <class T>

struct Hash_Function{

    int operator ()(T x, int n){

        //cout<<" USANDO mc"<<endl;
        stringstream buffer,aux,aux1,buff3;
        buffer<<x;
        string s,sub,sn,corrector;
        int a;
        s=buffer.str();
        buffer.clear();
        buffer.str("");
        int c=0, corregido=0;
        for(int i=0; i<s.length(); i++){

            c=((c<<5) - c + s[i]) & 2147483647;
        }
        buff3<<n;
        sn=buff3.str();

        aux<<c;
        corrector=aux.str();

        if(sn.length()%2==0) corrector.insert(corrector.begin(),sn.length()/2-1,corrector[0]);
        else corrector.insert(corrector.begin(),sn.length()/2,corrector[0]);
        corrector.insert(corrector.end(),sn.length()/2-1,corrector[corrector.length()-1]);

        aux1<<corrector;
        aux1>>corregido;

        buffer<<corregido*c;
        //cout<<"llegue "<<c<<endl;

        s=buffer.str();
        //for(int i=0; i<=s.length()/2; i++){

            stringstream buff2;
            sub=s.substr(s.length()/2-sn.length()/2,sn.length());
            cout<<s<<endl;
            cout<<sub<<endl;
            buff2<<sub;
            buff2>>a;
            if(a<n) return a;
        //}

        //return a/10;
        return a%n;
    }
};

template <class T>

struct Hash_Function1{

    int operator ()(T x, int n){
        //cout<<" USANDO modulo"<<endl;
        stringstream buffer;
        string s;

        buffer<<x;
        s=buffer.str();

        int c=0;
        for(int i=0; i<s.length(); i++){

            c=((c<<5) - c + s[i]) & 2147483647;
        }
        return c%n;
    }
};

int main()
{
    srand(time(NULL));
    c_Hash_Table<int,Hash_Function<int>,ListAdaptor<int> > HT(N);
    c_Hash_Table<int,Hash_Function1<int>,ListAdaptor<int> > HT1(N);

    int numeros[N];

    for(int i=0; i<N; i++){

        numeros[i]=rand()%1000000000;
    }

    for(int i=0; i<N; i++){

        HT.insert(numeros[i]);
        //cout<<"Encontre "<<HT.find(numeros[i])<<endl;
        HT1.insert(numeros[i]);
        //cout<<"Encontre "<<HT1.find(numeros[i])<<endl;

    }
    cout<<endl<<"RESULTADO COLISIONES:"<<endl<<endl;
    cout<<"MITAD CUADRADO: "<<HT.colisiones()<<endl;
    cout<<"MODULO: "<<HT1.colisiones()<<endl;
    /*HT.imprimir();
    cout<<"-----"<<endl;
    HT1.imprimir();*/

    //cout<<HT.find("hola");

    return 0;
}
