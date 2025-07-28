#include <string.h>

int has_prefix(char *s, char *pref, int len_pref) {
    int j = 0;
    for (; j < len_pref && s[j] != '\0'; j++) {
        if (s[j] != pref[j]) {
            return 0;
        }
    }
    return len_pref <= j;
}

int prefixCount(char** words, int wordsSize, char* pref) {
    int len_pref = strlen(pref);
    int count = 0;
    for (int i = 0; i < wordsSize; i++) {
        if (has_prefix(words[i], pref, len_pref)) {
            count++;
        }
    }
    return count;
}
