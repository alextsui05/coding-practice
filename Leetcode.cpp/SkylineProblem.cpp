#!/usr/bin/env cppsh
#include <vector>
#include <utility>
#include <iostream>
#include <map>

using namespace std;

class Solution {

public:
    /**
    Build the skyline formed by input rectangles directly.
    */
    vector<pair<int, int> > getSkyline(vector<vector<int>>& buildings) {
        vector<pair<int, int> > res;
        map<int, int> skyline;
        for (auto& building : buildings) {
            int l = building[0];
            int r = building[1];
            int h = building[2];
            int prev_h = 0;
            //std::cout << "processing " << l << " " << r << " " << h << std::endl;
            auto it1 = skyline.lower_bound( l );
            if (it1 == skyline.end()) {
                // there are no event points behind us
                it1 = skyline.insert( it1, make_pair( l, h ) );
            } else if (it1->first > l) {
                if ( it1 == skyline.begin() ) {
                    it1 = skyline.insert( it1, make_pair( l, h ) );
                } else {
                    // we land between event points
                    auto it_prev = it1;
                    --it_prev;
                    prev_h = it_prev->second;
                    if (it_prev->second < h) {
                        it1 = skyline.insert( it1, make_pair( l, h ) );
                    } else {
                        it1 = it_prev;
                    }
                }
            } else { // we land on an event point; update it maybe
                if ( it1 == skyline.begin() ) {
                    prev_h = it1->second;
                    if ( it1->second < h )
                        it1->second = h;
                } else {
                    auto it_prev = it1;
                    --it_prev;
                    prev_h = it_prev->second;
                    if (prev_h == h && it1->second < h) {
                        skyline.erase(it1);
                        it1 = it_prev;
                    } else if ( it1->second < h ) {
                        it1->second = h;
                    }
                }
            }

            auto it2 = skyline.upper_bound( r );
            ++it1;
            while ( it1 != it2 ) {
                if ( it1->first == r )
                    break;
                if ( it1->second > h ) {
                    prev_h = it1->second;
                    ++it1;
                } else if ( it1->second <= h ) {
                    if ( prev_h > h ) {
                        prev_h = it1->second;
                        it1->second = h;
                        ++it1;
                    } else {
                        // we overshadow this event point
                        prev_h = it1->second;
                        auto tmp = it1;
                        ++tmp;
                        skyline.erase( it1 );
                        it1 = tmp;
                    }
                }
            }

            if ( it1 == skyline.end() ) { // this building's end is the new end
                it1 = skyline.insert( it1, make_pair( r, 0 ) );
            } else if ( it1->first > r ) {
                if ( h > prev_h )
                    it1 = skyline.insert( it1, make_pair( r, prev_h ) );
            }

            //std::cout << "now skyline is..." << std::endl;
            //for (auto& it : skyline ) {
            //    std::cout << it.first << " " << it.second << std::endl;
            //}
        }

        copy(skyline.begin(), skyline.end(), back_inserter(res));
        return res;
    }
};

int main(int argc, char* argv[])
{
    Solution s;
    vector<vector<int> > in
    //{ { 2, 9, 10 }, { 3, 7, 15 }, { 5, 12, 12 }, { 15, 20, 10 }, { 19, 24, 8 } };
    //{ { 1, 2, 1 }, {1, 2, 2}, {1, 2, 3} };
    //{ { 0, 2, 3 }, {2, 5, 3} };
    //{ { 2, 4, 7 }, {2, 4, 6} };
    //{{3,10,20},{3,9,19},{3,8,18}};
    {{0,5,7},{5,10,7},{5,10,12},{10,15,7},{15,20,7},{15,20,12},{20,25,7}};

    vector<pair<int, int> > res = s.getSkyline( in );
    for (auto& it : res)
        std::cout << it.first << " " << it.second << std::endl;

    return 0;
}

