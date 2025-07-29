#include <stdbool.h>
#include <stdio.h>

/*******************************************/

#include <stdlib.h>
#include <string.h>

void free_map(char *(map[26])) {
    for (int i = 0; i < 26; i++) {
        if (map[i]) {
            free(map[i]);
        }
    }
}

bool mystrcmp(char *s, char *t, int len) {
    int i = 0;
    for (; i < len && s[i] != '\0' && t[i] != '\0'; i++) {
        if (s[i] != t[i])
            return false;
    }
    if (i == len && s[i] == '\0') {
        return true;
    }
    else {
        return false;
    }
}

bool wordPattern(char* pattern, char* s) {
    char *(map[26]) = { NULL };

    int len = 0;
    int i = 0;

    for (; *pattern != '\0' && s[i] != '\0'; pattern++) {
        while (s[i] != ' ' && s[i] != '\0') {
            i++;
            len++;
        }

        if (map[*pattern - 'a'] == NULL) {

            for (int j = 0; j < 26; j++) {
                if (map[j] != NULL && mystrcmp(map[j], s+(i-len), len)) {
                    // This word is already mapped to a different character.
                    free_map(map);
                    return false; // This handles the ("abba", "dog dog dog dog") case
                }
            }

            map[*pattern - 'a'] = (char *) malloc(sizeof(char) * (len+1));
            strncpy(map[*pattern - 'a'], s+(i-len), len);
            map[*pattern - 'a'][len] = '\0';
        }
        else if (!mystrcmp(map[*pattern - 'a'], s+(i-len), len)) {
            free_map(map);
            return false;
        }

        if (s[i] == ' ') { /* jumping the space */
            i++;
        }
        len = 0;
    }

    free_map(map);

    if (*pattern == '\0' && s[i] == '\0') {
        return true;
    }
    else {
        return false;
    }
}

/*******************************************/

int main() {
    bool result = wordPattern("abba", "dog constructor constructo dog");
    printf("%s\n", result == true ? "true" : "false");
}
