#include <stdio.h>
#include <stdbool.h>

/******************************************************************/

/* The optimal solution to this problem is based on the "Sliding Window" idea */

#include <string.h>

/* O(len) */
bool satisfiesKConstraint(char *s, int k, int start, int len) {
    int count_0 = 0;
    int count_1 = 0;
    for (int i = 0; i < len; i++) {
        if (s[start + i] == '0') {
            count_0++;
        }
        else if (s[start + i] == '1') {
            count_1++;
        }
        if (count_0 > k && count_1 > k) {
            return false;
        }
    }
    return true;
}

/* O(n^3) */
int countKConstraintSubstrings(char* s, int k) {
    int len_s = strlen(s);
    int count = 0;
    for (int len = 1; len <= len_s; len++) {
        for (int i = 0; i < len_s - len + 1; i++) {
            if (satisfiesKConstraint(s, k, i, len)) {
                count++;
            }
        }
    }
    return count;
}

/*****************************************************************/

int main() {
    char *s = "000011";
    int k = 1;
    printf("count = %d\n", countKConstraintSubstrings(s, k));

    //printf("%s\n", satisfiesKConstraint(s, k, 2, 4) ? "true" : "false");

    return 0;
}
