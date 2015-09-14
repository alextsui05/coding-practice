#!/usr/bin/env cppsh
#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    /**
    Returns the h-index given a sorted list of citations.
    \see HIndex.cpp
    */
    int hIndex(vector<int>& citations) {
        int N = citations.size();
        if (!N || citations[N-1] == 0)
            return 0;
        if (citations[0] >= N)
            return N;
        int l = 1;
        int r = citations.size();
        while (r > l) {
            int h = (r + l)/2;
            int i = N - h;
            if (citations[i] >= h && citations[i-1] > h)
                l = h + 1;
            else
                r = h;
        }
        return l;
    }
};

int main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " num1 num2 ..." << std::endl;
        std::cout << "Note: Input should be sorted" << std::endl;
        return 1;
    }

    vector<int> vi;
    for (int i = 1; i < argc; ++i) {
        vi.push_back(atoi(argv[i]));
    }
    Solution s;
    std::cout << s.hIndex(vi) << "\n";

    return 0;
}
