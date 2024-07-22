/// Afiseaza componentele conexe ale unui graf
/// Foloseste o lista de adiacenta
/// Nu folosseste costuri!!!
/// Merge pe grafuri orientate/neorientate
/// Complexitate: Theta(V + E)

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
#include <string>
using namespace std;

typedef struct Nod {
	string culoare;
	//int nr;
	int parinte;
	//int distanta;
	//int f; //timpul final
};

const int inf = 0x3f3f3f3f;

void citeste(string input);
void DFS();
void DFS_VISIT(int s);
void afiseaza(string output);

vector<Nod> lista_n;
vector<vector<int>> G; //graful = lista de adiacenta
vector<vector<int>> Padure;
int n; // numarul de varfuri
int cnt;

int main(int argc, char** argv)
{
	citeste(argv[1]); //graf neorientat
	DFS();
	afiseaza(argv[2]);
}

void citeste(string input)
{
	ifstream fin(input);
	fin >> n;
	G = vector<vector<int>>(n);
	lista_n = vector<Nod>(n);

	int x, y;
	while (fin >> x >> y)
	{

		G[x].push_back(y);
		G[y].push_back(x);
	}
	fin.close();
}

void DFS()
{
	lista_n = vector<Nod>(n, { "alb", -1 });

	int time = 0;

	for (int i = 0; i < n; ++i)
		if (lista_n[i].culoare == "alb")
		{
			Padure.push_back(vector<int>());
			Padure[cnt].push_back(i);
			DFS_VISIT(i);
			cnt++;
		}
}

void DFS_VISIT(int s)
{
	lista_n[s].culoare = "gri";
	for (const auto& v : G[s])
		if (lista_n[v].culoare == "alb")
		{
			lista_n[v].parinte = s;
			Padure[cnt].push_back(v);
			DFS_VISIT(v);
		}
	lista_n[s].culoare = "negru";
}

void afiseaza(string output)
{
	ofstream fout(output);

	for (int i = 0; i < cnt; ++i, fout << '\n')
		for (const auto& v : Padure[i])
			fout << v << ' ';

	fout.close();
}




