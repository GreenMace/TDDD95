#include <iostream>
#include <vector>
#include <stdlib.h>

const double EPS = 1e-9;

int gauss(std::vector<std::vector<double>> &A, std::vector<double> &ans, std::vector<int> &where) {
    int n = A.size();
    int m = A[0].size() - 1;

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

    for (int i = 0; i < n; ++i) {
        double sum = 0;
        for (int j = 0; j < m; ++j) {
            sum += ans[j] * A[i][j];
        }

        if (abs(sum - A[i][m]) > EPS) {
            return 0;
        }
    }
    
    return 1;
}

int main(int argc, char const *argv[]) {
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
        
        std::vector<int> where(n, -1);
        int solvable = gauss(Ab, ans, where);
        if (!solvable) {
            std::cout << "inconsistent\n";
        } else {
            for (int i = 0; i < n; ++i) {
                bool determined = true;
                for (int j = 0; j < n; ++j) {
                    if (abs(Ab[i][j]) > EPS && where[j] == -1) {
                        determined = false;
                        break;
                    }
                }
                if (determined && where[i] != -1) {
                    std::cout << ans[i] << " ";
                } else {
                    std::cout << "? ";
                }
            }
            std::cout << "\n";
        }
        
    }

    return 0;
}