#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <iomanip>

int main(int argc, char const *argv[]) {
    std::cout << std::setprecision(7);

    int N, L, W;
    std::cin >> N >> L >> W;
    float spacing = 2*L /(N-2);
    std::cout << spacing<< "\n";
    int p;
    std::vector<int> origPositions;
    for (int i = 0; i < N; i++) {
        std::cin >> p;
        origPositions.push_back(p);
    }
    std::sort(origPositions.begin(), origPositions.end());

    float sum = 0;
    float roadPos = 0;
    for (int i = 0; i < origPositions.size(); i += 2) {
        int t1 = origPositions[i];
        int t2 = origPositions[i + 1];
        sum += abs(t1 - roadPos);
        sum += sqrt((t2 - roadPos) * (t2 - roadPos) + W*W);
        roadPos += spacing;
    }

    std::cout << sum << "\n";
    

    return 0;
}
