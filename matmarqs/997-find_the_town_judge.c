/******************************************/

#include <stdlib.h>

int findJudge(int n, int** trust, int trustSize, int* trustColSize) {
    int *trusting = calloc(n, sizeof(int));   /* number of people they trust */
    int *trusted = calloc(n, sizeof(int)); /* number of people they are trusted by */

    for (int i = 0; i < trustSize; i++) {
        trusting[trust[i][0] - 1]++; /* people go from 1 to n */
        trusted[trust[i][1] - 1]++;
    }

    for (int p = 0; p < n; p++) {
        if (trusting[p] == 0 && trusted[p] == n-1) { /* trust no one, but are trusted by everyone */
            return p+1; /* people go from 1 to n */
        }
    }
    return -1;
}
