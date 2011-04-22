#include <stdio.h>
#include <stdlib.h>

struct node_s {
    int data;
    struct node_s *next;
};

void push(struct node_s **p, int value) {
    struct node_s *n;

    n = (struct node_s *)malloc(sizeof(struct node_s));
    n->data = value;
    n->next = *p;
    *p = n;
}

void pushback(struct node_s **head, int value) {
    struct node_s *n, *p;

    n = (struct node_s *)malloc(sizeof(struct node_s));
    n->data = value;
    n->next = NULL;

    /* this requires iterating over the entire list. a more efficient
     * solution is to keep a tail pointer to the end of the list. */
    p = *head;
    while (p) {
        if (!p->next) {
            p->next = n;
            printf("pushing back: %d\n", n->data);
            break;
        }
        p = p->next;
    }
}

struct node_s *pop(struct node_s **p) {
    /* pops off the head */
    struct node_s *n;
    n = *p;
    *p = (*p)->next;
    return n;
}

void delete(struct node_s **head, int value) {
    /* the trick to this is to have a trailing pointer to the previous node.
     * - in a doubly-linked list you'd automatically have a prev pointer */
    struct node_s *cur, *prev;
    for (cur = (*head)->next, prev = *head; cur; cur = cur->next, prev = prev->next) {
        if (cur->data == value) {
            prev->next = cur->next;
            printf("deleting: %d\n", cur->data);
            free(cur);
        }
    }
}

struct node_s *reverse(struct node_s *p) {
    /* returns reversed linked list */
    struct node_s *prev, *tmp;
    prev = NULL;
    while (p) {
        /* note how correct order of operations uses the right-hand arg from previous line
         * as the left-hand arg of next line. */
        tmp = p->next;
        p->next = prev;
        prev = p;
        p = tmp;
    }
    return prev;
}

int main(int argc, char **argv) {
    int i;
    struct node_s *head = NULL, *p, *q;

    for (i = 0; i < 10; ++i) {
        push(&head, i);
    }

    head = reverse(head);

    delete(&head, 4);
    pushback(&head, 4);

    for (p = head; p; p = p->next) {
        q = pop(&head);
        printf("popped: %d\n", q->data);
        free(q);
    }

    return 0;
}
