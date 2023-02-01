#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

int main(int argc, char const *argv[]) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int N;
    std::cin >> N;

    std::vector<int> numbers;
    int num;
    for (int i = 0; i < N; i++) {
        std::cin >> num;
        numbers.push_back(num);
    }

    std::ostringstream output;
    std::vector<int>::iterator start;
    std::vector<int>::iterator end;
    for (int i = 0; i < N; i++) {
        if (i % 2 == 0) {
            start = std::find(numbers.begin() + int(i/2), numbers.end() - int(i/2), int(i/2) + 1);
            end = numbers.begin() + int(i/2);
            std::rotate(end, start, start + 1);
            output << std::distance(end, start) << "\n";
        } else {
            start = std::find(numbers.begin() + int(i/2), numbers.end() - int(i/2), N - int(i/2));
            end = numbers.begin() + (N - (int(i/2) + 1));
            std::rotate(start, start + 1, end + 1);
            output << std::distance(start, end) << "\n";
        }
    }
    
    std::cout << output.str();
    return 0;
}
