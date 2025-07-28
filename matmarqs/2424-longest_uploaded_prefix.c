#include <stdbool.h>

/*************************************************/

#include <stdlib.h>

typedef struct {
    int size;
    bool *uploaded;
    int longest;
} LUPrefix;

LUPrefix* lUPrefixCreate(int n) {
    LUPrefix *server = (LUPrefix *) malloc(sizeof(LUPrefix));
    server->uploaded = (bool *) calloc(n+1, sizeof(bool));
    server->size = n;
    server->longest = 0;
    return server;
}

/* this is amortized O(1) */
/* each video is scanned (longest being incremented) at most once */
/* the worst case is O(n) but, for that to happen you need to upload n videos, so O(n)/n = O(1) */
void lUPrefixUpload(LUPrefix* obj, int video) {
    if (!obj->uploaded[video]) {
        obj->uploaded[video] = true;
    }
    int new_longest = obj->longest + 1;
    if (obj->uploaded[new_longest]) {
        int n = obj->size;
        while (new_longest <= n && obj->uploaded[new_longest]) {
            new_longest++;
        }
        obj->longest = new_longest-1;
    }
}

int lUPrefixLongest(LUPrefix* obj) {
    return obj->longest;
}

void lUPrefixFree(LUPrefix* obj) {
    free(obj->uploaded);
    free(obj);
}

/**
 * Your LUPrefix struct will be instantiated and called as such:
 * LUPrefix* obj = lUPrefixCreate(n);
 * lUPrefixUpload(obj, video);
 
 * int param_2 = lUPrefixLongest(obj);
 
 * lUPrefixFree(obj);
*/
