/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if (!head) return head;
        ListNode* it[2] = {
            head,
            head->next
        };
        while (it[0]) {
            while (it[1] && it[1]->val == it[0]->val) {
                it[1] = it[1]->next;
            }
            it[0]->next = it[1];
            it[0] = it[1];
            if (it[0]) {
                it[1] = it[0]->next;
            }
        }

        return head;
    }
};
