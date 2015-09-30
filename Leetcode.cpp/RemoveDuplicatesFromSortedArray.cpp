#!/usr/bin/env cppsh
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <iterator>
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>
using namespace std;
using namespace boost;

class Solution {
public:
    /**
    Return an array of unique elements.

    The approach is to swap each first occurrence of a value to the front.

    \param[in] nums - a sorted array of ints
    \return N - number of unique elements
    \post - nums[0:N] contains the unique elements
    */
    int removeDuplicates(vector<int>& nums) {
        if (nums.size() == 0)
            return 0;
        int front = 0;
        int i = 0;
        while (i < nums.size()) {
            int val = nums[i];
            swap(nums[front], nums[i]);
            ++i;
            while (i < nums.size() && nums[i] == val) {
                ++i;
            }
            ++front;
        }
        return front;
    }
};

int main(int argc, char* argv[])
{
    // read a list of sorted ints from stdin
    vector<int> nums;
    copy(istream_iterator<int>(cin), istream_iterator<int>(),
        back_inserter(nums));

    // remove duplicates
    Solution soln;
    int size = soln.removeDuplicates(nums);

    // print the output array
    for (int i = 0; i < size; ++i) {
        std::cout << nums[i];
        if (i + 1 < size)
            std::cout << ' ';
    }
    std::cout << std::endl;

    return 0;
}
