#include <iostream>

class Node {
public:
    int val;
    Node* left;
    Node* right;

    Node() {}

    Node(int _val) {
        val = _val;
        left = NULL;
        right = NULL;
    }

    Node(int _val, Node* _left, Node* _right) {
        val = _val;
        left = _left;
        right = _right;
    }
};

class Solution {
public:
    Node* treeToDoublyList(Node* root) {
        if (root == nullptr) {
            return nullptr;
        }

        Node* lastone = nullptr;
        convert(root, &lastone);

        Node* phead = lastone;
        while (phead != nullptr && phead->left != nullptr) {
            phead = phead->left;
        }
        return phead;
    }

    void convert(Node* root, Node** lastone) {
        if (root == nullptr) {
            return;
        }
        std::cout << "debug " << root->val << std::endl;
        Node* current = root;

        if (current->left != nullptr) {
            convert(current->left, lastone);
        }
        if (lastone != nullptr && *lastone != nullptr) {
            (*lastone)->right = current;
        }
        current->left = *lastone;
        *lastone = current;
        if (current->right != nullptr) {
            convert(current->right, lastone);
        }
    }
};

int main(void) {
    Node one(1);
    Node two(2);
    Node three(3);
    Node four(4);
    Node five(5);

    four.left = &two;
    four.right = &five;
    two.left = &one;
    two.right = &three;

    Solution solution;
    Node* head = solution.treeToDoublyList(&four);
    while (head != nullptr) {
        std::cout << head->val <<std::endl;
        head = head->right;
    }

    return 0;
}
