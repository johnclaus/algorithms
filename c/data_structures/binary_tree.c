#include <stdio.h>
#include <stdlib.h>

struct bst_node_s {
    int data;
    struct bst_node_s *parent;
    struct bst_node_s *left;
    struct bst_node_s *right;
};

struct stack_s {
    struct bst_node_s *node;
    struct stack_s *next;
};

void push(struct stack_s **s, struct bst_node_s *n) {
    struct stack_s *p;
    p = (struct stack_s *)malloc(sizeof(struct stack_s));
    p->node = n;
    p->next = *s;
    *s = p;
}

struct bst_node_s *pop(struct stack_s **s) {
    /* returns BST node pointed to by the top of the stack
     * and frees the stack element */
    struct stack_s *top;
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
    struct stack_s *stack;

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

void bst_destroy(struct bst_node_s *p) {
    if (p) {
        bst_destroy(p->left);
        bst_destroy(p->right);
        free(p);
    }
}

int main(int argc, char **argv) {
    struct bst_node_s *root;

    root = bst_new_node(5);
    root->parent = NULL;

    root->left = bst_new_node(3);
    root->left->parent = root;

    root->right = bst_new_node(7);
    root->right->parent = root;

    root->left->left = bst_new_node(2);
    root->left->left->parent = root->left;

    root->right->right = bst_new_node(8);
    root->right->right->parent = root->right;

    root->left->right = bst_new_node(5);
    root->left->right->parent = root->left;

    printf("inorder:\n");
    bst_inorder(root);

    printf("inorder2:\n");
    bst_inorder2(root);

    printf("preorder:\n");
    bst_preorder(root);

    printf("postorder:\n");
    bst_postorder(root);

    bst_destroy(root);

    return 0;
}
