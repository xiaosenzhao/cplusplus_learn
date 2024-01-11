/*
 * @lc app=leetcode.cn id=24 lang=cpp
 *
 * [24] 两两交换链表中的节点
 */

// @lc code=start
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        if (head == nullptr) {
            return head;
        }
        if (head->next == nullptr) {
            return head;
        }
        ListNode* p = head;
        ListNode* s = p->next;
        p->next = s->next;
        s->next = p;
        head = s;
        while (p->next != nullptr && p->next->next != nullptr) {
            s = p->next->next;
            p->next->next = s->next;
            s->next = p->next;
            p->next = s;
            p = s->next;
        }
        return head;
    }
};
// @lc code=end

