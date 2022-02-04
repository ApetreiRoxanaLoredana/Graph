/// Calculeaza drumul minim de la un nod s la restul nodurilor
/// Foloseste o lista de adiacenta
/// Nu folosseste costuri!!!
/// Merge pe grafuri orientate/neorientate
/// Complexitate: O(V + E)

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <string>
#include <algorithm>
using namespace std;

typedef struct Nod {
	string culoare;
	int nr;
	int parinte;
	int distanta;
};

const int inf = 0x3f3f3f3f;
vector<vector<int>> G; //graful = lista de adiacenta
vector<Nod> lista_n;
int n; //numarul de varfuri

void citeste(string input);
void BFS(int s);
void afisare(string output, int s);

int main(int argc, char** argv)
{
	citeste(argv[1]); 
	BFS(0);
	afisare(argv[2], 0);
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

void BFS(int s)
{
	for (int i = 0; i < n; ++i)
	{
		lista_n[i].culoare = "alb";
		lista_n[i].nr = i;
		lista_n[i].distanta = inf;
		lista_n[i].parinte = -1;
	}
	lista_n[s].culoare = "gri";

	queue<int> Q; //coada
	Q.push(s);

	while (!Q.empty())
	{
		int u = Q.front();
		Q.pop();
		for (auto& v: G[u])
		{
			if (lista_n[v].culoare == "alb")
			{
				lista_n[v].culoare = "gri";
				lista_n[v].distanta = lista_n[u].distanta + 1;
				lista_n[v].parinte = u;
				Q.push(v);
			}
		}
		lista_n[u].culoare = "negru";
	}


}

void afisare(string output, int s)
{
	ofstream fout(output);
	priority_queue<int, vector<int>, greater<int>> Qp;

	Qp.push(s);
	for (int i = 0; i < n; ++i)
		if (lista_n[i].parinte != -1)
			Qp.push(i);

	while (!Qp.empty())
	{
		fout << Qp.top() << ' ';
		Qp.pop();
	}

	fout.close();
}

