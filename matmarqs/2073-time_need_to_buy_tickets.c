#include <stdbool.h>

/*******************************************************************************/

// Circular buffer implementation

#include <stdlib.h>
#include <string.h>

#define DEFINE_QUEUE(name, prefix, type) \
    \
    typedef struct { \
        type *buffer;     /* Contiguous memory block */ \
        int capacity;     /* Total allocated capacity */ \
        int size;         /* Current number of elements */ \
        int head;         /* Index of first element */ \
        int tail;         /* Index where next element will be added */ \
    } name; \
    \
    static void prefix##_resize(name *q) { \
        int new_capacity = q->capacity * 2; \
        type *new_buffer = (type *)malloc(new_capacity * sizeof(type)); \
        \
        /* Copy elements in order */ \
        if (q->head < q->tail) { \
            memcpy(new_buffer, q->buffer + q->head, q->size * sizeof(type)); \
        } else { \
            int part1 = q->capacity - q->head; \
            memcpy(new_buffer, q->buffer + q->head, part1 * sizeof(type)); \
            memcpy(new_buffer + part1, q->buffer, q->tail * sizeof(type)); \
        } \
        \
        free(q->buffer); \
        q->buffer = new_buffer; \
        q->head = 0; \
        q->tail = q->size; \
        q->capacity = new_capacity; \
    } \
    \
    name *prefix##_create(int initial_capacity) { \
        name *q = (name *)malloc(sizeof(name)); \
        q->buffer = (type *)malloc(initial_capacity * sizeof(type)); \
        q->capacity = initial_capacity; \
        q->size = 0; \
        q->head = 0; \
        q->tail = 0; \
        return q; \
    } \
    \
    void prefix##_free(name *q) { \
        free(q->buffer); \
        free(q); \
    } \
    \
    bool prefix##_is_empty(name *q) { \
        return q->size == 0; \
    } \
    \
    bool prefix##_is_full(name *q) { \
        return q->size == q->capacity; \
    } \
    \
    type prefix##_peek(name *q) { \
        return q->buffer[q->head]; \
    } \
    \
    int prefix##_size(name *q) { \
        return q->size; \
    } \
    \
    type prefix##_dequeue(name *q) { \
        type data = q->buffer[q->head]; \
        q->head = (q->head + 1) % q->capacity; \
        q->size--; \
        return data; \
    } \
    \
    void prefix##_enqueue(name *q, type data) { \
        if (prefix##_is_full(q)) { \
            prefix##_resize(q); \
        } \
        q->buffer[q->tail] = data; \
        q->tail = (q->tail + 1) % q->capacity; \
        q->size++; \
    } \
    \
    void prefix##_clear(name *q) { \
        q->head = 0; \
        q->tail = 0; \
        q->size = 0; \
    } \
    \
    int prefix##_capacity(name *q) { \
        return q->capacity; \
    }

typedef struct {
    int index;
    int num_tickets;
} Person;

DEFINE_QUEUE(Queue, queue, Person);

int timeRequiredToBuy_Queue(int* tickets, int ticketsSize, int k) {
    Queue *q = queue_create(ticketsSize);
    for (int i = 0; i < ticketsSize; i++) {
        queue_enqueue(q, (Person) {i, tickets[i]});
    }

    bool done = false;
    int time = 0;

    while (!done) {
        Person person = queue_dequeue(q);
        if (person.index == k && person.num_tickets == 1) {
            done = true;
        }
        else if (person.num_tickets == 1) {
            ;
        }
        else {
            person.num_tickets--;
            queue_enqueue(q, person);
        }
        time++;
    }

    queue_free(q);
    return time;
}

int min(int a, int b) {
    return a < b ? a : b;
}

int timeRequiredToBuy(int* tickets, int ticketsSize, int k) {
    int time = 0;
    for (int i = 0; i < ticketsSize; i++) {
        if (i <= k) {
            time += min(tickets[i], tickets[k]);    /* kth person has to wait min(tickets[i], tickets[k]) for people in front of him */
        }
        else {
            time += min(tickets[i], tickets[k] - 1); /* kth person has to wait min(tickets[i], tickets[k] - 1) for people in the back of him */
        }
    }
    return time;
}
