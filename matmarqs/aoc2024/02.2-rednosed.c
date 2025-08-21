#include <stdio.h>
#include <stdbool.h>

/* 
 *  The levels are either all increasing or all decreasing.
 *  Any two adjacent levels differ by at least one and at most three.
 *
 * */

int increasing_condition(int a, int b) {
    if (1 <= b - a && b - a <= 3) {
        return 1;   /* increasing */
    }
    if (1 <= a - b && a - b <= 3) {
        return -1;  /* decreasing */
    }
    return 0;
}

int solve(int *report, int n) {
    /* 0 = decreasing, 1 = increasing, 2 = error */
    int old_condition = increasing_condition(report[0], report[1]);
    int new_condition;

    int single_exception = true;

    for (int i = 2; i < n; i++) {
        new_condition = increasing_condition(report[i-1], report[i]);
        if (single_exception && i < n-1 && new_condition != old_condition) {
            new_condition = increasing_condition(report[i-1], report[i+1]);
            single_exception = false;
            i++;
        }
        else if (new_condition != old_condition) {
            printf("%d %d %d %d %d | %s\n", report[0], report[1], report[2], report[3], report[4], "NOT SAFE");
            return 0;
        }
    }

    printf("%d %d %d %d %d | %s\n", report[0], report[1], report[2], report[3], report[4], "SAFE");
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
