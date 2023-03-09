/*
Author: Magnus Hjortswang, maghj433

Problem description: Calculate the shortest path between two nodes in a graph which might contain negative cycles,
or indicate that no path exists if there is no path between the nodes.

Time complexity: O(n*m) where n is the number of nodes and m the number of edges in the graph, due to the
nested loops in the bellmanFord algorithm.

Usage: Assumes all weights are integers. 
*/

#include <iostream>
#include <vector>
#include <math.h>
#include <set>
#include <algorithm>

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


// Calculate the shortest path from a given start node to every other node in the graph
void bellmanFord(std::vector<Edge> graph, int n, int start, std::vector<int> &d, std::vector<int> &p) {
    int m = graph.size();
    d.assign(n, INF);
    d[start] = 0;
    p.assign(n, -1);

    std::set<int> negatives;
    
    // Update the distance to all nodes n-1 times, storing which nodes achieve a distance of -INF
    // i.e, are affected by a negative cycle
    for (int i=0; i<n-1; ++i) {
        for (Edge e : graph) {
            if (d[e.from] < INF) {
                if (d[e.to] > d[e.from] + e.weight) {
                    d[e.to] = std::max(-INF, d[e.from] + e.weight);
                    if (d[e.to] == -INF) {
                        negatives.insert(e.to);
                    }
                    p[e.to] = e.from;
                }
            }
        }
    }

    // If any node is affected by an additional update iteration, that node is also affected by
    // a negative cycle
    for (Edge e : graph) {
        if (d[e.from] < INF) {
            if (d[e.to] > d[e.from] + e.weight) {
                d[e.to] = std::max(-INF, d[e.from] + e.weight);
                p[e.to] = e.from;
                negatives.insert(e.to);
            }
        }
    }

    // Update the distance to all nodes that are reachable from negative cycles to be -INF
    while (!negatives.empty()) {
        int node = *(negatives.begin());
        negatives.erase(node);
        d[node] = -INF;

        for (Edge e : graph) {
            if (e.from == node && d[e.to] != -INF) {
                d[e.to] = -INF;
                negatives.insert(e.to);
            }
        }
    }

}

// Reconstruct the shortest path between the start node and a given end node, if one exists
std::vector<int> restorePath(int start, int end, std::vector<int> const& parent) {
    std::vector<int> path;

    for (int v = end; v != start; v = parent[v]) {
        path.push_back(v);
    }
    path.push_back(start);

    reverse(path.begin(), path.end());

    return path;
}

int main(int argc, char const *argv[]) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int n, m, q, s;
    while (true) {
        std::cin >> n >> m >> q >> s;
        if (n == 0) {
            break;
        }

        std::vector<Edge> graph;

        int u, v, w;
        for (int i = 0; i < m; ++i) {
            std::cin >> u >> v >> w;
            graph.push_back(Edge(u, v, w));
        }
        
        std::vector<int> dist;
        std::vector<int> parent;
        bellmanFord(graph, n, s, dist, parent);

        int t;
        for (int i = 0; i < q; ++i) {
            std::cin >> t;
            int len = dist[t];
            if (len == INF) {
                std::cout << "Impossible\n";
            } else if (len == -INF){
                std::cout << "-Infinity\n";
            } else {
                std::cout << len << "\n";
            }
        }
    }

    return 0;
}
