#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
using namespace std;

typedef struct Varf {
	int h; // inaltime
	int e; // exces
	int nod;
};

struct CmpVarf
{
	bool operator()(const Varf* v1, const Varf* v2) const
	{
		return v1->h < v2->h;
	}
};

using VV = vector<Varf>;
using VI = vector<int>;
using VVI = vector<VI>;

const int inf = 0x3f3f3f3f;
int n, m, c;
VV V;
VVI G; // graful sub forma de lista de adiacenta
priority_queue<Varf*, vector<Varf*>, CmpVarf> Q; // coada

void pompare_preflux(int s, int t);
void initializare(int s, int t);
void pompare(int u, int v, int s, int t);
void inaltare(int u);

int main(int argc, char** argv)
{
	ifstream fin(argv[1]);
	ofstream fout(argv[2]);

	// citire
	fin >> n >> c >> m;
	n++;
	G = VVI(n);
	for (int i = 0; i < n; ++i)
		G[i] = VI(n, 0);
	V = VV(n);

	int x, y, w;
	while (fin >> x >> y >> w)
		G[x][y] = w;

	int cnt = 0;
	while (cnt < c)
	{
		G[n - 1][cnt] = inf;
		cnt++;
	}

	//salvam fluxul nodurilor s
	VI camine = VI(c, 0);
	for (int i = 0; i < c; ++i)
		for (int j = 0; j < n; ++j)
			if (G[i][j] != 0)
				camine[i] += G[i][j];

	pompare_preflux(n - 1, n - 2);

	fout << V[n - 2].e << '\n';

	int flux = V[n - 2].e;
	cnt = 0;
	//Afisam nr de studenti din camine
	while (cnt < c && flux - camine[cnt] >= 0)
	{
		flux -= camine[cnt];
		fout << camine[cnt] << ' ';
		cnt++;
	}
	if (flux != 0)
		fout << flux << ' ';

	fin.close();
	fout.close();
}

void pompare_preflux(int s, int t)
{
	initializare(s, t);

	while (!Q.empty())
	{
		auto u = Q.top();
		bool ok = false;
		for (int i = 0; i < n; ++i)
		{
			if (u->h == V[i].h + 1 && G[u->nod][i] > 0)
			{
				pompare(u->nod, i, s, t);
				ok = true;
				break;
			}
		}
		if (!ok)
			inaltare(u->nod);
	}
}

void initializare(int s, int t)
{
	for (int i = 0; i < n; ++i)
	{
		V[i].e = 0;
		V[i].h = 0;
		V[i].nod = i;
	}

	V[s].h = n;

	for (int i = 0; i < n; ++i)
	{
		if (G[s][i] != 0)
		{
			V[i].e = G[s][i];
			if (i != t)
				Q.push(&V[i]);
			G[i][s] += G[s][i];
			G[s][i] = 0;
		}
	}
}

void pompare(int u, int v, int s, int t)
{
	int d = min(V[u].e, G[u][v]);
	G[u][v] -= d;
	G[v][u] += d;

	V[u].e -= d;
	V[v].e += d;

	if (V[u].e == 0)
		Q.pop();

	if (s != v && t != v)
		Q.push(&V[v]);
}

void inaltare(int u)
{
	int h_min = 0x3f3f3f3f;
	for (int i = 0; i < n; ++i)
		if (G[u][i] > 0)
			h_min = min(h_min, V[i].h);
	V[u].h = 1 + h_min;
}
