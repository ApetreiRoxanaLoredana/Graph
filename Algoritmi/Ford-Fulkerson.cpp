#include <iostream>
#include <limits.h>
#include <queue>
#include <string.h>
#include <vector>
#include <fstream>
using namespace std;

typedef struct Nod {
    int nod;
    int cost;

    bool operator == (const Nod& p) const
    {
        return nod == p.nod;
    }
};

//cauta daca exista drum intre nodul s si t
bool bfs(int s, int t);
//returneaza fluxul maxim
int Ford_Fulkerson(int s, int t);
void citire(string input);

int n, m; //noduri/muchii
vector<vector<Nod>> G; //lista de adiacenta
vector<int> parent;
vector<int> dist;

int main(int argc, char** argv)
{
    
    citire(argv[1]);

    ofstream fout(argv[2]);
    fout << Ford_Fulkerson(0, n - 1);
    fout.close();

    return 0;
}

bool bfs(int s, int t)
{
    vector<bool> visited = vector<bool>(n, false);

    queue<int> Q;
    Q.push(s);
    visited[s] = true;
    parent[s] = -1;

    // Standard BFS Loop
    while (!Q.empty())
    {
        int u = Q.front();
        Q.pop();

        for (const auto& v : G[u])
            if (visited[v.nod] == false && v.cost > 0)
            {
                if (v.nod == t)
                {
                    parent[v.nod] = u;
                    return true;
                }
                Q.push(v.nod);
                parent[v.nod] = u;
                visited[v.nod] = true;
            }
    }
    return false;
}

int Ford_Fulkerson(int s, int t)
{
   
    //vector de parinti
    
    int max_flow = 0;

    while (bfs(s, t))
    {
        int path_flow = INT_MAX;
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            //cautam nodul in Gr[u] ca sa ii accesam costul
            auto it = find(G[u].begin(), G[u].end(), Nod{ v, 0 });
            int index = it - G[u].begin();
            //costul minim dintre nodurile lantului
            path_flow = min(path_flow, G[u][index].cost);
        }

        //facem update la valoarea fluxului
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            auto it = find(G[u].begin(), G[u].end(), Nod{ v, 0 });
            int index = it - G[u].begin();
            G[u][index].cost -= path_flow;

            auto it2 = find(G[v].begin(), G[v].end(), Nod{ u, 0 });
            int index2 = it2 - G[v].begin();
            if (index2 < 0 || index2 >= G[v].size())
            {
                G[v].push_back({ u, path_flow });
            }
            else
                G[v][index2].cost += path_flow;
        }

        max_flow += path_flow;
    }

    return max_flow;
}

void citire(string input)
{
    ifstream fin(input);
    fin >> n >> m;
    G = vector<vector<Nod>>(n);
    dist = vector<int>(n);
    parent = vector<int>(n);

    int x, y, w;

    while (fin >> x >> y >> w)
        G[x].push_back({ y, w });

    fin.close();
}
