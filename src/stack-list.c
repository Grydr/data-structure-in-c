#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Stack_Node_t {
    int data;
    struct Stack_Node_t *next;
} StackNode;

typedef struct Stack_t {
    struct Stack_Node_t *top;
    size_t size;
} Stack;

void init(Stack *st) {
    st->top = NULL;
    st->size = 0;
}

bool isEmpty(Stack *st) {
    return (st->top == NULL);
}

void push(Stack *st, int value) {
    StackNode *newNode = malloc(sizeof(StackNode));
    if (newNode) {
        newNode->data = value;
        newNode->next = NULL;
        st->size++;

        if (isEmpty(st)) {
            st->top = newNode;
            return;
        } else {
            newNode->next = st->top;
            st->top = newNode;
            return;
        }
    } else {
        fprintf(stderr, "ERROR: failed to allocate new stack node\n");
        return;
    }
}

void pop(Stack *st) {
    if (!isEmpty(st)) {
        StackNode *temp = st->top;
        st->top = st->top->next;
        free(temp);
        st->size--;
    }else {
        fprintf(stderr, "ERROR: Stack is empty\n");
        return;
    }
}

int top(Stack *st) {
    if (!isEmpty(st)) {
        return st->top->data;
    } else {
        fprintf(stderr, "ERROR: failed to allocate new stack node\n");
        return -1;
    }
}

int main() {
    Stack myStack;
    init(&myStack);

    for (size_t i = 0; i < 10; i++) {
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