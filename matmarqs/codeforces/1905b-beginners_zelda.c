// a tree with n vertices will always have n-1 edges
// you can choose any of these vertices to be the root, doesn't matter
//
// input:           1 is the root      2 is the root      3 is the root      4 is the root
// 4                     1                   2                  3                 4
// 1 2          ->      / \      ->          |       ->        / \       ->       |
// 1 3                 2   3                 1                1   4               3
// 3 4                      \                |               /                    |
//                           4               3              2                     1
//                                           |                                    |
//                                           4                                    2
//
// the idea is simple, at each step we compress the longest path that exists on the tree
// the longest path

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int u;
    int v;
} Edge;

int main() {
    int t, n;
    scanf("%d", &t);
    Edge edges[(int) 1e5];
    for (; t > 0; t--) {
        scanf("%d", n);
    }
}
