/* stack.c
 *
 * This is a simple implementation of a stack using an array.
 */

#include <stdio.h>
#include <stdlib.h>

struct stack_s {
    int *data;
    int top;
    int size;
};

static struct stack_s *create_stack(int N) {
    struct stack_s *stack;

    stack = (struct stack_s *)malloc(sizeof(struct stack_s));
    stack->data = (int *)malloc(sizeof(int)*N);
    stack->top = 0;
    stack->size = N;

    return stack;
}

static int push(struct stack_s **stack, int value) {
    if ((*stack)->top >= (*stack)->size)
        return -1;

    (*stack)->data[(*stack)->top++] = value;
    return 0;
}

static int pop(struct stack_s **stack) {
    --(*stack)->top;
    if ((*stack)->top < 0) {
        (*stack)->top = 0;
        /* -1 isn't exactly intuitive if the stack actually contains a -1 */
        return -1;
    }
    return (*stack)->data[(*stack)->top];
}

int main(int argc, char **argv) {
    int i, v;
    struct stack_s *stack;

    stack = create_stack(4);

    for (i = 0; i < stack->size; ++i) {
        if (push(&stack, i) == 0)
            printf("pushed %d\n", i);
    }

    for (i = 0; i < stack->size; ++i) {
        v = pop(&stack);
        if (v >= 0)
            printf("popped %d\n", v);
    }

    free(stack->data);
    free(stack);

    return 0;
}
