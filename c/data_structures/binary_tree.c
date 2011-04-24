#include <stdio.h>
#include <stdlib.h>

struct node_s {
    int data;
    struct node_s *parent;
    struct node_s *left;
    struct node_s *right;
};

struct stack_s {
    struct node_s *node;
    struct stack_s *next;
};

void push(struct stack_s **s, struct node_s *n) {
    struct stack_s *p;
    p = (struct stack_s *)malloc(sizeof(struct stack_s));
    p->node = n;
    p->next = *s;
    *s = p;
}

struct node_s *pop(struct stack_s **s) {
    /* returns BST node pointed to by the top of the stack
     * and frees the stack element */
    struct stack_s *top;
    struct node_s *n;

    top = *s;
    n = top->node;
    *s = (*s)->next;

    free(top);

    return n;
}

static struct node_s *new_node(int value) {
    struct node_s *n;
    n = (struct node_s *)malloc(sizeof(struct node_s));
    n->data = value;
    n->left = NULL;
    n->right = NULL;
    return n;
}

/*
 *
 *          5
 *         / \
 *        3   7
 *       / \   \
 *      2   5   8
 *
 */

/* implement an iterative inorder traversal algorithm */
void inorder2(struct node_s *p) {
    struct node_s *q;
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

void inorder(struct node_s *p) {
    if (p) {
        inorder(p->left);
        printf("  %d\n", p->data);
        inorder(p->right);
    }
}

void preorder(struct node_s *p) {
    if (p) {
        printf("  %d\n", p->data);
        preorder(p->left);
        preorder(p->right);
    }
}

void postorder(struct node_s *p) {
    if (p) {
        postorder(p->left);
        postorder(p->right);
        printf("  %d\n", p->data);
    }
}

void destroy_bst(struct node_s *p) {
    if (p) {
        destroy_bst(p->left);
        destroy_bst(p->right);
        free(p);
    }
}

int main(int argc, char **argv) {
    struct node_s *root;

    root = new_node(5);
    root->parent = NULL;

    root->left = new_node(3);
    root->left->parent = root;

    root->right = new_node(7);
    root->right->parent = root;

    root->left->left = new_node(2);
    root->left->left->parent = root->left;

    root->right->right = new_node(8);
    root->right->right->parent = root->right;

    root->left->right = new_node(5);
    root->left->right->parent = root->left;

    printf("inorder:\n");
    inorder(root);

    printf("inorder2:\n");
    inorder2(root);

    printf("preorder:\n");
    preorder(root);

    printf("postorder:\n");
    postorder(root);

    destroy_bst(root);

    return 0;
}
