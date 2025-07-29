#include <stdio.h>
#include <stdlib.h>

/*******************************************************/

#include <string.h>

int is_english_letter(char c) {
    return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z');
}

char* reverseOnlyLetters(char *s) {
    int len = strlen(s);
    int i = 0, j = len-1;
    while (i < j) {
        while (i < len && !is_english_letter(s[i])) {
            i++;
        }
        while (j >= 0 && !is_english_letter(s[j])) {
            j--;
        }
        if (i < j) {
            char c = s[i];
            s[i] = s[j];
            s[j] = c;
            i++;
            j--;
        }
    }
    return s;
}

/*******************************************************/

void reverse(char *s, int left, int right) {
    for (int i = 0; i < (right-left)/2; i++) {
        char c = s[left + i];
        s[left + i] = s[right-i-1];
        s[right-i-1] = c;
    }
}

char* reverseOnlyLetters_WrongInterpretation(char *s) {
    int left = 0, right = 0;
    while (s[right] != '\0') {
        left = right;
        while (is_english_letter(s[right])) {
            right++;
        }
        reverse(s, left, right);
        if (s[right] != '\0')
            right++;
    }
    return s;
}

