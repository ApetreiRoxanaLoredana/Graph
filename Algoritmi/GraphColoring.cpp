#include <iostream>
#include <fstream>
#include <queue>
#include <algorithm>
using namespace std;

typedef struct Nod {
	int nr;
	int grad;

	bool operator < (const Nod& ot) const {
		if (grad == ot.grad)
			return nr < ot.nr;
		return this->grad < ot.grad;
	}
};

vector<vector<int>> G; //lista de adiacenta
vector<bool>culori;
vector<int>rez;
priority_queue<Nod> Q;
int n, m;

void citire(string input);
void colorare();

int main(int argc, char** argv)
{
	citire(argv[1]);

	ofstream fout(argv[2]);
	if (n * (n - 1) / 2 == m)
	{
		fout << n << '\n';
		for (int i = 0; i < n; ++i)
			fout << i << ' ';
	}
	else
	{
		colorare();
		auto it = max_element(rez.begin(), rez.end());

		//afisare
		fout << *it + 1 << '\n';
		for (int i = 0; i < n; ++i)
			fout << rez[i] << ' ';
	}
	fout.close();

}

void citire(string input)
{
	ifstream fin(input);
	fin >> n >> m;

	G = vector<vector<int>>(n);
	culori = vector<bool>(n, false);
	rez = vector<int>(n, -1);

	int x, y;
	while (fin >> x >> y)
	{
		G[x].push_back(y);
		G[y].push_back(x);
	}
	fin.close();
}

void colorare()
{
	for (int i = 0; i < n; ++i)
		Q.push({ i, (int)G[i].size() }); // adaugam in coada nodurile si gradurile sale

	auto v_prim = Q.top();
	Q.pop();
	rez[v_prim.nr] = 0;

	while (!Q.empty())
	{
		auto v = Q.top();
		Q.pop();

		for (const auto& u : G[v.nr])
			if (rez[u] != -1)
				culori[rez[u]] = true;

		for (int i = 0; i < n; ++i)
			if (!culori[i])
			{
				rez[v.nr] = i;
				break;
			}

		for (int i = 0; i < n; ++i)
			culori[i] = false;
	}
}
