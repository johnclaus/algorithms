/*
 * graph.c
 * graph algorithms
 * - TODO: a better way to create graphs...
 */
#include <stdio.h>
#include <stdlib.h>

#include "graph.h"

#define WHITE 0
#define GRAY 1
#define BLACK 2
#define N 8

static struct queue_s *Q;

static struct queue_s *create_queue(int n) {
    struct queue_s *q;
    q = (struct queue_s *)malloc(sizeof(struct queue_s));
    q->vertices = (struct vertex_s **)malloc(sizeof(struct vertex_s)*n);
    q->head = q->tail = 0;
    q->size = n;
    return q;
}

static void enqueue(struct queue_s *q, struct vertex_s *v) {
    q->vertices[q->tail] = v;
    if (q->tail == q->size)
        q->tail = 0;
    else
        ++q->tail;
}

static struct vertex_s *dequeue(struct queue_s *q) {
    struct vertex_s *v;
    v = q->vertices[q->head];
    if (q->head == q->size)
        q->head = 0;
    else
        ++q->head;
    return v;
}

static int is_empty(struct queue_s *q) {
    return (q->tail == q->head);
}

static struct graph_s *graph_init(void) {
    /*
     * 0 --- 1     2 --- 3
     * |     |   / |   / |
     * |     |  /  |  /  |
     * |     | /   | /   |
     * 4     5 --- 6 --- 7
     */

    int i;
    struct graph_s *graph;

    graph = (struct graph_s *)malloc(sizeof(struct graph_s));
    graph->vertices = (struct vertex_s **)malloc(sizeof(struct vertex_s)*N);
    graph->d = (int *)malloc(sizeof(int)*N);
    graph->f = (int *)malloc(sizeof(int)*N);

    for (i = 0; i < N; ++i) {
        graph->vertices[i] = (struct vertex_s *)malloc(sizeof(struct vertex_s));
        graph->vertices[i]->adj = NULL;
        graph->vertices[i]->value = i;
    }

    push_vertex(&graph->vertices[0]->adj, graph->vertices[1]);
    push_vertex(&graph->vertices[0]->adj, graph->vertices[4]);

    push_vertex(&graph->vertices[1]->adj, graph->vertices[0]);
    push_vertex(&graph->vertices[1]->adj, graph->vertices[5]);

    push_vertex(&graph->vertices[2]->adj, graph->vertices[3]);
    push_vertex(&graph->vertices[2]->adj, graph->vertices[6]);
    push_vertex(&graph->vertices[2]->adj, graph->vertices[5]);

    push_vertex(&graph->vertices[3]->adj, graph->vertices[2]);
    push_vertex(&graph->vertices[3]->adj, graph->vertices[6]);
    push_vertex(&graph->vertices[3]->adj, graph->vertices[7]);

    push_vertex(&graph->vertices[4]->adj, graph->vertices[0]);

    push_vertex(&graph->vertices[5]->adj, graph->vertices[1]);
    push_vertex(&graph->vertices[5]->adj, graph->vertices[2]);
    push_vertex(&graph->vertices[5]->adj, graph->vertices[6]);

    push_vertex(&graph->vertices[6]->adj, graph->vertices[5]);
    push_vertex(&graph->vertices[6]->adj, graph->vertices[2]);
    push_vertex(&graph->vertices[6]->adj, graph->vertices[7]);
    push_vertex(&graph->vertices[6]->adj, graph->vertices[3]);

    push_vertex(&graph->vertices[7]->adj, graph->vertices[3]);
    push_vertex(&graph->vertices[7]->adj, graph->vertices[6]);

    return graph;
}

static void BFS(struct graph_s *graph, struct vertex_s *s) {
    /* assumes graph is an adjacency list */
    int i;
    struct listnode_s *adj;
    struct vertex_s *u, *v;

    Q = create_queue(N);

    for (i = 0; i < N; ++i) {
        graph->vertices[i]->color = WHITE;
        graph->vertices[i]->distance = 0;
        graph->vertices[i]->predecessor = NULL;
    }

    s->color = GRAY;
    enqueue(Q, s);

    while (!is_empty(Q)) {
        u = dequeue(Q);
        for (adj = u->adj; adj; adj = adj->next) {
            v = adj->v;
            if (v->color == WHITE) {
                v->color = GRAY;
                v->distance = u->distance+1;
                v->predecessor = u;
                enqueue(Q, v);
            }
        }
        u->color = BLACK;
    }

    free(Q->vertices);
    free(Q);
}

/*
static int dfs_time;

static void DFS_visit(struct graph_s *graph, int i) {
    int j;
    struct vertex_s *u;

    u = graph->vertices[i];
    graph->colors[i] = GRAY;
    graph->d[i] = ++dfs_time;

    for (j = 0; j < u->size; ++j) {
        if (graph->colors[j] == WHITE) {
            graph->predecessors[j] = i;
            DFS_visit(graph, j);
        }
    }

    graph->colors[i] = BLACK;
    graph->f[i] = ++dfs_time;
}

static void DFS(struct graph_s *graph) {
    int i;

    for (i = 0; i < N; ++i) {
        graph->colors[i] = WHITE;
        graph->predecessors[i] = -1;
    }

    dfs_time = 0;

    for (i = 0; i < N; ++i) {
        if (graph->colors[i] == WHITE)
            DFS_visit(graph, i);
    }
}
*/

/*
static listnode_s *topological_sort(struct graph_s *graph) {
    struct listnode_s *head;
    head = NULL;
}
*/

static void print_path(struct graph_s *graph, struct vertex_s *s, struct vertex_s *v) {
    if (s == v)
        printf("%d\n", s->value);
    else if (!v->predecessor)
        printf("no path from s to v\n");
    else {
        print_path(graph, s, v->predecessor);
        printf("%d\n", v->value);
    }
}

static void cleanup(struct graph_s *graph) {
    int i;
    struct listnode_s *adj, *next;

    for (i = 0; i < N; ++i) {
        adj = graph->vertices[i]->adj;
        while (adj) {
            next = adj->next;
            free(adj);
            adj = next;
        }
        free(graph->vertices[i]);
    }

    free(graph->vertices);
    free(graph->d);
    free(graph->f);
    free(graph);
}

int main(int argc, char **argv) {
    struct graph_s *graph;
    graph = graph_init();

//    DFS(graph);
    BFS(graph, graph->vertices[1]);
    print_path(graph, graph->vertices[1], graph->vertices[7]);
    cleanup(graph);

    return 0;
}
