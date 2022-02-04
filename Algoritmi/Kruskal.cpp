#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

//disjoint-set
class DS {

private:
	int n; //numarul de noduri
	vector<int> t;
	vector<int> h;

public:
	DS(int n) : n{ n }, t{ vector<int>(n) }, h{ vector<int>(n) }
	{
		for (int i = 0; i < n; ++i)
			t[i] = i;
	}

	int Find(int x)
	{
		if (x == t[x])
			return x;
		return t[x] = Find(t[x]);
	}

	void Union(int r1, int r2)
	{
		if (h[r1] > h[r2])
			t[r2] = r1;
		else
		{
			t[r1] = r2;

			if (h[r1] == h[r2])
				h[r2]++;
		}
	}
};

struct Edge {
	Edge(int a, int b, int w) : a{ a }, b{ b }, w{ w }{}

	bool operator < (const Edge& e) const
	{
		return w < e.w;
	}

	int a, b, w;
};

void citeste(string input);
void Kruskal();
void afiseaza(string output);

int n, m;            // noduri, muchii
int cmin = 0;        // costul arborelui minim de acoperire
vector<Edge> edges;  // retine graful ca vect de muchii
vector<Edge> apm; //arborele de acoperire

int main(int argc, char** argv)
{
	citeste(argv[1]);
	Kruskal();
	afiseaza(argv[2]);
}

void citeste(string input)
{
	ifstream fin(input);

	fin >> n >> m;
	int a, b, w; //muchia/costul
	while (fin >> a >> b >> w)
		edges.emplace_back(a, b, w);

	fin.close();
}

void Kruskal()
{
	int c1, c2;  // componentele conexe (arborii) din care fac parte nodurile a si b	

	DS ds(n);

	sort(edges.begin(), edges.end());

	for (const auto& edge : edges)
	{
		// find - O(1)
		c1 = ds.Find(edge.a);
		c2 = ds.Find(edge.b);
		if (c1 != c2)
		{
			cmin += edge.w;
			apm.emplace_back(edge);

			ds.Union(c1, c2);
			if (apm.size() == size_t(n - 1))
				break;
		}
	}
}

void afiseaza(string output)
{
	//afisare
	ofstream fout(output);

	fout << cmin << '\n'; //costul minim

	int nr_m = apm.size();
	fout << nr_m << '\n'; //numarul de muchii din arborele minim de acoperire

	sort(apm.begin(), apm.end(), [](const Edge& x, const Edge& y) {
		if (x.a == y.a)
			return x.b < y.b;
		return x.a < y.a;
		});

	//afiseaza muchiile sortate crescator
	for (const Edge& edge : apm)
		fout << edge.a << ' ' << edge.b << '\n';

	fout.close();
}



