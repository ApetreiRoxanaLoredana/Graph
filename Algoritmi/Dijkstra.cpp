/// Afiseaza drumul minim dintre un nod s si toate celelalte noduri
/// Foloseste costuri
/// Foloseste o lista de adiacenta
#include <fstream>
#include <vector>
#include <queue>
#include <fstream>
#include <tuple>
#include <iostream>
using namespace std;

const int Inf = 0x3f3f3f3f;

struct Pair {
    int node, dist;
    bool operator < (const Pair& p) const
    {
        return dist > p.dist;
    }
};

int n, m; // numarul de varfuri, muchii
int s; //nodul sursa
vector<int> d;  // d[x] = dist minima de la sursa la nodul x
vector<vector<Pair>> G; //lista de adiacenta a costurilor

void citire(string input);
void Dijkstra(int s);
void afisare(string output);

int main(int argc, char** argv)
{
    citire(argv[1]);
    Dijkstra(s);
    afisare(argv[2]);
}

void Dijkstra(int s)
{
    d = vector<int>(n, Inf);
    priority_queue<Pair> Q;

    d[s] = 0;
    Q.push({ s, 0 });

    int y, w, dist, u;
    while (!Q.empty())
    {
        u = Q.top().node;
        dist = Q.top().dist;
        Q.pop();
        if (dist <= d[u])
        {
            for (auto& p : G[u])
            {
                y = p.node;
                w = p.dist;
                if (d[y] > d[u] + w)
                {
                    d[y] = d[u] + w;
                    Q.push({ y, d[y] });
                }
            }
        }
    }
}

void citire(string input)
{
    ifstream fin(input);

    int x, y, w;

    fin >> n >> m >> s;
    G = vector<vector<Pair>>(n);

    while (fin >> x >> y >> w)
        G[x].push_back({ y, w });

    fin.close();
}

void afisare(string output)
{
    ofstream fout(output);

    for (int i = 0; i < n; ++i)
        if (d[i] == Inf)
            fout << "Inf" << ' ';
        else
            fout << d[i] << ' ';
    fout.close();
}
