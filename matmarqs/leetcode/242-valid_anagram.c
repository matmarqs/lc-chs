#include <stdbool.h>

/**********************************/

bool isAnagram(char* s, char* t) {
    int count_s[26] = {0};
    int count_t[26] = {0};

    for (int i = 0; s[i] != '\0'; i++) {
        count_s[s[i] - 'a']++;
    }
    for (int i = 0; t[i] != '\0'; i++) {
        count_t[t[i] - 'a']++;
    }

    for (int i = 0; i < 26; i++) {
        if (count_s[i] != count_t[i])
            return false;
    }
    return true;
}
