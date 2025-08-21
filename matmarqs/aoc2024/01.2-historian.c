#include <stdio.h>
#include <stdlib.h>

int cmp_int(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}

void solve(int *l1, int *l2, int n) {
    qsort(l1, n, sizeof(int), cmp_int);
    qsort(l2, n, sizeof(int), cmp_int);

    long long total = 0;

    int i = 0, j = 0;
    while (j < n && i < n) {
        int count = 0;
        while (l2[j] <= l1[i]) {
            if (l2[j] == l1[i]) {
                count++;
            }
            j++;
        }
        total += count * l1[i];
        while (i < n && l1[i+1] == l1[i]) {
            total += count * l1[i];
            i++;
        }
        i++;
        count = 0;
    }

    printf("%lld\n", total);
}

void get_input_call_solve(FILE *input) {
    int l1[1000], l2[1000];
    int n = 0;

    while (fscanf(input, "%d %d", &l1[n], &l2[n]) != EOF) {
        n++;
    }

    solve(l1, l2, n);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s %s\n", argv[0], "input.txt");
        return 1;
    }

    FILE *input_file = fopen(argv[1], "r");

    get_input_call_solve(input_file);

    fclose(input_file);
    return 0;
}
