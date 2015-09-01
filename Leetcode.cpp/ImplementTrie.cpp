#!/usr/bin/env cppsh
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

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
    void insert(string word) {
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
    bool search(string word) {
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
    bool startsWith(string prefix) {
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

int main(int argc, char* argv[])
{
// Your Trie object will be instantiated and called as such:
// Trie trie;
// trie.insert("somestring");
// trie.search("key");

    return 0;
}
