#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <stack>
#include <queue>

using namespace std;

template <typename T>
class cNode{
	public:

		pair<T,T> mData;
		pair<int,int> radios;
		cNode<T>* mChild[2];

		cNode(){
			mChild[0]=nullptr;
			mChild[1]=nullptr;
		}

};
