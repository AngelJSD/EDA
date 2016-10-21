#include <iostream>
#include <pthread.h>
#include <random>
#include <time.h>
#include "c_BSTree.h"

#define TOTAL_ELEMENTOS 5000

using namespace std;

c_BSTree<int> tree;

void* inserta (void* elem){

	int *datos= (int *)elem;
	for(int i = 1; i <= TOTAL_ELEMENTOS; ++i){
		tree.my_insert(datos[i], datos[0]);
	}
}

int main()
{

	int tam;
	insertados = 0;
	repetidos = 0;
	srand(time(NULL));
	tam = 4;
/*int elementos[tam];
	elementos[0] = 5;
	elementos[1] = 6;
	elementos[2] = 7;
	elementos[3] = 8;
	elementos[4] = 9;
	elementos[5] = 1;
	elementos[6] = 7;
	for(int i=0; i< tam; ++i){
	elementos[i]=rand()%100;
}
	*/

	cout<<"vivo"<<endl;
	struct arg_struct args;
	args.arg1 = &tree;

	flag = (bool*) malloc(tam * sizeof(bool));

	pthread_t* threads;

	threads = (pthread_t*) malloc( tam * sizeof(pthread_t) );

/*pthread_t* threads1;
	threads1 = (pthread_t*) malloc( 3 * sizeof(pthread_t) );*/

	for (int i = 0; i < tam; ++i) {

		int elementos[TOTAL_ELEMENTOS + 1];
		elementos[0] = i;				//my_rank

		for(int j = 1; j <= TOTAL_ELEMENTOS; ++j){	//100 elementos
			elementos[j] = rand() % 100000;
		}

		flag[i] = true;
		args.arg2 = &elementos[i];
		args.arg3 = &i;

		int a = *((int *)args.arg2);

		cout<<"Creo hilo: "<<a<<endl;

		pthread_create( &threads[i], NULL, &inserta, (void *)&elementos);

		while(flag[i]);
	}

	for (int i = 0; i < tam; ++i) {
		pthread_join( threads[i], NULL);
	}


/*	for (int i = 0; i < 3; ++i) {
		//cout<<"Creo hilo"<<endl;
		args.arg2 =&elementos[rand()%tam];
		pthread_create( &threads1[i], NULL, &c_BSTree<int>::delete_helper, (void *)&args);
	}

	for (int i = 0; i < 3; ++i) {
		pthread_join( threads1[i], NULL);
	}

	tree.my_insert(5);
	tree.my_insert(2);
	tree.my_insert(9);
	tree.my_insert(7);
	tree.my_insert(3);

	tree.my_delete(2);

	tree.print(tree.root);
	tree.transform();
	cout<<endl<<"Impresion por niveles: "<<endl;
	tree.print_bfs();
	tree.print(tree.root);
*/

	// cout<<endl<<"Impresion por niveles: "<<endl;
	// tree.print_bfs();
	cout<<endl<<"cont: "<<insertados<<" "<<repetidos<<" "<<col<<endl;

	return 0;
}
