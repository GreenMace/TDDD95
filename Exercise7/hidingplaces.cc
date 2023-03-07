#include <iostream>
#include <vector>
#include <unordered_map>
#include <utility>
#include <algorithm>
#include <deque>
#include <string>

std::vector<std::pair<int, int>> possibleMoves(std::pair<int, int> pos) {
    std::vector<std::pair<int, int>> positions;

    std::pair<int, int> newPos;
    newPos = {pos.first-2, pos.second-1};
    if (newPos.first >= 0 && newPos.second >= 0 && newPos.first < 8 && newPos.second < 8) {
        positions.push_back(newPos);
    }

    newPos = {pos.first-2, pos.second+1};
    if (newPos.first >= 0 && newPos.second >= 0 && newPos.first < 8 && newPos.second < 8) {
        positions.push_back(newPos);
    }

    newPos = {pos.first+2, pos.second-1};
    if (newPos.first >= 0 && newPos.second >= 0 && newPos.first < 8 && newPos.second < 8) {
        positions.push_back(newPos);
    }

    newPos = {pos.first+2, pos.second+1};
    if (newPos.first >= 0 && newPos.second >= 0 && newPos.first < 8 && newPos.second < 8) {
        positions.push_back(newPos);
    }

    newPos = {pos.first-1, pos.second-2};
    if (newPos.first >= 0 && newPos.second >= 0 && newPos.first < 8 && newPos.second < 8) {
        positions.push_back(newPos);
    }

    newPos = {pos.first-1, pos.second+2};
    if (newPos.first >= 0 && newPos.second >= 0 && newPos.first < 8 && newPos.second < 8) {
        positions.push_back(newPos);
    }

    newPos = {pos.first+1, pos.second-2};
    if (newPos.first >= 0 && newPos.second >= 0 && newPos.first < 8 && newPos.second < 8) {
        positions.push_back(newPos);
    }

    newPos = {pos.first+1, pos.second+2};
    if (newPos.first >= 0 && newPos.second >= 0 && newPos.first < 8 && newPos.second < 8) {
        positions.push_back(newPos);
    }

    return positions;
}

std::vector<std::string> hideHorse(std::string start, int &maxMoves) {
    int boardSize = 8;
    std::unordered_map<char, int> coordToIndex = {{'a', 0}, {'b', 1}, {'c', 2}, {'d', 3}, {'e', 4}, {'f', 5}, {'g', 6}, {'h', 7}};
    std::unordered_map<int, char> indexToCoord;
    for(auto const& x: coordToIndex) {
        indexToCoord[x.second] = x.first;
    }
    

    std::vector<int> row(boardSize, boardSize * boardSize);
    std::vector<std::vector<int>> board(boardSize);
    for (int i = 0; i < boardSize; ++i) {
        board[i] = row;    
    }

    
    std::pair<int, int> pos = {coordToIndex[start[0]], start[1] - '1'};
    board[pos.first][pos.second] = 0;

    std::deque<std::pair<int, int>> toTest = {pos};
    while(!toTest.empty()) {
        std::pair<int, int> currPos = toTest.front();
        toTest.pop_front();
        std::vector<std::pair<int, int>> newPositions = possibleMoves(currPos);

        for (auto p : newPositions) {
            if (board[p.first][p.second] > board[currPos.first][currPos.second] + 1) {
                board[p.first][p.second] = board[currPos.first][currPos.second] + 1;
                toTest.push_back(p);
                maxMoves = std::max(maxMoves, board[p.first][p.second]);
            }
        }
    }

    std::vector<std::string> hidingPlaces;
    for (int i = 0; i < boardSize; ++i) {
        for (int j = 0; j < boardSize; ++j) {
            if (board[i][j] == maxMoves) {
                hidingPlaces.push_back(indexToCoord[i] + std::to_string(j + 1));
            }
        }   
    }

    return hidingPlaces;
}

int main(int argc, char const *argv[]) {
    int n;
    std::cin >> n;

    std::string start;
    int maxMoves;
    for (int i = 0; i < n; ++i) {
        std::cin >> start;
        maxMoves = 0;
        std::vector<std::string> hidingPlaces = hideHorse(start, maxMoves);

        std::sort(hidingPlaces.begin(), hidingPlaces.end(), [](std::string const& a, std::string const& b) {
            if(a[1] == b[1]) {
                return a[0] < b[0];
            }
            return a[1] > b[1];
        });

        std::cout << maxMoves << " ";
        for (auto place : hidingPlaces) {
            std::cout << place << " ";
        }
        std::cout << "\n";
    }

    return 0;
}