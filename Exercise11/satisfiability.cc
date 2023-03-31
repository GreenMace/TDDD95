#include <iostream>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <utility>

bool satisfy(std::vector<std::vector<std::pair<int, int>>> &clauses, int n, std::vector<int> variables) {
    if (n == 0) {
        for (auto & clause : clauses) {
            bool fulfilled = false;
            for (auto & var : clause) {
                
                if (variables[var.first] == var.second) {
                    fulfilled = true;
                }
            }

            if (!fulfilled) {
                return false;
            }
        }
        
        return true;
    }
    
    variables[--n] = 1;
    if (satisfy(clauses, n, variables)) {
        return true;
    }

    variables[n] = 0;
    if (satisfy(clauses, n, variables)) {
        return true;
    }

    return false;
    
}

int main(int argc, char const *argv[]) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int t, n, m;
    std::cin >> t;

    for (int i = 0; i < t; ++i) {
        std::cin >> n >> m;
        std::vector<int> variables(n, -1);
        std::vector<std::vector<std::pair<int, int>>> clauses(m);

        std::string line;
        std::getline(std::cin, line);
        for (int j = 0; j < m; ++j) {
            std::getline(std::cin, line);
            
            int pos = 0;
            bool neg;
            int num;
            std::string delimiter = " v ";
            std::string token;
            while ((pos = line.find(delimiter)) != std::string::npos) {
                token = line.substr(0, pos);
                neg = token[0] == '~';
                num = std::stoi(token.substr(1 + neg, token.length())) - 1;
                clauses[j].push_back({num, !neg});
                line.erase(0, pos + delimiter.length());
            }
            neg = line[0] == '~';
            num = std::stoi(line.substr(1 + neg, line.length())) - 1;
            clauses[j].push_back({num, !neg});
        }

        if (satisfy(clauses, n, variables)) {
            std::cout << "satisfiable\n";
        } else {
            std::cout << "unsatisfiable\n";
        }
        
    }
    
    return 0;
}
