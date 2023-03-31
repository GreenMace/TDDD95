#include <iostream>

unsigned long numZeros(long long m) {
    unsigned long tot = 0;
    unsigned int i = 1;

    while (true) {
        unsigned int b = (unsigned int) m / i;
        unsigned int c = m % i;
        unsigned int a = (unsigned int) b / 10;
        b = b % 10;

        if (a == 0) {
            return tot;
        }

        if (b == 0) {
            tot += (a - 1) * i + c + 1;
        } else {
            tot += a * i;
        }

        i *= 10;
    }
}

int main(int argc, char const *argv[]) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);
    
    long long m, n;
    while (std::cin >> m >> n) {
        if (m < 0) {
            break;
        }

        if (m == 0) {
            std::cout << numZeros(n) + 1 << "\n";
        } else {
            std::cout << numZeros(n) - numZeros(m-1) << "\n";
        }
    }
    
    return 0;
}
