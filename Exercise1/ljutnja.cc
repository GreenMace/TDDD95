#include <iostream>
#include <map>

int main(int argc, char const *argv[])
{
    int M, N, w;
    std::cin >> M >> N;
    std::map<int, unsigned long long> kids;
    for (int i = 0; i < N; i++) {
        std::cin >> w;
        kids[w]++;
    }

    if (kids.count(0)) {
        N -= kids[0];
    }

    unsigned long long missing = 0;
    for (auto k : kids) {
        missing += k.first * k.second;
    }
    missing -= M;

    unsigned long long sum = 0;
    int divEqual = 0;
    int i = 1;
    while (missing >= 0) {
        if (N >= missing) {
            sum += missing * i * i + (N - missing) * divEqual * divEqual;
            break;
        }

        divEqual += int(missing / N);
        missing = missing % N;

        for (int j = i; j <= divEqual; j++) {
            if (kids.count(j)) {
                missing += (divEqual - j) * kids[j];
                N -= kids[j];
                sum += kids[j] * j * j;
            }
        }

        i = divEqual + 1;
    }

    std::cout << sum << std::endl;
    return 0;
}
