#include <string.h>

int lengthOfLastWord(char* s) {
    int n = strlen(s) - 1;
    while (s[n] == ' ') {
        n--;
    }
    int l = 0;
    while (n >= 0 && s[n] != ' ') {
        n--;
        l++;
    }
    return l;
}
