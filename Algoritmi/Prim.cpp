/* Algoritmul lui Prim
 * Determina APM astfel:
 * Asociaza fiecarui nod x, o cheie key[x], avand semnificatia
 * ca este costul minim al unei muchii incidente cu x
 * si cu un nod din APM.
 * APM porneste de la un nod de start (de ex 1), avand cheia 0.
 * Sirul key se initializeaza cu Infinit.
 * Pentru fiecare muchie avand un capat in arbore si celalalt
 * capat in graf, se alege "muchia usoara", adica de pondere minima.
 * Iar nodul din graf se adauga la APM.
 */
#include <fstream>
#include <vector>
#include <queue>
#include <bitset>
#include <tuple>
using namespace std;

const int Inf = 0x3f3f3f3f,
MaxN = 200001;

struct Edge {
	Edge() : node{ 0 }, key{ 0 } {};
	Edge(int node, int key) : node{ node }, key{ key } {};

	bool operator < (const Edge& e) const
	{
		return key > e.key;
	}

	int node, key;
};

int n;
vector<vector<pair<int, int>>> G;   // graful
vector<int> key;  // cheile asociate nodurilor
vector<int> t;    // sirul de "tati" (retine APM)

vector<bool> v; // marcheaza cu 1 nodurile 
				// aflate in APM (cele care ies din coada) 
vector<pair<int, int>> apm;  // retine muchiile APM-ului
long long cost_apm;


void citeste(string input);
void Prim(int x);
void afiseaza(string output);

int main(int argc, char** argv)
{
	citeste(argv[1]);
	Prim(1);
	afiseaza(argv[2]);
}

void citeste(string input)
{
	ifstream fin(input);

	int a, b, w, m;

	fin >> n >> m;
	G = vector<vector<pair<int, int>>>(n + 1);

	while (m--)
	{
		fin >> a >> b >> w;
		G[a].emplace_back(b, w);
		G[b].emplace_back(a, w);
	}

	fin.close();
}

void Prim(int x)
{
	priority_queue<Edge> Q;
	t = vector<int>(n + 1);
	key = vector<int>(n + 1, Inf);
	key[x] = 0;
	Q.emplace(x, 0);

	int y, w; // ky = ponderea muchiei de la x la y
	while (!Q.empty())
	{
		x = Q.top().node;
		v[x] = 1; // marcam ca x se adauga in APM
		for (auto& p : G[x])
		{
			tie(y, w) = p;

			if (v[y]) continue;
			if (key[y] > w)
			{
				key[y] = w;
				t[y] = x;
				Q.emplace(y, key[y]);
			}
		}

		apm.emplace_back(x, t[x]);
		cost_apm += key[x];

		while (!Q.empty() && v[Q.top().node])
			Q.pop();
	}
}

void afiseaza(string output)
{
	ofstream fout(output);
	fout << cost_apm << '\n';

	fout << apm.size() - 1 << '\n';

	for (size_t i = 1; i < apm.size(); ++i)
		fout << apm[i].first << ' ' << apm[i].second << '\n';
	fout.close();
}



