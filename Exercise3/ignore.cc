#include <iostream>
#include <unordered_map>
#include <string>

std::string nthNumber(int n) {
    std::unordered_map<int, std::string> flipped = {
        {0,"0"}, {1,"1"}, {2,"2"}, {3,"5"}, {4,"9"}, {5,"8"},
        {6,"6"}
    };

    std::string number;
    while (n > 0) {
        number += flipped[n % 7];
        n -= n%7;
        n /=7;
    }
    
    return number;
}

int main(int argc, char const *argv[]) {
    int n;
    while (std::cin >> n) {
        std::cout << nthNumber(n) + "\n";
    }

    return 0;
}