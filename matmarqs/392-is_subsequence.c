#include <stdbool.h>
#include <stdio.h>

/* debugging function */
void debug(int **table, int len_row, int len_col, char *s, char *t) {
    printf("s = %s\n", s);
    printf("t = %s\n", t);
    printf("\n");
    printf("    ");
    for (int j = 0; j < len_col; j++) {
        printf(" %c%s", t[j], (j != len_col-1) ? ",\t" : "");
    }
    printf("  \n");

    for (int i = 0; i < len_row; i++) {
        printf("%c [ ", s[i]);
        for (int j = 0; j < len_col; j++) {
            printf("%+d%s", table[i][j], (j != len_col-1) ? ",\t" : "");
        }
        printf(" ]\n");
    }
    printf("\n");
    printf("result = %s\n", table[len_row-1][len_col-1] == -1 ? "false" : "true");
    printf("\n\n");
}


/********************************************/

#include <stdlib.h>
#include <string.h>

// Dynamic Programming, which I firstly think of
// this one beats 100%, but memory O(n*m) beats 9.63%
bool isSubsequence_Table(char* s, char* t) {
    int s_len = strlen(s);
    if (s_len == 0)
        return true;
    int t_len = strlen(t);
    if (s_len > t_len)
        return false;

    int **table = (int **) calloc(s_len, sizeof(int *));
    for (int i = 0; i < s_len; i++) {
        table[i] = (int *) calloc(t_len, sizeof(int));
    }

    int old_next = 0;
    int new_next = 0;
    for (int i = 0; i < s_len; i++) {
        for (int j = 0; j < old_next; j++) {
            table[i][j] = -1;
        }
        for (int j = old_next; j < t_len; j++) {
            if (j > old_next && table[i][j-1] != -1) {
                table[i][j] = table[i][j-1];
            }
            else {
                if (s[i] == t[j]) {
                    table[i][j] = j;
                }
                else {
                    table[i][j] = -1;
                }
                new_next++;
            }
        }
        old_next = new_next;
    }

    /* DEBUGGING HERE */
    debug(table, s_len, t_len, s, t);

    bool result = table[s_len-1][t_len-1] == -1 ? false : true;

    /* free the resources */
    for (int i = 0; i < s_len; i++) {
        free(table[i]);
    }
    free(table);

    return result;
}

/* simpler two pointer approach */
bool isSubsequence(char *s, char *t) {
    int s_len = strlen(s);
    if (s_len == 0)
        return true;

    int t_len = strlen(t);
    if (s_len > t_len)
        return false;

    int i = 0;
    int j = 0;
    while (i < s_len && j < t_len) {
        if (s[i] == t[j]) {
            i++;
        }
        j++;
    }

    return i == s_len;
}

/***************************************************/

int main() {
    isSubsequence_Table("axc", "ahbgdc");
    isSubsequence_Table("ace", "abcde");
}
