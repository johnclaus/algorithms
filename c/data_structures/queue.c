/* queue.c
 *
 * Implementation of a queue using an array.
 */

#include <stdio.h>
#include <stdlib.h>

struct queue_s {
    int *data;
    int last;
    int size;
};

static struct queue_s *create_queue(int N) {
    struct queue_s *q;

    q = (struct queue_s *)malloc(sizeof(struct queue_s));
    q->data = (int *)malloc(sizeof(int)*N);
    q->last = 0;
    q->size = N;
    return q;
}

static int enqueue(struct queue_s **q, int value) {
    if ((*q)->last >= (*q)->size)
        return -1;

    /* last < 0 indicates an empty queue after dequeueping all the elements */
    if ((*q)->last < 0)
        (*q)->last = 0;

    (*q)->data[(*q)->last++] = value;

    /* the last element shouldn't ever exceed the size-1 of the queue */
    if ((*q)->last >= (*q)->size)
        (*q)->last = (*q)->size-1;
}

static int dequeue(struct queue_s **q) {
    int res, i, j, tmp;

    if ((*q)->last < 0)
        return -1;
    if ((*q)->last == 0) {
        (*q)->last = -1;
        return (*q)->data[0];
    }

    res = (*q)->data[0];

    /* shift queue -- probably not ideal, but I think it's required
     * for implementing a queue in an array. the 0th element should always be
     * the head of the queue. XXX: check pg. 203 in intro to algorithms for a good
     * implementation that's used in graph/graph.c */
    for (i = 1; i <= (*q)->last; ++i) {
        j = i-1;
        tmp = (*q)->data[i];
        (*q)->data[i] = (*q)->data[j];
        (*q)->data[j] = tmp;
    }

    --(*q)->last;

    return res;
}

int main(int argc, char **argv) {
    int i;
    struct queue_s *q;
    q = create_queue(4);

    for (i = 0; i < 4; ++i)
        enqueue(&q, i);

    for (i = 0; i < 4; ++i)
        printf("%d ", q->data[i]);
    printf("\n");

    printf("%d, %d\n", dequeue(&q), q->last);
    printf("%d, %d\n", dequeue(&q), q->last);
    printf("%d, %d\n", dequeue(&q), q->last);

    for (i = 0; i <= q->last; ++i)
        printf("%d ", q->data[i]);
    printf("\n");

    free(q);

    return 0;
}
