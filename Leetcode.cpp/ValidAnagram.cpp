#!/usr/bin/env cppsh
#include <iostream>
#include <boost/unordered_map.hpp>
#include <utility>
#include <vector>
using namespace std;
using namespace boost;

class Solution {
public:
    /**
    Return whether \a s is an anagram of \a t.
    */
    bool isAnagram(string s, string t) {
        unordered_map<int, int> b[2];
        for (auto& ch : s) {
            b[0][ch]++;
        }
        for (auto& ch : t) {
            b[1][ch]++;
        }
        return b[0] == b[1];
    }
};

int main(int argc, char const* argv[])
{
    Solution soln;
    vector<pair<string, string> > in {
        { "anagram", "nagaram" },
        { "rat", "car" }
    };
    vector<bool> out {
        true,
        false
    };
    for (int i = 0; i < in.size(); ++i) {
        std::cout << "Case #" << (i+1) << ": " << soln.isAnagram(in[i].first, in[i].second) << std::endl;
    }
    return 0;
}
