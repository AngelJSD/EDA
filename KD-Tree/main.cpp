#include <iostream>
#include "KDTree.cpp"

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


int main(int argc, char const *argv[]) {
    cout<<"----------------KDTree---------------"<<endl;
    int dimensions;
    cout<<"Ingresa la cantidad de dimensiones: ";
    cin>>dimensions;
	cKDTree<int> tree(dimensions);
    vector<float> cord;
    addCoordinates(&cord, dimensions);
    cCoordinate cordinadita(cord);
    cordinadita.print();
    tree.mInsert(cordinadita);
	return 0;
}
