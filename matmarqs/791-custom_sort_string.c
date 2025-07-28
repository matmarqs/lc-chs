char* customSortString(char* order, char* s) {
    int count[26] = {0};
    for (int i = 0; s[i] != '\0'; i++) {
        char c = s[i];
        count[c-'a']++;
    }
    int len = 0;
    for (int j = 0; order[j] != '\0'; j++) {
        while (count[order[j]-'a'] > 0) {
            s[len++] = order[j];
            count[order[j]-'a']--;
        }
    }
    for (int c = 0; c < 26; c++) {
        while (count[c] > 0) {
            s[len++] = c + 'a';
            count[c]--;
        }
    }
    return s;
}
