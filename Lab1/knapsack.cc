/*
Author: Magnus Hjortswang, maghj433

Problem description: Find the set of items with maximum value, with a combined weight less than a given limit.

Time complexity: O(n * c), where n is the number of items and c the maximum weight, since we iterate over all weights (O(c)) once for each item (O(n)).

Usage: Assumes all weights are positive, and that both values and weights are integers.
*/

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

// Class to represent an item, by its weight and value.
class Item {
public:
    Item(int v, int w) {
        value = v;
        weight = w;
    }

    int value;
    int weight;
};

// Dynamic algorithm which finds the set of items with maximum value without exceeding the weight limit C.
// This is achieved by creating a table with one row for each item, and one column for each possible weight less 
// than or equal to C. Each element in the table is the maximum value for that given weight limit (column) given 
//the items up to and including that item (row). Once the table is filled, iterate from the top right corner down 
// towards the bottom left adding all items that make up the solution
std::vector<int> maxValueSet(int C, std::vector<Item> items) {
    std::vector<std::vector<int>> S;

    // Initiate the table with zeros
    for (int k = 0; k <= items.size(); k++) {
        S.push_back({0});
        for (int v = 0; v <= C; v++) {
            S[k].push_back(0);
        }
    }

    // Fill the table with the maximum value for a given subset of items and maxmimum weight
    for (int v = 1; v <= C; v++) {
        for (int k = 1; k <= items.size(); k++) {
            S[k][v] = S[k-1][v];
            Item item = items[k - 1];
            if (item.weight <= v && S[k-1][v-item.weight] + item.value > S[k][v]) {
                S[k][v] = S[k-1][v-item.weight] + item.value;
            }
        }
    }

    // Find the set of items which make up the maximum value given the total weight limit
    int w = C;
    int k = items.size();
    std::vector<int> output;
    while (w > 0 && k > 0) {
        if (items[k-1].weight <= w) {
            int w2 = w - items[k-1].weight;
            // Add the item if removing that item takes us to a new position (weight, item, value)
            // also that exists in the table
            if (S[k][w] == S[k-1][w2] + items[k-1].value) {
                output.push_back(k-1);
                w = w2;
            }
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

        std::vector<int> chosen = maxValueSet(C, items);
        std::cout << chosen.size() << "\n";
        for (auto item : chosen) {
            std::cout << item << " ";
        }
        std::cout << "\n";
    }
    return 0;
}

