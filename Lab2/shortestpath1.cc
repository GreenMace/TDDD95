/*
Author: Magnus Hjortswang, maghj433

Problem description: Calculate the shortest path between two nodes in a graph, if such a path exists.

Time complexity: O(m*log(n)) where n is the number of nodes and m is the number of edges. We utilize
a set which sorts the nodes on the current distance to them from the start node. Extracting, inserting and removing 
items takes log(n) time. We visit each node at most once, so we need n extractions and m updates, which gives us 
O(n*log(n) + m*log(n)) = O(m*log(n)) since m > n and we only update along edges.


Usage: Assumes no negative edges exist. 
*/

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <set>


// Node class which stores a vector of edges with weights and destinations
class Node {
public:
    Node(){

    };

    void addEdge(int n, int w) {
        edges.push_back({n, w});
    }

    std::vector<std::pair<int, int>> edges;
};

const int INF = 1000000000;


// Calculate the shortest distance to all nodes from the node start. Assumes no all weights > 0
void dijkstras(std::vector<Node> graph, int start, std::vector<int> & currLength, std::vector<int> & parent) {
    int n = graph.size();

    parent.assign(n, -1);
    currLength.assign(n, INF);
    currLength[start] = 0;
    
    std::set<std::pair<int, int>> q;
    q.insert({0, start});

    // Update the distance to all nodes until no updates are possible
    while (!q.empty()) {
        int v = q.begin() -> second;
        q.erase(q.begin());

        for (auto edge : graph[v].edges) {
            int to = edge.first;
            int len = edge.second;

            // Update the distance to destination node
            if (currLength[v] + len < currLength[to]) {
                q.erase({currLength[to], to});
                currLength[to] = currLength[v] + len;
                parent[to] = v;
                q.insert({currLength[to], to});
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

        std::vector<Node> graph(n, Node());

        int u, v, w;
        for (int i = 0; i < m; ++i) {
            std::cin >> u >> v >> w;
            graph[u].addEdge(v, w);
        }
        
        std::vector<int> parent;
        std::vector<int> dist;
        dijkstras(graph, s, dist, parent);

        int t;
        for (int i = 0; i < q; ++i) {
            std::cin >> t;
            int len = dist[t];
            if (len == INF) {
                std::cout << "Impossible\n";
            } else {
                std::cout << len << "\n";
            }
        }
    }

    return 0;
}
