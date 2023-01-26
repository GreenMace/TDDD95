#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <unordered_map>

class Item {
public:
    Item(int v, int w) {
        value = v;
        weight = w;
    }

    int value;
    int weight;
};

std::vector<int> solve(int C, std::vector<Item> items) {
    std::vector<std::vector<int>> S;

    for (int k = 0; k <= items.size(); k++) {
        S.push_back({0});
        for (int v = 0; v <= C; v++) {
            S[k].push_back(0);
        }
    }

    for (int v = 1; v <= C; v++) {
        for (int k = 1; k <= items.size(); k++) {
            S[k][v] = S[k-1][v];
            Item item = items[k - 1];
            if (item.weight <= v && S[k-1][v-item.weight] + item.value > S[k][v]) {
                S[k][v] = S[k-1][v-item.weight] + item.value;
            }
        }
    }

    int w = C;
    int k = items.size();
    std::vector<int> output;
    while (w > 0) {
        if (items[k-1].weight <= w) {
            output.push_back(k-1);
            w -= items[k-1].weight;
        }
        k--;
    }

    return output;
}

int main(int argc, char const *argv[]) {
    
    int C, n;
    while (std::cin >> C >> n) {
        std::vector<Item> items;
        int v, w;
        for (int i = 0; i < n; i++) {
            std::cin >> v >> w;
            items.push_back(Item(v, w));
        }

        std::vector<int> chosen = solve(C, items);
        std::cout << chosen.size() << "\n";
        for (auto item : chosen) {
            std::cout << item << " ";
        }
        std::cout << "\n";
    }
    return 0;
}
