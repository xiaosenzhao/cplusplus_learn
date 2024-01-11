/*
 * @lc app=leetcode.cn id=1110 lang=cpp
 *
 * [1110] 删点成林
 */

// @lc code=start
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    vector<TreeNode*> delNodes(TreeNode* root, vector<int>& to_delete) {
        std::vector<TreeNode*> ans;
        if (root == nullptr) {
            return ans;
        }
        std::unordered_set<int> to_delete_set;
        for (int val : to_delete) {
            to_delete_set.emplace(val);
        }
        root = run(root, to_delete_set, ans);
        if (root != nullptr) {
            ans.emplace_back(root);
        }
        return ans;
    }

    TreeNode* run(TreeNode* root, const std::unordered_set<int> to_delete_set, std::vector<TreeNode*>& ans) {
        if (root == nullptr) {
            return nullptr;
        }
        root->left = run(root->left, to_delete_set, ans);
        root->right = run(root->right, to_delete_set, ans);
        if (to_delete_set.find(root->val) != to_delete_set.end()) {
            if (root->left != nullptr) {
                ans.emplace_back(root->left);
            }
            if (root->right != nullptr) {
                ans.emplace_back(root->right);
            }
           root = nullptr;
        }
        return root;
    } 
    
};
// @lc code=end

