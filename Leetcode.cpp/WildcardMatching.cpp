#!/usr/bin/env cppsh
#include <string>
#include <iostream>
using namespace std;

class Solution {
public:
    bool isMatch(string s, string p) {
        int is = 0;
        int ip = 0;
        bool wildcard = false;
        while (is < s.size()) {
            string token = grabToken(p, &ip, &wildcard);
            if (!match(s, token, &is, wildcard))
                return false;
        }

        if (is == s.size() && ip == p.size())
            return true;
        else if (ip < p.size()) {
            while (ip < p.size() && p[ip] == '*')
                ++ip;
            return ip == p.size();
        }
        return false;
    }

    bool match(const string& s, const string& token, int* is, bool wildcard) {
        cout << "match " << s << " to " << token << " from pos " << *is << endl;
        if (!wildcard) { // match token
            return matchOne(s, token, is);
        } else { // match token at all possible start positions
            bool matched = false;
            for (int start = *is; start < s.size(); ++start) {
                cout << "match " << s << " to " << token << " from pos " << start << endl;
                matched = matchOne(s, token, &start);
                if (matched) {
                    *is = start;
                    break;
                }
            }
            return matched;
        }
    }

    bool matchOne(const string& s, const string& token, int* is) {
        for (int i = 0; i < token.size(); ++i) {
            if (*is + i == s.size())
                return false;
            if (token[i] != '?' && s[*is + i] != token[i]) {
                cout << s[*is + i] << " doesn't match " << token[i] << endl;
                return false;
            }
        }
        *is += token.size();
        return true;
    }

    string grabToken(const string& p, int* ip, bool* wildcard) {
        if (p[*ip] == '*') {
            *wildcard = true;
            while (*ip < p.size() && p[*ip] == '*') {
                *ip += 1;
            }
        }
        if (*ip == p.size())
            return "";

        int start = *ip;
        while (*ip < p.size() && p[*ip] != '*') {
            *ip += 1;
        }
        return p.substr(start, *ip - start);
    }

};


int main(int argc, char* argv[])
{
    Solution s;
    cout << s.isMatch("abefcdgiescdfimde", "ab*cd?i*de") << "\n";
    return 0;
}
