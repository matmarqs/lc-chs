struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

/***************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define DEFINE_QUEUE(type, name)                                                        \
typedef struct Node {                                                                   \
    type data;                                                                          \
    struct Node *next;                                                                  \
} Node;                                                                                 \
                                                                                        \
typedef struct {                                                                        \
    Node *head;                                                                         \
    Node *tail;                                                                         \
    int size;                                                                           \
} Queue;                                                                                \
                                                                                        \
static Node *name##_create_node(type data) {                                            \
    Node *node = (Node *)malloc(sizeof(Node));                                          \
    if (!node) {                                                                        \
        fprintf(stderr, "Memory allocation failed\n");                                  \
        exit(EXIT_FAILURE);                                                             \
    }                                                                                   \
    node->data = data;                                                                  \
    node->next = NULL;                                                                  \
    return node;                                                                        \
}                                                                                       \
                                                                                        \
Queue *name##_init() {                                                                  \
    Queue *q = (Queue *)malloc(sizeof(Queue));                                          \
    if (!q) {                                                                           \
        fprintf(stderr, "Memory allocation failed\n");                                  \
        exit(EXIT_FAILURE);                                                             \
    }                                                                                   \
    q->head = NULL;                                                                     \
    q->tail = NULL;                                                                     \
    q->size = 0;                                                                        \
    return q;                                                                           \
}                                                                                       \
                                                                                        \
int name##_is_empty(Queue *q) {                                                         \
    return q->size == 0;                                                                \
}                                                                                       \
                                                                                        \
type name##_peek(Queue *q) {                                                            \
    if (name##_is_empty(q)) {                                                           \
        fprintf(stderr, "Queue is empty, cannot peek\n");                               \
        exit(EXIT_FAILURE);                                                             \
    }                                                                                   \
    return q->head->data;                                                               \
}                                                                                       \
                                                                                        \
int name##_size(Queue *q) {                                                             \
    return q->size;                                                                     \
}                                                                                       \
                                                                                        \
type name##_dequeue(Queue *q) {                                                         \
    if (name##_is_empty(q)) {                                                           \
        fprintf(stderr, "Queue is empty, cannot dequeue\n");                            \
        exit(EXIT_FAILURE);                                                             \
    }                                                                                   \
    type data = q->head->data;                                                          \
    Node *old_head = q->head;                                                           \
    q->head = q->head->next;                                                            \
    free(old_head);                                                                     \
    q->size--;                                                                          \
    if (q->size == 0) {                                                                 \
        q->tail = NULL;                                                                 \
    }                                                                                   \
    return data;                                                                        \
}                                                                                       \
                                                                                        \
void name##_enqueue(Queue *q, type data) {                                              \
    Node *new_node = name##_create_node(data);                                          \
    if (name##_is_empty(q)) {                                                           \
        q->head = new_node;                                                             \
        q->tail = new_node;                                                             \
    } else {                                                                            \
        q->tail->next = new_node;                                                       \
        q->tail = new_node;                                                             \
    }                                                                                   \
    q->size++;                                                                          \
}                                                                                       \
                                                                                        \
void name##_free(Queue *q) {                                                            \
    while (q->head) {                                                                   \
        Node *current = q->head;                                                        \
        q->head = q->head->next;                                                        \
        free(current);                                                                  \
    }                                                                                   \
    free(q);                                                                            \
}


DEFINE_QUEUE(struct TreeNode *, queue);

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
int minDepth(struct TreeNode *root) {
    if (!root)
        return 0;

    Queue *q = queue_init();

    queue_enqueue(q, root);
    int level = 1;

    while (!queue_is_empty(q)) {
        int nodes_in_level = queue_size(q);
        
        for (int i = 0; i < nodes_in_level; i++) {
            struct TreeNode *n = queue_dequeue(q);

            // Check if it's a leaf node
            if (!n->left && !n->right) {
                queue_free(q);
                return level;
            }

            if (n->left)
                queue_enqueue(q, n->left);
            if (n->right)
                queue_enqueue(q, n->right);
        }
        level++;
    }

    // Should never reach here if tree is valid
    queue_free(q);
    return level;
}
