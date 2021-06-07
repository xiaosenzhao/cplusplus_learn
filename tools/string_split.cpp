#include <string>
#include <vector>
#include <iostream>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

string do_serialize(TreeNode* root, std::string& serialize_str) {
    if (root == nullptr) {
        serialize_str.append("$");
        serialize_str.append(",");
        cout << serialize_str << endl;
        return serialize_str;
    }

    serialize_str.append(std::to_string(root->val));
    serialize_str.append(",");

    do_serialize(root->left, serialize_str);
    do_serialize(root->right, serialize_str);

    return serialize_str;
}

TreeNode* do_deserialize(vector<std::string> vec, int& index) {
    if (index < 0 || index > vec.size() - 1) {
        return nullptr;
    }
    TreeNode* root = nullptr;
    if (vec[index] == "$") {
        root = nullptr;
    } else {
        int num = std::stoi(vec[index]);
        root = new TreeNode(num);
        index += 1;
        root->left = do_deserialize(vec, index);
        index += 1;
        root->right = do_deserialize(vec, index);
    }
    return root;
}

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
    do_serialize(root, serialize_str);
    serialize_str.pop_back();
    return serialize_str;
}

TreeNode* deserialize(string data) {
    TreeNode* root = nullptr;
    vector<string> vec = split(data, ",");
    int index = 0;
    return do_deserialize(vec, index);
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

