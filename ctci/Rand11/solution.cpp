#!/usr/bin/env cppsh
#include <iostream>
#include <boost/unordered_map.hpp>

using namespace std;
using namespace boost;

/**
Given a random number generator that gives a random number in the range
of [0, 3), compute a random number generator for the range [0, 11).
*/
class Solution {
public:
    int rand11() const {
        int r1, r2;

        do { // randomly choose a positive even number < 12
            r1 = 2 * rand9();
        } while (r1 > 12);

        do { // randomly choose 0 or 1
            r2 = rand3();
        } while (r2 == 2);

        // the sum is a random number between [0, 12)
        return r1 + r2;
    }

private:
    /**
    [0, 3), [3, 6), [6, 9) each have probability 1/3 of being chosen,
    and then within those, each element has probability 1/3 of being chosen.

    \return a random number in [0, 9)
    */
    int rand9() const {
        return 3*rand3() + rand3();
    }

    int rand3() const {
        return rand() % 3;
    }
};

int main(int argc, char* argv[])
{
    unordered_map<int, int> counts;
    Solution s;
    for (int i = 0; i < 10000000; ++i) {
        counts[s.rand11()]++;
    }
    for (int i = 0; i < 11; ++i) {
        std::cout << i << " : " << counts[i] << std::endl;
    }
    return 0;
}
