#!/usr/bin/env cppsh
#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>

using namespace std;
typedef pair<int, int> cell;
typedef pair<cell, cell> cell_pair;

struct PublicTransit {
    /**
    Return the longest distance between any two cells, assuming a pair of
    teleporters is optimally placed.
    */
    int minimumLongestDistance(int R, int C) {
        int res = 100;
        for (auto& tp : pairs(R, C)) {
            auto& c1 = tp.first;
            auto& c2 = tp.second;
            //std::cout << c1.first
            //    << ' ' << c1.second
            //    << ' ' << c2.first
            //    << ' ' << c2.second
            //    << std::endl;
            int maxDist = 0;
            for (auto& cp : pairs(R, C)) {
                auto& a = cp.first;
                auto& b = cp.second;
                int dist = md(a, b);
                dist = min(dist, md(a, c1) + md(c2, b));
                dist = min(dist, md(a, c2) + md(c1, b));
                maxDist = max(maxDist, dist);
            }
            res = min(res, maxDist);
        }
        return res;
    }

    int md(const cell& a, const cell& b) {
        return abs(a.first - b.first) + abs(a.second - b.second);
    }

    vector<cell> cells(int R, int C) {
        vector<cell> res;
        for (int i = 0; i < R; ++i)
        for (int j = 0; j < C; ++j)
            res.push_back(cell(i, j));
        return res;
    }

    vector<cell_pair> pairs(int R, int C) {
        vector<cell> a(cells(R, C));
        vector<cell> b(cells(R, C));
        vector<cell_pair> res;
        for (auto& c1 : a)
        for (auto& c2 : b)
            res.push_back(cell_pair(c1, c2));
        return res;
    }

};

int main(int argc, char* argv[])
{
    PublicTransit pt;
    vector<pair<int, int> > inputs {
       { 4, 1 },
       { 2, 2 },
       { 5, 3 },
       { 8, 2 }
    };
    for ( int i = 0; i < inputs.size(); ++i ) {
        auto& sz = inputs[i];
        int ans = pt.minimumLongestDistance(sz.first, sz.second);
        std::cout << "Case #" << (i+1) << ": " << ans << std::endl;
    }
    return 0;
}
