/// Afiseaza cele mai scurte drumuri de la nodul s la toate celelalte
/// Merge pe grafuri orientate/neorientate
/// Nu merge pt grafuri cu costuri!!!
/// Foloseste lista de adiacenta

#include <vector>
#include <iostream>
#include <fstream>
#include <queue>
using namespace std;

const int inf = 0x3f3f3f3f;
int n; // numarul de noduri
vector<vector<int>> G; //lista de adiacenta
vector<int>L; //lungimea drumurilor
vector<int>P; //parintii

void citeste(string input);
void Moore(int s);
void afisare(string output);

int main(int argc, char** argv)
{
	citeste(argv[1]);
	Moore(0);
	afisare(argv[2]);
}

void citeste(string input)
{
	ifstream fin(input);

	fin >> n;
	G = vector<vector<int>>(n);
	L = vector<int>(n); //lungimea drumurilor
	P = vector<int>(n); //parintii

	int x, y;
	while (fin >> x >> y)
	{
		G[x].push_back(y);
		G[y].push_back(x);
	}

	fin.close();
}

void Moore(int s)
{
	L.assign(n, inf);
	L[s] = 0;

	queue<int> Q;
	Q.push(s);

	int x, y;

	while (!Q.empty())
	{
		x = Q.front();
		Q.pop();
		for (const auto& y : G[x])
		{
			if (L[y] == inf)
			{
				P[y] = x;
				L[y] = L[x] + 1;
				Q.push(y);
			}
		}
	}
}

void afisare(string output)
{
	ofstream fout(output);

	for (int i = 0; i < n; ++i)
	{
		fout << i << ": ";
		int j = L[i];
		if (j == inf)
			fout << "Nu exista drum" << '\n';
		else
		{
			fout << i << ' ';
			int k = i;
			while (j)
			{
				fout << P[k] << ' ';
				k = P[k];
				j--;
			}
			fout << '\n';
		}
	}
	fout.close();
}

