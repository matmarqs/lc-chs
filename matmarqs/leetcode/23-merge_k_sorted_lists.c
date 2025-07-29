struct ListNode {
    int val;
    struct ListNode *next;
};

/**************************/

#include <stdlib.h> /* NULL */

struct ListNode* mergeTwoLists(struct ListNode* list1, struct ListNode* list2);

struct ListNode* mergeKLists(struct ListNode** lists, int listsSize) {
    if (listsSize == 0) {
        return NULL;
    }
    while (listsSize > 1) {
        int newListsSize = 0;
        for (int i = 0; i + 1 < listsSize; i += 2) {
            lists[newListsSize++] = mergeTwoLists(lists[i], lists[i+1]);
        }
        if (listsSize % 2 == 1) {
            lists[newListsSize++] = lists[listsSize - 1];
        }
        listsSize = newListsSize;
    }
    return lists[0];
}

struct ListNode* mergeTwoLists(struct ListNode* list1, struct ListNode* list2) {
    if (list1 == NULL) {
        return list2;
    }
    if (list2 == NULL) {
        return list1;
    }
    struct ListNode* root;
    if (list1->val < list2->val) {
        root = list1;
        list1 = list1->next;
    } else {
        root = list2;
        list2 = list2->next;
    }
    struct ListNode* node = root;
    while (list1 && list2) {
        if (list1->val < list2->val) {
            node->next = list1;
            list1 = list1->next;
        } else {
            node->next = list2;
            list2 = list2->next;
        }
        node = node->next;
    }
    if (list1) {
        node->next = list1;
    } else {
        node->next = list2;
    }
    return root;
}
