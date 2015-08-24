#!/usr/bin/env cppsh
#include <string>
#include <iostream>
#include <boost/unordered_set.hpp>
#include <vector>

using namespace std;
using namespace boost;

/**
Determine all ways string can be segmented into words in a dictionary.

Uses DP to determine word breaks. A particular string has a word break if
it can be broken into a prefix-suffix pair where

    1. suffix is a word and
    2. the prefix has a word break.

For each word discovered, record a backlink to the word in the position just
one-beyond the end of the word. We use backtracking to gather all word breaks
efficiently.
*/
class Solution {
public:
    vector<string> wordBreak(string s, unordered_set<string>& wordDict) {
        int N = s.size();
        bool dp[N + 1];
        fill( dp, dp + N + 1, false );
        vector<vector<int> > pred(N + 1);
        dp[0] = true;
        for (int i = 1; i <= N; ++i) {
            for (int k = 0; k < i; ++k) {
                string word = s.substr(k, i - k);
                bool isWord = wordDict.count(word);
                dp[i] |= isWord && dp[i - (i - k)];
                if (isWord) {
                    pred[i].push_back(k);
                }
            }
        }

        vector<string> partial;
        vector<string> res;
        collect( s, dp, N + 1, pred, N, partial, &res );

        return res;
    }

    void collect( const string& blob, bool* dp, int dp_len,
        vector<vector<int> >& pred, int pos,
        vector<string>& partial,
        vector<string>* res ) {
        if ( pos == 0 ) {
            stringstream ss;
            for (int i = partial.size() - 1; i >= 0; --i) {
                ss << partial[i];
                if (i != 0)
                    ss << ' ';
            }
            res->push_back(ss.str());
            return;
        }

        for ( int start : pred[pos] ) {
            if ( !dp[ start ] )
                continue;
            string word = blob.substr( start, pos - start );
            partial.push_back(word);
            collect( blob, dp, dp_len, pred,
                start, partial, res );
            partial.pop_back();
        }
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
