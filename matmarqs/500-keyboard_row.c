#include <stdio.h>
#include <stdbool.h>

/***************************************************************/

#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Node {
    char key;
    struct Node *next;
} Node;

Node *create_node (char key) {
    Node *n = (Node *) malloc(sizeof(Node));
    n->key = key;
    n->next = NULL;
    return n;
}

typedef struct {
    Node *head;
} Chain;

void append_to_chain(Chain *chain, char key) {
    Node *new = create_node(key);
    if (!chain->head) {
        chain->head = new;
    }
    else {
        new->next = chain->head;
        chain->head = new;
    }
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
    int size;
    int cardinality;
} HashSet;

/* simple hash function with prime number */
    int h(long long key, int m) {
    return (int) ((key * 31LL) % m + m) % m;
    // a % b is not a modulo operator, but a remainder operator
    // a % b can return negative values
}

HashSet *create_set(int cardinality) {
    HashSet *set = (HashSet *) malloc(sizeof(HashSet));
    set->cardinality = cardinality;
    set->size = 0;
    set->chains = (Chain *) malloc(sizeof(Chain) * cardinality);
    for (int i = 0; i < cardinality; i++) {
        set->chains[i].head = NULL;
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

bool is_in_set(HashSet *set, char key) {
    Chain *chain = &set->chains[h(key, set->cardinality)];
    Node *current = chain->head;
    while (current) {
        if (current->key == key) {
            return true;
        }
        current = current->next;
    }
    return false;
}


void add_to_set(HashSet *set, char key) {
    if (!is_in_set(set, key)) {
        append_to_chain(&set->chains[h(key, set->cardinality)], key);
        set->size++;
    }
}

/* more complex, because we have to find the previous node, since we have a singly linked list */
void remove_from_set(HashSet *set, char key) {
    Chain *chain = &set->chains[h(key, set->cardinality)];

    Node *current = chain->head;
    if (chain->head && chain->head->key == key) {
        if (!chain->head->next) {   // there is only one node in the Chain
            free(chain->head);
            chain->head = NULL;
        }
        else {  // there is more than one node in Chain, and key is on the head
            chain->head = chain->head->next;
            free(current);
        }
        set->size--;
        return;
    }

    while (current->next) {
        if (current->next->key == key) {
            Node *next_node = current->next;
            current->next = current->next->next;
            free(next_node);
            set->size--;
            return;
        }
        current = current->next;
    }

}

bool word_is_subset(char *word, HashSet *set) {
    for (int i = 0; word[i] != '\0'; i++) {
        if (!is_in_set(set, tolower(word[i]))) {
            return false;
        }
    }
    return true;
}

bool can_be_typed_using_single_row(char *word, HashSet *set[3]) {
    for (int i = 0; i < 3; i++) {
        if (word_is_subset(word, set[i])) {
            return true;
        }
    }
    return false;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** findWords(char** words, int wordsSize, int* returnSize) {
    char *rows[3] = {
        "qwertyuiop",
        "asdfghjkl",
        "zxcvbnm"
    };

    HashSet *set[3];
    for (int i = 0; i < 3; i++) {
        set[i] = create_set(2 * strlen(rows[i]));
        for (int j = 0; rows[i][j] != '\0'; j++) {
            add_to_set(set[i], tolower(rows[i][j]));
        }
    }

    // First pass to count matches
    *returnSize = 0;
    for (int i = 0; i < wordsSize; i++) {
        if (can_be_typed_using_single_row(words[i], set)) {
            (*returnSize)++;
        }
    }

    // Allocate result array
    char **returnWords = (char **)malloc(sizeof(char *) * (*returnSize));
    int index = 0;
    for (int i = 0; i < wordsSize; i++) {
        if (can_be_typed_using_single_row(words[i], set)) {
            returnWords[index] = strdup(words[i]);  // create a copy
            index++;
        }
    }

    // Free the sets
    for (int i = 0; i < 3; i++) {
        free_set(set[i]);
    }

    return returnWords;
}

/***************************************************************/

int main() {
    return 0;
}
