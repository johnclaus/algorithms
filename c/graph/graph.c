/*
 * graph.c
 * graph algorithms
 * - TODO: a better way to create graphs...
 */
#include <stdio.h>
#include <stdlib.h>

#define WHITE 0
#define GRAY 1
#define BLACK 2
#define N 8

struct vertex_s {
    int *adj;
    int size;
};

struct graph_s {
    struct vertex_s **vertices;
    int *colors;
    int *distances;
    int *predecessors;
};

struct queue_s {
    int *data;
    int head;
    int tail;
    int size;
};

static struct queue_s *Q;
static struct graph_s *graph;

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

    graph = (struct graph_s *)malloc(sizeof(struct graph_s));
    graph->vertices = (struct vertex_s **)malloc(sizeof(struct vertex_s)*N);
    graph->colors = (int *)malloc(sizeof(int)*N);
    graph->distances = (int *)malloc(sizeof(int)*N);
    graph->predecessors = (int *)malloc(sizeof(int)*N);

    int n = 2;
    graph->vertices[0] = (struct vertex_s *)malloc(sizeof(struct vertex_s));
    graph->vertices[0]->adj = (int *)malloc(sizeof(int)*n);
    graph->vertices[0]->size = n;
    graph->vertices[0]->adj[0] = 1;
    graph->vertices[0]->adj[1] = 4;

    n = 2;
    graph->vertices[1] = (struct vertex_s *)malloc(sizeof(struct vertex_s));
    graph->vertices[1]->adj = (int *)malloc(sizeof(int)*n);
    graph->vertices[1]->size = n;
    graph->vertices[1]->adj[0] = 0;
    graph->vertices[1]->adj[1] = 5;

    n = 3;
    graph->vertices[2] = (struct vertex_s *)malloc(sizeof(struct vertex_s));
    graph->vertices[2]->adj = (int *)malloc(sizeof(int)*n);
    graph->vertices[2]->size = n;
    graph->vertices[2]->adj[0] = 3;
    graph->vertices[2]->adj[1] = 6;
    graph->vertices[2]->adj[2] = 5;

    n = 3;
    graph->vertices[3] = (struct vertex_s *)malloc(sizeof(struct vertex_s));
    graph->vertices[3]->adj = (int *)malloc(sizeof(int)*n);
    graph->vertices[3]->size = n;
    graph->vertices[3]->adj[0] = 2;
    graph->vertices[3]->adj[1] = 6;
    graph->vertices[3]->adj[2] = 7;

    n = 1;
    graph->vertices[4] = (struct vertex_s *)malloc(sizeof(struct vertex_s));
    graph->vertices[4]->adj = (int *)malloc(sizeof(int)*n);
    graph->vertices[4]->size = n;
    graph->vertices[4]->adj[0] = 0;

    n = 3;
    graph->vertices[5] = (struct vertex_s *)malloc(sizeof(struct vertex_s));
    graph->vertices[5]->adj = (int *)malloc(sizeof(int)*n);
    graph->vertices[5]->size = n;
    graph->vertices[5]->adj[0] = 1;
    graph->vertices[5]->adj[1] = 2;
    graph->vertices[5]->adj[2] = 6;

    n = 4;
    graph->vertices[6] = (struct vertex_s *)malloc(sizeof(struct vertex_s));
    graph->vertices[6]->adj = (int *)malloc(sizeof(int)*n);
    graph->vertices[6]->size = n;
    graph->vertices[6]->adj[0] = 5;
    graph->vertices[6]->adj[1] = 2;
    graph->vertices[6]->adj[2] = 7;
    graph->vertices[6]->adj[3] = 3;

    n = 2;
    graph->vertices[7] = (struct vertex_s *)malloc(sizeof(struct vertex_s));
    graph->vertices[7]->adj = (int *)malloc(sizeof(int)*n);
    graph->vertices[7]->size = n;
    graph->vertices[7]->adj[0] = 3;
    graph->vertices[7]->adj[1] = 6;
}

void BFS(struct graph_s *graph, int s) {
    /* assumes graph is an adjacency list */
    int i, u, v;

    Q = create_queue(N);

    for (i = 0; i < N; ++i) {
        graph->colors[i] = WHITE;
        graph->distances[i] = 0;
        graph->predecessors[i] = -1;
    }

    graph->colors[s] = GRAY;
    enqueue(Q, s);

    while (!is_empty(Q)) {
        u = dequeue(Q);
        for (i = 0; i < graph->vertices[u]->size; ++i) {
            v = graph->vertices[u]->adj[i];
            if (graph->colors[v] == WHITE) {
                graph->colors[v] = GRAY;
                graph->distances[v] = graph->distances[u]+1;
                graph->predecessors[v] = u;
                enqueue(Q, v);
            }
        }
    }
    graph->colors[u] = BLACK;
    for (i = 0; i < N; ++i)
        printf("%d\n", graph->distances[i]);
}

int main(int argc, char **argv) {
    int i;
    graph_init();
    BFS(graph, 1);

    free(Q->data);
    free(Q);

    for (i = 0; i < N; ++i) {
        free(graph->vertices[i]->adj);
        free(graph->vertices[i]);
    }

    free(graph->vertices);
    free(graph->colors);
    free(graph->distances);
    free(graph->predecessors);
    free(graph);

    return 0;
}
