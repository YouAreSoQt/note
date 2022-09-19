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
    ListNode* deleteDuplicates(ListNode* head) {
        if (!head) return nullptr;
        ListNode dummy(0, head);
        ListNode *p = &dummy;
        while (p->next && p->next->next) {
            const auto x = p->next->val;
            if (x != p->next->next->val) {
                p = p->next;
            } else {
                while (p->next && p->next->val == x) {
                    auto next = p->next->next;
                    delete p->next;
                    p->next = next;
                }
            }
        }
        return dummy.next;
    }
};