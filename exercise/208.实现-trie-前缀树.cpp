/*
 * @lc app=leetcode.cn id=208 lang=cpp
 *
 * [208] 实现 Trie (前缀树)
 */

// @lc code=start
class TrieNode {
public:
    TrieNode* childNode[26];
    bool isVal;
    TrieNode() : isVal(false) {
        for (int i = 0; i < 26; ++i) {
            childNode[i] = nullptr;
        }
    }
};

class Trie {
private:
    TrieNode* root;
public:
    Trie() : root(new TrieNode()){
    }
    
    void insert(string word) {
        TrieNode* tmp = root;
        for (int i = 0; i < word.size(); ++i) {
            if (tmp->childNode[word[i] - 'a'] == nullptr) {
                tmp->childNode[word[i] - 'a'] = new TrieNode();
            }
            tmp = tmp->childNode[word[i] - 'a'];
        }
        tmp->isVal = true;
    }
    
    bool search(string word) {
        TrieNode* tmp = root;
        for (int i = 0; i < word.size(); ++i) {
            if (tmp == nullptr) {
                break;
            }
            tmp = tmp->childNode[word[i] - 'a'];
        }
        return tmp == nullptr ? false : tmp->isVal;
    }
    
    bool startsWith(string prefix) {
        TrieNode* tmp = root;
        for (int i = 0; i < prefix.size(); ++i) {
            if (tmp == nullptr) {
                break;
            }
            tmp = tmp->childNode[prefix[i] - 'a'];
        }
        return tmp != nullptr;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */
// @lc code=end

