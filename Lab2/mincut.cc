/*
Author: Magnus Hjortswang, maghj433

Problem description: Calculate the minimal cut in a flow graph, such that the node are split into two distinct subsets 
U and V, where the sum of the capacities from U to V is minimal.

Time complexity: O(m*f) where m is the number of edges and f is the maximum flow. The minimum increase of flow between
iterations is 1, which means at most f iterations are needed (O(f)). In each iteration a breadth first search is used
to find a path which increases flow (O(m)). Once the maximum flow has been found we use a dfs to find all nodes
reachable from the start node (O(m)). Therefore the total time complexity is O(m*f + m) = O(m*f).

Usage: The maximum throughput of all edges must be positive.
*/

#include <iostream>
#include <vector>

#include <limits.h>
#include <string.h>
#include <queue>
#include <set>

int n;
const int INF = 1000000000;

std::vector<std::vector<int>> adj;

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

// Depth first search for identifying which nodes are reachable from the start node in the residual graph
void dfs(std::vector<std::vector<int>> &rGraph, int s, std::vector<bool> &visited)
{
    visited[s] = true;
    for (int i = 0; i < rGraph.size(); i++)
       if (rGraph[s][i] && !visited[i])
           dfs(rGraph, i, visited);
}

// Find the subset of nodes U which are connected to the start node after a minimal cut has been made
std::set<int> minCut(int s, int t, std::vector<std::vector<int>> &capacity) {
    std::vector<int> parent(n);
    int new_flow;

    // Calculate the maximum flow
    while (new_flow = bfs(s, t, parent, capacity)) {
        int cur = t;
        while (cur != s) {
            int prev = parent[cur];
            capacity[prev][cur] -= new_flow;
            capacity[cur][prev] += new_flow;
            cur = prev;
        }
    }


    // Flow is maximum now, find all vertices reachable from s in the residual graph.
    std::vector<bool> visited(n, false);
    dfs(capacity, s, visited);
 
    std::set<int> U;

    for (int i = 0; i < n; ++i) {
        if (visited[i]) {
            U.insert(i);
        }
    }
    
    return U;
}

int main(int argc, char const *argv[]) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int m, s, t;
    std::cin >> n >> m >> s >> t;

    std::vector<int> zeroRow(n, 0);
    std::vector<std::vector<int>> graph(n, zeroRow);
    adj.resize(n);
    
    int u, v, w;
    for (int i = 0; i < m; ++i) {
        std::cin >> u >> v >> w;
        graph[u][v] = w;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    std::set<int> U = minCut(s, t, graph);
    
    std::cout << U.size() << "\n";
    for (auto elem : U) {
        std::cout << elem << "\n";
    }

    return 0;
}
