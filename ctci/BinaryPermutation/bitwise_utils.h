#ifndef BITWISE_UTILS_H
#define BITWISE_UTILS_H

#include <limits>
#include <iostream>
#include <vector>

template <class T>
void printb(T n) {
    using namespace std;
    vector<char> seq;
    int N = numeric_limits<T>::digits;
    if (numeric_limits<T>::is_signed) ++N;
    for (int i = 0; i < N; ++i) {
        if (i && i % 8 == 0) {
            seq.push_back(' ');
        }
        if (n & (1 << i)) {
            seq.push_back('1');
        } else {
            seq.push_back('0');
        }
    }
    for (int i = seq.size() - 1; i >= 0; --i) {
        std::cout << seq[i];
    }
}

#endif // BITWISE_UTILS_H
