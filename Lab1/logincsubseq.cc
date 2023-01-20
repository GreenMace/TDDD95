#include <iostream>
#include <vector>
#include <deque>
#include <unordered_map>
#include <algorithm>

std::unordered_map<int, std::deque<int>> longestSequences;

std::deque<int> solve(std::vector<int> sequence, int start = 0) {
    std::deque<int> output = {start};
    if (longestSequences.count(start)) {
        return longestSequences[start];
    }

    for (int i = start + 1; i < sequence.size(); i++) {
        if (sequence[i] > sequence[start]) {
            std::deque<int> seq = solve(sequence, i);
            if (seq.size() >= output.size()) {
                output = seq;
                output.push_front(start);
            }
        }
    }

    longestSequences[start] = output;

    return output;
}

int main(int argc, char const *argv[]) {
    int n;
    while (std::cin >> n) {
        std::vector<int> sequence;
        
        int num;
        for (int i = 0; i < n; i++) {
            std::cin >> num;
            sequence.push_back(num);
        }
        
        longestSequences = {};
        std::deque<int> longest = solve(sequence);
        std::cout << longest.size() << "\n";
        for (int i : longest) {
            std::cout << i << " ";
        }
        std::cout << "\n";
    }
    return 0;
}
