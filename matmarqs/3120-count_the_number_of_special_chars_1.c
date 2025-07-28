#include <stdbool.h>

/************************************/

bool is_lower(char c) {
    return 'a' <= c && c <= 'z';
}

bool is_upper(char c) {
    return 'A' <= c && c <= 'Z';
}

int numberOfSpecialChars(char* word) {
    char lower[26] = {false};
    char upper[26] = {false};
    int count = 0;
    for (int i = 0; word[i] != '\0'; i++) {
        char c = word[i];
        if (is_lower(c)) {
            if (lower[c-'a'] == false && upper[c - 'a'] == true) {
                count++;
            }
            lower[c - 'a'] = true;
        }
        else if (is_upper(c)) {
            if (upper[c-'A'] == false && lower[c - 'A'] == true) {
                count++;
            }
            upper[c - 'A'] = true;
        }
    }
    return count;
}
