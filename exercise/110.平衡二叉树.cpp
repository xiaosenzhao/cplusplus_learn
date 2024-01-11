/*
 * @lc app=leetcode.cn id=110 lang=cpp
 *
 * [110] 平衡二叉树
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
    bool isBalanced(TreeNode* root) {
        if (root == nullptr) {
            return true;
        }

        return helper(root) != -1;
    }

    int helper(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }
        int left_depth = helper(root->left);
        int right_depth = helper(root->right);
        if (left_depth == -1 || right_depth == -1 || std::abs(left_depth - right_depth) > 1) {
            return -1;
        }
        return std::max(left_depth, right_depth) + 1;
    }
};
// @lc code=end

