#!/usr/bin/env cppsh
#include <algorithm>
#include <iostream>
#include <bitset>
#include <string>
#include <vector>
#include "bitwise_utils.h"

using namespace std;

/**
Given an integer, return the next largest and next smallest integer whose
binary representation has the same number of 1 bits.
*/
class BitsetSolution {
public:
    vector<int> next(int n)
    {
        bitset<32> bs(n);
        string s = bs.to_string();
        string sn[2] = { s, s };
        prev_permutation( sn[0].begin(), sn[0].end() );
        next_permutation( sn[1].begin(), sn[1].end() );
        return vector<int> { bitset<32>(sn[0]).to_ulong(),
            bitset<32>(sn[1]).to_ulong() };
    }
};

class Solution {
public:
    vector<int> prev_and_next(int n)
    {
        vector<int> res { 0, 0 };
        res[0] = prev(n);
        res[1] = next(n);

        return res;
    }

private:
    int next(int n) {
        if (n == -1) return n; // all 1-bits
        unsigned int m = n;
        int offset = 0;
        while (m % 2 == 0 && offset < 32) {
            m >>= 1;
            ++offset;
            //printb(m); std::cout << std::endl;
        }
        if (offset == 32) // no 1-bits
            return n;

        ++m;
        int low_bit = m & (m - 1) ^ m;
        if ((low_bit << offset) == 0) {
            // n is a sequence of 1's followed by 0's; wrap around
            return --m;
        }

        return (m << offset) | ((low_bit >> 1) - 1);
    }

    int prev(int n) {
        if (!n || n == -1) return n;
        // at this point, n has at least one 0 and 1
        int m = n;
        // find run of leading 1's and turn them off
        int leading_ones = 0;
        while ((m & (1 << leading_ones)) != 0) {
            ++leading_ones;
        }
        m = m & ~((1 << leading_ones) - 1);

        // find the leading 1-bit after that
        int target_one = m & (m - 1) ^ m;

        // if there is no leading 1-bit, fill the end with the leading 1's
        if (!target_one) { // m is 0's followed by 1's; wrap around
            m = (1 << leading_ones) - 1;
            while (m > 0) {
                m <<= 1;
            }
            return m;
        }

        // if there is, then shift it right and fill the leading 1's after
        if (target_one == (1 << 31)) {
            m = 0;
        } else {
            m &= ~((target_one << 1) - 1);
        }
        m |= (target_one >> 1);
        for (int i = 0; i < leading_ones; ++i) {
            m |= (target_one >> (1 + 1 + i));
        }

        return m;
    }

    int reverse(int n) {
        int l = 0;
        int r = 31;
        while (l < r) {
            n = (((n & (1 << l)) >> l) << r) |
                (((n & (1 << r)) >> r) << l) |
                (n & ~((1 << l) | (1 << r)));
            ++l;
            --r;
        }
        return n;
    }
};

int main(int argc, char* argv[])
{

    Solution soln;
    int n = atoi(argv[1]);
    auto res = soln.prev_and_next(n);
    printb(res[0]);
    std::cout << std::endl;
    printb(n);
    std::cout << std::endl;
    printb(res[1]);
    std::cout << std::endl;
    std::cout << res[0] << " " << res[1] << std::endl;
    return 0;
}
