#include <fstream>
#include <vector>
#include <queue>
#include <fstream>
#include <iostream>
#include <tuple>
#include <string>
using namespace std;

const int Inf = 0x3f3f3f3f;

struct Pair {
    int node, dist;
    bool operator < (const Pair& p) const
    {
        return dist > p.dist;
    }
};

//s nod sursa
//n numarul de varfuri
//referinta la un vector de vector de pair 
//d referinta la o lista de distante
void Dijkstra(int s, vector<int>& d);
bool bellman_ford(int s, vector<int> d);
bool johnson();
void citire(string input);
void afisare(string output);

int n; // numarul de varfuri
vector<vector<int>> d;  // d[x] = dist minima de la sursa la nodul x
vector<vector<Pair>> G; //matricea costurilor
vector<int> h;

int main(int argc, char** argv)
{
    citire(argv[1]);

    if (johnson())
        afisare(argv[2]);
    else
    {
        ofstream fout(argv[2]);
        fout << -1;
        fout.close();
    }
}

bool johnson()
{
    for (int i = 0; i < n; ++i)
        G[n].push_back({ i, 0 });

    if (!bellman_ford(n, h))
        return false;

    bool ok = false;
    for(int i = 0; i < n; ++i)
        if (!h[i])
        {
            ok = true;
            break;
        }

    for(int i = 0; i < n + 1; i++)
        for (int j = 0; j < G[i].size(); ++j)
            G[i][j].dist += h[i] - h[G[i][j].node];

    for (int i = 0; i < n; ++i)
    {
        Dijkstra(i, d[i]);
        if (ok)
            for (int j = 0; j < n; j++)
                d[i][j] = d[i][j] - h[i] + h[j];
    }

    true;  
}

void Dijkstra(int s, vector<int>& d)
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
    return;

}

bool bellman_ford(int s, vector<int> d)
{
    int m = n + 1;
    d = vector<int>(m, Inf); //initializare
    d[s] = 0;

    for (int i = 1; i <= m - 1; i++)
        for (int j = 0; j < m; j++)
            for (int k = 0; k < G[j].size(); ++k)
            {
                int u = j;
                int v = G[j][k].node;
                int w = G[j][k].dist;

                if (d[v] > d[u] + w)
                    d[v] = d[u] + w;
            }

    for (int j = 0; j < m; ++j)
        for (int k = 0; k < G[j].size(); ++k)
        {
            int u = j;
            int v = G[j][k].node;
            int w = G[j][k].dist;

            if (d[v] > d[u] + w)
                return false;
        }

    return true;
}

void citire(string input)
{
    ifstream fin(input);

    int e, x, y, w;

    fin >> n >> e;

    G = vector<vector<Pair>>(n + 1);
    d = vector<vector<int>>(n + 1);
    h = vector<int>(n + 1);

    while (fin >> x >> y >> w)
        G[x].push_back({ y, w });

    fin.close();
}

void afisare(string output)
{
    ofstream fout(output);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < G[i].size(); ++j)
            fout << i << ' ' << G[i][j].node << ' ' << G[i][j].dist << '\n';

    for (int i = 0; i < n; ++i, fout << '\n')
        for (int j = 0; j < n; ++j)
            if (d[i][j] >= Inf - 1000)
                fout << "INF" << ' ';
            else
                fout << d[i][j] << ' ';

    fout.close();
}
