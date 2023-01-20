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

std::unordered_map<int, std::unordered_map<int, std::pair<std::vector<int>, int>>> cases; 

std::pair<std::vector<int>, int> solveHelper(int maxWeight, std::vector<Item> items, int start) {
    std::vector<int> output;
    int outputValue = 0;

    if(cases.count(start) && cases[start].count(maxWeight)) {
        std::cout << "used" << "\n";
        return cases[start][maxWeight];
    }

    for(int i = start; i < items.size(); i++) {
        if (items[i].weight <= maxWeight) {
            std::pair<std::vector<int>, int> packedBag = solveHelper(maxWeight - items[i].weight, items, i + 1);
            if (items[i].value + packedBag.second > outputValue) {
                output = packedBag.first;
                output.push_back(i);
                outputValue = items[i].value + packedBag.second;
            }
        }

        std::pair<std::vector<int>, int> packedBag = solveHelper(maxWeight, items, i + 1);
        if (packedBag.second > outputValue) {
            output = packedBag.first;
            outputValue = packedBag.second;
        }
    }

    cases[start][maxWeight] = {output, outputValue};
    return {output, outputValue};
}

std::vector<int> solve(int maxWeight, std::vector<Item> items) {
    std::vector<int> output;
    int outputValue = 0;

    for(int i = 0; i < items.size(); i++) {
        if (items[i].weight <= maxWeight) {
            std::pair<std::vector<int>, int> packedBag = solveHelper(maxWeight - items[i].weight, items, i + 1);
            if (items[i].value + packedBag.second > outputValue) {
                output = packedBag.first;
                output.push_back(i);
                outputValue = items[i].value + packedBag.second;
            }
        }

        std::pair<std::vector<int>, int> packedBag = solveHelper(maxWeight, items, i + 1);
        if (packedBag.second > outputValue) {
            output = packedBag.first;
            outputValue = packedBag.second;
        }
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
        
        cases = {};
        std::vector<int> chosen = solve(C, items);
        std::cout << chosen.size() << "\n";
        for (auto item : chosen) {
            std::cout << item << " ";
        }
        std::cout << "\n";
    }
    return 0;
}
