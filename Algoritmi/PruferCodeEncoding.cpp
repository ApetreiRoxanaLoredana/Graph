#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

struct Varf {
    int tata;
    int nr_fii;
};

struct Frunza {
    int nod;
    bool operator <(const Frunza& ot) const {
        return nod > ot.nod;
    }
};

void citire(string input);
void codare_prufer();
void afisare(string output);

int n;
int radacina = -1;
vector<Varf> G;
vector<int> prufer;

int main(int argc, char* argv[]) {
   
    citire(argv[1]);
    codare_prufer();
    afisare(argv[2]);
}

void citire(string input)
{
    ifstream fin(input);

    int tata;
    radacina = -1;
    fin >> n;

    G = vector<Varf>(n);

    for (int i = 0; i < n; ++i)
    {
        fin >> tata;
        G[i].tata = tata;
        if (tata != -1)
            G[tata].nr_fii++;
        else
            radacina = i;
    }

    fin.close();
}

void codare_prufer()
{
    priority_queue<Frunza> frunze;

    for (int i = 0; i < n; ++i)
        if (G[i].nr_fii == 0)
            frunze.push(Frunza{ i });

    while (!frunze.empty() && frunze.top().nod != radacina)
    {
        Frunza fr = frunze.top();
        frunze.pop();

        prufer.push_back(G[fr.nod].tata);
        G[G[fr.nod].tata].nr_fii--;
        if (G[G[fr.nod].tata].nr_fii == 0)
            frunze.push(Frunza{ G[fr.nod].tata });
    }
}

void afisare(string output)
{
    ofstream fout(output);

    fout << prufer.size() << "\n";
    for (auto& el : prufer)
        fout << el << " ";

    fout.close();
}
