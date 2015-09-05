#!/usr/bin/env cppsh
#include <vector>
#include <string>
#include <iostream>
#include <boost/unordered_set.hpp>
using namespace std;
using namespace boost;

/**
DFS + backtracking, modifying the board to mark visited nodes.

32 ms
*/
class Solution {
    bool check(int r, int c, vector<vector<char> >& board, const string& word, int pos) {
            //std::cout << "checking for " << word << " at " << r << ", " << c << "(" << pos << ")"<< "..." << std::endl;
        if (board[r][c] != word[pos]) {
            std::cout << "failed at " << r << ", " << c << " : " << board[r][c] << " != " << word[pos]<< std::endl;
            return false;
        }
        if (pos + 1 == word.size()) {
            std::cout << "found" << std::endl;
            return true;
        }
        char save = board[r][c];
        board[r][c] = '#';
        //visited.insert(make_pair(r, c));

        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                if (r + i < 0 || r + i >= board.size())
                    continue;
                if (c + j < 0 || c + j >= board[0].size())
                    continue;
                if (i == 0 && j == 0)
                    continue;
                if (i != 0 && j != 0)
                    continue;
                //std::cout << "visiting " << (r + i) << ", " << (c + j) << std::endl;
                if (check(r + i, c + j, board, word, pos + 1))
                    return true;
            }
        }
        //visited.erase(make_pair(r, c));
        board[r][c] = save;
        return false;
    }

public:
    bool exist(vector<vector<char>>& board, string word) {
        int R = board.size();
        if (!R) return false;
        int C = board[0].size();
        if (!C) return false;
        for (int r = 0; r < R; ++r) {
            for (int c = 0; c < C; ++c) {
                if (check(r, c, board, word, 0))
                    return true;
            }
        }
        return false;
    }
};

/**
DFS + backtracking, not modifying the board but keeping a separate set of visited nodes.

256 ms with set
176 ms with unordered_set
*/
class SolutionWithHashtable {
    bool check(int r, int c, const vector<vector<char> >& board, const string& word, int pos, unordered_set<pair<int, int> >& visited) {
            //std::cout << "checking for " << word << " at " << r << ", " << c << "(" << pos << ")"<< "..." << std::endl;
        if (board[r][c] != word[pos]) {
            std::cout << "failed at " << r << ", " << c << " : " << board[r][c] << " != " << word[pos]<< std::endl;
            return false;
        }
        if (pos + 1 == word.size()) {
            std::cout << "found" << std::endl;
            return true;
        }
        visited.insert(make_pair(r, c));
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                if (r + i < 0 || r + i >= board.size())
                    continue;
                if (c + j < 0 || c + j >= board[0].size())
                    continue;
                if (i == 0 && j == 0)
                    continue;
                if (i != 0 && j != 0)
                    continue;
                if (visited.count(make_pair(r + i, c + j)))
                    continue;
                //std::cout << "visiting " << (r + i) << ", " << (c + j) << std::endl;
                if (check(r + i, c + j, board, word, pos + 1, visited))
                    return true;
            }
        }
        visited.erase(make_pair(r, c));
        return false;
    }

public:
    bool exist(vector<vector<char>>& board, string word) {
        int R = board.size();
        if (!R) return false;
        int C = board[0].size();
        if (!C) return false;
        for (int r = 0; r < R; ++r) {
            for (int c = 0; c < C; ++c) {
                unordered_set<pair<int, int> > visited;
                if (check(r, c, board, word, 0, visited))
                    return true;
            }
        }
        return false;
    }
};

int main(int argc, char* argv[])
{
    std::cout << argv[0] << std::endl;
    vector<vector<char> > board {
        { 'A', 'B', 'C', 'E' },
        { 'S', 'F', 'E', 'S' },
        { 'A', 'D', 'E', 'E' },
    };
    vector<string> strs = {
        //"ABCCED",
        //"SEE",
        //"ABCB"
        "ABCESEEEFS"
    };
    Solution soln;
    for (string s : strs) {
        bool res = soln.exist(board, s);
        std::cout << res << std::endl;
    }

    return 0;
}
