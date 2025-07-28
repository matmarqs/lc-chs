struct ListNode {
    int val;
    struct ListNode *next;
};

/**************************************************/

#include <stdlib.h>

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* reverseList(struct ListNode* head) {
    struct ListNode *current = NULL;
    struct ListNode *previous = NULL;
    // struct ListNode *node = (struct ListNode *node) malloc(sizeof(struct ListNode));
    while (head) {
        current = (struct ListNode *) malloc(sizeof(struct ListNode));
        current->val = head->val;
        current->next = previous;
        previous = current;
        head = head->next;
    }
    return current;
}
