/*
Author: Magnus Hjortswang, maghj433

Problem description: Find the longest increasing subsequence in a sequence of integers, not nessecarily contiguous.

Time complexity: O(n*log(n)), since we loop through the whole sequence once (O(n)) and in each iteration use a binary search (O(log(n))).

Usage: Assumes all intervals have an end point equal to or greater than their start. 
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <deque>

// Determine the longest increasing subsequence by looping through the whole sequence once, and for each element
// determining the largest possible predecessor. Then, compare the end-value of the current sequence with the same length
// as the one the new element creates to the new end-value. If the new sequence ends with a smaller value, store the index
// to that end value. Once the best subsequences of all possible lengths have been determined, return the longest one.
std::deque<int> longestIncreasingSequence(std::vector<int> sequence) {
    std::vector<int> parents = {-1};
    std::vector<int> longest = {0};

    // Find and store the end points for each length of subsequence, where the value of that end point is the smallest
    // possible for that length.
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

    // Iterate through the longest found sequence by going through the parent of each element in the sequence
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

        std::deque<int> longest = longestIncreasingSequence(sequence);

        std::cout << longest.size() << "\n";
        for (int i : longest) {
            std::cout << i << " ";
        }
        std::cout << "\n";
    }
    return 0;
}
