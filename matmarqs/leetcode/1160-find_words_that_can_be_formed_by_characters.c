#include <stdbool.h>

/*************************************************************/

#include <string.h>

bool string_is_good(char *s, int freq[26]) {
    int count[26] = {0};
    for (; *s != '\0'; s++) {
        count[*s - 'a']++;
    }

    for (int i = 0; i < 26; i++) {
        if (count[i] > freq[i])
            return false;
    }
    return true;
}

int countCharacters(char** words, int wordsSize, char* chars) {
    int freq[26] = {0};
    for (int i = 0; chars[i] != '\0'; i++) {
        freq[chars[i] - 'a']++;
    }

    int total = 0;
    for (int w = 0; w < wordsSize; w++) {
        if (string_is_good(words[w], freq)) {
            total += strlen(words[w]);
        }
    }

    return total;
}
