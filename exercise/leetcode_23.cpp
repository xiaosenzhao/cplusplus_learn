#include <vector>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
  ListNode* mergeKLists(vector<ListNode*>& lists) {
    if (lists.empty()) {
      return nullptr;
    }
    return merge(lists, 0, lists.size() - 1);
  }

  ListNode* merge(vector<ListNode*>& lists, size_t start, size_t end) {
    if (start == end) {
      return lists[start];
    }
    if (start > end) {
      return nullptr;
    }
    size_t mid = (start + end) >> 1;
    return merge2(merge(lists, start, mid), merge(lists, mid + 1, end));
  }

  ListNode* merge2(ListNode* left, ListNode* right) {
    if (left == nullptr || right == nullptr) {
      return left == nullptr ? right : left;
    }

    ListNode head;
    ListNode* tail = &head;
    ListNode* a = left;
    ListNode* b = right;

    while (a != nullptr && b!= nullptr) {
      if (a->val < b->val) {
        tail->next = a;
        a = a->next;
      } else {
        tail->next = b;
        b = b->next;
      }
      tail = tail->next;
    }

    tail->next = (a == nullptr ? b : a);
    return head.next;
  }
};
