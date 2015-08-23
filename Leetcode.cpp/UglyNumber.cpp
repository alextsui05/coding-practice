#!/usr/bin/env cppsh
#include <iostream>
#include <cstdlib>

class Solution {
public:
    /**
    Return whether a number is ugly i.e. can be factored into a product of 2s, 3s, and 5s.
    */
    bool isUgly(int num) {
        if (num < 1)
            return false;

        while (num % 5 == 0) {
            num /= 5;
        }
        while (num % 3 == 0) {
            num /= 3;
        }
        while (num % 2 == 0) {
            num /= 2;
        }
        return (num == 1);
    }
};

int main(int argc, char * argv[])
{
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " n" << std::endl;
        return 0;
    }
    Solution s;
    std::cout << s.isUgly(atoi(argv[1])) << std::endl;

    return 0;
}
