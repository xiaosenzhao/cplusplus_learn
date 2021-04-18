/**
 * 输入某二叉树的前序遍历和中序遍历的结果，请重建该二叉树。假设输入的前序遍历和中序遍历的结果中都不含重复的数字。

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
    TreeNode* do_build_tree(vector<int>& preorder, int pstart, int pend,
            vector<int>& inorder, int istart, int iend) {
        if (pstart > pend || istart > iend) {
            return nullptr;
        }
        //root
        TreeNode* root = new TreeNode(preorder[pstart]);
        if (pstart == pend) {
            if (istart == iend && preorder[pstart] == inorder[istart]) {
                return root;
            } else {
                return nullptr;
            }
        }
        //left
        int iorder_root = istart;
        for (int i = istart; i <= iend; i++) {
            if (inorder[i] == preorder[pstart]) {
                iorder_root = i;
                break;
            }
        }
        if (inorder[iorder_root] != inorder[iend] &&
                iorder_root == iend) {
            return nullptr;
        }
        int left_length = iorder_root - istart;
        if (left_length > 0) {
            root->left = do_build_tree(preorder, pstart + 1, pstart + left_length,
                    inorder, istart, iorder_root - 1);
        }
        if (left_length < pend - pstart) {
            root->right = do_build_tree(preorder, pstart + left_length + 1, pend,
                    inorder, iorder_root + 1, iend);
        }
        return root;
    }

    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
       TreeNode* root = do_build_tree(preorder, 0, preorder.size(), inorder, 0, inorder.size());
        return root;       
    }
};
