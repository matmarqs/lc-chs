#include <stdlib.h>

typedef struct {
    char *name;
    int height;
} Person;

int cmp_people(const void *a, const void *b) {
    Person pa = *(Person *)a;
    Person pb = *(Person *)b;
    return pa.height < pb.height;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** sortPeople(char** names, int namesSize, int* heights, int heightsSize, int* returnSize) {
    int size = heightsSize;
    *returnSize = size;

    Person *people = (Person *) malloc(sizeof(Person) * size);

    for (int p = 0; p < size; p++) {
        people[p].height = heights[p];
        people[p].name = names[p];
    }

    qsort(people, size, sizeof(Person), cmp_people);

    char **sorted_names = (char **) malloc(sizeof(char *) * size);

    for (int p = 0; p < size; p++) {
        sorted_names[p] = people[p].name;
    }

    free(people);
    return sorted_names;
}
