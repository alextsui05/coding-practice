#!/usr/bin/env cppsh
#include <iostream>
#include <cstdlib>
#include <deque>

using namespace std;

class Solution {
public:
    int nthUglyNumber(int n) {
        deque<int> q[3];
        int factors[3] = { 2, 3, 5 };
        for (int i = 0; i < 3; ++i)
            q[i].push_back(factors[i]);
        int res = 1;
        for (int i = 1; i < n; ++i) {
            int tmp = res;
            res = min(q[0].front(), min(q[1].front(), q[2].front()));
            for (int j = 0; j < 3; ++j)
                if (q[j].front() == res)
                    q[j].pop_front();
            if (tmp != res) {
                for (int j = 0; j < 3; ++j)
                    q[j].push_back(factors[j] * res);
            }
        }
        return res;
    }
};

int main(int argc, char * argv[])
{
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " n" << std::endl;
        return 0;
    }
    Solution s;
    std::cout << s.nthUglyNumber(atoi(argv[1])) << std::endl;

    return 0;
}
