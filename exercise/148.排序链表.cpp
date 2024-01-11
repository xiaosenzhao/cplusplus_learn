/*
 * @lc app=leetcode.cn id=148 lang=cpp
 *
 * [148] 排序链表
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
    ListNode* sortList(ListNode* head) {
        if (head == nullptr) {
            return head;
        }
        return sortList(head, nullptr);
    }

    ListNode* sortList(ListNode* head, ListNode* tail) {
        if (head == nullptr) {
            return nullptr;
        }
        if (head->next == tail) {
            head->next = nullptr;
            return head;
        }
        ListNode* fast = head;
        ListNode* slow = head;
        while (fast != tail) {
            slow = slow->next;
            fast = fast->next;
            if (fast != tail) {
                fast = fast->next;
            }
        }
        return merge(sortList(head, slow), sortList(slow, tail));
    }

    ListNode* merge(ListNode* head1, ListNode* head2) {
        if (head1 == nullptr) {
            return head2;
        }
        if (head2 == nullptr) {
            return head1;
        }
        ListNode* tmp_node = new ListNode();
        ListNode* tmp = tmp_node;
        ListNode* tmp1 = head1;
        ListNode* tmp2 = head2;
        while (tmp1 != nullptr && tmp2 != nullptr) {
            if (tmp1->val <= tmp2->val) {
                tmp->next = tmp1;
                tmp1 = tmp1->next;
            } else {
                tmp->next = tmp2;
                tmp2 = tmp2->next;
            }
            tmp = tmp->next;
        }
        if (tmp1 != nullptr) {
            tmp->next = tmp1;
        } else if (tmp2 != nullptr) {
            tmp->next = tmp2;
        }
        ListNode* ret_head = tmp_node->next;
        delete tmp_node;
        return ret_head;
    }
};
// @lc code=end

