#include <iostream>
#include <unordered_map>
#include <math.h>
#include <algorithm>
#include <numeric>

void factorize(long n, std::unordered_map<long, long> &factors) {
    n = abs(n);
    int top = sqrt(n);
    long i = 2;
    while (i <= top) {
        if (n%i == 0) {
            n /= i;
            factors[i]++;
            top = sqrt(n);
        } else {
            i++;
        }
    }
    factors[n]++;
}

long greatestCommonDivisor(long n, std::unordered_map<long, long> &factors) {
    long greatestCommon = 0;

    for (auto elem : factors) {
        if (!greatestCommon) {
            greatestCommon = elem.second;
        } else {
            greatestCommon = std::gcd(greatestCommon, elem.second);
        }
    }

    if (n < 0) {
        while (!(greatestCommon % 2)) {
            greatestCommon /= 2;
        }
    }
    return greatestCommon;
}

int main(int argc, char const *argv[]) {
    long x;
    while (std::cin >> x) {
        if (x == 0) {
            break;
        }            
        std::unordered_map<long, long> factors;
        
        factorize(x, factors);
        long pthPower = greatestCommonDivisor(x, factors);
        

        std::cout << pthPower << "\n";

    }

    return 0;
}