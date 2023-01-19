#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>

class Interval {
public:
    Interval(float a, float b, float i) {
        start = a;
        end = b;
        index = i;
    }

    float start;
    float end;
    int index;
};

std::vector<int> cover(std::pair<float, float> toCover, std::vector<Interval> intervals) {
    if (intervals[0].start > toCover.first) {
        return {};
    }

    std::vector<int> covering = {intervals[0].index};
    Interval bestNextInterval = intervals[0];
    float currEnd = bestNextInterval.end;
    for (int i = 1; i < intervals.size(); i++) {
        if (currEnd >=  toCover.second) {
            return covering;
        }

        if (intervals[i].start > currEnd && bestNextInterval.end > currEnd) {
            covering.push_back(bestNextInterval.index);
            currEnd = bestNextInterval.end;
        }

        if (intervals[i].start <= currEnd && intervals[i].end > bestNextInterval.end) {
            bestNextInterval = intervals[i];
        } 
        
        if (intervals[i].start > currEnd && currEnd < toCover.second) {
            return {};
        }
    }

    if (bestNextInterval.index != covering.back()) {
        covering.push_back(bestNextInterval.index);
        currEnd = bestNextInterval.end;
    }

    if (currEnd >= toCover.second) {
        return covering;
    }

    return {};
}

int main(int argc, char const *argv[]) {
    
    float A,B;
    while (std::cin >> A >> B) {
        int n;
        std::cin >> n;
        
        std::vector<Interval> intervals;
        float a, b;
        for(int i = 0; i < n; i++) {
            std::cin >> a >> b;
            a = std::max(A, a);
            b = std::min(B, b);
            intervals.push_back(Interval(a,b,i));
        }
        
        std::sort(intervals.begin(), intervals.end(), [](auto &left, auto &right) {
            if (left.start == right.start) {
                return left.end > right.end;
            }
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
