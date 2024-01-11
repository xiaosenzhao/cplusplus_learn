/*
 * @lc app=leetcode.cn id=637 lang=cpp
 *
 * [637] 二叉树的层平均值
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
    vector<double> averageOfLevels(TreeNode* root) {
        std::vector<double> ans;
        if (root == nullptr) {
            return ans;
        }
        
        std::queue<TreeNode*> queue;
        queue.push(root);
        while (!queue.empty()) {
            int count = queue.size();
            double sum = 0.0f;
            for (int i = 0; i < count; ++i) {
                TreeNode* node = queue.front();
                queue.pop();
                sum += node->val;
                if (node->left != nullptr) {
                    queue.push(node->left);
                }
                if (node->right != nullptr) {
                    queue.push(node->right);
                }
            }
            ans.emplace_back(sum / count);
        }
        return ans;
    }
};
// @lc code=end

