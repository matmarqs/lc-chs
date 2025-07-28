#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>

#define DEFINE_QUEUE(name, prefix, type) \
    \
    typedef struct prefix##_Node { \
        type data; \
        struct prefix##_Node *next; \
    } prefix##_Node; \
    \
    typedef struct { \
        prefix##_Node *head; \
        prefix##_Node *tail; \
        int size; \
    } name; \
    \
    static prefix##_Node *prefix##_create_node(type data) { \
        prefix##_Node *node = (prefix##_Node*)malloc(sizeof(prefix##_Node)); \
        node->data = data; \
        node->next = NULL; \
        return node; \
    } \
    \
    name *prefix##_create() { \
        name *q = (name*)malloc(sizeof(name)); \
        q->head = NULL; \
        q->tail = NULL; \
        q->size = 0; \
        return q; \
    } \
    \
    int prefix##_is_empty(name *q) { \
        return q->size == 0; \
    } \
    \
    type prefix##_peek(name *q) { \
        return q->head->data; \
    } \
    \
    int prefix##_size(name *q) { \
        return q->size; \
    } \
    \
    type prefix##_dequeue(name *q) { \
        type data = q->head->data; \
        prefix##_Node *old_head = q->head; \
        q->head = q->head->next; \
        free(old_head); \
        q->size--; \
        if (q->size == 0) { \
            q->tail = NULL; \
        } \
        return data; \
    } \
    \
    void prefix##_enqueue(name *q, type data) { \
        prefix##_Node *new_node = prefix##_create_node(data); \
        if (prefix##_is_empty(q)) { \
            q->head = new_node; \
            q->tail = new_node; \
        } else { \
            q->tail->next = new_node; \
            q->tail = new_node; \
        } \
        q->size++; \
    } \
    \
    void prefix##_free(name *q) { \
        while (q->head) { \
            prefix##_Node *current = q->head; \
            q->head = q->head->next; \
            free(current); \
        } \
        free(q); \
    }

#endif // QUEUE_H
