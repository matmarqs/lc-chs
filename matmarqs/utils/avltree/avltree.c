#include <stdlib.h>

typedef struct TreeNode {
    int val;
    int height;
    struct TreeNode *parent;
    struct TreeNode *left;
    struct TreeNode *right;
} Tree;

void insert(Tree *t, int k);
Tree *find(Tree *t, int k);
static void rebalance(Tree *t);
static void rebalance_left(Tree *t);
static void rebalance_right(Tree *t);
static int get_height(Tree *t);
static void adjust_height(Tree *t);
static void rotate_left(Tree *t);
static void rotate_right(Tree *t);

/*****************************************************/

#define max(a,b) (((a) > (b)) ? (a) : (b))

Tree *create_node(Tree *parent, int val) {
    Tree *n = (Tree *) malloc(sizeof(Tree));
    n->val = val;
    n->height = 1;
    n->parent = parent;
    n->left = NULL;
    n->right = NULL;
    return n;
}

void adjust_height(Tree *n) {
    if (n) {
        n->height = 1 + max(get_height(n->left), get_height(n->right));
    }
}

static int get_height(Tree *t) {
    return t ? t->height : 0;
}

void replace_child(Tree *old, Tree *new) {
    Tree *parent = old->parent;
    new->parent = parent;
    old->parent = NULL;
    if (parent) {
        if (parent->left == old) {
            parent->left = new;
        }
        else {
            parent->right = new;
        }
    }
}

/*      A > Y > B > X > C
 *
 *      X             Y
 *     / \           / \
 *    C   Y    ->   X   A
 *       / \       / \
 *      B   A     C   B
*/
void rotate_left(Tree *x) {
    if (!x || !x->right) return; // Safety check
    Tree *y = x->right;
    replace_child(x, y);
    x->parent = y;
    y->left = x;
    Tree *b = y->left;
    if (b) b->parent = x;
    x->right = b;
    adjust_height(x);
    adjust_height(y);
}

/*      A < Y < B < X < C
 *
 *      X               Y
 *     / \             / \
 *    Y   C    ->     A   X
 *   / \                 / \
 *  A   B               B   C
*/
void rotate_right(Tree *x) {
    if (!x || !x->left) return; // Safety check
    Tree *y = x->left;
    replace_child(x, y);
    x->parent = y;
    y->right = x;
    Tree *b = y->right;
    if (b) b->parent = x;
    x->left = b;
    adjust_height(x);
    adjust_height(y);
}

/*
 *          _ B _                        _ B _                       _ X _
 *         /     \                      /     \                     /     \
 *        A       C         ->         X       C        ->         A       B
 *       / \     / \                  / \     / \                 / \     / \
 *      n   X  n-1 n-1               A  n-1  n-1 n-1             n   n  n-1  C
 *         / \                      / \                                     / \
 *        n   n-1                  n   n                                  n-1  n-1
*/
void rebalance_right(Tree *b) {
    if (!b || !b->left) return;
    Tree *a = b->left;
    if (get_height(a->right) > get_height(a->left)) {
        rotate_left(a);
        adjust_height(a);
    }
    rotate_right(b);
    adjust_height(b);
    adjust_height(b->parent);
}

/*
 *          _ B _                      _ B _                      _ X _
 *         /     \                    /     \                    /     \
 *        C       A        ->        C       X        ->        B       A
 *       / \     / \                / \     / \                / \     / \
 *     n-1 n-1  X   n             n-1 n-1 n-1  A              C  n-1  n   n
 *             / \                            / \            / \
 *           n-1  n                          n   n         n-1 n-1
*/
void rebalance_left(Tree *b) {
    if (!b || !b->right) return;
    Tree *a = b->right;
    if (get_height(a->left) > get_height(a->right)) {
        rotate_right(a);
        adjust_height(a);
    }
    rotate_left(b);
    adjust_height(b);
    adjust_height(b->parent);
}

void rebalance(Tree *t) {
    if (!t) return;
    int left_height = get_height(t->left);
    int right_height = get_height(t->right);
    if (right_height - left_height > 1) {
        rebalance_left(t);
    }
    else if (left_height - right_height > 1) {
        rebalance_right(t);
    }
    adjust_height(t);
    if (t->parent) rebalance(t->parent);
}

Tree *find(Tree *root, int k) {
    Tree *current = root;
    while (current) {
        if (k == current->val) return current;
        else if (k < current->val) {
            if (!current->left) return current;
            current = current->left;
        } else {
            if (!current->right) return current;
            current = current->right;
        }
    }
    return NULL; // Empty tree
}

Tree *left_descendant(Tree *n) {
    if (!n->left) {
        return n;
    }
    else {
        return left_descendant(n->left);
    }
}

Tree *right_ancestor(Tree *n) {
    if (n->val < n->parent->val) {
        return n->parent;
    }
    else {
        return right_ancestor(n->parent);
    }
}

Tree *next(Tree *n) {
    if (n->right) {
        return left_descendant(n->right);
    }
    else {
        return right_ancestor(n);
    }
}

void insert(Tree *root, int k) {
    Tree *p = find(root, k);
    Tree *new = create_node(p, k);
    if (k <= p->val) {
        p->left = new;
    }
    else {
        p->right = new;
    }
}

void delete(Tree *n) {
    if (!n->right) {
        replace_child(n, n->left);
        free(n);
    }
    else {
        Tree *x = next(n);
        replace_child(x, x->right);
        x->right = n->right;
        x->right->parent = x;
        x->left = n->left;
        x->left->parent = x;
        replace_child(n, x);
        free(n);
    }
}

/* AVL Tree is a binary tree that maintains the property |N.left.height - N.right.height| <= 1 for all nodes N */

void avl_insert(Tree *root, int k) {
    insert(root, k);
    Tree *n = find(root, k);
    rebalance(n);
}

void avl_delete(Tree *n) {
    if (!n) return;
    Tree *parent = n->parent;
    delete(n); // Assumes `delete` updates parent pointers
    if (parent) rebalance(parent);
}

/***********************************************/
/****************** TESTING ********************/
/***********************************************/


#include <stdio.h>

// Gets the balance factor of a node
int get_balance(Tree *n) {
    return n ? get_height(n->left) - get_height(n->right) : 0;
}

// Utility function to print the tree inorder (for testing)
void print_inorder(Tree *root) {
    if (root != NULL) {
        print_inorder(root->left);
        printf("%d (h:%d, b:%d) ", root->val, get_height(root), get_balance(root));
        print_inorder(root->right);
    }
}

// Example main function
int main() {
    Tree *root = NULL;

    // Insertion
    printf("Inserting: 50, 30, 70, 20, 40, 60, 80, 10, 25\n");
    avl_insert(root, 50);
    avl_insert(root, 30);
    avl_insert(root, 70);
    avl_insert(root, 20);
    avl_insert(root, 40);
    avl_insert(root, 60);
    avl_insert(root, 80);
    avl_insert(root, 10);
    avl_insert(root, 25); // This will trigger rotations

    printf("Inorder traversal of the balanced tree:\n");
    print_inorder(root);
    printf("\n\n");

    //// Deletion
    //printf("Deleting 80...\n");
    //root = avl_delete(root, 80);
    //printf("Inorder after deleting 80:\n");
    //print_inorder(root);
    //printf("\n\n");
    //
    //printf("Deleting 70 (triggers rebalance)...\n");
    //root = avl_delete(root, 70);
    //printf("Inorder after deleting 70:\n");
    //print_inorder(root);
    //printf("\n");

    return 0;
}
