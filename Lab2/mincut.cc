#include <iostream>
#include <vector>

#include <limits.h>
#include <string.h>
#include <queue>
#include <set>

int n;
const int INF = 1000000000;

std::vector<std::vector<int>> adj;

int bfs(int s, int t, std::vector<int>& parent, std::vector<std::vector<int>> &capacity) {
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

void dfs(std::vector<std::vector<int>> &rGraph, int s, std::vector<bool> &visited)
{
    visited[s] = true;
    for (int i = 0; i < rGraph.size(); i++)
       if (rGraph[s][i] && !visited[i])
           dfs(rGraph, i, visited);
}
 
std::set<int> minCut(int s, int t, std::vector<std::vector<int>> &capacity) {
    std::vector<int> parent(n);
    int new_flow;

    while (new_flow = bfs(s, t, parent, capacity)) {
        int cur = t;
        while (cur != s) {
            int prev = parent[cur];
            capacity[prev][cur] -= new_flow;
            capacity[cur][prev] += new_flow;
            cur = prev;
        }
    }


    // Flow is maximum now, find vertices reachable from s
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
