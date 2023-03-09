/*
Author: Magnus Hjortswang, maghj433

Problem description: Calculate the shortest path between all pairs of nodes in a graph which might include negative
cycles, if such a path exists.

Time complexity: O(n^3) where n is the number of nodes, due to the 3 nested loops in the Floyd Warshall algorithm,
which all iterate over all nodes.

Usage: Assumes all weights are integers.
*/

#include <iostream>
#include <vector>
#include <math.h>
#include <set>

// Class which stores the information for a given edge (i.e which nodes it connects and the weight)
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

// Calculate the shortest distance between all pairs of nodes and store them in the matrix d
void floydWarshall(std::vector<Edge> graph, int n, std::vector<std::vector<int>> &d) {
    std::vector<int> row(n, INF);
    d.assign(n, row);

    // Initially, the distance between nodes which share atleast one edge is the smallest weight
    // among all those edges
    for (auto edge : graph) {
        d[edge.from][edge.to] = std::min(d[edge.from][edge.to], edge.weight);
    }
    // Nodes are at distance 0 from themselves
    for (int i = 0; i < n; ++i) {
        d[i][i] = 0;
    }

    // Update the distance of all nodes to all other nodes along a path which includes a third node
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (d[i][k] < INF && d[k][j] < INF)
                    d[i][j] = std::max(-INF, std::min(d[i][j], d[i][k] + d[k][j])); 
            }
        }
    }

    // If any additional update occours to a path, then that path is affected by a negative cycle
    // and has a distance of -INF
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
