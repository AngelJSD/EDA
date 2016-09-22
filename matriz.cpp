#include <iostream>
using namespace std;

template<class T>
struct CNODE
{
    T m_data;
    CNODE<T>* m_vertical[2];  // 0 arriba    , 1 abajo
    CNODE<T>* m_horizontal[2];// 0 izquierda , 1 derecha
    int m_x,m_y;
    CNODE(int x,int y,T a)
    {
        m_data=a;
        m_x=x;
        m_y=y;
    }
};

template <class T>
struct Cless
{
    inline bool operator()(T a, T b)
    {   return a<b;}
};
template <class T>
struct Cgreater
{
    inline bool operator()(T a, T b)
    {   return a>b;}
};

template <class T>
class SparseMatrix
{
    public:
    CNODE<T>* m_root;
    SparseMatrix(int x,int y,T a)
    {
        m_root =new CNODE<T>(x,y,a);
    }
    bool m_findy(int y, CNODE<T>** &p)
    {
        cout<<"buscando Y "<<(*p)->m_y<<endl;
        //nodo donde se va a insertar verticalmente
        if(y>(*p)->m_y) Cgreater<T> cmp;
        else Cless<T> cmp;
        for(;(*p) && y!=(*p)->m_y && cmp(y,(*p)->m_y) && ( (*p)->m_vertical[y>(*p)->m_y] ) ; p=&(*p)->m_vertical[y>(*p)->m_y]);
        if((*p) && (*p)->m_y==y)return 1;
        return 0;
    }
    bool m_findx(int x, CNODE<T>** &q)
    {
        cout<<"buscando X"<<endl;
        //nodo donde se va a insertar horizontalmente
        if(x>(*q)->m_x) Cgreater<T> cmp;
        else Cless<T> cmp;
        for(;(*q) && x!=(*q)->m_x && cmp(x,(*q)->m_x) && (*q)->m_horizontal[x>(*q)->m_x]  ; q=&(*q)->m_horizontal[x>(*q)->m_x]);
        if((*q)->m_x==x )return 1;
        return 0;
    }
    bool m_find(int x,int y, CNODE<T>** &p,CNODE<T>** &q)
    {
        cout<<"buscando"<<endl;
        p=&m_root;
        if(m_findy(y,p))
        {
            q=p;
            if(m_findx(x,q))return 1;
        }
        return 0;
    }
    bool m_insert(int x,int y, T a)// falta evaluar todos los casos =P (osea esto no sirve para nada)
    {
        CNODE<T>**p,**q;
        if(m_find(x,y,p,q))//si lo encuentra solo modifica el valor
        {
            (*q)->m_data=a;
            return 0;
        }
        cout<<"insertando"<<endl;
        CNODE<T> *t =new CNODE<T>(x,y,a);
//        if( x==(*p)->m_x )
//        {
//
//        }
        if(x<(*p)->m_x)//si va a la izquierda
        {
            t->m_horizontal[1]=(*p);                    //derecha
            t->m_horizontal[0]=(*p)->m_horizontal[0];   // izquierda

        }
//        if((*p)->m_x==x)//si ya existe la columna busca verticalmente
//        {
//            if((*q)->m_y>y) // si va encima
//            {
//                t->m_down=(*q);
//                *q=t;
//                return 1;
//            }
//            (*q)->m_down=t; // si va debajo
//            return 1;
//        }
        cout<<(*p)->m_x<<" ; "<<(*p)->m_y<<endl;

//        delete t;
        return 1;
    }
    bool m_remove(int x, int y)
    {
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
int main()
{
    cout << "Hello world!" << endl;
    SparseMatrix<char> Matriz(1,2,'a');
    Matriz.m_insert(3,5,'z');
    Matriz.m_insert(2,3,'s');
    return 0;
}
