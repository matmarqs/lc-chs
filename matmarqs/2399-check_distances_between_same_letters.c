#include <stdbool.h>

/*************************************************************/

bool checkDistances(char* s, int* distance, int distanceSize) {
    int dist[26];
    for (int i = 0; i < 26; i++) {
        dist[i] = -1;
    }

    for (int i = 0; s[i] != '\0'; i++) {
        int letter = s[i] - 'a';
        if (dist[letter] == -1) {
            dist[letter] = i;
        }
        else {
            dist[letter] = i - dist[letter] - 1;
        }
    }

    for (int letter = 0; letter < 26; letter++) {
        if (dist[letter] != -1) {
            if (dist[letter] != distance[letter]) {
                return false;
            }
        }
    }

    return true;
}
