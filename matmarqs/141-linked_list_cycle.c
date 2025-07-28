#include <stdbool.h>

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

/* below we have a cheating solution */

#define PASSED 900000

bool hasCycle_Cheating(struct ListNode *head) {
    if (!head) {
        return false;
    }
    head->val = PASSED;
    head = head->next;
    while (head) {
        if (head->val == PASSED)
            return true;
        head->val = PASSED;
        head = head->next;
    }
    return false;
}

/* Tortoise vs Rabbit algorithm */
/* Two pointers, one runs faster than the other */
/* if they match at some time, it is because there is a cycle */
bool hasCycle(struct ListNode *head) {
    struct ListNode *slow = head;
    struct ListNode *fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (fast == slow) {
            return true;
        }
    }
    return false;
}
