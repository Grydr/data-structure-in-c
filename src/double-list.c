#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct D_Node_t {
    int data;
    struct D_Node_t *next, *prev;
} DListNode;

typedef struct S_List_t {
    size_t size;
    struct D_Node_t *head, *tail;
} DList;

DListNode *createNode(int value) {
    DListNode *newNode = malloc(sizeof(DListNode));
    if (newNode == NULL) {
        fprintf(stderr, "ERROR: failed to create new node\n");
        return NULL;
    }
    
    newNode->data = value;
    newNode->next = newNode->prev = NULL;
    return newNode;
}

bool isEmpty(DList *list) {
    return (list->head == NULL && list->tail == NULL);
}

void init(DList *list) {
    list->head = list->tail = NULL;
    list->size = 0;
}

void pushBack(DList *list, int value) {
    DListNode *newNode = createNode(value);
    if (newNode) {
        list->size++;

        if (isEmpty(list)) {
            list->head = list->tail = newNode;
            return;
        } else {
            list->tail->next = newNode;
            newNode->prev = list->tail;
            list->tail = newNode;
            return;
        }
    } else {
        fprintf(stderr, "ERROR: failed to create new node\n");
        return;
    }
}

void pushFront(DList *list, int value) {
    DListNode *newNode = createNode(value);
    if (newNode) {
        list->size++;
        
        if (isEmpty(list)) {
            list->head = list->tail = newNode;
            return;
        } else {
            newNode->next = list->head;
            list->head->prev = newNode;
            list->head = newNode;
            return;
        }
    } else {
        fprintf(stderr, "ERROR: failed to create new node\n");
        return;
    }
}

void insertAt(DList *list, unsigned index, int value) {
    if (index == 0) {
        pushFront(list, value);
        return;
    } else if (isEmpty(list) || index >= list->size) {
        pushFront(list, value);
        return;
    }

    DListNode *newNode = createNode(value);
    if (newNode) {
        DListNode *temp = list->head;
        unsigned counter = 0;

        while (counter < index-1 && temp->next != NULL) {
            temp = temp->next;
            counter++;
        }
        newNode->next = temp->next;
        newNode->prev = temp;
        
        if (temp->next) {
            temp->next->prev = newNode;
        }
        
        temp->next = newNode;
        list->size++;
    } else {
        fprintf(stderr, "ERROR: failed to create new node\n");
        return;
    }
}

int front(DList *list) {
    if (!isEmpty(list)) {
        return list->head->data;
    } else {
        return -1;
    }
}

int back(DList *list) {
    if (!isEmpty(list)) {
        return list->tail->data;
    } else {
        return -1;
    }
}

int getAt(DList *list, unsigned index) {
    if (!isEmpty(list)) {
        DListNode *temp = list->head;
        unsigned counter = 0;

        while (counter < index && temp->next != NULL) {
            temp = temp->next;
            counter++;
        }

        return temp->data;
    } else {
        return -1;
    }
}

void popBack(DList *list) {
    if (!isEmpty(list)) {
        DListNode *temp;
        if (list->head == list->tail) {
            temp = list->head;
            list->head = list->tail = NULL;
            free(temp);
        } else {
            temp = list->tail;
            list->tail = list->tail->prev;
            list->tail->next = NULL;
            free(temp);
        }
        list->size--;
        return;
    }
}

void popFront(DList *list) {
    if (!isEmpty(list)) {
        DListNode *temp = list->head;
        if (list->head == list->tail) {
            list->head = list->tail = NULL;
            free(temp);
        } else {
            list->head = list->head->next;
            list->head->prev = NULL;
            free(temp);
        }
        list->size--;
    }
}

void removeValue(DList *list, int value) {
    if (!isEmpty(list)) {
        DListNode *temp, *prev;
        temp = list->head;

        if (temp->data == value) {
            popFront(list);
            return;
        }

        while (temp != NULL && temp->data != value) {
            prev = temp;
            temp = temp->next;
        }

        if (temp == NULL)
            return;
        
        if (temp == list->tail) {
            list->tail = temp->prev;
        }

        prev->next = temp->next;
        if (temp->next != NULL) {
            temp->next->prev = prev;
        }
        free(temp);
        list->size--;
    }
}

int main() {
    DList myList;
    init(&myList);

    pushBack(&myList, 1);
    pushBack(&myList, 2);
    pushBack(&myList, 3);
    pushBack(&myList, 4);

    pushFront(&myList, 10);
    pushFront(&myList, 9);
    pushFront(&myList, 8);
    pushFront(&myList, 7);

    popBack(&myList);
    popFront(&myList);

    // Isi List => [8, 9, 10, 1, 2, 3]

    removeValue(&myList, 3);

    insertAt(&myList, 1, 13);
    pushBack(&myList, 1);
    removeValue(&myList, 1);
    
    // Isi List => [8, 13, 9, 10, 2, 1]

    while (myList.head != NULL) {
        printf("%d ", front(&myList));
        popFront(&myList);
    }
    puts("");

    return 0;
}