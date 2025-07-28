int sumDigits(int n) {
    int sum = 0;
    while (n > 0) {
        sum += n % 10;
        n /= 10;
    }
    return sum;
}

int getLucky(char* s, int k) {
    int sum = 0;
    for (int i = 0; s[i] != '\0'; i++) {
        int c = s[i];
        if ('a' <= c && c <= 'i') {
            sum += c - 'a' + 1;
        }
        else if ('j' <= c && c <= 's') {
            sum += c - 'j' + 1;
        }
        else { /* 't' <= c && c <= 'z' */
            sum += c - 't' + 2;
        }
    }
    k--;
    while (k > 0) {
        sum = sumDigits(sum);
        k--;
    }
    return sum;
}
