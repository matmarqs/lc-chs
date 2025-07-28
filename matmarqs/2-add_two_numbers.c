/* Definition for singly-linked list. */
struct ListNode {
    int val;
    struct ListNode *next;
};

/************************************************/

#include <stdlib.h>

struct ListNode* createListNode() {
    struct ListNode* l = (struct ListNode *) malloc(sizeof(struct ListNode));
    l->val = 0;
    l->next = NULL;
    return l;
}

struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
    int overflow = 0;
    struct ListNode *root = createListNode();
    struct ListNode *l = root;
    while (l1 || l2 || overflow) {
        int add;
        if (l1 && l2) {
            add = (l1->val + l2->val + overflow) % 10;
            overflow = (l1->val + l2->val + overflow) / 10;
        }
        else if (l1) {
            add = (l1->val + overflow) % 10;
            overflow = (l1->val + overflow) / 10;
        }
        else if (l2) {
            add = (l2->val + overflow) % 10;
            overflow = (l2->val + overflow) / 10;
        }
        else {  /* only overflow: l1 == NULL && l2 == NULL */
            add = overflow;
            overflow = 0;
        }
        l1 = l1 ? l1->next : NULL;
        l2 = l2 ? l2->next : NULL;
        l->val = add;
        l->next = (l1 || l2 || overflow) ? createListNode() : NULL;
        l = l->next;
    }
    return root;
}
