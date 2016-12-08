#include <iostream>
#include "KDTree.h"

using namespace std;

void addCoordinates(vector<float>* coord, int dim)
{
    for (int i=0;i<dim;i++)
    {
        cout<<"i:";
        float coordinateI;
        cin>>coordinateI;
        coord->push_back(coordinateI);
    }
}

void addCoordinatesRan(vector<float>* coord, int dim)
{
    for (int i=0;i<dim;i++)
    {
        float coordinateI=rand() % 100;
        coord->push_back(coordinateI);
    }
}


int main() {
    cout<<"----------------KDTree---------------"<<endl;
    int dimensions;
    cout<<"Ingresa la cantidad de dimensiones: ";
    cin>>dimensions;
    cKDTree tree(dimensions);
    int cantidad=11;
    vector<float> cord;
    for (int i=0;i<cantidad;i++)
    {
        addCoordinates(&cord, dimensions);
        cCoordinate cordenadita(cord);
        cordenadita.print();
        tree.mInsert(cordenadita);
        cord.clear();
    }

    cout<<"Arbol"<<endl;
    tree.print();
    //tree.mInsert(cordenadita);
    return 0;
}
