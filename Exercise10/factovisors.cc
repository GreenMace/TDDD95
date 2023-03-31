#include <iostream>
#include <map>
#include <math.h>

void factorize(long n, std::map<long, long> &factors) {
    int top = sqrt(n);
    long i = 2;
    while (i <= top) {
        if (n%i == 0) {
            n /= i;
            ++factors[i];
            top = sqrt(n);
        } else {
            ++i;
        }
    }
    ++factors[n];
}

bool divFactorial(long n, std::map<long, long> &factors) {
    for (auto f : factors) {
        long exp = 0;
        for (long i = f.first; i <= n; i = i*f.first) {
            exp += floor(n / i);
        }

        if (exp < f.second) {
            return false;
        }
    }

    return true;
}

int main(int argc, char const *argv[]) {
    //std::ios::sync_with_stdio(false);
    //std::cin.tie(NULL);
    //std::cout.tie(NULL);

    long n, m;
    while (std::cin >> n >> m) {
        if (m == 0) {
            std::cout << m << " does not divide " << n << "!\n";
            continue;
        }

        std::map<long, long> factorsM;
        factorize(m, factorsM);
        factorsM.erase(1);

        if (divFactorial(n, factorsM)) {
            std::cout << m << " divides " << n << "!\n";
        } else {
            std::cout << m << " does not divide " << n << "!\n";
        }
        
    }

    return 0;
}
