#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct PQueue_Node_t {
    int data;
    struct PQueue_Node_t *next;
} PQueueNode;

typedef struct PQueue_t {
    struct PQueue_Node_t *top;
    size_t size;
} PQueue;

void init(PQueue *pq) {
    pq->size = 0;
    pq->top = NULL;
}

bool isEmpty(PQueue *pq) {
    return (pq->top == NULL);
}

void push(PQueue *pq, int value) {
    PQueueNode *temp = pq->top;
    PQueueNode *newNode = malloc(sizeof(PQueueNode));
    if (newNode) {
        newNode->data = value;
        newNode->next = NULL;

        if (isEmpty(pq)) {
            pq->top = newNode;
        } else if (value < pq->top->data) {
            newNode->next = pq->top;
            pq->top = newNode;
        } else {
            while (temp->next != NULL && value > temp->next->data) {
                temp = temp->next;
            }
            
            newNode->next = temp->next;
            temp->next = newNode;
        }
        pq->size++;
    }
}

void pop(PQueue *pq) {
    if (!isEmpty(pq)) {
        PQueueNode *temp = pq->top;
        pq->top = pq->top->next;
        free(temp);
        pq->size--;
    }
}

int top(PQueue *pq) {
    if (!isEmpty(pq)) {
        return (pq->top->data);
    } else {
        return -1;
    }
}

int main() {
    PQueue pq;
    init(&pq);

    push(&pq, 7);
    push(&pq, 3);
    push(&pq, 3);
    push(&pq, 5);
    push(&pq, 9);
    push(&pq, 1);

    printf("Size: %ld\n", pq.size);
    printf("PQueue: ");
    while (!isEmpty(&pq)) {
        printf("%d ", top(&pq));
        pop(&pq);
    }
    puts("");
    return 0;
}