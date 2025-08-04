int longestPalindrome(char** words, int wordsSize) {
    int count[676] = {0};
    int len = 0;
    int hasMiddle = 0;

    for (int i = 0; i < wordsSize; ++i) {
        int x = words[i][0] - 'a';
        int y = words[i][1] - 'a';
        if (count[y + 26*x] > 0) {
            count[y + 26*x]--;
            len += 4;
        } else {
            count[x + 26*y]++;
        }
    }

    // Look for a middle word like "aa", "bb", ...
    for (int i = 0; i < 26; ++i) {
        if (count[i + 26*i]) {
            hasMiddle = 1;
            break;
        }
    }

    if (hasMiddle)
        len += 2;

    return len;
}
