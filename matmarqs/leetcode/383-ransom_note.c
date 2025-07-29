#include <stdbool.h>

/***********************************************************/

bool canConstruct(char* ransomNote, char* magazine) {
    int letters[26] = { 0 };

    for (; *ransomNote != '\0'; ransomNote++) {
        letters[*ransomNote - 'a']++;
    }

    for (; *magazine != '\0'; magazine++) {
        if (letters[*magazine - 'a']) {
            letters[*magazine - 'a']--;
        }
    }

    for (int i = 0; i < 26; i++) {
        if (letters[i] != 0)
            return false;
    }

    return true;
}
