#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

void addUnvisited(std::vector<std::pair<int, int>> &visited, std::vector<std::pair<int, int>> &toVisit, std::pair<int, int> newPos) {
    if (std::find(visited.begin(), visited.end(), newPos) == visited.end() && std::find(toVisit.begin(), toVisit.end(), newPos) == toVisit.end()) {
        toVisit.push_back(newPos);
    }
}

int safeGold(std::vector<std::vector<char>> map) {
    int totGold = 0;

    std::vector<std::pair<int, int>> visited;
    std::vector<std::pair<int, int>> toVisit;

    std::pair<int, int> currPos;
    for (int i = 0; i < map.size(); ++i) {
        auto it = std::find(map[i].begin(), map[i].end(), 'P');
        if (it != map[i].end()) {
            currPos = {i, it-map[i].begin()};
            break;
        }
    }

    toVisit.push_back(currPos);
    while (!toVisit.empty()) {
        currPos = toVisit.back();
        visited.push_back(currPos);
        toVisit.pop_back();
        char c = map[currPos.first][currPos.second];
        if (c == 'G') {
            totGold++;
        }
        
        if (c != '#') {
            char left = map[currPos.first-1][currPos.second];
            char right = map[currPos.first+1][currPos.second];
            char up = map[currPos.first][currPos.second-1];
            char down = map[currPos.first][currPos.second+1];
            bool safe = (left != 'T' && right != 'T' && up != 'T' && down != 'T');
            
            if (safe) {
                addUnvisited(visited, toVisit, {currPos.first-1, currPos.second});
                addUnvisited(visited, toVisit, {currPos.first+1, currPos.second});
                addUnvisited(visited, toVisit, {currPos.first, currPos.second-1});
                addUnvisited(visited, toVisit, {currPos.first, currPos.second+1});
            }
        }
    }

    return totGold;
}

int main(int argc, char const *argv[]) {
    int W, H;
    std::cin >> W >> H;
    std::vector<std::vector<char>> map(H);
    std::vector<char> row(W);
    for (int h = 0; h < H; ++h) {
        for (int w = 0; w < W; ++w) {
            std::cin >> row[w];
        }
        map[h] = row;
    }

    std::cout << safeGold(map) << "\n";

    return 0;
}
