#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

// darray struct
// data, size, caps
typedef struct D_Array_t {
    int *data;
    size_t size;
    size_t caps;
} D_Array;

void init(D_Array *darray) {
    darray->size = 0;
    darray->caps = 2;
    darray->data = malloc(sizeof(*darray->data) * darray->caps);
    if (darray->data == NULL) {
        fprintf(stderr, "ERROR: failed to allocate data: \n");
        return;
    }
}

bool isEmpty(D_Array *darray) {
    if (darray->size == 0) {
        return true;
    }
    return false;
}

void pushBack(D_Array *darray, int value) {
    if (darray->size < darray->caps) {
        darray->data[darray->size++] = value;
    } else {
        darray->caps = darray->caps + (darray->caps / 2);

        int *dataTemp = realloc(darray->data, sizeof(*darray->data) * darray->caps);
        if (dataTemp == NULL) {
            fprintf(stderr, "ERROR: failed to reallocate memory: \n");
            return;
        }
        
        darray->data = dataTemp;
        darray->data[darray->size++] = value;
    }
}

void pushFront(D_Array *darray, int value) {
    if (isEmpty(darray)) {
        darray->data[0] = value;
        darray->size++;
        return;
    } 

    if (darray->size < darray->caps) {
        int *dataTemp = malloc(sizeof(*darray->data) * darray->caps);
        if (dataTemp == NULL) {
            fprintf(stderr, "ERROR: failed to allocate data: \n");
            return;
        }

        for (size_t i = 0; i < darray->size; i++) {
            dataTemp[i+1] = darray->data[i];
        }
        dataTemp[0] = value;

        free(darray->data);

        darray->data = dataTemp;
        darray->size++;
    } else {
        darray->caps = darray->caps + (darray->caps / 2);

        int *dataTemp = malloc(sizeof(*darray->data) * darray->caps);
        if (dataTemp == NULL) {
            fprintf(stderr, "ERROR: failed to allocate memory: \n");
            return;
        }

        for (size_t i = 0; i < darray->size; i++) {
            dataTemp[i+1] = darray->data[i];
        }
        dataTemp[0] = value;

        free(darray->data);

        darray->data = dataTemp;
        darray->size++;
    }
}

void popBack(D_Array *darray) {
    if (!isEmpty(darray)) {
        darray->size--;
        return;
    } else {
        fprintf(stderr, "ERROR: array is empty: \n");
        return;
    }
}

void popFront(D_Array *darray) {
    if (!isEmpty(darray)) {
        for (size_t i = 0; i < darray->size; i++) {
            darray->data[i] = darray->data[i+1];
        }
        darray->size--;
        return;
    } else {
        fprintf(stderr, "ERROR: array is empty: \n");
        return;
    }
}

int back(D_Array *darray) {
    if (!isEmpty(darray)) {
        return darray->data[darray->size-1];
    } else {
        fprintf(stderr, "ERROR: array is empty: \n");
        return -1;
    }
}

int front(D_Array *darray) {
    if (!isEmpty(darray)) {
        return darray->data[0];
    } else {
        fprintf(stderr, "ERROR: array is empty: \n");
        return -1;
    }
}

int getAt(D_Array *darray, unsigned int index) {
    if (!isEmpty(darray) && index < darray->size) {
        return darray->data[index];
    } else {
        fprintf(stderr, "ERROR: array is empty: \n");
        return -1;
    }
}

void setAt(D_Array *darray, unsigned int index, int value) {
    if (!isEmpty(darray) && index < darray->size) {
        darray->data[index] = value;
        return;
    } else {
        fprintf(stderr, "ERROR: array is empty: \n");
        return;
    }
}

void insertAt(D_Array *darray, unsigned int index, int value) {
    if (isEmpty(darray) && index != 0) {
        fprintf(stderr, "ERROR: array is empty: \n");
        return;
    }

    if (index > darray->size) {
        fprintf(stderr, "ERROR: index must be less than size: \n");
        return;
    }

    if (darray->size < darray->caps) {
        for (size_t i = darray->size; i > index; i--) {
            darray->data[i] = darray->data[i-1];
        }
        darray->data[index] = value;
        darray->size++;
        return;
    } else {
        darray->caps = darray->caps + (darray->caps / 2);

        int *dataTemp = malloc(sizeof(*darray->data) * darray->caps);
        if (dataTemp == NULL) {
            fprintf(stderr, "ERROR: failed to allocate memory: \n");
            return;
        }

        for (size_t i = 0; i < index; i++) {
            dataTemp[i] = darray->data[i];
        }
        dataTemp[index] = value;
        for (size_t i = index; i < darray->size; i++) {
            dataTemp[i+1] = darray->data[i];
        }

        free(darray->data);

        darray->data = dataTemp;
        darray->size++;
        return;
    }
}

void freeDArray(D_Array *darray) {
    memset(darray->data, 0, sizeof(*darray->data) * darray->size);
    free(darray->data);
    darray->data = NULL;
}

int main() {
    D_Array darray;
    init(&darray);

    pushBack(&darray, 1);
    pushBack(&darray, 4);
    pushBack(&darray, 3);
    pushBack(&darray, 5);
    pushBack(&darray, 6);
    pushBack(&darray, 10);

    int backVal = back(&darray);
    popBack(&darray);
    printf("back: %d\n", backVal);

    int frontVal = front(&darray);
    popFront(&darray);
    printf("front: %d\n", frontVal);

    int valAt2 = getAt(&darray, 2);
    printf("value at index 2: %d\n", valAt2);

    setAt(&darray, 2, 2);

    pushFront(&darray, 8);
    pushFront(&darray, 11);

    insertAt(&darray, 0, 15);
    insertAt(&darray, darray.size/2, 20);
    insertAt(&darray, darray.size, 30);

    printf("size: %ld\ncaps: %ld\n", darray.size, darray.caps);
    for (size_t i = 0; i < darray.size; i++) {
        printf("data[%ld]: %d\n", i, darray.data[i]);
    }

    freeDArray(&darray);
    return 0;
}