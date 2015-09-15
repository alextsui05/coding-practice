#!/usr/bin/env cppsh
#include <iostream>

// global to track API calls
int count = 0;

// global to specify bad number
int bad = 1700000000;

bool isBadVersion(int m) {
    ++count;
    return m >= bad;
}

class Solution {
public:
    /**
    Find the first bad version in a range of versions [1, n].

    \return the first bad version in the range of versions [1, n]
    */
    int firstBadVersion(int n) {
        // set the API call count for diagnostic
        count = 0;

        // initialize the binary search range to [1, n)
        int l = 1;
        int r = n;

        while (r > l) {
            // write the midpoint in this way to avoid overflow
            int m = l + (r - l)/2;
            if (isBadVersion(m)) {
                r = m;
            } else {
                l = m + 1;
            }
        }
        std::cout << count << " API calls" << std::endl;

        return l;
    }
};

int main(int argc, char* argv[])
{
    int n = 2126753390;
    if (argc != 1 && argc != 3) {
        std::cout << "Usage 1: FirstBadVersion" << std::endl;
        std::cout << "Usage 2: FirstBadVersion n bad" << std::endl;
        return 1;
    }
    if (argc == 3) {
        n = atoi(argv[1]);
        bad = atoi(argv[2]);
    }
    Solution s;
    std::cout << s.firstBadVersion(n) << std::endl;
    return 0;
}
