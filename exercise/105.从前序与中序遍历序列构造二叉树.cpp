/*
 * @lc app=leetcode.cn id=105 lang=cpp
 *
 * [105] 从前序与中序遍历序列构造二叉树
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
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        if (preorder.empty() || inorder.empty() || preorder.size() != inorder.size()) {
            return nullptr;
        }
        std::unordered_map<int, int> inorder_dic;
        for (int i = 0; i < inorder.size(); ++i) {
            inorder_dic[inorder[i]] = i;
        }
        return build(preorder, inorder_dic, 0, preorder.size() - 1, 0, inorder.size() - 1);
    }

    TreeNode* build(const std::vector<int>& preorder, const std::unordered_map<int, int>& inorder_dic, int preorder_start, int preorder_end, int inorder_start, int inorder_end) {
        if (preorder_start > preorder_end) {
            return nullptr;
        }
        int root_val = preorder[preorder_start];
        int inorder_root_index = inorder_dic.at(root_val);
        int left_size = inorder_root_index - inorder_start;
        int right_size = inorder_end - inorder_root_index;
        TreeNode* root = new TreeNode(root_val);
        root->left = build(preorder, inorder_dic, preorder_start + 1, preorder_start + left_size, inorder_start, inorder_root_index - 1);
        root->right = build(preorder, inorder_dic, preorder_start + left_size + 1, preorder_end, inorder_root_index + 1, inorder_end);
        return root;
    }
};
// @lc code=end

