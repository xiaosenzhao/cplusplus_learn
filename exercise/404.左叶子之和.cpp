/*
 * @lc app=leetcode.cn id=404 lang=cpp
 *
 * [404] 左叶子之和
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
    int sumOfLeftLeaves(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }
        int sum = 0;
        dfs(root, sum);
        return sum;
    }

    void dfs(TreeNode* root, int& sum) {
        if (root == nullptr) {
            return;
        }
        if (root->left != nullptr) {
            if (root->left->left == nullptr && root->left->right == nullptr) {
                sum += root->left->val;
            } else {
                dfs(root->left, sum);
            }
        }
        if (root->right != nullptr) {
            dfs(root->right, sum);
        }
    }
};
// @lc code=end

