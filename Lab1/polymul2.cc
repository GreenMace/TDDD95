#include <iostream>
#include <vector>
#include <math.h>
#include <complex>

typedef std::complex<double> cd;

std::vector<cd> RecursiveFFT(std::vector<cd>& a) {
    int n = a.size();
    if (n == 1) {
        return std::vector<cd>(1, a[0]);
    }

    std::vector<cd> w(n);
    for (int i = 0; i < n; i++) {
        double alpha = -2 * M_PI * i / n;
        w[i] = cd(cos(alpha), sin(alpha));
    }

    std::vector<cd> A0(n/2), A1(n/2);
    for (int i = 0; i < n / 2; i++) {
        A0[i] = a[i*2];
        A1[i] = a[i*2+1];
    }

    std::vector<cd> y0 = RecursiveFFT(A0);
    std::vector<cd> y1 = RecursiveFFT(A1);

    std::vector<cd> y(n);
    for (int k = 0; k < n / 2; k++) {
        y[k] = y0[k] + w[k] * y1[k];
        y[k + n / 2] = y0[k] - w[k] * y1[k];
    }

    return y;
}

std::vector<cd> Multiply(std::vector<cd>& a, std::vector<cd>& b) {
    std::vector<cd> output;
    

    
    return output;
}

std::vector<cd> Interpolation(std::vector<cd>& a) {
    int n = a.size();
    if (n == 1) {
        return std::vector<cd>(1, a[0]);
    }

    std::vector<cd> wInv(n);
    for (int i = 0; i < n; i++) {
        // What is this supposed to be?...
        cd c = a[i];
        c.imag(-imag(c));
        wInv[i] = c;
    }

    std::vector<cd> A0(n/2), A1(n/2);
    for (int i = 0; i < n / 2; i++) {
        A0[i] = a[i*2];
        A1[i] = a[i*2+1];
    }

    std::vector<cd> y0 = Interpolation(A0);
    std::vector<cd> y1 = Interpolation(A1);

    std::vector<cd> y(n);
    for (int k = 0; k < n / 2; k++) {
        y[k] = y0[k] + wInv[k] * y1[k];
        y[k + n / 2] = y0[k] - wInv[k] * y1[k];
    }

    return y;
}

int main(int argc, char const *argv[]) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int T, n;
    std::cin >> T >> n;
    
    std::vector<cd> poly1;
    int coeff;
    for (int i = 0; i <= n; i++) {
        std::cin >> coeff;
        poly1.push_back(coeff);
    }
/*
    std::cin >> n;
    std::vector<cd> poly2;
    for (int i = 0; i <= n; i++) {
        std::cin >> coeff;
        poly2.push_back(coeff);
    }
*/
    std::vector<cd> polyResult = RecursiveFFT(poly1);

    std::cout << polyResult.size()-1 << "\n";
    for(auto& elem : polyResult) {
        std::cout << elem << " ";
    }
    std::cout << "\n";

    polyResult = Interpolation(polyResult);
    std::cout << polyResult.size()-1 << "\n";
    for(auto& elem : polyResult) {
        std::cout << elem << " ";
    }
    std::cout << "\n";

    return 0;
}
