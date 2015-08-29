#!/usr/bin/env cppsh
#include <utility>
#include <vector>
#include <boost/unordered_set.hpp>
using namespace std;
using namespace boost;

struct point : pair<int, int> {
    typedef pair<int, int> base;
    point(int x, int y): base(x, y) { }
};

namespace std {
template <>
struct hash<point> {
size_t operator()(const point& pt) const {
    size_t res = pt.first;
    res = 180811 * res + pt.second;
    return res;
}
};
}

class Solution {
public:
    void solve(vector<vector<char>>& board) {
        unordered_set<point> visited;
        int R = board.size();
        if (!R) return;
        int C = board[0].size();
        if (!C || R < 3 || C < 3) return;
        visit_borders(board, R, C, &visited);
        for (int i = 0; i < R; ++i)
        for (int j = 0; j < C; ++j)
            if (!visited.count(point(i, j)))
                board[i][j] = 'X';
    }

private:
    void visit_borders(vector<vector<char>>& board, int R, int C,
        unordered_set<point>* visited) {
        deque<point> q;
        for (int i = 0; i < R; ++i) {
            if (board[i][0] == 'O')
                q.push_back(point(i, 0));
            if (board[i][C-1] == 'O')
                q.push_back(point(i, C-1));
        }
        for (int i = 0; i < C; ++i) {
            if (board[0][i] == 'O')
                q.push_back(point(0, i));
            if (board[R-1][i] == 'O')
                q.push_back(point(R-1, i));
        }
        while (!q.empty()) {
            point p = q.front(); q.pop_front();
            if (visited->count(p))
                continue;
            visited->insert(p);
            for (int i = -1; i <= 1; ++i)
            for (int j = -1; j <= 1; ++j) {
                int r = p.first + i;
                int c = p.second + j;
                if (r < 0 || r >= R || c < 0 || c >= C
                    || (i && j) || (!i && !j)
                    || visited->count(point(r, c))
                    || board[r][c] == 'X') {
                        continue;
                }
                q.push_back(point(r, c));
            }
        }
    }
};

int main(int argc, char* argv[])
{
    Solution s;
    vector<vector<char> > in {
        { 'O', 'X', 'O' },
        { 'X', 'O', 'X' },
        { 'O', 'X', 'O' }
    };
    s.solve(in);
    for (auto& it: in) {
        for (auto& it2: it) {
            std::cout << it2;
        }
        std::cout << std::endl;
    }

    return 0;
}
