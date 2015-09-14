#!/usr/bin/env cppsh
#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    /**
    A researcher has h-index of h if h of her papers have been cited at least h
    times while the remainder has been cited at most h times.

    \param[in] citations - a list of a  researcher's citation counts. \a
    citations[i] gives the number of citations of paper i.
    \return the h-index for the researcher
    */
    int hIndex(vector<int>& citations) {
        int N = citations.size();
        vector<int> counts(N+1);
        for (auto cites : citations) {
            if (cites > N) counts[N]++;
            else counts[cites]++;
        }
        if (counts[N] == N)
            return N;
        for (int h = N-1; h >= 0; --h) {
            counts[h] += counts[h+1];
            if (counts[h] >= h)
                return h;
        }
        return 0;
    }
};

int main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " num1 num2 ..." << std::endl;
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
