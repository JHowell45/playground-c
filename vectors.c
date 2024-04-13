#include <stdlib.h>
#include <stdio.h>

#define DEFAULT_VECTOR_CAPACITY 5;

typedef struct vector {
    size_t capacity;
    size_t length;
    int *items;
} vector;

vector * newVector() {
    vector *v = malloc(sizeof(vector));
    v->capacity = DEFAULT_VECTOR_CAPACITY;
    v->length = 0;
    v->items = calloc(v->capacity, sizeof(int));
    return v;
}

void freeVector(vector *v) {
    free(v->items);
    free(v);
}

void vectorIncreaseArray(vector *vec) {
    vec->capacity *= 2;
    vec->items = realloc(vec->items, vec->capacity);
}

void vectorPush(vector *vec, int value) {
    vec->length++;
    if (vec->length > vec->capacity) {
        vectorIncreaseArray(vec);
    }
    vec->items[vec->length - 1] = value;
}

void vectorInsert(vector *vec, int value, size_t index) {
    vec->length++;
    if (vec->length > vec->capacity) {
        vectorIncreaseArray(vec);
    }
    for (size_t i = vec->length - 1; i >= index; i--) {
        vec->items[i+1] = vec->items[i];
    }
    vec->items[index] = value;
}

void vectorPop(vector *vec) {
    vec->length--;
}

void vectorRemove(vector *vec, size_t index) {
    vec->length--;
    for (size_t i = index; i < vec->length; i++) {
        vec->items[i] = vec->items[i + 1];
    }
}

void vectorPrint(vector *vec) {
    printf("[");
    for (size_t i = 0; i < vec->length; i++) {
        int item = vec->items[i];
        if (i == 0) {
            printf("%d", item);
        } else {
            printf(", %d", item);
        }
    }
    printf("]\n");
}

int main(void) {
    vector *vec = newVector();
    vectorPrint(vec);

    for (size_t i = 0; i < 5; i++) {
        vectorPush(vec, i);
        vectorPrint(vec);
    }

    for (size_t i = 0; i < 2; i++) {
        vectorPop(vec);
        vectorPrint(vec);
    }

    vectorInsert(vec, 10, 2);
    vectorPrint(vec);

    vectorInsert(vec, 5, 1);
    vectorPrint(vec);

    vectorRemove(vec, 0);
    vectorPrint(vec);

    vectorRemove(vec, 1);
    vectorPrint(vec);

    vectorRemove(vec, 1);
    vectorPrint(vec);

    vectorRemove(vec, 1);
    vectorPrint(vec);

    freeVector(vec);
    return 0;
}