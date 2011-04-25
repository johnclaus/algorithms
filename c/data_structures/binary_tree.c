#include <stdio.h>
#include <stdlib.h>

struct bst_node_s {
    int data;
    struct bst_node_s *parent;
    struct bst_node_s *left;
    struct bst_node_s *right;
};

struct stack_node_s {
    struct bst_node_s *node;
    struct stack_node_s *next;
};

void push(struct stack_node_s **s, struct bst_node_s *n) {
    struct stack_node_s *p;
    p = (struct stack_node_s *)malloc(sizeof(struct stack_node_s));
    p->node = n;
    p->next = *s;
    *s = p;
}

struct bst_node_s *pop(struct stack_node_s **s) {
    /* returns BST node pointed to by the top of the stack
     * and frees the stack element */
    struct stack_node_s *top;
    struct bst_node_s *n;

    top = *s;
    n = top->node;
    *s = (*s)->next;

    free(top);

    return n;
}

static struct bst_node_s *bst_new_node(int value) {
    struct bst_node_s *n;
    n = (struct bst_node_s *)malloc(sizeof(struct bst_node_s));
    n->data = value;
    n->left = NULL;
    n->right = NULL;
    n->parent = NULL;
    return n;
}

void bst_inorder(struct bst_node_s *p) {
    if (p) {
        bst_inorder(p->left);
        printf("  %d\n", p->data);
        bst_inorder(p->right);
    }
}

/* implement an iterative inorder traversal algorithm */
void bst_inorder2(struct bst_node_s *p) {
    struct bst_node_s *q;
    struct stack_node_s *stack;

    stack = NULL;
    q = p;

    while (1) {
        if (q) {
            push(&stack, q);
            q = q->left;
        } else {
            if (stack) {
                q = pop(&stack);
                printf("  %d\n", q->data);
                q = q->right;
            } else {
                break;
            }
        }
    }
}

void bst_preorder(struct bst_node_s *p) {
    if (p) {
        printf("  %d\n", p->data);
        bst_preorder(p->left);
        bst_preorder(p->right);
    }
}

void bst_postorder(struct bst_node_s *p) {
    if (p) {
        bst_postorder(p->left);
        bst_postorder(p->right);
        printf("  %d\n", p->data);
    }
}

struct bst_node_s *bst_search(struct bst_node_s *p, int k) {
    if (!p || p->data == k)
        return p;

    if (k < p->data)
        return bst_search(p->left, k);
    return bst_search(p->right, k);
}

void bst_destroy(struct bst_node_s *p) {
    if (p) {
        bst_destroy(p->left);
        bst_destroy(p->right);
        free(p);
    }
}

struct bst_node_s *bst_minimum(struct bst_node_s *p) {
    while (p->left)
        p = p->left;
    return p;
}

struct bst_node_s *bst_maximum(struct bst_node_s *p) {
    while (p->right)
        p = p->right;
    return p;
}

struct bst_node_s *bst_minimum2(struct bst_node_s *p) {
    /* recursive implementation */
    if (!p->left)
        return p;
    return bst_minimum2(p->left);
}

struct bst_node_s *bst_maximum2(struct bst_node_s *p) {
    /* recursive implementation */
    if (!p->right)
        return p;
    return bst_maximum2(p->right);
}

struct bst_node_s *bst_successor(struct bst_node_s *p) {
    struct bst_node_s *t;

    if (p->right)
        return bst_minimum(p->right);

    t = p->parent;
    while (t && p == t->right) {
        p = t;
        t = t->parent;
    }

    return t;
}

struct bst_node_s *bst_predecessor(struct bst_node_s *p) {
    struct bst_node_s *t;

    if (p->left)
        return bst_maximum(p->left);

    t = p->parent;
    while (t && p == t->left) {
        p = t;
        t = t->parent;
    }

    return t;
}

void bst_insert(struct bst_node_s **T, struct bst_node_s *z) {
    /* insert `z` into tree T */
    struct bst_node_s *x, *y;

    y = NULL;
    x = *T;

    while (x) {
        y = x;
        if (z->data < x->data)
            x = x->left;
        else
            x = x->right;
    }

    z->parent = y;
    if (!y) {
        *T = z;
    } else {
        if (z->data < y->data)
            y->left = z;
        else
            y->right = z;
    }
}

int main(int argc, char **argv) {
    struct bst_node_s *root;

    root = NULL;

    bst_insert(&root, bst_new_node(5));
    bst_insert(&root, bst_new_node(3));
    bst_insert(&root, bst_new_node(7));
    bst_insert(&root, bst_new_node(2));
    bst_insert(&root, bst_new_node(8));
    bst_insert(&root, bst_new_node(4));
    bst_preorder(root);

    bst_destroy(root);

    return 0;
}
