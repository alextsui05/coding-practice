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
    int length(ListNode* head) {
        int res = 0;
        while (head) {
            ++res;
            head = head->next;
        }
        return res;
    }
    
    ListNode* reverse(ListNode* head) {
        ListNode* tail = NULL;
        while (head) {
            ListNode* tmp = head->next;
            head->next = tail;
            tail = head;
            head = tmp;
        }
        return tail;
    }
    
    ListNode* advance(ListNode* head, int n) {
        while (n--) {
            head = head->next;
        }
        return head;
    }
    
    bool isPalindrome(ListNode* head) {
        int len = length(head);
        if (!head || len < 2)
            return true;
        ListNode* it1 = head;
        ListNode* it2 = (len % 2 == 0)? advance(head, len/2) : advance(head, len/2 + 1);
        it2 = reverse(it2);
        ListNode* save = it2;
        for (int i = 0; i < len/2; ++i) {
            if (it1->val == it2->val) {
                it1 = it1->next;
                it2 = it2->next;
            } else {
                reverse(save);
                return false;
            }
        }
        reverse(save);
        return true;
    }
};