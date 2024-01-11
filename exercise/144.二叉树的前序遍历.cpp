/*
 * @lc app=leetcode.cn id=144 lang=cpp
 *
 * [144] 二叉树的前序遍历
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
    vector<int> preorderTraversal(TreeNode* root) {
        std::vector<int> ans;
        if (root == nullptr) {
            return ans;
        }
        preorder(root, ans);
        return ans;
    }
    void preorder(TreeNode* root, std::vector<int>& ans) {
        if (root == nullptr) {
            return;
        }
        ans.emplace_back(root->val);
        preorder(root->left, ans);
        preorder(root->right, ans);
    }
};
// @lc code=end

