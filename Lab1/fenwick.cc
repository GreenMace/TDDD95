#include <iostream>
#include <vector>
#include <sstream>

class FenwickTree {
public:
    FenwickTree(int n) {
        N = n;
        T.assign(n, 0);
    }

    long long sum(int r) {
        long long res = 0;
        while (r >= 0) {
            res += T[r];
            r = g(r) - 1;
        }
        return res;
    }

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
