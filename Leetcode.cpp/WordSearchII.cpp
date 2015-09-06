#!/usr/bin/env cppsh
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <boost/unordered_set.hpp>
using namespace std;
using namespace boost;

class TrieNode {
    TrieNode *child[26];
    bool m_here;

public:
    // Initialize your data structure here.
    TrieNode(): m_here(false) {
        fill(child, child + 26, nullptr);
    }

    TrieNode* operator[](char ch) const {
        return child[ch - 'a'];
    }

    TrieNode*& operator[](char ch) {
        return child[ch - 'a'];
    }

    bool here() const {
        return m_here;
    }

    bool& here() {
        return m_here;
    }
};

class Trie {
public:
    Trie() {
        root = new TrieNode();
    }

    // Inserts a word into the trie.
    void insert(const string& word) {
        TrieNode* it = root;
        for (char ch : word) {
            if (!(*it)[ch]) {
                (*it)[ch] = new TrieNode();
            }
            it = (*it)[ch];
        }
        it->here() = true;
    }

    // Returns if the word is in the trie.
    bool search(const string& word) {
        TrieNode* it = root;
        for (char ch : word) {
            it = (*it)[ch];
            if (!it)
                break;
        }
        return (it && it->here());
    }

    // Returns if there is any word in the trie
    // that starts with the given prefix.
    bool startsWith(const string& prefix) {
        TrieNode* it = root;
        for (char ch : prefix) {
            it = (*it)[ch];
            if (!it)
                break;
        }
        return it;
    }

private:
    TrieNode* root;
};

class Solution {
    void check(int r, int c, vector<vector<char> >& board, Trie& trie, vector<char>& prefix,
        set<string>* res) {
        char save = board[r][c];
        prefix.push_back(save);
        int pos = prefix.size();
        //std::cout << "checking for " << word << " at " << r << ", " << c << "(" << pos << ")"<< "..." << std::endl;

        // quick exit if no candidates to find
        string pref(prefix.begin(), prefix.end());
        //std::cout << "prefix: " << pref << std::endl;
        //std::cout << "quick exit" << std::endl;
        if (!trie.startsWith(pref)) {
            prefix.pop_back();
            return;
        }
        if (trie.search(pref))
            res->insert(pref);

        board[r][c] = '#';
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                if (r + i < 0 || r + i >= board.size())
                    continue;
                if (c + j < 0 || c + j >= board[0].size())
                    continue;
                //if (i == 0 && j == 0)
                //    continue;
                if (i != 0 && j != 0)
                    continue;
                if (board[r + i][c + j] == '#')
                    continue;

                check(r + i, c + j, board, trie, prefix, res);
            }
        }
        board[r][c] = save;
        prefix.pop_back();
    }

public:

    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        Trie trie;
        for (string& str : words)
            trie.insert(str);
        int R = board.size();
        if (!R) return vector<string>();
        int C = board[0].size();
        if (!C) return vector<string>();

        set<string> res;
        vector<char> prefix;
        for (int r = 0; r < R; ++r) {
            for (int c = 0; c < C; ++c) {
                check(r, c, board, trie, prefix, &res);
            }
        }
        return vector<string>(res.begin(), res.end());
    }
};

int main(int argc, char* argv[])
{
    std::cout << argv[0] << std::endl;
    vector<vector<char> > board {
        { 'o', 'a', 'a', 'n' },
        { 'e', 't', 'a', 'e' },
        { 'i', 'h', 'k', 'r' },
        { 'i', 'f', 'l', 'v' }
    };
    vector<string> strs = {
        "oath",
        "pea",
        "eat",
        "rain"
    };
    Solution soln;
    vector<string> res = soln.findWords(board, strs);
    for (auto& str: res) {
        std::cout << str << std::endl;
    }

    return 0;
}
