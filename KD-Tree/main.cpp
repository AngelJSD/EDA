#include <iostream>
#include "KDTree.h"

using namespace std;

string vocabulario ="xyz";

/*Funcion para insertar elementos por teclado*/
void addCoordinates(vector<float>* coord, int dim)
{
    for (int i=0;i<dim;i++)
    {
        cout<<vocabulario[i]<<" = ";
        float coordinateI;
        cin>>coordinateI;
        coord->push_back(coordinateI);
    }
}

/*Funcion para insertar elementos Random*/
void addCoordinatesRan(vector<float>* coord, int dim)
{
    for (int i=0;i<dim;i++)
    {
        float coordinateI=rand() % 100;
        coord->push_back(coordinateI);
    }
}

void menu()
{

    cout<<"1) Insertar Datos Random"<<endl;
    cout<<"2) Insertar Datos por Consola"<<endl;
    cout<<"3) Borrar"<<endl;
    cout<<"4) Encontrar vecino mas cercano"<<endl;
    cout<<"5) Encontrar el minimo"<<endl;
    cout<<"6) Salir"<<endl;
    cout<<"Opcion -> ";
}


int main() {
    cout<<"-------------------------------------KDTree--------------------------------"<<endl;
    int dimensions;
    cout<<"Ingresa la quantity de dimensiones: ";
    cin>>dimensions;
    cKDTree tree(dimensions);
    int option;
    int quantity;
    vector<float> cord;
    menu();
    cin>>option;
    while (option<6){
        switch(option){
            case 1: //Insert random
                cout<<"Ingrese la cantidad de datos a insertar: ";
                cin>>quantity;
                for (int i=0;i<quantity;i++)
                {
                    addCoordinatesRan(&cord, dimensions);
                    cCoordinate cordenadita(cord);
                    cordenadita.print();
                    tree.mInsert(cordenadita);
                    cord.clear();
                }
                break;
            case 2: // Insert for console
                cout<<"Ingrese la cantidad de datos a insertar: ";
                cin>>quantity;
                for (int i=0;i<quantity;i++)
                {
                    addCoordinates(&cord, dimensions);
                    cCoordinate cordenadita(cord);
                    cordenadita.print();
                    tree.mInsert(cordenadita);
                    cord.clear();
                }
                break;
            case 3: break;
            case 4: break;
            case 5: break;
        }
        cout<<"-----------------------------Arbol-------------------------"<<endl;
        tree.print();
        cout<<endl;
        menu();
        cin>>option;
    }
    return 0;
}
