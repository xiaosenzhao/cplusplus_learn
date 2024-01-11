/*
 * @lc app=leetcode.cn id=328 lang=cpp
 *
 * [328] 奇偶链表
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
    ListNode* oddEvenList(ListNode* head) {
        if (head == nullptr || head->next == nullptr) {
            return head;
        }
        ListNode* first = head;
        ListNode* second = head->next;
        ListNode* p = first;
        ListNode* s = second;
        while (s != nullptr && s->next != nullptr) {
            p->next = s->next;
            s->next = s->next->next;
            p = p->next;
            s = s->next;
        }
        p->next = second;
        return first;
    }
};
// @lc code=end

