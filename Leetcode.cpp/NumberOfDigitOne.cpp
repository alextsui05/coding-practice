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
        int cols = log(n)/log(10) + 1;
        int base = 1;
        for (int i = 0; i < cols; ++i) {
            int digit = (n / base) % 10;
            // first add contribution due to right side
            if (digit == 1) {
                int rem = n % base;
                sum += rem + 1;
            } else if (digit > 1) {
                sum += base;
            }
            // add contribution due to left side
            int ones = ll(n)/(ll(10) * base);
            ones *= base;
            sum += ones;

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
