/*
 * @lc app=leetcode.cn id=543 lang=cpp
 *
 * [543] 二叉树的直径
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
    int diameterOfBinaryTree(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }
        int result = 0;
        helper(root, result);
        return result;
    }

    int helper(TreeNode* root, int& result) {
        if (root == nullptr) {
            return 0;
        }
        int left = helper(root->left, result);
        int right = helper(root->right, result);
        result = std::max(result, left + right);
        return std::max(left, right) + 1;
    }
};
// @lc code=end

