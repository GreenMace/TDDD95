/*
Author: Magnus Hjortswang, maghj433

Problem description: Construct the minimum spanning tree for a given graph.

Time complexity: O(m*log(m)) where n is the number of nodes and m is the number of edges. Using a DSU tree structure we 
create n separate trees (O(n)) and sort the edges in ascending order (O(m*log(m)). We then iterate through all edges and 
determine if the ends of each set belong to the same tree (close to O(1)). We then union the trees if they belonged to 
different sets (also close to  O(1)). This gives us the complexity O(m*log(m) + N + M) = O(m*log(m))

Usage: Does not calculate the weight of the constructed tree.
*/


#include <iostream>
#include <vector>
#include <utility>
#include <math.h>
#include <algorithm>

// Class that handles all disjoint set union operations.
class TreeDSU {
public:
    TreeDSU(int n) {
        parent.resize(n);
        rank.assign(n, 0);
    };

    // Initialize trees
    void make_set(int v) {
        parent[v] = v;
    }

    // Find the root of the tree which contains node v
    int find_set(int v) {
        if (v == parent[v]) {
            return v;
        }

        return parent[v] = find_set(parent[v]);
    }

    // Union two trees such that they share the same root node
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

// Class which stores the information for a given edge (i.e which nodes it connects and the weight)
class Edge {
public:
    Edge(int n1, int n2, double w) {
        u = n1;
        v = n2;
        weight = w;
    }

    // Comparison operator for sorting in ascending order of weight
    bool operator<(Edge const& other) {
        return weight < other.weight;
    }

    int u, v;
    double weight;
};

// Construct the minimum spanning tree using kruskal's algorithm. 
// Uses DSU trees for checking if two nodes are connected, and to connect nodes.
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
