#!/usr/bin/env cppsh
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <cassert>
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>
using namespace std;
using namespace boost;

class Solution {
public:
    vector<int> countBits(int num) {
        vector<int> res(num + 1);
        for (int i = 0; i <= num; ++i) {
            res[i] = __builtin_popcount(i);
        }
        return res;
    }
};

class Solution2 {
public:
    vector<int> countBits(int num) {
        vector<int> res(num + 1);
        for (int i = 0; i <= num; ++i) {
            int count = 0;
            for (int j = 0; j < sizeof(int); ++j) {
                if (i & (1 << j))
                    ++count;
            }
            res[i] = count;
        }
        return res;
    }
};

class Solution3 {
public:

    /**
    Return a vector of ints where the i-th entry gives the number of 1's in the
    binary representation of i.

    The approach uses memoization. Suppose i has the binary representation

        i = (b_n, b_{n-1}, ..., b_1, b_0).

    Let C(i) denote the number of 1 bits in the binary representation of i, and
    let r be the number with the binary representation given by the n-1 highest
    order bits in i. That is,

        r = (b_{n}, ..., b_1).

    Then, C(i) is given by the recurrence

        C(0) = 0
        C(1) = 1
        C(i) = C(r)         if b_0 is 0
             = 1 + C(r)     otherwise

    In this approach, we iterate from i = 0...n, computing and caching C(i).
    The space complexity is O(n) and the time complexity is O(n).
    */
    vector<int> countBits(int num) {
        vector<int> res;
        unordered_map<int, int> counts;
        counts[0] = 0;
        counts[1] = 1;
        res.push_back(0);
        if (num > 0)
            res.push_back(1);
        for (int i = 2; i <= num; ++i) {
            unsigned int lo = (i % 2);
            counts[i] = 0;
            if ( i & lo )
                counts[i] += 1;
            counts[i] += counts[(i >> 1)];
            res.push_back(counts[i]);
        }
        return res;
    }
};

class Solution4 {
public:

    /**
    Return a vector of ints where the i-th entry gives the number of 1's in the
    binary representation of i.

    The approach uses memoization. Suppose i has the binary representation

        i = (b_n, b_{n-1}, ..., b_0).

    Let C(i) denote the number of 1 bits in the binary representation of i, and
    let r be the number with the binary representation given by the n-1 lowest
    order bits in i. That is,

        r = (b_{n-1}, ..., b_0).

    Then, C(i) is given by the recurrence

        C(0) = 0
        C(1) = 1
        C(i) = C(r)         if b_n is 0
        C(i) = 1 + C(r)     otherwise

    In this approach, we iterate from i = 0...n, computing and caching C(i).
    The space complexity is O(n) and the time complexity depends on our ability
    to check the highest order bit, which we can do in O(1) for a fixed-width
    integer. So the time complexity is O(n).
    */
    vector<int> countBits(int num) {
        vector<int> res;
        unordered_map<int, int> counts;
        counts[0] = 0;
        counts[1] = 1;
        res.push_back(0);
        res.push_back(1);
        for (int i = 2; i <= num; ++i) {
            unsigned int hi = hibit(i);
            counts[i] = 0;
            if ( i & hibit(i) )
                counts[i] += 1;
            counts[i] += counts[(i & (hi - 1))];
            res.push_back(counts[i]);
        }
        return res;
    }

    int hibit(unsigned int n) {
        n |= (n >>  1);
        n |= (n >>  2);
        n |= (n >>  4);
        n |= (n >>  8);
        n |= (n >> 16);
        return n - (n >> 1);
    }
};

int main(int argc, char* argv[])
{
    Solution3 soln;
    vector<int> exp {0,1,1,2,1,2};
    vector<int> res = soln.countBits(5);
    assert(exp.size() == res.size());
    for (int i = 0; i < res.size(); ++i) {
        assert(exp[i] == res[i]);
    }

    return 0;
}
