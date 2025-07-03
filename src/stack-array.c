#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Stack_t {
    int *data;
    int topIdx;
    size_t size, caps;
} Stack;

void init(Stack *st, size_t stackSize) {
    st->caps = stackSize;
    st->size = 0;
    st->topIdx = -1;
    st->data = malloc(sizeof(*st->data) * st->caps);
    if (st->data == NULL) {
        fprintf(stderr, "ERROR: failed to allocate stack\n");
        return;
    }
}

bool isEmpty(Stack *st) {
    return (st->topIdx == -1);
}

void push(Stack *st, int value) {
    if (st->size < st->caps) {
        st->data[++st->topIdx] = value;
        st->size++;
    }
}

void pop(Stack *st) {
    if (!isEmpty(st)) {
        st->topIdx--;
        st->size--;
    }
}

int top(Stack *st) {
    if (!isEmpty(st)) {
        return st->data[st->topIdx];
    } else {
        return -1;
    }
}

int main() {
    Stack myStack;
    init(&myStack, 10);

    for (size_t i = 0; i < myStack.caps; i++) {
        push(&myStack, i);
    }

    int topVal = top(&myStack);
    pop(&myStack);
    printf("TOP: %d\n", topVal);

    while (!isEmpty(&myStack)) {
        printf("%d\n", top(&myStack));
        pop(&myStack);
    }
    return 0;
}