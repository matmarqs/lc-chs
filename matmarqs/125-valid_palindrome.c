#include <stdio.h>
#include <stdbool.h>

/****************************/

#include <string.h>

char lower(char c) {
    if ('A' <= c && c <= 'Z') {
        return c - 'A' + 'a';
    }
    return c;
}

bool is_alphanumeric(char c) {
    return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') || ('0' <= c && c <= '9');
}

bool isPalindrome(char* s) {
    int len = strlen(s);
    int i = 0, j = len-1;
    while (i <= j) {
        while (i < len && !is_alphanumeric(s[i])) {
            i++;
        }
        while (j >= 0 && !is_alphanumeric(s[j])) {
            j--;
        }
        if (0 <= i && i <= j && j < len) {
            if (lower(s[i]) != lower(s[j])) {
                return false;
            }
        }
        i++;
        j--;
    }
    return true;
}

/* "A man, a plan, a canal: Panama" */
