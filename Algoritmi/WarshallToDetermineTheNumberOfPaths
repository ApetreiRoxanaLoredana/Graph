///Calculeaza matricea drumurilor (cate drumuri exista de la un nod u la v)
///Foloseste o matrice de adiacenta
///Graf orientat neponderat
///Poate spune daca exista sau nu un drum intre nodul i si nodul j
///Complexitate O(n^3)

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

//const int inf = 0x3f3f3f3f;
vector<vector<int>> d; // matricea distantelor
int n; // numarul de muchii

void citeste(string input);
void warshall();
void afiseaza(string output);

int main(int argc, char** argv)
{
	citeste(argv[1]);
	warshall();
	afiseaza(argv[2]);
}

void citeste(string input)
{
	ifstream fin(input);
	fin >> n;
	d = vector<vector<int>>(n);

	for (int i = 0; i < n; ++i)
		d[i] = vector<int>(n, 0);
	

	int x, y;
	while (fin >> x >> y)
		d[x][y] = 1;

	fin.close();
}

void warshall()
{
	for (int k = 0; k < n; ++k)
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n; ++j)
				d[i][j] += d[i][k] * d[k][j];
}

void afiseaza(string output)
{
	ofstream fout(output);

	for (int i = 0; i < n; ++i, fout << '\n')
		for (int j = 0; j < n; ++j)
			fout << d[i][j] << ' ';
	fout.close();
}
