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
#include <utility>
#include <math.h>
#include <algorithm>

class TreeDSU {
public:
    TreeDSU(int n) {
        parent.resize(n);
        rank.assign(n, 0);
    };

    void make_set(int v) {
        parent[v] = v;
    }

    int find_set(int v) {
        if (v == parent[v]) {
            return v;
        }

        return parent[v] = find_set(parent[v]);
    }

    void union_sets(int a, int b) {
        a = find_set(a);
        b = find_set(b);
        if (a != b) {
            if (rank[a] < rank[b]) {
                std::swap(a, b);
            }
                
            parent[b] = a;
            if (rank[a] == rank[b]) {
                rank[a]++;
            }
        }
    }

private:
    std::vector<int> parent;
    std::vector<int> rank;

};

class Edge {
public:
    Edge(int n1, int n2, double w) {
        u = n1;
        v = n2;
        weight = w;
    }

    bool operator<(Edge const& other) {
        return weight < other.weight;
    }

    int u, v;
    double weight;
};

std::vector<Edge> kruskal(std::vector<Edge> edges, int n) {
    std::vector<Edge> minTree;
    TreeDSU tree(n);
    for (int i = 0; i < n; ++i) {
        tree.make_set(i);
    }

    sort(edges.begin(), edges.end());

    for (Edge e : edges) {
        if (tree.find_set(e.u) != tree.find_set(e.v)) {
            minTree.push_back(e);
            tree.union_sets(e.u, e.v);
        }
    }

    return minTree;
}

int main(int argc, char const *argv[]) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);
    
    int n, m;
    while (true) {
        std::cin >> n >> m;
        if (n == 0) {
            break;
        }

        std::vector<Edge> edges;

        int u, v, w;
        for (int j = 0; j < m; ++j) {
            std::cin >> u >> v >> w;

            if (u < v) {
                edges.push_back(Edge(u, v, w));
            } else {
                edges.push_back(Edge(v, u, w));
            }
            
            
        }
        std::vector<Edge> minTree = kruskal(edges, n);
        if (minTree.size() == n - 1) {
            sort(minTree.begin(), minTree.end(), [](Edge const&a, Edge const&b){
                if (a.u == b.u) {
                    return a.v < b.v;
                }
                return a.u < b.u;
            });

            int len = 0;
            for (Edge e : minTree) {
                len += e.weight;
            }
            std::cout << len << "\n";

            for (Edge e : minTree) {
                std::cout << e.u << " " << e.v << "\n";
            }
            
        } else {
            std::cout << "Impossible\n";
        }
        
        
    }
    return 0;
}
