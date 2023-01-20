#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>

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

std::vector<int> cover(std::pair<double, double> toCover, std::vector<Interval> intervals) {
    if (!intervals.size() || intervals[0].start > toCover.first) {
        return {};
    }
    
    std::vector<int> covering;
    Interval bestNextInterval = intervals[0];
    
    double currEnd;
    for (int i = 0; i < intervals.size(); i++) {
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

        if (currEnd >= toCover.second) {
            return covering;
        }

        if (intervals[i].start <= currEnd) {
            if (intervals[i].end > bestNextInterval.end) {
                bestNextInterval = intervals[i];
            }
        } else {
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

    if (covering.empty() || bestNextInterval.index != covering.back()) {
        covering.push_back(bestNextInterval.index);
        currEnd = bestNextInterval.end;
    }

    if (currEnd >= toCover.second) {
        return covering;
    }

    return {};
}

int main(int argc, char const *argv[]) {
    
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
        
        std::sort(intervals.begin(), intervals.end(), [](auto &left, auto &right) {
            return left.start < right.start;
        });

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