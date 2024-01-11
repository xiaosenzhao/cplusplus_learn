/*
 * @lc app=leetcode.cn id=99 lang=cpp
 *
 * [99] 恢复二叉搜索树
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
    void recoverTree(TreeNode* root) {
        if (root == nullptr) {
            return;
        }
        TreeNode* mistake1 = nullptr;
        TreeNode* mistake2 = nullptr;
        TreeNode* pre = nullptr;
        inorder(root, mistake1, mistake2, pre);
        if (mistake1 != nullptr && mistake2 != nullptr) {
            int tmp = mistake1->val;
            mistake1->val = mistake2->val;
            mistake2->val = tmp;
        }
    }

    void inorder(TreeNode* root, TreeNode*& mistake1, TreeNode*& mistake2, TreeNode*& pre) {
        if (root == nullptr) {
            return;
        }
        if (root->left != nullptr) {
            inorder(root->left, mistake1, mistake2, pre);
        }
        if (pre != nullptr && root->val < pre->val) {
            if (mistake1 == nullptr) {
                mistake1 = pre;
                mistake2 = root;
            } else {
                mistake2 = root;
            }
        }
        pre = root;
        if (root->right != nullptr) {
            inorder(root->right, mistake1, mistake2, pre);
        }
    }
};
// @lc code=end

