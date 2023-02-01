#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>

std::vector<int> parent;
std::vector<int> size;
 
void make_set(int v) {
    parent.push_back(v);
    size.push_back(1);
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
