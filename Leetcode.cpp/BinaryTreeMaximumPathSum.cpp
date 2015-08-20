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
public:
    int maxPathSum(TreeNode* root) {
        if (!root) return 0;
        
        map<TreeNode*, int> best_path; // best path rooted with root
        return maxPathSum(root, best_path);
    }
    
    int maxPathSum(TreeNode* root, map<TreeNode*, int>& best_path)
    {
        if (!root->left && !root->right) {
            best_path[root] = root->val;
            return root->val;
        }
        
        vector<int> possible;
        if (root->left)
            possible.push_back(maxPathSum(root->left, best_path));
        if (root->right)
            possible.push_back(maxPathSum(root->right, best_path));
        int branch[2] = {
            (root->left)? max(best_path[root->left], 0) : 0,
            (root->right)? max(best_path[root->right], 0) : 0
        };
        possible.push_back(root->val + branch[0] + branch[1]);
        int ans = *max_element(possible.begin(), possible.end());

        // save max sum of path with root as the root node
        best_path[root] = root->val;
        if (root->left) best_path[root] = max(best_path[root],
            root->val + best_path[root->left]);
        if (root->right) best_path[root] = max(best_path[root],
            root->val + best_path[root->right]);

        return ans;
    }
};