#include <string>
#include <vector>
#include <iostream>
#include <queue>

using namespace std;

vector<string> split(const string& s, const string& delim) {
    vector<string> result;
    if (s.size() == 0) {
        return result;
    }
    size_t last = 0;
    size_t index = s.find(delim, last);
    while (index != std::string::npos) {
        result.push_back(s.substr(last, index - last));
        last = index + 1;
        index = s.find(delim, last);
    }
    if (last < s.size() - 1 ) {
        result.push_back(s.substr(last, s.size() - last));
    }
    return result;
}

void do_print_tree(TreeNode* root, string& prefix) {
    if (root == nullptr) {
        cout << prefix << "null" << endl;
        return;
    }

    cout << prefix << root->val << endl;

    prefix.append("-");
    if (root->left != nullptr) {
        do_print_tree(root->left, prefix);
    }
    if (root->right != nullptr) {
        do_print_tree(root->right, prefix);
    }
    prefix.pop_back();
}

void print_tree(TreeNode* root) {
    if (root == nullptr) {
        cout << "empty tree" << endl;
        return;
    }

    string prefix = "-";
    do_print_tree(root, prefix);
}

