#include <stdio.h>

/********************/

#include <string.h> /* strlen */ 

int strStr(char* haystack, char* needle) {
    int haystack_len = strlen(haystack);
    int needle_len = strlen(needle);
    int i = 0;
    while(i < haystack_len) {
        int j = 0;
        int k = i;
        while (j < needle_len && haystack[k] == needle[j]) {
            k++;
            j++;
        }
        if (j == needle_len)
            return k-j;
        i++;
    }
    return -1;
}

/********************/

int main() {
    int index = strStr("mississippi", "issip");
    printf("index = %d\n", index);
    return 0;
}
