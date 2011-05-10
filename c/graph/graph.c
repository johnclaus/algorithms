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
#define DAG_N 9

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

static struct graph_s *dag_init(void) {
    int i;
    struct graph_s *graph;

    graph = (struct graph_s *)malloc(sizeof(struct graph_s));
    graph->vertices = (struct vertex_s **)malloc(sizeof(struct vertex_s)*DAG_N);
    //graph->num_vertices = DAG_N;
    graph->num_vertices = N;

    for (i = 0; i < graph->num_vertices; ++i) {
        graph->vertices[i] = (struct vertex_s *)malloc(sizeof(struct vertex_s));
        graph->vertices[i]->adj = NULL;
        graph->vertices[i]->value = i;
    }

    graph->vertices[0]->value = 7;
    graph->vertices[1]->value = 5;
    graph->vertices[2]->value = 3;
    graph->vertices[3]->value = 11;
    graph->vertices[4]->value = 8;
    graph->vertices[5]->value = 2;
    graph->vertices[6]->value = 9;
    graph->vertices[7]->value = 10;

    push_vertex(&graph->vertices[0]->adj, graph->vertices[3]);
    push_vertex(&graph->vertices[0]->adj, graph->vertices[4]);

    push_vertex(&graph->vertices[1]->adj, graph->vertices[3]);

    push_vertex(&graph->vertices[2]->adj, graph->vertices[4]);
    push_vertex(&graph->vertices[2]->adj, graph->vertices[7]);

    push_vertex(&graph->vertices[3]->adj, graph->vertices[5]);
    push_vertex(&graph->vertices[3]->adj, graph->vertices[6]);
    push_vertex(&graph->vertices[3]->adj, graph->vertices[7]);

    push_vertex(&graph->vertices[4]->adj, graph->vertices[6]);

    /*
     * Clothing example in CLRS -- uses DAG_N
     *
     * 0 -> 1, 7        (boxers -> pants, shoes)
     * 1 -> 2, 7        (pants -> belt, shoes)
     * 2 -> 5           (belt -> jacket)
     * 3 -> 2, 4        (shirt -> belt, tie)
     * 4 -> 5           (tie -> jacket)
     * 5 -> NULL        (jacket -> NULL)
     * 6 -> 7           (socks -> shoes)
     * 7 -> NULL        (shoes -> NULL)
     * 8 -> NULL        (watch -> NULL)
     */

/*
    push_vertex(&graph->vertices[0]->adj, graph->vertices[1]);
    push_vertex(&graph->vertices[0]->adj, graph->vertices[7]);

    push_vertex(&graph->vertices[1]->adj, graph->vertices[2]);
    push_vertex(&graph->vertices[1]->adj, graph->vertices[7]);

    push_vertex(&graph->vertices[2]->adj, graph->vertices[5]);

    push_vertex(&graph->vertices[3]->adj, graph->vertices[2]);
    push_vertex(&graph->vertices[3]->adj, graph->vertices[4]);

    push_vertex(&graph->vertices[4]->adj, graph->vertices[5]);

    push_vertex(&graph->vertices[6]->adj, graph->vertices[7]);
*/

    return graph;
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
    graph->num_vertices = N;

    for (i = 0; i < graph->num_vertices; ++i) {
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

    Q = create_queue(graph->num_vertices);

    for (i = 0; i < graph->num_vertices; ++i) {
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

static int dfs_time;
static struct listnode_s *toplist = NULL;

static void DFS_visit(struct vertex_s *u) {
    int j;
    struct listnode_s *n;
    struct vertex_s *v;

    u->color = GRAY;
    u->dt = ++dfs_time;

    for (n = u->adj; n; n = n->next) {
        v = n->v;
        if (v->color == WHITE) {
            v->predecessor = u;
            DFS_visit(v);
        }
    }

    u->color = BLACK;
    u->ft = ++dfs_time;

    push_vertex(&toplist, u);
}

static void DFS(struct graph_s *graph) {
    int i;

    for (i = 0; i < graph->num_vertices; ++i) {
        graph->vertices[i]->color = WHITE;
        graph->vertices[i]->predecessor = NULL;
    }

    dfs_time = 0;

    for (i = 0; i < graph->num_vertices; ++i) {
        if (graph->vertices[i]->color == WHITE) {
            DFS_visit(graph->vertices[i]);
        }
    }
}

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

    for (i = 0; i < graph->num_vertices; ++i) {
        adj = graph->vertices[i]->adj;
        while (adj) {
            next = adj->next;
            free(adj);
            adj = next;
        }
        free(graph->vertices[i]);
    }

    adj = toplist;
    while (adj) {
        next = adj->next;
        free(adj);
        adj = next;
    }

    free(graph->vertices);
    free(graph);
}

int main(int argc, char **argv) {
    struct graph_s *graph;
    struct listnode_s *n, *adj;
    struct vertex_s *u, *v;

    graph = dag_init();

/*
    DFS(graph);

    for (n = toplist; n; n = n->next) {
        u = n->v;
        printf("%d (%d/%d)\n", u->value, u->dt, u->ft);
    }
*/
    BFS(graph, graph->vertices[1]);
    print_path(graph, graph->vertices[1], graph->vertices[6]);
    cleanup(graph);

    return 0;
}
