#include <stdio.h>
#include <stdlib.h>

#include "graph.h"

void push_vertex(struct listnode_s **p, struct vertex_s *v) {
    struct listnode_s *n;

    n = (struct listnode_s *)malloc(sizeof(struct listnode_s));
    n->v = v;
    n->next = *p;
    *p = n;
}

struct listnode_s *pop_vertex(struct listnode_s **p) {
    /* pops off the head */
    struct listnode_s *n;
    n = *p;
    *p = (*p)->next;
    return n;
}

void delete_vertex(struct listnode_s **head, struct vertex_s *v) {
    /* the trick to this is to have a trailing pointer to the previous node.
     * - in a doubly-linked list you'd automatically have a prev pointer */
    struct listnode_s *cur, *prev;
    for (cur = (*head)->next, prev = *head; cur; cur = cur->next, prev = prev->next) {
        if (cur->v == v) {
            prev->next = cur->next;
            free(cur);
        }
    }
}

struct listnode_s *reverse(struct listnode_s *p) {
    /* returns reversed linked list */
    struct listnode_s *prev, *tmp;
    prev = NULL;
    while (p) {
        /* note how the correct order of operations uses the right-hand arg
         * from previous line as the left-hand arg of next line. */
        tmp = p->next;
        p->next = prev;
        prev = p;
        p = tmp;
    }
    return prev;
}
