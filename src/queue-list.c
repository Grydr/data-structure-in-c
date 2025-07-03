#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Queue_Node_t {
    int data;
    struct Queue_Node_t *next;
} QueueNode;

typedef struct Queue_t {
    struct Queue_Node_t *front, *rear;
    size_t size;
} Queue;

void init(Queue *q) {
    q->size = 0;
    q->front = q->rear = NULL;
}

bool isEmpty(Queue *q) {
    return (q->front == NULL && q->rear == NULL);
}

void push(Queue *q, int value) {
    QueueNode *newNode = malloc(sizeof(QueueNode));
    if (newNode) {
        newNode->data = value;
        newNode->next = NULL;

        if (isEmpty(q)) {
            q->front = q->rear = newNode;
        } else {
            q->rear->next = newNode;
            q->rear = newNode;
        }

        q->size++;
    }
}

void pop(Queue *q) {
    if (!isEmpty(q)) {
        QueueNode *temp = q->front;
        q->front = q->front->next;
        free(temp);

        if (q->front == NULL) {
            q->rear = NULL;
        }
        q->size--;
    }
}

int front(Queue *q) {
    if (!isEmpty(q)) {
        return q->front->data;
    } else {
        return -1;
    }
}

int main() {

    Queue queue;
    init(&queue);

    for (size_t i = 0; i < 10; i++) {
        push(&queue, i);
    }

    printf("Size: %ld\n", queue.size);
    printf("Queue: ");
    while (!isEmpty(&queue)) {
        printf("%d ", front(&queue));
        pop(&queue);
    }
    puts("");

    return 0;
}