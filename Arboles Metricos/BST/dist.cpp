#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char const *argv[]) {

	string s1 = argv[1];
	string s2 = argv[2];

	int N1 = s1.size();
	int N2 = s2.size();
	int i, j;
	vector<int> vec(N2+1);

	for ( i = 0; i <= N2; i++ ){
		vec[i] = i;
	}

	for ( i = 0; i < N1; i++ ){
		vec[0] = i+1;
		int corner = i;
		for ( j = 0; j < N2; j++ )
		{
			int upper = vec[j+1];
			if ( s1[i] == s2[j] ){
				vec[j+1] = corner;
			}
			else{
				vec[j+1] = min(vec[j], min(upper, corner)) + 1;
			}
		corner = upper;
		}
	}
	cout<<"Distancia: "<<vec[N2]<<endl;
}
