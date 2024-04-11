#include <stdlib.h>
#include <stdio.h>

#define VEC_SIZE 5
typedef struct vector {
    size_t capacity;
    float *items;
} vector;

vector * newVec(size_t capacity) {
    vector *vec = malloc(sizeof(vector));
    vec->capacity = capacity;
    vec->items = calloc(vec->capacity, sizeof(float));
    return vec;
}

vector * vecFromArray(float *arr, size_t length) {
    vector *vec = newVec(length);
    for (size_t i = 0; i < length; i++) {
        vec->items[i] = arr[i];
    }
    return vec;
}

void destroyVec(vector *vec) {
    free(vec->items);
    free(vec);
}

float getValueVector(vector *vec, size_t index) {
    return vec->items[index];
}

void setValueVector(vector *vec, size_t index, float value) {
    vec->items[index] = value;
}

void addScalarVector(vector *vec, float scalar) {
    for (size_t i = 0; i < vec->capacity; i++) {
        vec->items[i] += scalar;
    }
}

void printVector(vector *vec) {
    printf("[%.2f", vec->items[0]);
    for (size_t i = 1; i < vec->capacity; i++) {
        printf(", %.2f", vec->items[i]);
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
    for (size_t i = 0; i < df->yCapacity; i++) {
        df->data[i] = newVec(df->xCapacity);
    }
    return df;
}

void destroyDataframe(dataframe *df) {
    for (size_t i = 0; i < df->yCapacity; i++) {
        destroyVec(df->data[i]);
    }
    free(df->data);
    free(df);
}

float getValueDataframe(dataframe *df, size_t x, size_t y) {
    return getValueVector(df->data[y], x);
}

vector * getVectorDataframe(dataframe *df, size_t y) {
    return df->data[y];
}

void setValueDataframe(dataframe *df, size_t x, size_t y, float value) {
    setValueVector(df->data[y], x, value);
}

void addScalarDataframe(dataframe *df, float value) {
    for (size_t y = 0; y < df->yCapacity; y++) {
        addScalarVector(df->data[y], value);
    }
}

float addVectorDataframe(dataframe *df, vector *vec) {
    if (df->yCapacity != vec->capacity) {
        return -1;
    }
    for (size_t i = 0; i < df->yCapacity; i++) {
        addScalarVector(df->data[i], getValueVector(vec, i));
    }
    return 0;
}

void printDataframe(dataframe *df) {
    for (size_t y = 0; y < df->yCapacity; y++) {
        for (size_t x = 0; x < df->xCapacity; x++) {
            printf("%.2f ", getValueDataframe(df, x, y));
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
    destroyVec(v);
}

void testDataframe() {
    dataframe *df = newDataframe(5, 5);
    printDataframe(df);

    setValueDataframe(df, 1, 2, 5);
    printDataframe(df);

    for (size_t i = 0; i < df->yCapacity; i++) {
        vector *v = getVectorDataframe(df, i);
        printVector(v);
    }

    // addScalarDataframe(df, 3);
    float arr[VEC_SIZE] = {1,2,3,4,5};
    printf("Vector:\n");
    vector *vec = vecFromArray(arr, VEC_SIZE);
    // free(arr);
    printVector(vec);

    addVectorDataframe(df, vec);

    destroyVec(vec);

    printDataframe(df);

    destroyDataframe(df);
}

int main(void) {
    testVector();
    testDataframe();

    return 0;
}