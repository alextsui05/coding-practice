#!/usr/bin/env cppsh
#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Interval {
    int start;
    int end;
    Interval() : start(0), end(0) {}
    Interval(int s, int e) : start(s), end(e) {}
    bool operator< (const Interval& o) const {
        return (start < o.start) ||
            ((start == o.start) && (end < o.end));
    }
};

class Solution {
public:
    vector<Interval> merge(vector<Interval>& intervals) {
        vector<Interval> res;
        sort(intervals.begin( ), intervals.end( ));
        for (int i = 0; i < intervals.size(); ++i) {
            // take the largest interval starting at the current position
            Interval interval = intervals[i];
            int j = i + 1;
            while (j < intervals.size() &&
                intervals[j].start == interval.start) {
                ++j;
            }
            interval.end = intervals[j-1].end;
            // while there is an overlap with an interval with the next current
            // position
            while (j < intervals.size() &&
                intervals[j].start <= interval.end) {
                // merge the next interval with this interval
                int k = j + 1;
                while (k < intervals.size() &&
                    intervals[k].start == intervals[j].start) {
                    ++k;
                }
                interval.end = max(interval.end, intervals[k-1].end);
                j = k;
            }
            i = j-1;
            res.push_back(interval);
        }
        return res;
    }
};

Interval parseInterval(const string& str) {
    std::cout << str << std::endl;
    int i = 1;
    while (str[i] != ',')
        ++i;
    int j = i + 1;
    int k = j;
    while (str[k] != ']')
        ++k;
    int a = stol(str.substr(1, i - 1));
    int b = stol(str.substr(j, k - j));
    return Interval(a, b);
}

void loadIntervals(vector<Interval>* intervals) {
    string str;
    getline(cin, str);
    for (int i = 0; i < str.size(); ++i) {
        if (str[i] == ',')
            continue;
        int j = i + 1;
        while (j < str.size() && str[j++] != ']');
        Interval interval = parseInterval(str.substr(i, j - i));
        intervals->push_back(interval);
        i = j;
    }
}

int main(int argc, char const* argv[])
{
    if (argc > 1) {
        std::cout << "[1,3],[2,6],[8,10],[15,18],[15,12],[15,20]" << std::endl;
        return 0;
    }

    vector<Interval> intervals;
    loadIntervals(&intervals);
    for (auto& interval : intervals) {
        std::cout << interval.start << ", " << interval.end << std::endl;
    }
    Solution soln;
    vector<Interval> res = soln.merge(intervals);
    std::cout << "result: " << std::endl;
    for (auto& interval : res) {
        std::cout << interval.start << ", " << interval.end << std::endl;
    }

    std::cout << "hello, world!" << std::endl;
    return 0;
}
