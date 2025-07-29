#include <stdio.h>
#include <stdbool.h>

/***************************************************************/

#include <stdlib.h>

typedef struct Node {
    int x;
    struct Node *next;
} Node;

Node *create_node (int x) {
    Node *n = (Node *) malloc(sizeof(Node));
    n->x = x;
    n->next = NULL;
    return n;
}

typedef struct {
    Node *head;
    Node *tail;
    int size;
} Chain;

void add_to_chain(Chain *chain, int x) {
    Node *new = create_node(x);
    if (!chain->head) {
        chain->head = new;
        chain->tail = new;
    }
    else {
        chain->tail->next = new;
        chain->tail = new;
    }
}

void remove_from_chain(Chain *chain, int x) {
    Node *current = chain->head;
    if (chain->head && chain->head->x == x) {
        if (!chain->head->next) {   // there is only one node in the Chain
            free(chain->head);
            chain->head = NULL;
            chain->tail = NULL;
        }
        else {  // there is more than one node in Chain, and x in on the head
            chain->head = chain->head->next;
            free(current);
        }
    }

    while (current->next) {
        if (current->next->x == x) {
            Node *next_node = current->next;
            current->next = current->next->next;
            if (!next_node->next) { // next_node is the tail
                chain->tail = current;
            }
            free(next_node);
        }
        current = current->next;
    }
}

bool is_in_chain(Chain *chain, int x) {
    Node *current = chain->head;
    while (current) {
        if (current->x == x) {
            return true;
        }
        current = current->next;
    }
    return false;
}

void free_chain(Chain *chain) {
    while (chain->head) {
        Node *next = chain->head->next;
        free(chain->head);
        chain->head = next;
    }
}

typedef struct {
    Chain *chains;
    int cardinality;
} HashSet;

/* simple hash function with prime number */
    int h(long long key, int size) {
    return (int) ((key * 31LL) % size + size) % size;
    // a % b is not a modulo operator, but a remainder operator
    // a % b can return negative values
}

HashSet *create_set(int cardinality) {
    HashSet *set = (HashSet *) malloc(sizeof(HashSet));
    set->cardinality = cardinality;
    set->chains = (Chain *) malloc(sizeof(Chain) * cardinality);
    for (int i = 0; i < cardinality; i++) {
        set->chains[i].head = NULL;
        set->chains[i].tail = NULL;
        set->chains[i].size = 0;
    }
    return set;
}

void free_set(HashSet *set) {
    for (int i = 0; i < set->cardinality; i++) {
        free_chain(&set->chains[i]);
    }
    free(set->chains);
    free(set);
}

void add_to_set(HashSet *set, int x) {
    add_to_chain(&set->chains[h(x, set->cardinality)], x);
}

void remove_from_set(HashSet *set, int x) {
    remove_from_chain(&set->chains[h(x, set->cardinality)], x);
}

bool is_in_set(HashSet *set, int x) {
    return is_in_chain(&set->chains[h(x, set->cardinality)], x);
}

int sum_square_digits(int n) {
    int sum = 0;
    while (n) {
        int r = n % 10;
        sum += r*r;
        n /= 10;
    }
    return sum;
}

bool isHappy(int n) {
    HashSet *set = create_set(20);
    add_to_set(set, n);
    while (n != 1) {
        n = sum_square_digits(n);
        if (is_in_set(set, n)) {
            return false;
        }
        add_to_set(set, n);
    }
    free_set(set);
    return true;
}

/***************************************************************/

int main() {
    printf("%d\n", sum_square_digits(82));
    return 0;
}
