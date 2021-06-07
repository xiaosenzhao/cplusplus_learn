#include <string>
#include <vector>
#include <iostream>
#include <queue>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

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

string serialize(TreeNode* root) {
    std::string serialize_str = "";
    if (root == nullptr) {
        return serialize_str;
    }
    std::queue<TreeNode*> queue;
    queue.push(root);
    while (!queue.empty()) {
        TreeNode* node = queue.front();
        queue.pop();
        if (node == nullptr) {
            serialize_str += "$";
            serialize_str += ",";
        } else {
            serialize_str += (to_string(node->val) + ",");
            queue.push(node->left);
            queue.push(node->right);
        }
    }
    serialize_str.pop_back();
    return serialize_str;
}

// Decodes your encoded data to tree.
TreeNode* deserialize(string data) {
    if (data.size() == 0) {
        return nullptr;
    }
    TreeNode* root = nullptr;
    vector<string> vec = split(data, ",");
    if (vec.size() == 0) {
        return nullptr;
    }
    int index = 1;
    root = new TreeNode(stoi(vec[0]));
    std::queue<TreeNode*> queue;
    queue.push(root);

    while (!queue.empty() && index < vec.size()) {
        TreeNode* node = queue.front();
        queue.pop();
        if (index <vec.size() && vec[index] != "$") {
            TreeNode* left = new TreeNode(stoi(vec[index]));
            node->left = left;
            queue.push(left);
        }
        index += 1;
        if (index < vec.size() && vec[index] != "$") {
            TreeNode* right = new TreeNode(stoi(vec[index]));
            node->right = right;
            queue.push(right);
        }
        index += 1;
    }
    return root;
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

int main(void) {
    TreeNode one(1);
    TreeNode two(2);
    TreeNode three(3);
    TreeNode four(4);
    TreeNode five(5);

    one.left = &two;
    one.right = &three;
    three.left = &four;
    three.right = &five;

    string s = serialize(&one);
    cout << s << endl;

    TreeNode* root = deserialize(s);
    print_tree(root);
    return 0;
}

