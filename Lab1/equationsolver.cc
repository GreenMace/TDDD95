/*
Author: Magnus Hjortswang, maghj433

Problem description: Calculate the solution to a system of equation, or whether multiple or no solutions exist.

Time complexity: O(n^3) due to the tripple loop in the gauss function.

Usage: The right hand side vector b must be included as the final column in the matrix A for the gauss function. 
*/
#include <iostream>
#include <vector>
#include <stdlib.h>

const double EPS = 1e-9;
const int INF = 2;

// Calculate the unique solution to the equation system and stores it in the vector ans
// Returns 1 if a single solution exists, 2 if multiple exist, and 0 if no solution exists
int gauss(std::vector<std::vector<double>> A, std::vector<double> &ans) {
    int n = A.size();
    int m = A[0].size() - 1;


    // Gauss eliminate elements by finding pivot elements with the largest coefficients
    std::vector<int> where(m, -1);
    for (int col = 0, row = 0; col < m && row < n; ++col) {
        int sel = row;
        for (int i = row; i < n; ++i) {
            if (abs(A[i][col]) > abs(A[sel][col])) {
                sel = i;
            }
        }

        if (abs(A[sel][col]) < EPS) {
            continue;
        }

        for (int i = col; i <= m; ++i) {
            std::swap(A[sel][i], A[row][i]);
        }

        where[col] = row;

        for (int i = 0; i < n; ++i) {
            if (i != row) {
                double c = A[i][col] / A[row][col];
                for (int j = col; j <= m; j++) {
                    A[i][j] -= A[row][j] * c;
                }
            }
        }

        row++;
    }

    ans.assign(m, 0);
    for (int i = 0; i < m; ++i) {
        if (where[i] != -1) {
            ans[i] = A[where[i]][m] / A[where[i]][i];
        }
    }

    // Check whether the system is solved
    for (int i = 0; i < n; ++i) {
        double sum = 0;
        for (int j = 0; j < m; ++j) {
            sum += ans[j] * A[i][j];
        }

        if (abs(sum - A[i][m]) > EPS) {
            return 0;
        }
    }

    // Check wether multiple solutions exist
    for (int i = 0; i < m; ++i) {
        if (where[i] == -1) {
            return INF;
        }
    }
    
    return 1;
}

int main(int argc, char const *argv[]) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int n;
    while (std::cin >> n) {
        if (n == 0) {
            break;
        }

        std::vector<std::vector<double>> Ab(n);
        std::vector<double> ans;

        double input;
        for (int i = 0; i < n; ++i) {
            std::vector<double> row(n);
            for (int j = 0; j < n; ++j) {
                std::cin >> input;
                row[j] = input;
            }
            Ab[i] = row;
        }

        for (int i = 0; i < n; ++i) {
            std::cin >> input;
            Ab[i].push_back(input);
        }
        
        int solvable = gauss(Ab, ans);
        if (!solvable) {
            std::cout << "inconsistent\n";
        } else if (solvable == INF) {
            std::cout << "multiple\n";
        } else {
            for (auto elem : ans) {
                std::cout << elem << " ";
            }
            std::cout << "\n";
        }
        
    }

    return 0;
}