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

#define WHITE 0
#define GRAY 1
#define BLACK 2
#define N 8

static struct vertex_s *graph[N];
static int colors[N];
static int distances[N];
static int predecessors[N];
static struct queue_s *Q;

static struct queue_s *create_queue(int n) {
    struct queue_s *q;
    q = (struct queue_s *)malloc(sizeof(struct queue_s));
    q->data = (int *)malloc(sizeof(int)*n);
    q->head = q->tail = 0;
    q->size = n;
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
     * 0 --- 1     2 --- 3
     * |     |   / |   / |
     * |     |  /  |  /  |
     * |     | /   | /   |
     * 4     5 --- 6 --- 7
     */

    int n = 2;
    graph[0] = (struct vertex_s *)malloc(sizeof(struct vertex_s));
    graph[0]->adj = (int *)malloc(sizeof(int)*n);
    graph[0]->size = n;
    graph[0]->adj[0] = 1;
    graph[0]->adj[1] = 4;

    n = 2;
    graph[1] = (struct vertex_s *)malloc(sizeof(struct vertex_s));
    graph[1]->adj = (int *)malloc(sizeof(int)*n);
    graph[1]->size = n;
    graph[1]->adj[0] = 0;
    graph[1]->adj[1] = 5;

    n = 3;
    graph[2] = (struct vertex_s *)malloc(sizeof(struct vertex_s));
    graph[2]->adj = (int *)malloc(sizeof(int)*n);
    graph[2]->size = n;
    graph[2]->adj[0] = 3;
    graph[2]->adj[1] = 6;
    graph[2]->adj[2] = 5;

    n = 3;
    graph[3] = (struct vertex_s *)malloc(sizeof(struct vertex_s));
    graph[3]->adj = (int *)malloc(sizeof(int)*n);
    graph[3]->size = n;
    graph[3]->adj[0] = 2;
    graph[3]->adj[1] = 6;
    graph[3]->adj[2] = 7;

    n = 1;
    graph[4] = (struct vertex_s *)malloc(sizeof(struct vertex_s));
    graph[4]->adj = (int *)malloc(sizeof(int)*n);
    graph[4]->size = n;
    graph[4]->adj[0] = 0;

    n = 3;
    graph[5] = (struct vertex_s *)malloc(sizeof(struct vertex_s));
    graph[5]->adj = (int *)malloc(sizeof(int)*n);
    graph[5]->size = n;
    graph[5]->adj[0] = 1;
    graph[5]->adj[1] = 2;
    graph[5]->adj[2] = 6;

    n = 4;
    graph[6] = (struct vertex_s *)malloc(sizeof(struct vertex_s));
    graph[6]->adj = (int *)malloc(sizeof(int)*n);
    graph[6]->size = n;
    graph[6]->adj[0] = 5;
    graph[6]->adj[1] = 2;
    graph[6]->adj[2] = 7;
    graph[6]->adj[3] = 3;

    n = 2;
    graph[7] = (struct vertex_s *)malloc(sizeof(struct vertex_s));
    graph[7]->adj = (int *)malloc(sizeof(int)*n);
    graph[7]->size = n;
    graph[7]->adj[0] = 3;
    graph[7]->adj[1] = 6;
}

void BFS(struct vertex_s *graph[], int s) {
    /* assumes graph is an adjacency list */
    int i, u, v;

    Q = create_queue(N);

    for (i = 0; i < N; ++i) {
        colors[i] = WHITE;
        distances[i] = 0;
        predecessors[i] = -1;
    }

    colors[s] = GRAY;
    enqueue(Q, s);

    while (!is_empty(Q)) {
        u = dequeue(Q);
        for (i = 0; i < graph[u]->size; ++i) {
            v = graph[u]->adj[i];
            if (colors[v] == WHITE) {
                colors[v] = GRAY;
                distances[v] = distances[u]+1;
                predecessors[v] = u;
                enqueue(Q, v);
            }
        }
    }
    colors[u] = BLACK;
    for (i = 0; i < N; ++i)
        printf("%d\n", distances[i]);
}

int main(int argc, char **argv) {
    int i;
    graph_init();
    BFS(graph, 1);
    free(Q->data);
    free(Q);

    for (i = 0; i < N; ++i) {
        free(graph[i]->adj);
        free(graph[i]);
    }

    return 0;
}
