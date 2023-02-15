/*
Author: Magnus Hjortswang

Problem description: Find the minimal number of intervals needed to completely cover a given interval.

Time complexity: O(n*log(n)), since we sort the intervals once (O(n*log(n)) and then iterate over each one only once (O(n)).

Usage: Assumes all intervals have an end point equal to or greater than their start. 
*/

#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>

// Class to represent an interval, with a start and end as well as its index before sorting
class Interval {
public:
    Interval(double a, double b, int i) {
        start = a;
        end = b;
        index = i;
    }

    double start;
    double end;
    int index;
};

// Greedy algorithm which finds a minimal set of intervals needed to cover the given interval
// Returns a vector with their indicies
std::vector<int> cover(std::pair<double, double> toCover, std::vector<Interval> intervals) {
    // Sort all intervals based on start value
    // Time complexity O(n*log(n))
    std::sort(intervals.begin(), intervals.end(), [](auto &left, auto &right) {
        return left.start < right.start;
    });

    if (!intervals.size() || intervals[0].start > toCover.first) {
        return {};
    }
    
    std::vector<int> covering;
    Interval bestNextInterval = intervals[0];
    
    double currEnd;
    // Iterate over all intervals
    // Time complexity: O(n)
    for (int i = 0; i < intervals.size(); i++) {
        // Find best start interval
        if (covering.empty()) {
            if (intervals[i].start <= toCover.first) {
                if (intervals[i].end > bestNextInterval.end) {
                    bestNextInterval = intervals[i];
                }
                continue;
            }
            covering.push_back(bestNextInterval.index);
            currEnd = bestNextInterval.end;
        }

        // Check wether a solution as been found
        if (currEnd >= toCover.second) {
            return covering;
        }

        // Check wether the interval is a possible next candidate
        if (intervals[i].start <= currEnd) {
            // Check wether the interval covers more than the previous best
            if (intervals[i].end > bestNextInterval.end) {
                bestNextInterval = intervals[i];
            }
        } else {
            // Add the current candidate unless it is already added
            if (bestNextInterval.index != covering.back()) {
                covering.push_back(bestNextInterval.index);
                currEnd = bestNextInterval.end;
                
                if (intervals[i].start <= currEnd && intervals[i].end > bestNextInterval.end) {
                    bestNextInterval = intervals[i];
                }

                if (currEnd >= toCover.second) {
                    return covering;
                }
            }
        }
    }

    // Add the last best candidate to our minimal set unless it is already added.
    if (covering.empty() || bestNextInterval.index != covering.back()) {
        covering.push_back(bestNextInterval.index);
        currEnd = bestNextInterval.end;
    }

    // Check wether a solution exists
    if (currEnd >= toCover.second) {
        return covering;
    }

    return {};
}

int main(int argc, char const *argv[]) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    double A,B;
    while (std::cin >> A >> B) {
        int n;
        std::cin >> n;
        
        std::vector<Interval> intervals;
        double a, b;
        for(int i = 0; i < n; i++) {
            std::cin >> a >> b;
            if (a <= B && b >= A) {
                intervals.push_back(Interval(a,b,i));
            }
        }

        std::vector<int> covering = cover({A,B}, intervals);
        if (!covering.size()) {
            std::cout << "impossible" << "\n";
            continue;
        }

        std::cout << covering.size() << "\n";
        for(int i = 0; i < covering.size(); i++) {
            std::cout << covering[i] << " ";
        }
        std::cout << "\n";

    }

    return 0;
}
