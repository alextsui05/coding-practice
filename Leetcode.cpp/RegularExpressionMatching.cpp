#!/usr/bin/env cppsh
#include <string>
#include <iostream>
#include <utility>
#include <vector>
#include <sstream>

using namespace std;

class Solution {
    struct token : public pair<int, int> {
        typedef pair<int, int> base;
        
        token(): base() { }
        
        token(int a, int b): base(a, b)
        { }
        
        char is() const { return first; }
        int ip() const { return second; }
        void inc_is() { ++first; }
    };
    
public:
    bool isMatch(string s, string p) {
        p = preprocess(p);
        int is = 0;
        int ip = 0;
        vector<token> wildcards; // position of last .* token
        while (is < s.size()) {
            // handle wildcard token
            if (ip + 1 < p.size() && p[ip + 1] == '*') {
                wildcards.push_back(token(is, ip));
                ip += 2;
                continue;
            }
            
            // handle mismatch or incomplete match
            if (ip == p.size()
                || (p[ip] != '.' && s[is] != p[ip]))
            {
                // go back, consume one token from the previous wildcard
                while (wildcards.size()) {
                    is = wildcards.back().is();
                    ip = wildcards.back().ip();
                    wildcards.back().inc_is();
                    if (is == s.size()) {
                        wildcards.pop_back();
                        continue;
                    }
                    char tok = p[ip];
                    ip += 2;
                    if (tok != '.' && s[is] != tok) {
                        wildcards.pop_back();
                        continue;
                    }
                    // we're in business
                    ++is;
                    break;
                }
                
                // if we don't have wildcards to expand, we lose
                if (wildcards.empty())
                    return false;
                
                continue;
            }
            
            // at this point, we match a single token
            ++ip;
            ++is;
        }
        
        // consume remaining wildcards as empty matches
        while (ip + 1 < p.size() && p[ip + 1] == '*') {
            ip += 2;
        }
        return ip == p.size();
    }

private:
    string preprocess(const string& p) {
        stringstream ss;
        char wildcard = 0;
        int ip = 0;
        while (ip != p.size()) {
            if (ip+1 < p.size() && p[ip+1] == '*') {
                if (wildcard != p[ip]) {
                    ss << p[ip] << p[ip+1];
                }
                wildcard = p[ip];
                ip += 2;
            } else {
                ss << p[ip];
                ++ip;
                wildcard = 0;
            }
        }
        return ss.str();
    }
};


int main(int argc, char* argv[])
{
    Solution s;
    cout << s.isMatch("aab", "c*a*b") << "\n";
    if (argc > 2) {
        cout << s.isMatch(argv[1], argv[2]) << "\n";
    }
    return 0;
}
