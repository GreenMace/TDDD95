#include <iostream>
#include <vector>
#include <math.h>
#include <set>

class Edge {
public:
    Edge(int f, int t, int w) {
        from = f;
        to = t;
        weight = w;
    }

    int from;
    int to;
    int weight;
};

const int INF = 1000000000;

void floydWarshall(std::vector<Edge> graph, int n, std::vector<std::vector<int>> &d) {
    std::vector<int> row(n, INF);
    d.assign(n, row);

    for (auto edge : graph) {
        d[edge.from][edge.to] = std::min(d[edge.from][edge.to], edge.weight);
    }
    for (int i = 0; i < n; ++i) {
        d[i][i] = 0;
    }

    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (d[i][k] < INF && d[k][j] < INF)
                    d[i][j] = std::max(-INF, std::min(d[i][j], d[i][k] + d[k][j])); 
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int t = 0; t < n; ++t) {
                if (d[i][t] < INF && d[t][t] < 0 && d[t][j] < INF){
                    d[i][j] = - INF; 
                }
            }
        }
    }
}

int main(int argc, char const *argv[]) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int n, m, q;
    while (true) {
        std::cin >> n >> m >> q;
        if (n == 0) {
            break;
        }

        std::vector<Edge> graph;

        int u, v, w;
        for (int i = 0; i < m; ++i) {
            std::cin >> u >> v >> w;
            graph.push_back(Edge(u, v, w));
        }
        
        std::vector<std::vector<int>> dist;
        floydWarshall(graph, n, dist);

        for (int i = 0; i < q; ++i) {
            std::cin >> u >> v;
            int len = dist[u][v];
            if (len == INF) {
                std::cout << "Impossible\n";
            } else if (len == -INF){
                std::cout << "-Infinity\n";
            } else {
                std::cout << len << "\n";
            }
        }
        std::cout << "\n";
    }

    return 0;
}
