#include "qtree.h"

main(){

    coord c1(2, 2);
    coord c2(5, 5);
    coord c3(1, 1);
    cQTree<int> arbol(c1, c2, 400);
    arbol.insert(98734, c3);
}