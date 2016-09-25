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
