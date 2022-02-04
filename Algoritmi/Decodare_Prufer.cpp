#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;


void citire(string input);
void decodare_prufer();
void afisare(string output);

int n;
vector<int>fii;
vector<int> tati;
queue<int>K;

int main(int argc, char** argv) {
   
    citire(argv[1]);
    decodare_prufer();
    afisare(argv[2]);
}

void citire(string input)
{
    ifstream fin(input);
    fin >> n;
    fii = vector<int>(n + 1, 0);
    tati = vector<int>(n + 1, -1);

    int x;
    while (fin >> x)
    {
        K.push(x);
        fii[x]++;
    }

    ;
    fin.close();
}

void decodare_prufer()
{
    for (int i = 0; i < n; ++i) 
    {
        int x = K.front();
        K.pop();

        int y = find(fii.begin(), fii.end(), 0) - fii.begin();
        fii[x]--;
        fii[y]++;

        tati[y] = x;
        K.push(y);
    }
}

void afisare(string output)
{
    ofstream fout(output);

    fout << n + 1 << '\n';
    for (const auto& el : tati)
        fout << el << " ";

    fout.close();
}
