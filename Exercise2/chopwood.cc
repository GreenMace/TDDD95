#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

int main(int argc, char const *argv[]) {
    int n;
    std::cin >> n;

    std::vector<int> v;
    std::map<int, int> order = {};
    int num;
    for (int i = 0; i < n; i++) {
        std::cin >> num;
        v.push_back(num);
        order[i+1] = num;
    }
    
    if (n+1 == v.back()) {
        std::vector<int> u;
        for (int i = v.size()-1; i > 0; i--) {
            if (order.find(v[i-1]) != order.end()) {
                u.push_back(v[i-1]);
                order.erase(v[i-1]);
            } else {
                u.push_back(order.rbegin()->first);
                order.erase(order.rbegin()->first);
            }
        }
        u.push_back(order.begin()->first);

        for (std::vector<int>::reverse_iterator i = u.rbegin(); i != u.rend(); ++i ) { 
            std::cout << *i << "\n";
        }

    } else {
        std::cout << "Error\n";
    }

    return 0;
}
