#!/usr/bin/env cppsh

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
class PrivateD2party {

public:
    int getsz(vector<int> a) {
        vector<int> comps = connectedComponents(a);
        //std::copy(comps.begin(), comps.end(),
        //    std::ostream_iterator<int>(std::cout, " "));
        //std::cout << std::endl;
        int numComps = *std::max_element(comps.begin(), comps.end()) + 1;
        std::vector<int> reps(numComps);
        std::vector<int> compSize(numComps);
        for (int i = 0; i < numComps; ++i) {
            int rep = -1;
            for (int j = 0; j < a.size(); ++j) {
                if (comps[j] == i) {
                    rep = j;
                    if (a[j] == j) {
                        break;
                    }
                }
            }
            reps[i] = rep;
            compSize[i] = std::count_if(a.begin(), a.end(), [&](int x) { return comps[x] == i; });
            //std::cout << "comp size " << i << " : " << compSize[i] << std::endl;
        }

        int ans = 0;
        for (int i = 0; i < reps.size(); ++i) {
            if (a[reps[i]] == reps[i]) {
                ans += compSize[i];
            } else {
                ans += compSize[i] - 1;
            }
        }

        return ans;
    }

    vector<int> connectedComponents(const vector<int>& a) {
        std::vector<int> comp(a.size(), -1);
        int nextCompId = 0;
        for (int i = 0; i < a.size(); ++i) {
            std::set<int> seen;
            int node = i;
            while (!seen.count(node) && comp[node] == -1) {
                seen.insert(node);
                node = a[node];
            }
            if (comp[node] == -1) {
                comp[node] = nextCompId++;
            }
            for (auto v : seen) {
                comp[v] = comp[node];
            }
        }

        return comp;
    }
};

int main(int argc, char *argv[]) {
    PrivateD2party soln;
    std::vector<int> in;
    if (argc > 1) {
        for (int i = 1; i < argc; ++i) {
            in.push_back(atoi(argv[i]));
        }
        std::cout << soln.getsz(in) << std::endl;
    } else {
        vector<string> vs {
            "0 1",
            "1 0",
            "1 0 3 2",
            "5 2 2 4 5 0",
            "3 2 1 0 5 4"
        };
        vector<int> exp { 2, 1, 2, 5, 3 };
        for (int i = 0; i < vs.size(); ++i) {
            stringstream ss(vs[i]);
            in.clear();
            std::copy(istream_iterator<int>(ss), istream_iterator<int>(),
                back_inserter(in));
            std::cout << "Case #" << (i+1) << ": " << soln.getsz(in) << std::endl;
        }
    }
}
