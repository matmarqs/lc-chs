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

int solve_without_removing(int *report, int n, int start_condition) {
    if (start_condition == 0) {
        return 0;
    }
    for (int i = 1; i < n; i++) {
        if (increasing_condition(report[i-1], report[i]) != start_condition) {
            return 0;
        }
    }
    return 1;
}

// O(n)
int solve_removing_middle(int *report, int n, int start_condition) {
    int exception = true;
    for (int i = 1; i < n; i++) {
        int condition = increasing_condition(report[i-1], report[i]);
        if (exception && i < n-1 && condition != start_condition) {
            condition = increasing_condition(report[i-1], report[i+1]);
            bool remove_curr = true;
            if (condition != start_condition) {
                if (i-2 >= 0) {
                    remove_curr = false;
                    condition = increasing_condition(report[i-2], report[i]);
                    if (condition != start_condition)
                        return 0;
                }
                else {
                    return 0;
                }
            }
            exception = false;
            if (remove_curr) i++;
        }
        else if (condition != start_condition) {
            return 0;
        }
    }
    return 1;
}

// O(n)
int solve(int *report, int n) {
    if (n <= 3) {
        return 1;
    }
    int first = increasing_condition(report[0], report[1]);
    int last = increasing_condition(report[n-2], report[n-1]);
    if (first == 0 && last == 0) {
        return 0;
    }
    else if (first == 0) {
        if (increasing_condition(report[0], report[2]) == last || increasing_condition(report[1], report[2]) == last) {
            return solve_without_removing(report+2, n-2, last);
        }
        else {
            return 0;
        }
    }
    else if (last == 0) {
        if (increasing_condition(report[n-3], report[n-1]) == first || increasing_condition(report[n-3], report[n-2]) == first) {
            return solve_without_removing(report, n-2, first);
        }
        else {
            return 0;
        }
    }
    else if (first == 1 && last == 1) {
        return solve_removing_middle(report, n, 1);
    }
    else if (first == -1 && last == -1) {
        return solve_removing_middle(report, n, -1);
    }
    else {  // first != last, 1 and -1
        if (increasing_condition(report[0], report[2]) == last || increasing_condition(report[1], report[2]) == last) {
            return solve_without_removing(report+2, n-2, last);
        }
        else if (increasing_condition(report[n-3], report[n-1]) == first || increasing_condition(report[n-3], report[n-2]) == first) {
            return solve_without_removing(report, n-2, first);
        }
        else {
            return 0;
        }
    }
}

// O(n^2), for stress testing
int solve_by_jumping(int *report, int n) {
    if (n <= 2) {
        return 1;
    }
    // First try without removing any element
    int initial_condition = increasing_condition(report[0], report[1]);
    if (initial_condition != 0) {
        int valid_without_removal = 1;
        for (int i = 1; i < n - 1; i++) {
            int current_condition = increasing_condition(report[i], report[i + 1]);
            if (current_condition != initial_condition) {
                valid_without_removal = 0;
                break;
            }
        }
        if (valid_without_removal) {
            return 1;
        }
    }
    // Try removing each element one by one
    for (int r = 0; r < n; r++) {
        int valid = 1;
        int condition = 0;
        int found_condition = 0;

        // Find the first valid condition to use as reference
        for (int i = 0; i < n - 1; i++) {
            if (i == r) continue; // skip the removed element
            if (i + 1 == r) continue; // skip if next element is removed

            int next_idx = (i + 1 == r) ? i + 2 : i + 1;
            if (next_idx >= n) break;

            condition = increasing_condition(report[i], report[next_idx]);
            if (condition != 0) {
                found_condition = 1;
                break;
            }
        }
        if (!found_condition) {
            continue; // all differences are invalid, try next removal
        }
        // Check all pairs with this element removed
        for (int i = 0; i < n - 1; i++) {
            if (i == r) continue; // skip the removed element

            int next_idx = i + 1;
            if (next_idx == r) {
                next_idx++; // skip over the removed element
            }
            if (next_idx >= n) break;

            int current_condition = increasing_condition(report[i], report[next_idx]);
            if (current_condition != condition) {
                valid = 0;
                break;
            }
        }
        if (valid) {
            return 1;
        }
    }
    return 0;
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
        //if (solve_by_jumping(report, n) != solve(report, n)) {
        //    for (int i = 0; i < n; i++) {
        //        printf("%d ", report[i]);
        //    }
        //    putchar('\n');
        //}
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
