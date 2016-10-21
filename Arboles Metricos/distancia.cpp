#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<pair<string, int>> leer_palabras() {

	string palabra;
	vector<pair<string, int>> palabras;

	ifstream myfile("ejemplo.txt");

	int num = 10;

	if (myfile.is_open()) {
		while (getline(myfile, palabra)) {
			cout << palabra << '\n';
			palabras.push_back(make_pair(palabra, num));
			num = num - 1;
		}
		myfile.close();
		palabras.pop_back();
	}

	return palabras;
}

bool myfunction(pair<string, int> i, pair<string, int> j) {
	return (i.second < j.second);
}

void ordenar(vector<pair<string, int>> &palabras) {
	sort(palabras.begin(), palabras.end(), myfunction);
}

int main() {
  string palabra;
  vector<pair<string, int>> palabras = leer_palabras();

  for (int i; i < palabras.size(); i++) {
    cout << palabras[i].first << " " << palabras[i].second << endl;
  }

  ordenar(palabras);

  for (int i; i < palabras.size(); i++) {
    cout << palabras[i].first << " " << palabras[i].second << endl;
  }
}
