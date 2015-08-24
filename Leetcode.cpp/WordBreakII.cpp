#!/usr/bin/env cppsh
#include <string>
#include <iostream>
#include <boost/unordered_set.hpp>
#include <vector>

using namespace std;
using namespace boost;

/**
Determine all ways string can be segmented into words in a dictionary.
*/
class Solution {
public:
    vector<string> wordBreak(string s, unordered_set<string>& wordDict) {
        int N = s.size();
        bool dp[N + 1];
        fill( dp, dp + N + 1, false );
        vector<vector<string> > data(N + 1);
        dp[0] = true;
        for (int i = 1; i <= N; ++i) {
            for (int k = 0; k < i; ++k) {
                string word = s.substr(k, i - k);
                bool isWord = wordDict.count(word);
                dp[i] |= isWord && dp[i - (i - k)];
                if (isWord) {
                    if (k == 0) {
                        data[i].push_back(word);
                    } else if (dp[i - (i - k)]) {
                        for (auto& it: data[i - (i - k)]) {
                            data[i].push_back(it + " " + word);
                        }
                    }
                }
                //bool isWord = wordDict.count(word);
                //if (isWord)
                //    std::cout << word << " is  a wrd" << std::endl;
            }
        }
        //return dp[N];
        return data[N];
    }

};

int main(int argc, char * argv[])
{
    unordered_set<string> in { "cat", "cats", "and", "sand", "dog" };
    Solution s;
    auto res = s.wordBreak( "catsanddog", in );
    for (string& str : res) {
        std::cout << str << std::endl;
    }

    return 0;
}
