/*
Author: Magnus Hjortswang, maghj433

Problem description: Determine the coefficients of the product of two polynomials.

Time complexity: O(n*log(n)), since the FFT is calculated recursively while applying divide and conquer.

Usage: Only works for polynomials with small or few coefficients (around 10^5). 
*/
#include <iostream>
#include <vector>
#include <math.h>
#include <complex>
#include <algorithm>

typedef std::complex<double> cd;

// Calculates the DFT (or invers DFT) of a polynomial
void FFT(std::vector<cd>& a, bool invert) {
    int n = a.size();
    if (n == 1) {
        return;
    }

    std::vector<cd> A0(n/2), A1(n/2);
    for (int i = 0; i < n / 2; i++) {
        A0[i] = a[i*2];
        A1[i] = a[i*2+1];
    }

    FFT(A0, invert);
    FFT(A1, invert);

    double alpha = 2 * M_PI / n * (invert ? -1 : 1);
    cd w(1), wn(cos(alpha), sin(alpha));

    for (int i = 0; i < n / 2; i++) {
        a[i] = A0[i] + w * A1[i];
        a[i + n / 2] = A0[i] - w * A1[i];
        if (invert) {
            a[i] /= 2;
            a[i + n / 2] /= 2;
        }
        w *= wn;
    }
}

// Multiply two polynomials by calculating their DFT, multiplying them elementwise, and then using
// the inverse DFT.
std::vector<int> Multiply(std::vector<int> const& a, std::vector<int> const& b) {
    std::vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < a.size() + b.size()) {
        n <<= 1;
    }
    fa.resize(n);
    fb.resize(n);

    FFT(fa, false);
    FFT(fb, false);

    for (int i = 0; i < n; i++) {
        fa[i] *= fb[i];
    }

    FFT(fa, true);

    std::vector<int> result(n);
    for (int i = 0; i < n; i++) {
        result[i] = round(fa[i].real());
    }

    return result;
}

int main(int argc, char const *argv[]) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int T, n1;
    std::cin >> T >> n1;
    
    std::vector<int> poly1;
    int coeff;
    for (int i = 0; i <= n1; i++) {
        std::cin >> coeff;
        poly1.push_back(coeff);
    }

    if (!(n1%2)) {
        poly1.push_back(0);
        n1 += 1;
    }

    int n2;
    std::cin >> n2;
    std::vector<int> poly2;
    for (int i = 0; i <= n2; i++) {
        std::cin >> coeff;
        poly2.push_back(coeff);
    }

    if (n1 > n2) {
        for (int i = 0; i < n1 - n2; i++) {
            poly2.push_back(0);
        }
    } else if (n2 > n1) {
        for (int i = 0; i < n2 - n1; i++) {
            poly1.push_back(0);
        }
    }

    int inc = poly1.size();
    for (int i = 0; i < inc; i++) {
        poly1.push_back(0);
        poly2.push_back(0);
    }

    std::vector<int> polyResult = Multiply(poly1, poly2);

    auto rit = std::find_if(polyResult.rbegin(), polyResult.rend(), 
                        [](int v) { return v != 0; });

    polyResult.erase(rit.base(), end(polyResult));

    std::cout << polyResult.size()-1 << "\n";
    for(auto& elem : polyResult) {
        std::cout << elem << " ";
    }
    std::cout << "\n";

    return 0;
}