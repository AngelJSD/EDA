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
            //cout<<s<<endl;
            //cout<<sub<<endl;
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

unsigned reverse(unsigned x) {
	x = ((x & 0x55555555) <<  1) | ((x >>  1) & 0x55555555);
	x = ((x & 0x33333333) <<  2) | ((x >>  2) & 0x33333333);
	x = ((x & 0x0F0F0F0F) <<  4) | ((x >>  4) & 0x0F0F0F0F);
	x = (x << 24) | ((x & 0xFF00) << 8) | ((x >> 8) & 0xFF00) | (x >> 24);
	return x;
}

unsigned int crc(string message) {
	int i, j;
	unsigned long long int byte, crc;

	i = 0;
	crc = 0xFFFFFFFF;
	while (message[i] != 0) {
		byte = message[i];
		for (j = 0; j <= 7; j++)
		{
			if ((int)(crc ^ byte) < 0)
				crc = (crc << 1) ^ 0x1EDC6F41 /*0x04C11DB7*/;
			else crc = crc << 1;
			byte = byte << 1;
		}
		i = i + 1;
	}
	return (crc);
}

unsigned int crc(int id) {

unsigned int   crc = 0xFFFFFFFF;

	for (int j = 0; j <= 7; j++) {
		if ((int)(crc ^ id) < 0){
			crc = (crc << 1) ^ 0x1EDC6F41 /*0x04C11DB7*/;      //Estándar que maximiza la detección de errores y minimiza las colisiones//IEEE 802.3 --> además es difícil encontrar uno perfecto
		}//x27 + x26 + x23 + x22 + x16 + x12 + x11 + x10 + x8 + x7 + x5 + x4 + x2 + x + 1
		else{
			crc = crc << 1;
		}
		id <<= 1;
	}
	return (crc);
}

template <class T>

struct Hash_Function2{

    int operator ()(T x, int n){

	return crc(x) % n;
    }
};

unsigned int FNC(string id)
{
	unsigned long int hash = 2166136261;
	int i = 0;
	char tmp;

	while(id[i] != 0)
	{
		tmp = id[i];
		tmp = reverse(tmp);
		for(int i = 0; i < 7; i++)
		{
			hash = hash ^ 1099511628211;
			hash = hash * (int)tmp;
		}
		i++;
	}
	return (hash);
}

unsigned int FNC(int id)
{
	unsigned long int hash = 2166136261;

	for(int i = 0; i < 7; i++)
	{
		hash = hash ^ 1099511628211;
		hash = hash * id;
	}
	return (hash);
}

template <class T>

struct Hash_Function3{

	int operator()(T x, int n){
		return FNC(x) % n;
	}
};

int main()
{
    srand(time(NULL));
    c_Hash_Table<int,Hash_Function<int>,ListAdaptor<int> > HT(N);
    c_Hash_Table<int,Hash_Function1<int>,ListAdaptor<int> > HT1(N);
    c_Hash_Table<int,Hash_Function2<int>,ListAdaptor<int> > HT2(N);
    c_Hash_Table<int,Hash_Function3<int>,ListAdaptor<int> > HT3(N);

    int numeros[N];

    for(int i=0; i<N; i++){

        numeros[i]=rand()%1000000000;
    }

    for(int i=0; i<N; i++){

        HT.insert(numeros[i]);
        //cout<<"Encontre "<<HT.find(numeros[i])<<endl;
        HT1.insert(numeros[i]);
        //cout<<"Encontre "<<HT1.find(numeros[i])<<endl;
	HT2.insert(numeros[i]);
	HT3.insert(numeros[i]);

    }
    cout<<endl<<"RESULTADO COLISIONES:"<<endl<<endl;
    cout<<"MITAD CUADRADO: "<<HT.colisiones()<<endl;
    cout<<"MODULO: "<<HT1.colisiones()<<endl;
    cout<<"CRC: "<<HT2.colisiones()<<endl;
    cout<<"FNC: "<<HT3.colisiones()<<endl;
    /*HT.imprimir();
    cout<<"-----"<<endl;
    HT1.imprimir();*/

    //cout<<HT.find("hola");

    return 0;
}
