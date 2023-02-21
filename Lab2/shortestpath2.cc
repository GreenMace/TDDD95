#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <set>

const int INF = 1000000000;

class Edge {
public:
    Edge(int n, int w, int t, int p) {
        to = n;
        weight = w;
        t0 = t;
        P = p;
    }

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

class Node {
public:
    Node(){};

    void addEdge(int n, int w, int t0, int P) {
        edges.push_back(Edge(n, w, t0, P));
    }

    std::vector<Edge> edges;
};

void dijkstrasWithTime(std::vector<Node> graph, int start, std::vector<int> & currLength, std::vector<int> & parent) {
    int n = graph.size();

    parent.assign(n, -1);
    currLength.assign(n, INF);
    currLength[start] = 0;
    
    std::set<std::pair<int, int>> q;
    q.insert({0, start});
    while (!q.empty()) {
        int v = q.begin() -> second;
        q.erase(q.begin());

        for (auto edge : graph[v].edges) {
            int to = edge.to;
            int len = edge.weight;
            int waitTime = edge.timeToNextCross(currLength[v]);

            if (currLength[v] + len + waitTime < currLength[to]) {
                q.erase({currLength[to], to});
                currLength[to] = currLength[v] + len + waitTime;
                parent[to] = v;
                q.insert({currLength[to], to});
            }
        }
    }
}

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
