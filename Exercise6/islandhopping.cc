#include <iostream>
#include <vector>
#include <utility>
#include <math.h>
#include <algorithm>

class Edge {
public:
    Edge(int n1, int n2, double w) {
        u = n1;
        v = n2;
        weight = w;
    }

    bool operator<(Edge const& other) {
        return weight < other.weight;
    }

    int u, v;
    double weight;
};

float euclidianDistance(std::pair<float, float> a, std::pair<float, float> b) {
    return sqrt(pow(a.first - b.first, 2) + pow(a.second - b.second, 2));
}

float kruskal(std::vector<Edge> edges, int n) {
    float cost = 0;
    std::vector<int> treeID(n);
    for (int i = 0; i < n; ++i) {
        treeID[i] = i;
    }

    sort(edges.begin(), edges.end());

    for (Edge e : edges) {
        if (treeID[e.u] != treeID[e.v]) {
            cost += e.weight;

            int oldID = treeID[e.u];
            int newID = treeID[e.v];
            for (int i = 0; i < n; ++i) {
                if (treeID[i] == oldID) {
                    treeID[i] = newID;
                }
            }
        }
    }
    return cost;
}

int main(int argc, char const *argv[]) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);
    
    int n, m;
    std::cin >> n;

    for (int i = 0; i < n; ++i) {
        std::cin >> m;

        std::vector<std::pair<float, float>> islands(m);
        float x, y;
        for (int j = 0; j < m; ++j) {
            std::cin >> x >> y;
            islands[j] = {x, y};
        }

        std::vector<Edge> bridges;

        for (int j = 0; j < m; ++j) {
            for (int k = j+1; k < m; ++k) {
                bridges.push_back(Edge(j, k, euclidianDistance(islands[j], islands[k])));
            }
        }

        std::cout << kruskal(bridges, m) << "\n";
    }
    return 0;
}