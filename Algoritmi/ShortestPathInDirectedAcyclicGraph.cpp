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
void drum_minim_dag(int s);
void afiseaza(string output);

struct Pair {
	int node, dist;
	bool operator < (const Pair& p) const
	{
		return dist > p.dist;
	}
};

vector<Nod> lista_n;
vector<vector<Pair>> G; //graful = lista de adiacenta
stack<int>stk;
vector<int> d; //vector de drumuri
int n, s; // numarul de varfuri
int time_varf;

int main(int argc, char** argv)
{
	citeste(argv[1]);
	drum_minim_dag(s);
	afiseaza(argv[2]);
}

void citeste(string input)
{
	ifstream fin(input);
	fin >> n >> s;
	G = vector<vector<Pair>>(n);

	int x, y, w;
	while (fin >> x >> y >> w)
		G[x].push_back({ y, w });

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
		if (lista_n[v.node].culoare == "alb")
		{
			lista_n[v.node].parinte = s;
			DFS_VISIT(v.node);
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

void drum_minim_dag(int s)
{
	sortare_topologica();
	d = vector<int>(n, inf);
	d[s] = 0;

	int y, w;
	while (!stk.empty())
	{
		auto u = stk.top();
		stk.pop();
		for (auto& p : G[u])
		{
			y = p.node;
			w = p.dist;
			if (d[y] > d[u] + w)
				d[y] = d[u] + w;
		}
	}

}

void afiseaza(string output)
{
	ofstream fout(output);

	for (int i = 0; i < n; ++i)
		if (d[i] == inf)
			fout << "Inf" << ' ';
		else
			fout << d[i] << ' ';
	fout.close();
}






