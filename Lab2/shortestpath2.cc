/*
Author: Magnus Hjortswang, maghj433

Problem description: Calculate the shortest path between two nodes in a graph where some edges are only available
periodically, if such a path exists.

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

const int INF = 1000000000;


// Class which stores all information about a given edge (where it leads to, its weight
// and the time intervals where it is available)
class Edge {
public:
    Edge(int n, int w, int t, int p) {
        to = n;
        weight = w;
        t0 = t;
        P = p;
    }


    // Calculate how much time is left until the edge can be used again
    int timeToNextCross(int t) {
        if (t <= t0) {
            return t0-t;
        } else if(P == 0) {
            return INF;
        }
        if ((t-t0) % P) {
            return P - (t-t0) % P;
        }
        return 0;
    }

    int to;
    int weight;
    int t0;
    int P;
};

// Class which stores the edges which lead from a given node
class Node {
public:
    Node(){};

    void addEdge(int n, int w, int t0, int P) {
        edges.push_back(Edge(n, w, t0, P));
    }

    std::vector<Edge> edges;
};


// Calculate the minimum time needed to reach all reachable nodes in the graph from a given start node
// where some edges might only be used periodically
void dijkstrasWithTime(std::vector<Node> graph, int start, std::vector<int> & currLength, std::vector<int> & parent) {
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
            int to = edge.to;
            int len = edge.weight;
            int waitTime = edge.timeToNextCross(currLength[v]);

            // Update the distance to destination node
            if (currLength[v] + len + waitTime < currLength[to]) {
                q.erase({currLength[to], to});
                currLength[to] = currLength[v] + len + waitTime;
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

        int u, v, t0, P, w;
        for (int i = 0; i < m; ++i) {
            std::cin >> u >> v >> t0 >> P >> w;
            graph[u].addEdge(v, w, t0, P);
        }
        
        std::vector<int> parent;
        std::vector<int> dist;
        dijkstrasWithTime(graph, s, dist, parent);

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
