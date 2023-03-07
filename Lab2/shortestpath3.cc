#include <iostream>
#include <vector>
#include <math.h>
#include <set>
#include <algorithm>

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

void floydWarshall(std::vector<Edge> graph, int n, int start, std::vector<int> &d, std::vector<int> &p) {
    int m = graph.size();
    d.assign(n, INF);
    d[start] = 0;
    p.assign(n, -1);

    std::set<int> negatives;
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

    
    for (Edge e : graph) {
        if (d[e.from] < INF) {
            if (d[e.to] > d[e.from] + e.weight) {
                d[e.to] = std::max(-INF, d[e.from] + e.weight);
                p[e.to] = e.from;
                negatives.insert(e.to);
            }
        }
    }

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
        floydWarshall(graph, n, s, dist, parent);

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
