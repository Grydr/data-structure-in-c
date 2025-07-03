#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct D_Node_t {
    int data;
    struct D_Node_t *next, *prev;
} DListNode;

typedef struct Deque_t {
    DListNode *head, *tail;
    size_t size;
} Deque;

DListNode *createNode(int value) {
    DListNode *newNode = malloc(sizeof(DListNode));
    if (!newNode)
        return NULL;

    newNode->data = value;
    newNode->next = newNode->prev = NULL;
    return newNode;
}

void init(Deque *dq) {
    dq->size = 0;
    dq->head = dq->tail = NULL;
}

bool isEmpty(Deque *dq) {
    return (dq->head == NULL && dq->tail == NULL);
}

void pushFront(Deque *dq, int value) {
    DListNode *newNode = createNode(value);
    if (newNode) {
        if (isEmpty(dq)) {
            dq->head = dq->tail = newNode;
        } else {
            newNode->next = dq->head;
            dq->head->prev = newNode;
            dq->head = newNode;
        }
        dq->size++;
    }
}

void pushBack(Deque *dq, int value) {
    DListNode *newNode = createNode(value);
    if (newNode) {
        if (isEmpty(dq)) {
            dq->head = dq->tail = newNode;
        } else {
            newNode->prev = dq->tail;
            dq->tail->next = newNode;
            dq->tail = newNode;
        }
        dq->size++;
    }
}

int front(Deque *dq) {
    if (!isEmpty(dq)) {
        return (dq->head->data);
    } else {
        return -1;
    }
}

int back(Deque *dq) {
    if (!isEmpty(dq)) {
        return (dq->tail->data);
    } else {
        return -1;
    }
}

void popFront(Deque *dq) {
    if (!isEmpty(dq)) {
        DListNode *temp = dq->head;
        if (dq->head == dq->tail) {
            dq->head = dq->tail = NULL;
            free(temp);
        } else {
            dq->head = dq->head->next;
            dq->head->prev = NULL;
            free(temp);
        }
        dq->size--;
    }
}

void popBack(Deque *dq) {
    if (!isEmpty(dq)) {
        DListNode *temp;
        if (dq->head == dq->tail) {
            temp = dq->head;
            dq->head = dq->tail = NULL;
            free(temp);
        } else {
            temp = dq->tail;
            dq->tail = dq->tail->prev;
            dq->tail->next = NULL;
            free(temp);
        }
        dq->size--;
    }
}

int main() {
    Deque dq;
    init(&dq);

    for (size_t i = 0; i < 10; i++) {
        pushBack(&dq, i);
    }

    for (size_t i = 20; i > 10; i--) {
        pushFront(&dq, i);
    }

    popBack(&dq);
    popFront(&dq);

    printf("Deque: ");
    while (!isEmpty(&dq)) {
        printf("%d ", front(&dq));
        popFront(&dq);
    }
    puts("");
    return 0;
}