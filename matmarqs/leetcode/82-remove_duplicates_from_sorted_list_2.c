struct ListNode {
    int val;
    struct ListNode *next;
};

/*********************************************************/

struct ListNode* deleteDuplicates(struct ListNode* head) {
    if (!head || !head->next) {
        return head;
    }

    // Use a dummy node to simplify edge cases (when head itself is a duplicate)
    struct ListNode dummy;
    dummy.next = head;
    struct ListNode *prev = &dummy;
    struct ListNode *curr = head;

    while (curr) {
        // Skip all duplicates for the current node
        if (curr->next && curr->val == curr->next->val) {
            int duplicate_val = curr->val;
            while (curr && curr->val == duplicate_val) {
                curr = curr->next;
            }
            prev->next = curr; // Skip all duplicates
        } else {
            // No duplicates, move both pointers forward
            prev = curr;
            curr = curr->next;
        }
    }

    return dummy.next;
}
