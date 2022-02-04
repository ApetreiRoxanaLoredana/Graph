#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
#include <string>
#include <stack>
using namespace std;

typedef struct Nod {
	string culoare;
	int nr;
	int parinte;
	//int distanta;
	int f; //timpul final

	bool operator < (const Nod& ot) const {
		return f < ot.f;
	}
};

const int inf = 0x3f3f3f3f;

void citeste(string input);
void DFS();
void DFS_VISIT(int s);
void sortare_topologica();
void afiseaza(string output);

vector<Nod> lista_n;
vector<vector<int>> G; //graful = lista de adiacenta
stack<int>stk;
int n; // numarul de varfuri
int time_varf;

int main(int argc, char** argv)
{
	citeste(argv[1]);
	sortare_topologica();
	afiseaza(argv[2]);
}

void citeste(string input)
{
	ifstream fin(input);
	fin >> n;
	G = vector<vector<int>>(n);

	int x, y;
	while (fin >> x >> y)
		G[x].push_back(y);

	fin.close();
}

void DFS()
{
	for (int i = 0; i < n; ++i)
		lista_n.push_back({ "alb", i, -1, -1 });

	time_varf = 0;

	for (int i = 0; i < n; ++i)
		if (lista_n[i].culoare == "alb")
			DFS_VISIT(i);
}

void DFS_VISIT(int s)
{
	time_varf++;
	lista_n[s].culoare = "gri";
	for (const auto& v : G[s])
		if (lista_n[v].culoare == "alb")
		{
			lista_n[v].parinte = s;
			DFS_VISIT(v);
		}
	lista_n[s].culoare = "negru";
	time_varf++;
	lista_n[s].f = time_varf;
	stk.push(s);
}

void sortare_topologica()
{
	DFS();
	sort(lista_n.begin(), lista_n.end(), [](const Nod& a, const Nod& b) {return a.f > b.f;});
}

void afiseaza(string output)
{
	ofstream fout(output);

	while (!stk.empty())
	{
		fout << stk.top() << ' ';
		stk.pop();
	}

	fout.close();
}






