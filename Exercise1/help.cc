#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <map>

int main(int argc, char const *argv[])
{
    int n;
    std::cin >> n;
    std::cin.ignore(1000, '\n');
    
    std::string line1, line2;
    
    for(int i = 0; i < n; i++) {
        std::vector<std::string> splitLine1, splitLine2;
        
        getline(std::cin, line1);
        
        std::stringstream ss(line1);
        std::string word;
        while(std::getline(ss, word, ' ')) {
            splitLine1.push_back(word);
        }
        
        getline(std::cin, line2);
        std::stringstream ss2(line2);
        while(std::getline(ss2, word, ' ')) {
            splitLine2.push_back(word);
        }
        
        std::string result = "-";
        
        if (splitLine1.size() == splitLine2.size()) {
            bool updated = true;
            while(updated) {
                updated = false;
                std::map<std::string, std::string> pattern1, pattern2;
                for(int j = 0; j < splitLine1.size(); j++) {
                    if (splitLine1[j][0] == '<') {
                        if (!pattern1.count(splitLine1[j])) {
                            if (splitLine2[j][0] != '<'){
                                pattern1[splitLine1[j]] = splitLine2[j];
                            }
                        }
                    } 

                    if (splitLine2[j][0] == '<') {
                        if (!pattern2.count(splitLine2[j])) {
                            if (splitLine1[j][0] != '<'){
                                pattern2[splitLine2[j]] = splitLine1[j];
                            }
                        }
                    }
                }
                
                for(int j = 0; j < splitLine1.size(); j++) {
                    if (pattern1.count(splitLine1[j])) {
                        updated = true;
                        splitLine1[j] = pattern1[splitLine1[j]];
                    } 

                    if (pattern2.count(splitLine2[j])) {
                        updated = true;
                        splitLine2[j] = pattern2[splitLine2[j]];
                    } 
                }
            }
            std::string res1 = "";
            for (int j = 0; j < splitLine1.size(); j++) {
                if (!res1.empty()){
                    res1 += " ";
                }
                if (splitLine1[j][0] == '<') {
                    res1 += "a";
                } else {
                    res1 += splitLine1[j];
                }
            }

            std::string res2 = "";
            for (int j = 0; j < splitLine2.size(); j++) {
                if (!res2.empty()){
                    res2 += " ";
                }
                if (splitLine2[j][0] == '<') {
                    res2 += "a";
                } else {
                    res2 += splitLine2[j];
                }
            }

            if (res1 == res2) {
                result = res1;
            }
        }
        
        std::cout << result << std::endl;
    }
    
    return 0;
}