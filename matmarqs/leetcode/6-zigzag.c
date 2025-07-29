#include <stdio.h>

#include <stdlib.h>
#include <string.h>

char* convert(char* s, int numRows) {
    if (numRows == 1)
        return s;
    int len_s = strlen(s);
    char *converted_s = malloc(sizeof(char) * (len_s+1));
    int k = 0;
    for (int i = 0; i < numRows; i++) {
        if (i == 0 || i == numRows-1) {
            int c = i;
            while (c < len_s) {
                converted_s[k++] = s[c];
                c += 2*numRows-2;
            }
        }
        else {
            int c = i, zigzag = 0;
            while (c < len_s) {
                converted_s[k++] = s[c];
                zigzag = !zigzag;
                c += zigzag ? (2*numRows - 2 - 2*i) : 2*i;
            }
        }
    }
    converted_s[k] = '\0';
    return converted_s;
}

int main() {
    printf("%s\n", convert("PAYPALISHIRING", 4));
    return 0;
}

/* 
0, 2n-2
1, 2n-2 - 2*1
2, 2n-2 - 2*2
...
n-1, 2n-2


PAYPALISHIRING

PYAIHRN
APLSIIG

P A H N
APLSIIG
Y I R

P  I  N
A LS IG
YA HR
P  I

P   H
A  SI
Y I R
PL  IG
A   N


1, 6, 2
2, 4, 4
3, 2, 6

2n-2 - 2*i
*/
