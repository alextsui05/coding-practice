#!/usr/bin/env cppsh
#include <iostream>
#include <cmath>

using namespace std;

typedef long long ll;

/**
Return the total number of digit 1 appearing in all non-negative integers less
than or equal to n.

This approach is log(n), summing the digits appearing in each digit place
separately.
*/
class Solution {
public:
    int countDigitOne(int n) {
        int sum = 0;
        int cols = 0;
        for (int i = n; i > 0; i /= 10, ++cols);
        int base = 1;
        for (int i = 0; i < cols; ++i) {
            int digit = (n / base) % 10;
            // first add contribution due to right side
            int contrib = 0;
            if (digit == 1) {
                int rem = n % base;
                contrib += rem + 1;
            } else if (digit > 1) {
                contrib += base;
            }
            // add contribution due to left side
            int ones = ll(n)/(ll(10) * base);
            ones *= base;
            contrib += ones;

            //std::cout << "contrib from i = " << i << ": " << contrib << std::endl;
            sum += contrib;

            base *= 10;
        }

        return sum;
    }
};

int main(int argc, char* argv[])
{
    Solution s;
    std::cout << s.countDigitOne(atoi(argv[1])) << std::endl;
    return 0;
}
