#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <iterator>
#include <deque>

std::deque<int> test(std::vector<int> sequence) {
    std::vector<int> parents = {-1};
    std::vector<int> longest = {0};

    for (int i = 1; i < sequence.size(); i++) {
        auto smallestLargerIter = std::lower_bound(longest.begin(), longest.end(), i, [&sequence](int a, int b) {
            return sequence[a] < sequence[b];
        });
        
        auto n = std::distance(longest.begin(), smallestLargerIter);
        if (n == longest.size()) {
            parents.push_back(longest[n-1]);
            longest.push_back(i);
        } else {
            if (n > 0) {
                parents.push_back(longest[n-1]);
            } else {
                parents.push_back(-1);
            }
                
            if (sequence[i] < sequence[longest[n]]) {
                longest[n] = i;
            }
        }
    }

    std::deque<int> output = {longest.back()};
    int parent = parents[longest.back()];
    while (parent != -1) {
        output.push_front(parent);
        parent = parents[parent];
    }

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

        std::deque<int> longest = test(sequence);

        std::cout << longest.size() << "\n";
        for (int i : longest) {
            std::cout << i << " ";
        }
        std::cout << "\n";
    }
    return 0;
}