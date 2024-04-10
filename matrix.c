#include <stdlib.h>
#include <stdio.h>

typedef struct vector {
    size_t capacity;
    int *items;
} vector;

vector * newVec(size_t capacity) {
    vector *vec = malloc(sizeof(vector));
    vec->capacity = capacity;
    vec->items = calloc(vec->capacity, sizeof(int));
    return vec;
}

void destroyVec(vector *vec) {
    free(vec->items);
    free(vec);
}

int getValueVector(vector *vec, size_t index) {
    return vec->items[index];
}

void setValueVector(vector *vec, size_t index, int value) {
    vec->items[index] = value;
}

void addScalarVector(vector *vec, int scalar) {
    for (int i = 0; i < vec->capacity; i++) {
        vec->items[i] += scalar;
    }
}

void printVector(vector *vec) {
    printf("[%d", vec->items[0]);
    for (int i = 0; i < vec->capacity; i++) {
        printf(", %d", vec->items[i]);
    }
    printf("]\n");
}

typedef struct dataframe {
    size_t xCapacity;
    size_t yCapacity;
    vector **data;
} dataframe;

dataframe * newDataframe(size_t xCapacity, size_t yCapacity) {
    dataframe *df = malloc(sizeof(dataframe));
    df->xCapacity = xCapacity;
    df->yCapacity = yCapacity;
    df->data = calloc(df->yCapacity, sizeof(vector));
    for (int i = 0; i < df->yCapacity; i++) {
        df->data[i] = newVec(df->xCapacity);
    }
    return df;
}

void destroyDataframe(dataframe *df) {
    for (int i = 0; i < df->yCapacity; i++) {
        destroyVec(df->data[i]);
    }
    free(df->data);
    free(df);
}

int getValueDataframe(dataframe *df, size_t x, size_t y) {
    return getValueVector(df->data[y], x);
}

vector * getVectorDataframe(dataframe *df, size_t y) {
    return df->data[y];
}

void setValueDataframe(dataframe *df, size_t x, size_t y, int value) {
    setValueVector(df->data[y], x, value);
}

void addScalarDataframe(dataframe *df, int value) {
    for (int y = 0; y < df->yCapacity; y++) {
        addScalarVector(df->data[y], value);
    }
}

void printDataframe(dataframe *df) {
    for (int y = 0; y < df->yCapacity; y++) {
        for (int x = 0; x < df->xCapacity; x++) {
            printf("%d ", getValueDataframe(df, x, y));
        }
        printf("\n");
    }
    printf("\n");
}

void testVector() {
    vector *v = newVec(5);
    printVector(v);
    addScalarVector(v, 3);
    printVector(v);
}

void testDataframe() {
    dataframe *df = newDataframe(5, 5);
    printDataframe(df);

    setValueDataframe(df, 1, 2, 5);
    printDataframe(df);

    for (int i = 0; i < df->yCapacity; i++) {
        vector *v = getVectorDataframe(df, i);
        printVector(v);
    }

    addScalarDataframe(df, 3);
    printDataframe(df);

    destroyDataframe(df);
}

int main(void) {
    testVector();
    testDataframe();

    return 0;
}