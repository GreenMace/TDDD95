#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <utility>

int globalHeight;
std::pair<std::string, int> climb(std::vector<int> dists, int i, int height, int maxHeight, std::string s) {
    int elem = dists[i];
    if (i == dists.size() - 1) {
        if (height == elem) {
            globalHeight = std::min(globalHeight, maxHeight);
            return {s + "D", maxHeight};
        }
        return {"IMPOSSIBLE", maxHeight};
    }

    std::pair<std::string, int> res1 = {"IMPOSSIBLE", 0};
    std::pair<std::string, int> res2 = {"IMPOSSIBLE", 0};;
    if (height >= elem) {
        res1 = climb(dists, i+1, height - elem, maxHeight, s + "D");
    }

    if (height + elem <= globalHeight) {
        res2 = climb(dists, i+1, height + elem, std::max(maxHeight, height + elem), s + "U");
        if (res1.first == "IMPOSSIBLE" || (res1.second > res2.second && res2.first != "IMPOSSIBLE")) {
            return res2;
        }
    }

    return res1;
}

int main(int argc, char const *argv[]) {
    int N;
    std::cin >> N;

    int M;
    for (int i = 0; i < N; i++) {
        std::vector<int> distances;
        std::cin >> M;
        
        int d;
        for(int j = 0; j < M; j++) {
            std::cin >> d;
            distances.push_back(d);
        }

        int totDist = std::reduce(distances.begin(), distances.end());
        if (totDist % 2 || *std::max_element(distances.begin(), distances.end()) > totDist/2) {
            std::cout << "IMPOSSIBLE" << "\n";
            continue;
        }

        globalHeight = totDist/2;
        std::pair<std::string, int> schedule = climb(distances, 1, distances[0], distances[0], "U");
        std::cout << schedule.first << "\n";
    }

    return 0;
}
