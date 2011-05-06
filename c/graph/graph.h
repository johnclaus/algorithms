struct vertex_s {
    struct listnode_s *adj;
    struct vertex_s *predecessor;
    int distance;
    int value;
    int color;
};

struct graph_s {
    struct vertex_s **vertices;
    int *d, *f; /* discovery and finishing event timestamps */
};

struct queue_s {
    struct vertex_s **vertices;
    int head;
    int tail;
    int size;
};

struct listnode_s {
    struct vertex_s *v;
    struct listnode_s *next;
};

void push_vertex(struct listnode_s **p, struct vertex_s *v);
struct listnode_s *pop_vertex(struct listnode_s **p);
void delete_vertex(struct listnode_s **head, struct vertex_s *v);
struct listnode_s *reverse(struct listnode_s *p);