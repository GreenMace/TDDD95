/*
Author: Magnus Hjortswang, maghj433

Problem description: Determine wether two sets are joined, given all previous join operations recieved as input.

Time complexity: O(log(n)) for both the union and same operations, since we flatten the tree structure each time a node
at depth larger than 1 is accessed.

Usage: Assumes all sets are referenced by positive integers. 
*/

#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>

std::vector<int> parent;
std::vector<int> size;

// Initiate the vectors parents and size
void make_set(int v) {
    parent.push_back(v);
    size.push_back(1);
}

// Find the root node of a node
int find_set(int v) {
    if (v == parent[v]) {
        return v;
    }
    return parent[v] = find_set(parent[v]);
}

// Join two sets of trees by setting the root of one as the parent of the other
void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        if (size[a] < size[b]) {
            std::swap(a, b);
        }
        parent[b] = a;
        size[a] += size[b];
    }
}

int main(int argc, char const *argv[]) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int N, Q;
    std::cin >> N >> Q;

    for (int i = 0; i < N; i++) {
        make_set(i);
    }

    std::ostringstream output;
    std::string op;
    int a, b;
    for (int i = 0; i < Q; i++) {
        getline(std::cin, op, ' ');
        std::cin >> a >> b;
        if (op[1] == '?') {
            // Check wether two sets are joined by checking if they have the same root node
            if (find_set(a) == find_set(b)) {
                output << "yes" << "\n";
            } else {
                output << "no" << "\n";
            }
        } else {
            union_sets(a, b);
        }
    }

    std::cout << output.str() << "\n";
    return 0;
}