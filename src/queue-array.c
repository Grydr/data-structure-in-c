#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Queue_t {
    int *data;
    int front, rear;
    size_t size, caps;
} Queue;

void init(Queue *q, size_t queueSize) {
    q->front = q->rear = -1;
    q->size = 0;
    q->caps = queueSize;
    q->data = malloc(sizeof(*q->data) * q->caps);
    if (q->data == NULL) {
        fprintf(stderr, "ERROR: failed to allocate queue\n");
        return;
    }
}

bool isEmpty(Queue *q) {
    return (q->front == -1 && q->rear == -1);
}

void push(Queue *q, int value) {
    if (q->size < q->caps) {
        if (isEmpty(q)) {
            q->front = 0;
        }

        q->rear = (q->rear + 1) % q->caps;
        q->data[q->rear] = value;
        q->size++;
    }
}

void pop(Queue *q) {
    if (!isEmpty(q)) {
        if (q->front == q->rear) {
            q->front = q->rear = -1;
        } else {
            q->front = (q->front + 1) % q->caps;
        }
        q->size--;
    }
}

int front(Queue *q) {
    if (!isEmpty(q)) {
        return q->data[q->front];
    } else {
        return -1;
    }
}

int main() {
    Queue queue;
    init(&queue, 10);

    for (size_t i = 0; i < queue.caps; i++) {
        push(&queue, i);
    }

    printf("Size: %ld\n", queue.size);
    printf("Queue: ");
    while (!isEmpty(&queue)) {
        printf("%d ", front(&queue));
        pop(&queue);
    }
    puts("");

    free(queue.data);
    return 0;
}