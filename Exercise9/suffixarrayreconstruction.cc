#include <iostream>
#include <map>

int main(int argc, char const *argv[]) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int t;
    std::cin >> t;

    int l, s;
    for (int i = 0; i < t; ++i) {
        std::cin >> l >> s;

        std::string word(l, '_');
        bool possible = true;

        int p;
        std::string suffix;
        for (int j = 0; j < s; ++j) {
            std::cin >> p >> suffix;

            for (int k = 0; k < suffix.length(); ++k) {
                if (suffix[k] == '*') {
                    p = l - suffix.length() + 1;
                    continue;
                }

                if (word[p+k-1] != '_') {
                    if (word[p+k-1] != suffix[k]) {
                        possible = false;
                    }
                    continue;
                }
                word[p+k-1] = suffix[k];
            }
        }

        std::string output;
        for (auto c : word) {
            if (c == '_') {
                possible = false;
            }
        }

        if (possible) {
            std::cout << word << "\n";
        } else {
            std::cout << "IMPOSSIBLE\n";
        }
    }
    
    return 0;
}
