/*
Author: Magnus Hjortswang, maghj433

Problem description: Calculate the sum of all elements in an array up to index i, exclusive.

Time complexity: O(log(n)) for both the increase and sum operations, because of the use of a fenwick tree structure.

Usage: Only handles integers, no decimals. 
*/

#include <iostream>
#include <vector>
#include <sstream>

class FenwickTree {
public:    
    FenwickTree(int n) {
        N = n;
        T.assign(n, 0);
    }

    // Calculates the sum of all values in the array up to index r
    long long sum(int r) {
        long long res = 0;
        while (r >= 0) {
            res += T[r];
            // The next element to add is determined by g
            r = g(r) - 1;
        }
        return res;
    }

    // Add delta to all elements in the tree which have array element i as a descendent
    void increase(int i, int delta) {
        for (int j = i; j < N; j = h(j)) {
            T[j] += delta;
        }
    }

    int g(int i) {
        return i & (i + 1);
    }

    int h(int i) {
        return i | (i + 1);
    }

    std::vector<long long> T;
    int N;
};

int main(int argc, char const *argv[]) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int N, Q;
    std::cin >> N >> Q;
    FenwickTree FT = FenwickTree(N);
    
    std::ostringstream output;
    std::string op;
    for (int j = 0; j < Q; j++) {
        std::getline(std::cin, op, ' ');

        if (op[1] == '?')
        {
            int i;
            std::cin >> i;

            output << FT.sum(i-1) << "\n";
        } else {
            int i, delta;
            std::cin >> i >> delta;
            FT.increase(i, delta);
        }
        
    }
    std::cout << output.str();
    
    return 0;
}
