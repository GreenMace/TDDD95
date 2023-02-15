#include <iostream>
#include <vector>
#include <unordered_map>

#define outcomes 8

// Börja med äldsta
// 1. Ranka alternativ beroende på input från föregående
// 2. Skicka till föregående
// 3. Ranka om beroende på nästas output
// Börja om från 1.

int stringDiff(std::string a, std::string b) {
    int different = 0;
    
    for(int i = 0; i < a.length(); ++i) {
        if (a[i] != b[i]) {
            ++different;
        }
    } 

    return different;
}

std::unordered_map<std::string, int> states = {{"NNN", 0}, {"NNY", 1}, {"NYN", 2}, {"NYY", 3}, {"YNN", 4}, {"YNY", 5}, {"YYN", 6}, {"YYY", 7}};

std::string uxuhulVoting(std::vector<std::vector<int>> preferences) {
    std::vector<std::string> evenInput = {"NYY", "YYN", "YNY", "NNN"}; 
    std::vector<std::string> oddInput = {"NNY", "NYN", "YNN", "YYY"};

    int numPriestsLeft = preferences.size();

    std::unordered_map<std::string, std::string> consequences;
    
    // Initiera consequences med sista prästen
    std::vector<std::string> input;
    std::vector<std::string> output;
    if (numPriestsLeft % 2) {
        input = evenInput;
        output = oddInput;
    } else {
        input = oddInput;
        output = evenInput;
    }

    for (auto in : input) {
        int pref = 9;
        for (auto out : output) {
            if (stringDiff(in, out) == 1 && preferences.back()[states[out]] < pref) {
                pref = preferences.back()[states[out]];
                consequences[in] = out;
            }
        }
    }
    --numPriestsLeft;

    // Låt resterande präster göra sina val
    for (int i = preferences.size()-2; i >= 0; --i) {
        if (numPriestsLeft % 2) {
            input = evenInput;
            output = oddInput;
        } else {
            input = oddInput;
            output = evenInput;
        }

        // Hitta bästa valen givet vad alla som följer därefter kommer att göra
        std::unordered_map<std::string, std::string> choices;
        for (auto in : input) {
            int pref = 9;
            for (auto out : output) {
                if (stringDiff(in, out) == 1 && preferences[i][states[consequences[out]]] < pref) {
                    pref = preferences[i][states[consequences[out]]];
                    choices[in] = out;
                }
            }
        }

        for (auto choice : choices) {
            consequences[choice.first] = consequences[choice.second];
        }

        --numPriestsLeft;    
    }

    // Första prästen bestämmer slutresultatet
    return consequences["NNN"];
}


int main(int argc, char const *argv[]) {
    int n;
    std::cin >> n;

    int m;
    for(int i = 0; i < n; ++i) {
        std::cin >> m;
        std::vector<std::vector<int>> preferences(m);

        std::vector<int> p(outcomes);
        for(int j = 0; j < m; ++j) {
            for(int k = 0; k < outcomes; ++k) {
                std::cin >> p[k];
            }
            preferences[j] = p;
        }

        std::cout << uxuhulVoting(preferences) << "\n";
    }

    return 0;
}
