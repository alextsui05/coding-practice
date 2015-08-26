#!/usr/bin/env cppsh
#include <vector>
#include <iostream>
using namespace std;

class Solution
{
public:
    /**
    \param[in] a list of numbers where all but two appear twice
    \return the two numbers that appear just once
    */
    vector<int> singleNumber(vector<int>& nums) {
        // Note 1: XOR is commutative
        // Note 2: for any number x, x XOR x is 0
        // If we XOR all numbers in nums, we get the XOR of the single numbers
        int a_xor_b = 0;
        for (int num : nums) {
            a_xor_b ^= num;
        }

        // Compute the lowest order bit of a_xor_b.
        int leading_one = ((a_xor_b & (a_xor_b - 1)) ^ a_xor_b);

        // The lowest order bit is the first bit where a differs from b.
        // We can partition nums by whether this bit is set to separate a and b.
        vector<int> res(2);
        for (int num: nums) {
            if (num & leading_one) {
                res[0] ^= num;
            } else {
                res[1] ^= num;
            }
        }
        return res;
    }
};

int main(int argc, char* argv[])
{
    Solution s;
    vector<int> nums { 1, 1, 2, 2, 3, 3, 4, 5 };
    vector<int> res = s.singleNumber( nums );
    std::cout << res[0] << " " << res[1] << std::endl;

    return 0;
}
