#!/usr/bin/env cppsh
#include <utility>
#include <vector>
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>
#include <queue>
#include <string>
#include <iostream>

using namespace std;
using namespace boost;

class Solution {
public:
    typedef pair<int, string> node;
    typedef priority_queue<node, vector<node>, greater<node> > min_heap;

    /**
    Collect paths leading up to word.
    
    \param word - the current node
    \param pred - the list of predecessors associated with a node
    \param partial - the current working path
    \param res - the list of finalized paths
    */
    void paths(const string& word, const unordered_map<string, set<string> >& pred,
        vector<string>* partial, vector<vector<string> >* res)
    {
        partial->push_back(word);
        if (!pred.count(word)) {
            res->push_back(*partial);
            partial->pop_back();
            return;
        }
        for (auto& it : pred.find(word)->second) {
            paths(it, pred, partial, res);
        }
        partial->pop_back();
    }

    /**
    Find all shortest paths from beginWord to endWord.
    */
    vector<vector<string>> findLadders(string beginWord, string endWord, unordered_set<string> &wordDict) {
        vector<vector<string> > res;
        unordered_set<string> visited;
        unordered_map<string, set<string> > pred;
        unordered_map<string, int > dist;
        int maxDist = 0;
        min_heap q;
        if (beginWord == endWord) {
            res.push_back(vector<string>(1, endWord));
            return res;
        }
        
        q.push(node(1, beginWord));
        while (!q.empty()) {
            node n = q.top();
            string& word = n.second;
            q.pop();
            if (visited.count(word))
                continue;
            visited.insert(word);

            // collect all paths
            if (word == endWord) {
                //cout << "found. collect results..." << endl;
                //debug(pred);
                vector<string> partial;
                paths(endWord, pred, &partial, &res);

                return res;
            }
            for (int i = 0; i < word.size(); ++i) {
                for (int j = 0; j < 26; ++j) {
                    string nextWord(word);
                    int nextDist = n.first + 1;
                    nextWord[i] = 'a' + j;
                    
                    if (nextWord == endWord && !maxDist)
                        maxDist = nextDist;
                    if (visited.count(nextWord) || !wordDict.count(nextWord))
                        continue;
                    if (!dist.count(nextWord))
                        dist[nextWord] = nextDist;
                    if (nextDist > dist[nextWord] || (maxDist && nextDist > maxDist))
                        continue;

                    pred[nextWord].insert(word);
                    q.push(node(nextDist, nextWord));
                }
            }
        }
        return res;
    }
    
    void debug(const unordered_map<string, set<string> >& pred) {
        for (auto& it : pred) {
            cout << it.first << ": ";
            for (auto& it2 : it.second) {
                cout << it2 << " ";
            }
            cout << endl;
        }
    }
};

int main(int argc, char* argv[])
{
    Solution soln;
    //string begin = "aaa";
    //string end = "bbb";
    //unordered_set<string> dict { "aaa", "baa", "aab", "bab", "bbb" };
    string begin = "qa";
    string end = "sq";
    unordered_set<string> dict { "si","go","se","cm","so","ph","mt","db","mb","sb","kr","ln","tm","le","av","sm","ar","ci","ca","br","ti","ba","to","ra","fa","yo","ow","sn","ya","cr","po","fe","ho","ma","re","or","rn","au","ur","rh","sr","tc","lt","lo","as","fr","nb","yb","if","pb","ge","th","pm","rb","sh","co","ga","li","ha","hz","no","bi","di","hi","qa","pi","os","uh","wm","an","me","mo","na","la","st","er","sc","ne","mn","mi","am","ex","pt","io","be","fm","ta","tb","ni","mr","pa","he","lr","sq","ye" };
    vector<vector<string> > res = soln.findLadders(begin, end, dict);
    for (int i = 0; i < res.size(); ++i) {
        cout << (i+1) << ": ";
        for (int j = 0; j < res[i].size(); ++j) {
            cout << "'" << res[i][j] << "'";
            if (j < res[i].size()-1)
                cout << " ";
        }
        cout << endl;
    }

    return 0;
}
