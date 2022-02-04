#include <fstream>
#include <vector>
#include <tuple>
#include <bitset>
#include <stack>
#include <string>
using namespace std;

vector<bool> v;
vector<vector<tuple<int, int>>> G;   // G[x] - vector de muchii
vector<int> ce;   // ciclul eulerian
int n, m;

void CitesteGraf(string input);
void AfiseazaCiclu(string output);
bool EsteEulerian();
void DeterminaCiclu(int x);

int main(int argc, char* argv[])
{
    
    ofstream fout(argv[2]);

    CitesteGraf(argv[1]);

    if (!EsteEulerian())
        fout << "-1";
    else
    {   
        fout.close();
        DeterminaCiclu(1);
        AfiseazaCiclu(argv[2]);
    }
}

void CitesteGraf(string input)
{
    ifstream fin(input);
    fin >> n >> m;
    G = vector<vector<tuple<int, int>>>(n);
    v = vector<bool>(m, false);

    for (int i = 0, a, b; i < m; ++i)
    {
        fin >> a >> b;
        G[a].emplace_back(b, i);
        G[b].emplace_back(a, i);
    }
    fin.close();
}


void DeterminaCiclu(int x)
{
    vector<vector<tuple<int, int>>::iterator> p(n);

    for (int i = 0; i < n; ++i)
        p[i] = G[i].begin();

    int y, e;
    stack<int> stk;
    stk.push(0);

    while (!stk.empty())
    {
        x = stk.top();
        if (p[x] == G[x].end())
        {
            ce.emplace_back(x);
            stk.pop();
        }
        else
            while (p[x] != G[x].end())
            {
                tie(y, e) = *p[x]++;
                if (v[e]) continue;
                v[e] = true;
                stk.push(y);
                break;
            }
    }
}

void AfiseazaCiclu(string output)
{
    ofstream fout(output);
    for (size_t i = 0; i < ce.size() - 1; ++i)
        fout << ce[i] << ' ';
    fout.close();
}

bool EsteEulerian()
{
    for (int x = 0; x < n; ++x)
        if (G[x].size() % 2 == 1)
            return false;
    return true;
}