#!/usr/bin/env cppsh
#include <string>
#include <iostream>
#include <boost/unordered_set.hpp>

using namespace std;
using namespace boost;

/**
Determine if a string can be segmented into words in a dictionary.
*/
class Solution {
public:
    bool wordBreak(string s, unordered_set<string>& wordDict) {
        int N = s.size();
        bool dp[N + 1];
        fill( dp, dp + N + 1, false );
        dp[0] = true;
        for (int i = 1; i <= N; ++i) {
            for (int k = 0; k < i; ++k) {
                string word = s.substr(k, i - k);
                //bool isWord = wordDict.count(word);
                //if (isWord)
                //    std::cout << word << " is  a wrd" << std::endl;
                dp[i] |= wordDict.count(word) && dp[i - (i - k)];
            }
        }
        return dp[N];
    }

};

int main(int argc, char * argv[])
{
    unordered_set<string> in { "cat", "cats", "and", "sand", "dog" };
    Solution s;
    bool res = s.wordBreak( "catsanddog", in );
    std::cout << res << std::endl;

    return 0;
}
