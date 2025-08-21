#include <stdio.h>

/* 
 *  The levels are either all increasing or all decreasing.
 *  Any two adjacent levels differ by at least one and at most three.
 *
 * */

int solve(int *report, int n) {
    /* 0 = decreasing, 1 = increasing, 2 = error */
    int increasing = report[0] < report[1] ? 1 : report[0] > report[1] ? 0 : 2;

    if (increasing == 2) {
        return 0;
    }

    if (increasing == 1) {
        for (int i = 2; i < n; i++) {
            if (!(1 <= report[i] - report[i-1] && report[i] - report[i-1] <= 3)) {
                return 0;
            }
        }
    }
    else if (increasing == 0) {
        for (int i = 2; i < n; i++) {
            if (!(1 <= report[i-1] - report[i] && report[i-1] - report[i] <= 3)) {
                return 0;
            }
        }
    }

    return 1;
}

void get_input_and_sum_total(FILE *input) {
    char line[256];
    int report[100];  // max integers per line

    int total_safe = 0;
    while (fgets(line, sizeof(line), input)) {
        int n = 0, offset = 0, consumed;
        while (sscanf(line + offset, "%d%n", &report[n], &consumed) == 1) {
            n++;
            offset += consumed;
        }
        total_safe += solve(report, n);
    }

    printf("%d\n", total_safe);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s %s\n", argv[0], "input.txt");
        return 1;
    }

    FILE *input_file = fopen(argv[1], "r");

    get_input_and_sum_total(input_file);

    fclose(input_file);
    return 0;
}
