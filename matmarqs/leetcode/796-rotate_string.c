#include <stdio.h>
#include <stdbool.h>

/***********************************************/

#include <string.h> /* strlen */

/* in order for goal to be shift of s, two things are necessary: */
/*      1. they have the same length */
/*      2. goal is a substring of s+s (concatenation of s with itself) */
bool rotateString(char* s, char* goal) {
    /* check if they have the same length */
    int len_s = strlen(s), len_goal = strlen(goal);
    if (len_s != len_goal) {
        return false;
    }

    /* check if goal is a substring of s+s */
    int i = 0, num_turns = 0;
    int j = 0;
    while (num_turns != 2) {
        if (j == len_goal)
            return true;

        if (num_turns == 0) {
            if (s[i] == goal[j]) {
                j++;
            }
        }
        else {  /* num_turns == 1 */
            if (s[i] == goal[j]) {
                j++;
            }
            else {
                return false;
            }
        }

        /* increment circularly */
        if (i == len_s-1) {
            if (j == 0) {   /* not found first character */
                return false;
            }
            i = 0;
            num_turns++;
        }
        else {
            i++;
        }
    }
    return true;
}

/***********************************************/

int main() {
    int rot = rotateString("abcde", "cdeab");
    printf("rot = %s\n", rot ? "true" : "false");
    return 0;
}
