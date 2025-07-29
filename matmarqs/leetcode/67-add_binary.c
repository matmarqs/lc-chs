#include <stdlib.h>
#include <string.h>

void str_reverse(char *s, int len_s) {
    int aux;
    for (int i = 0; i < len_s/2; i++) {
        aux = s[i];
        s[i] = s[len_s - 1 - i];
        s[len_s - 1 - i] = aux;
    }
}

char* addBinary(char* a, char* b) {
    int len_a = strlen(a);
    int len_b = strlen(b);

    char *s = (char *) malloc(sizeof(char) * (len_a < len_b ? len_b : len_a) + 2);

    int i = len_a - 1;
    int j = len_b - 1;

    int k = 0;
    int carry = 0;
    while (i >= 0 || j >= 0) {
        int c = (i >= 0 ? a[i] - '0' : 0) + (j >= 0 ? b[j] - '0' : 0) + carry;
        if (c > 1) {
            s[k] = (c % 2) ? '1' : '0';
            carry = 1;
        }
        else {
            s[k] = c ? '1' : '0';
            carry = 0;
        }
        i--;
        j--;
        k++;
    }
    
    int len_s;
    if (carry) {
        s[k] = '1';
        len_s = k+1;
    }
    else {
        len_s = k;
    }
    s[len_s] = '\0';

    str_reverse(s, len_s);

    return s;
}
