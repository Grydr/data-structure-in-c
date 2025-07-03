#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct S_Node_t {
    int data;
    struct S_Node_t *next;
} SListNode;

typedef struct S_List_t {
    size_t size;
    struct S_Node_t *head;
} SList;

bool isEmpty(SList *list) {
    return (list->head == NULL);
}

void init(SList *list) {
    list->head = NULL;
    list->size = 0;
}

void pushBack(SList *list, int value) {
    SListNode *newNode = malloc(sizeof(SListNode));
    if (newNode) {
        newNode->data = value;
        newNode->next = NULL;
        list->size++;

        if (isEmpty(list)) {
            list->head = newNode;
        } else {
            SListNode *temp = list->head;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    } else {
        fprintf(stderr, "ERROR: failed to create new node\n");
        return;
    }
}

void pushFront(SList *list, int value) {
    SListNode *newNode = malloc(sizeof(SListNode));
    if (newNode) {
        newNode->data = value;
        newNode->next = NULL;
        list->size++;
        
        if (isEmpty(list)) {
            list->head = newNode;
        } else {
            newNode->next = list->head;
            list->head = newNode;
        }
    } else {
        fprintf(stderr, "ERROR: failed to create new node\n");
        return;
    }
}

void insertAt(SList *list, unsigned index, int value) {
    if (index == 0) {
        pushFront(list, value);
        return;
    } else if (isEmpty(list) || index >= list->size) {
        pushFront(list, value);
        return;
    }

    SListNode *newNode = malloc(sizeof(SListNode));
    if (newNode) {
        SListNode *temp = list->head;
        unsigned counter = 0;

        while (counter < index-1 && temp->next != NULL) {
            temp = temp->next;
            counter++;
        }

        newNode->data = value;
        newNode->next = temp->next;
        temp->next = newNode;
        list->size++;
    } else {
        fprintf(stderr, "ERROR: failed to create new node\n");
        return;
    }
}

int front(SList *list) {
    if (!isEmpty(list)) {
        return list->head->data;
    } else {
        return -1;
    }
}

int back(SList *list) {
    if (!isEmpty(list)) {
        SListNode *temp = list->head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        return temp->data;
    } else {
        return -1;
    }
}

int getAt(SList *list, unsigned index) {
    if (!isEmpty(list)) {
        SListNode *temp = list->head;
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

void popBack(SList *list) {
    if (!isEmpty(list)) {
        SListNode *currNode = list->head;
        SListNode *nextNode = list->head->next;

        if (currNode->next == NULL) {
            free(currNode);
            list->head = NULL;
            return;
        }

        while (nextNode->next != NULL) {
            currNode = nextNode;
            nextNode = nextNode->next;
        }
        currNode->next = NULL;
        free(nextNode);
        list->size--;
        return;
    }
}

void popFront(SList *list) {
    if (!isEmpty(list)) {
        SListNode *tempHead = list->head;
        list->head = tempHead->next;
        free(tempHead);
        list->size--;
    }
}

void removeValue(SList *list, int value) {
    if (!isEmpty(list)) {
        SListNode *temp, *prev;
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
        
        prev->next = temp->next;
        free(temp);
        list->size--;
    }
}

int main() {
    SList myList;
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