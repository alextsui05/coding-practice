#!/usr/bin/env cppsh
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

void print(vector<int>& nums) {
    for (int i = 0; i < nums.size( ); ++i) {
        std::cout << nums[i];
        if (i < nums.size() - 1)
            std::cout << ' ';
    }
    std::cout << std::endl;
}

class Solution {
public:
    /**
    Move all zero elements to the end of the array in place.
    */
    void moveZeroes(vector<int>& nums) {
        int zi = 0;
        while (zi < nums.size() && nums[zi])
            ++zi;
        if (zi == nums.size())
            return;

        int i = zi + 1;
        while (i < nums.size()) {
            while (i < nums.size() && !nums[i])
                ++i;
            if (i < nums.size()) {
                swap(nums[zi], nums[i]);
                ++zi;
                ++i;
            }
            print(nums);
        }
    }
};

int main(int argc, char* argv[])
{
    vector<int> nums;
    int i;
    while (cin >> i) {
        nums.push_back(i);
    }
    Solution soln;
    soln.moveZeroes(nums);
    print(nums);

    return 0;
}
