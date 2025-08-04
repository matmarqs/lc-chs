int longestPalindrome(char** words, int wordsSize) {
    int count[26][26] = {0};
    int middle = 0;
    int len = 0;

    for (int i = 0; i < wordsSize; i++) {
        int x = words[i][0] - 'a';
        int y = words[i][1] - 'a';
        if (count[y][x] > 0) {
            count[y][x]--;
            len += 4;
            if (x == y)
                middle--;
        }
        else {
            count[x][y]++;
            if (x == y)
                middle++;
        }
    }
    if (middle)
        len += 2;
    return len;
}
