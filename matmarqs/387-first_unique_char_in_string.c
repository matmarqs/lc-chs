/* After a few submissions, this code beats 100% */

#include <stdlib.h>

typedef enum { in, not_in, ignore } state;

typedef struct Node {
    char c;
    int index;
    struct Node *next;
} Node;

Node *create_node(char c, int index) {
    Node *node = (Node *) malloc(sizeof(Node));
    node->c = c;
    node->index = index;
    node->next = NULL;
    return node;
}

typedef struct {
    Node *head;
    Node *tail;
    int size;
} Queue;

Queue *init_queue() {
    Queue *q = (Queue *) malloc(sizeof(Queue));
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

int peek(Queue *q) {
    return q->head->c;
}

int peek_index(Queue *q) {
    return q->head->index;
}

int is_empty(Queue *q) {
    return q->size == 0;
}

void dequeue(Queue *q) {
    if (is_empty(q)) {
        exit(1);    /* ERROR: queue is empty, cannot dequeue */
    }
    Node *old_head = q->head;
    q->head = q->head->next;
    free(old_head);
    q->size--;
}

void enqueue(Queue *q, char c, int index) {
    Node *new_tail = create_node(c, index);
    if (is_empty(q)) {
        q->head = new_tail;
        q->tail = new_tail;
    }
    else {
        q->tail->next = new_tail;
        q->tail = new_tail;
    }
    q->size++;
}

void free_queue(Queue *q) {
    while (q->head) {
        Node *current = q->head;
        q->head = q->head->next;
        free(current);
    }
    free(q);
}

int firstUniqChar(char* s) {
    Queue *q = init_queue();
    state in_queue[26];
    for (int i = 0; i < 26; i++) {
        in_queue[i] = not_in;
    }

    for (int i = 0; s[i] != '\0'; i++) {
        char ch = s[i];

        if (in_queue[ch - 'a'] == not_in) {
            enqueue(q, ch, i);
            in_queue[ch - 'a'] = in;
        }
        else if (in_queue[ch - 'a'] == in) {
            in_queue[ch - 'a'] = ignore;
        }
        while (!is_empty(q) && in_queue[peek(q) - 'a'] == ignore) {
            dequeue(q);
        }
    }

    int result = is_empty(q) ? -1 : peek_index(q);
    free_queue(q);
    return result;
}
