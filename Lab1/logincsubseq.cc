#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

int getKey(std::map<int, std::vector<int>>& v, std::vector<int> sequence, int l, int r, int elem)
{
    while (r - l > 1) {
        int m = l + (r - l) / 2;
        if (sequence[v[m].back()] >= elem) {
            r = m;
        } else {
            l = m;
        }
    }
  
    return r;
}

std::vector<int> solve(std::vector<int> sequence) {
    std::map<int, std::vector<int>> activeLists;

    activeLists[0] = {0};
    for (int i = 1; i < sequence.size(); i++) {
        int elem = sequence[i];

        if (elem < sequence[activeLists[0].back()]) {
            activeLists[0] = {i};
        } else if (elem > sequence[activeLists.rbegin()->second.back()]) {
            std::vector<int> seq =  activeLists.rbegin()->second;
            seq.push_back(i);
            activeLists[seq.size() - 1] = seq;
        } else {
            int largestSmallerKey = getKey(activeLists, sequence, -1, activeLists.size()-1, elem);

            if (sequence[activeLists[largestSmallerKey].back()] == elem) {
                largestSmallerKey -= 1;
            }

            std::vector<int> seq = activeLists[largestSmallerKey];
            seq.push_back(i);
            activeLists[seq.size() - 1] = seq;
        }
    }

    return activeLists.rbegin()->second;
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

        std::vector<int> longest = solve(sequence);

        std::cout << longest.size() << "\n";
        for (int i : longest) {
            std::cout << i << " ";
        }
        std::cout << "\n";
    }
    return 0;
}
