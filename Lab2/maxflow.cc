/*
Author: Magnus Hjortswang, maghj433

Problem description: Calculate the maximum flow through a graph where the directed edges each have a maximum throughput.

Time complexity: O(m*f) where m is the number of edges and f is the maximum flow. The minimum increase of flow between
iterations is 1, which means at most f iterations are needed (O(f)). In each iteration a breadth first search is used
to find a path which increases flow (O(m)). This means the total time complexity is O(m*f).

Usage: The maximum throughput of all edges must be positive.
*/

#include <iostream>
#include <vector>
#include <queue>
#include <utility>

int n;
const int INF = 1000000000;

std::vector<std::vector<int>> adj;
std::vector<std::vector<int>> fl;

// Breadth first search for finding a path, from the start node to the terminal node, which can increase the flow
int bfs(int s, int t, std::vector<int>& parent, std::vector<std::vector<int>> &capacity) {
    // parent stores the path so that it can be reconstructed
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;

    std::queue<std::pair<int, int>> q;
    q.push({s, INF});

    while (!q.empty()) {
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int next : adj[cur]) {
            if (parent[next] == -1 && capacity[cur][next]) {
                parent[next] = cur;
                int new_flow = std::min(flow, capacity[cur][next]);
                if (next == t)
                    return new_flow;
                q.push({next, new_flow});
            }
        }
    }

    return 0;
}

// Calculate the maximum flow from the start node to the terminal node. The maximum flow is returned, and the flow
// through each edge is stored in the matrix fl.
int maxflow(int s, int t, std::vector<std::vector<int>> &capacity) {
    int flow = 0;
    std::vector<int> parent(n);
    int new_flow;

    // Iterate untill flow cannot increase
    while (new_flow = bfs(s, t, parent, capacity)) {
        flow += new_flow;
        int cur = t;
        while (cur != s) {
            int prev = parent[cur];
            capacity[prev][cur] -= new_flow;
            capacity[cur][prev] += new_flow;
            fl[prev][cur] = std::max(0, fl[prev][cur] + new_flow - fl[cur][prev]);
            fl[cur][prev] = std::max(0, fl[cur][prev] - new_flow);
            cur = prev;
        }
    }

    return flow;
}

class Edge {
public:
    Edge(int u, int v, int f) {
        from = u;
        to = v;
        flow = f;
    }

    int from;
    int to;
    int flow;
};

int main(int argc, char const *argv[]) {
    int m, s, t;
    std::cin >> n >> m >> s >> t;

    std::vector<int> zeroRow(n, 0);
    std::vector<std::vector<int>> capacity(n, zeroRow);
    adj.resize(n);
    fl.assign(n, zeroRow);

    int u, v, c;
    for (int i = 0; i < m; ++i) {
        std::cin >> u >> v >> c;
        capacity[u][v] = c;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int f = maxflow(s, t, capacity);

    std::vector<Edge> edges;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (fl[i][j] > 0) {
                edges.push_back(Edge(i, j, fl[i][j]));
            }
        }
    }

    std::cout << n << " " << f << " " << edges.size() << "\n";

    for (auto edge : edges) {
        std::cout << edge.from << " " << edge.to << " " << edge.flow << "\n";
    }
}
