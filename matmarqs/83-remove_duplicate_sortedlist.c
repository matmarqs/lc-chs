struct ListNode {
    int val;
    struct ListNode *next;
};

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

struct ListNode* deleteDuplicates(struct ListNode* head) {
    struct ListNode *node = head;
    while (node && node->next) {
        if (node->val == node->next->val) {
            node->next = node->next->next;
        }
        else {
            node = node->next;
        }
    }
    return head;
}
