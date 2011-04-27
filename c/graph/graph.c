/*
 * graph.c
 * graph algorithms
 * - TODO: a better way to create graphs...
 */
#include <stdio.h>
#include <stdlib.h>

struct vertex_s {
    int *adj;
    int size;
};

struct queue_s {
    int *data;
    int head;
    int tail;
    int size;
};

static struct vertex_s *graph[5];
static int colors[5];
static int distances[5];
static int predecessors[5];
static struct queue_s *Q;

#define WHITE 0
#define GRAY 1
#define BLACK 2

static struct queue_s *create_queue(int N) {
    struct queue_s *q;
    q = (struct queue_s *)malloc(sizeof(struct queue_s));
    q->data = (int *)malloc(sizeof(int)*N);
    q->head = q->tail = 0;
    q->size = N;
    return q;
}

void enqueue(struct queue_s *q, int x) {
    q->data[q->tail] = x;
    if (q->tail == q->size)
        q->tail = 0;
    else
        ++q->tail;
}

int dequeue(struct queue_s *q) {
    int x;
    x = q->data[q->head];
    if (q->head == q->size)
        q->head = 0;
    else
        ++q->head;
    return x;
}

int is_empty(struct queue_s *q) {
    return (q->tail == q->head);
}

void graph_init(void) {
    /*
     *  0 ---- 1
     *  |    / | \
     *  |   /  |  \
     *  |  /   |   2
     *  | /    |  /
     *  |/     | /
     *  4 ---- 3
     */

    int n = 2;
    graph[0] = (struct vertex_s *)malloc(sizeof(struct vertex_s));
    graph[0]->adj = (int *)malloc(sizeof(int)*n);
    graph[0]->size = n;
    graph[0]->adj[0] = 1;
    graph[0]->adj[1] = 4;

    n = 4;
    graph[1] = (struct vertex_s *)malloc(sizeof(struct vertex_s));
    graph[1]->adj = (int *)malloc(sizeof(int)*n);
    graph[1]->size = n;
    graph[1]->adj[0] = 0;
    graph[1]->adj[1] = 4;
    graph[1]->adj[2] = 2;
    graph[1]->adj[3] = 3;

    n = 2;
    graph[2] = (struct vertex_s *)malloc(sizeof(struct vertex_s));
    graph[2]->adj = (int *)malloc(sizeof(int)*n);
    graph[2]->size = n;
    graph[2]->adj[0] = 1;
    graph[2]->adj[1] = 3;

    n = 3;
    graph[3] = (struct vertex_s *)malloc(sizeof(struct vertex_s));
    graph[3]->adj = (int *)malloc(sizeof(int)*n);
    graph[3]->size = n;
    graph[3]->adj[0] = 1;
    graph[3]->adj[1] = 4;
    graph[3]->adj[2] = 2;

    n = 3;
    graph[4] = (struct vertex_s *)malloc(sizeof(struct vertex_s));
    graph[4]->adj = (int *)malloc(sizeof(int)*n);
    graph[4]->size = n;
    graph[4]->adj[0] = 3;
    graph[4]->adj[1] = 0;
    graph[4]->adj[2] = 1;
}

void BFS(struct vertex_s *graph[], int s) {
    /* assumes graph is an adjacency list */
    int i, u, v;

    Q = create_queue(5);

    for (i = 0; i < 5; ++i) {
        colors[i] = WHITE;
        distances[i] = 0;
        predecessors[i] = -1;
    }

    colors[s] = GRAY;
    enqueue(Q, s);

    while (!is_empty(Q)) {
        u = dequeue(Q);
        for (v = 0; v < graph[u]->size; ++v) {
            if (colors[v] == WHITE) {
                colors[v] = GRAY;
                distances[v] = distances[u]+1;
                predecessors[v] = u;
                enqueue(Q, v);
            }
        }
    }
    colors[u] = BLACK;
    for (i = 0; i < 5; ++i)
        printf("%d\n", distances[i]);
}

int main(int argc, char **argv) {
    int i;
    graph_init();
    BFS(graph, 0);
    free(Q->data);
    free(Q);

    for (i = 0; i < 5; ++i) {
        free(graph[i]->adj);
        free(graph[i]);
    }

    return 0;
}
