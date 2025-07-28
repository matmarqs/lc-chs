#include <stdio.h>

/***************************************/

#include <string.h>

typedef enum {first, second} op;

op choose_min_operation(int i, int len_s) {
    if (i + 1 < len_s - i) {
        return first;
    }
    else {
        return second;
    }
}

long long minimumCost(char* s) {
    return 0LL;
}

/***************************************/

int main() {
    minimumCost("010101");
    printf("hello\n");
    return 0;
}
