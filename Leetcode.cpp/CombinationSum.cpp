#!/usr/bin/env cppsh
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;

class Solution {

public:
    /**
    Compute all unique combinations of candidates that add up to target.

    Candidates can be repeatedly select.

    Combinations are monotonically increasing.
    */
    vector<vector<int> > combinationSum(vector<int>& candidates, int target) {
        vector<vector<int> > res;
        sort(candidates.begin(), candidates.end());
        map<int, int> counts;
        generateCombinations(candidates, candidates.size(), &counts, target, &res);

        return res;
    }

private:
    void generateCombinations(const vector<int>& candidates, int candidates_end,
        map<int, int>* counts, int target,
        vector<vector<int> >* res) {
        if (target < 0) return;

        if (target == 0 && counts->size()) {
            vector<int> combo;
            for (auto& it : *counts) {
                for (int i = 0; i < it.second; ++i)
                    combo.push_back(it.first);
            }
            res->push_back(combo);
            return;
        }

        for (int i = candidates_end - 1; i >= 0; --i) {
            if (candidates[i] > target)
                continue;
            int times = target / candidates[i];
            for (int j = 0; j < times; ++j) {
                (*counts)[ candidates[i] ] += 1;
                generateCombinations( candidates, i,
                    counts,
                    target - candidates[i] * (*counts)[ candidates[i] ],
                    res );
            }
            if (times)
                counts->erase( candidates[i] );
        }
    }
};

int main(int argc, char* argv[])
{
    Solution s;
    vector<int> candidates
        //{ 2, 3, 6, 7 }
    { 1, 5, 10, 25 }
    ;
    int target =
        226
    ;
    vector<vector<int> > res = s.combinationSum( candidates, target );
    for (auto& combo : res ) {
        for (auto& val : combo ) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
