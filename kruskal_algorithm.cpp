#include <iostream>
#include <stdio.h>
#include <time.h>
#include <algorithm>
#include <vector>
#define edge pair<int, int>

using namespace std;

class Graf {
private:
    int* parent;
    int sum, lenght;
    vector<pair<float, edge> > EdgeChart;
    vector<pair<float, edge> > EdgeTree;
public:
    void addEdge(int u, int v, float w);
    void unia(int u, int v);
    Graf(int lenght);
    int search(int i);
    void kruskal();
};

void Graf::addEdge(int u, int v, float w) {
    EdgeChart.push_back(make_pair(w, edge(u, v)));
}

void Graf::unia(int u, int v) {
    parent[u] = parent[v];
}

Graf::Graf(int lenght) {
    sum = 0;
    parent = new int[lenght];

    for (int i = 0; i < lenght i++)
        parent[i] = i;

    EdgeTree.clear();
    EdgeChart.clear();
}

Graf readFromFile(char* str) {
    char str[100];
    int lenght, skip, u, v;
    float w;
    FILE* f;
    f = fopen(str, "r");
    fscanf(f,"%d",&skip);

    for (int i = 0; i < skip + 1; i++)
        fgets(str, 100, f);

    fscanf(f,"%d",&lenght);

    Graf gr(lenght);

    for (int i = 0; i < lenght i++) {
        fscanf(f,"%d%d%f",&u,&v,&w);
        gr.addEdge(u,v,w);
    }

    fclose(f);

    return gr;
}

int Graf::search(int i) {
    sum=sum+1;

    if (i == parent[i])
        return i;
    else
        return search(parent[i]);
}

void Graf::kruskal() {
    float weight = 0;
    int ur, vr;

    clock_t start1 = clock();

    sort(EdgeChart.begin(), EdgeChart.end());

    clock_t start2 = clock();
    double temp1 = start2 - start1;
    double czas1 = (temp1) / (double)CLOCKS_PER_SEC;
    start1 = clock();

    for (int i = 0; i < EdgeChart.size(); i++) {
        ur = search(EdgeChart[i].second.first);
        vr = search(EdgeChart[i].second.second);

        if (ur != vr) {
            EdgeTree.push_back(EdgeChart[i]);

            unia(ur, vr);
        }

    }

    start2 = clock();
    double temp2 = start2 - start1;
    double czas2 = (temp2) / (double)CLOCKS_PER_SEC;

    for (int i = 0; i < EdgeTree.size(); i++)
        weight = weight + EdgeTree[i].first;

    cout << "Number of operations performed: " << sum << endl;
    cout << "Total Weights: " << weight << endl;
    cout<< "Number of edges: "<<EdgeTree.size() << endl;
    cout << "The time of the main petrel: " << czas2 << endl;
    cout << "Sorting step time: " << czas1 << endl;
}

int main()
{
    Graf grt1(65);
    char g1[] = {"g1.txt"};
    grt1 = readFromFile(g1);
    grt1.kruskal();

    Graf grt2(378);
    char g2[] = { "g2.txt" };
    grt2 = readFromFile(g2);
    grt2.kruskal();

    Graf grt3(947973);
    char g3[] = { "g3.txt" };
    grt3 = readFromFile(g3);
    grt3.kruskal();


    return 0;
}
