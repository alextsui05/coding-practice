#!/usr/bin/env cppsh
#include <vector>
#include <map>
#include <list>
#include <iostream>

struct TreeNode {
    int val;
    TreeNode* left, *right;
    TreeNode(int x): val(x), left(NULL), right(NULL) {}

};

using namespace std;

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
    typedef pair<int, int> xy;

    // dp[l][r] == all BSTs with values ranging from l to r
    map<xy, list<TreeNode> > dp;

    TreeNode* clone(TreeNode* root) {
        if (!root)
            return NULL;

        TreeNode* copy = new TreeNode(root->val);
        copy->left = clone(root->left);
        copy->right = clone(root->right);
        return copy;
    }

public:
    vector<TreeNode*> generateTrees(int n) {
        if (n == 0)
            return vector<TreeNode*>(1);

        vector<TreeNode*> res;

        list<TreeNode>& trees = getTrees(1, n);
        for (TreeNode& tree : trees) {
            res.push_back(clone(&tree));
        }

        return res;
    }

    // recursive memoized lookup into dp table
    list<TreeNode>& getTrees(int l, int r)
    {
        // check if memoized result is available
        xy p(l, r);
        if (dp.count(p))
            return dp[p];

        // generate and memoize result
        list<TreeNode>& res = dp[p];

        if (l == r) { // base case: singleton tree
            res.push_back(TreeNode(l));
            return res;
        }

        for (int i = l; i <= r; ++i) {
            list<TreeNode>* lefts = NULL;
            list<TreeNode>* rights = NULL;
            if (i > l) {
                xy o(l, max(i-1, l));
                lefts = &getTrees(o.first, o.second);
            }
            if (i < r) {
                xy o(min(i+1, r), r);
                rights = &getTrees(o.first, o.second);
            }
            if (lefts && rights) {
                // for all pairs of (left, right), make a tree
                list<TreeNode>::iterator lit = lefts->begin();
                for (; lit != lefts->end(); ++lit) {
                    list<TreeNode>::iterator rit = rights->begin();
                    for (; rit != rights->end(); ++rit) {
                        TreeNode* left = &*lit;
                        TreeNode* right = &*rit;
                        TreeNode tree(i);
                        tree.left = left;
                        tree.right = right;
                        res.push_back(tree);
                    }
                }
            } else { // either lefts or rights is NULL
                list<TreeNode>::iterator it = lefts?
                    lefts->begin() : rights->begin();
                list<TreeNode>::iterator it_end = lefts?
                    lefts->end() : rights->end();
                for ( ; it != it_end; ++it ) {
                    TreeNode tree(i);
                    TreeNode* child = &*it;
                    if (lefts) {
                        tree.left = child;
                    } else {
                        tree.right = child;
                    }
                    res.push_back(tree);
                }
            }
        } // for

        return res;
    } // getTrees
}; // Solution


void print(TreeNode* tree) {
    if (!tree) return;
    print(tree->left);
    std::cout << tree->val << " ";
    print(tree->right);
}

int main(int argc, char* argv[])
{
    if (argc < 2)
        std::cout << "Usage: " << argv[0] << " n" << std::endl;

    Solution sol;
    vector<TreeNode*> trees = sol.generateTrees(atoi(argv[1]));
    for (TreeNode* tree : trees) {
        print(tree);
        std::cout << "(" << tree->val << ")";
        std::cout << std::endl;
    }

    return 0;
}
