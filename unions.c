#include <stdlib.h>
#include <stdio.h>

typedef enum DataType {
    INT,
    FLOAT,
    DOUBLE,
    CHAR,
    STRING,
} DataType;

typedef union object {
    int i;
    float f;
    double d;
    char c;
} object;

object * newInt(int value) {
    object *newObj = malloc(sizeof(object));
    newObj->i = value;
    return newObj;
}

typedef struct generic {
    object *data;
    DataType type;
} generic;

generic * Int(int value) {
    generic *gen = malloc(sizeof(generic));
    gen->data = newInt(value);
    gen->type = INT;
    return gen;
}

void addGeneric(generic *root, generic *add) {
    if (root->type == INT && add->type == INT) {
        root->data->i += add->data->i;
    }
}

void printGeneric(generic *gen) {
    switch (gen->type)
    {
    case INT:
        printf("Integer { %d }\n", gen->data->i);
        break;
    
    default:
        break;
    }
}

int main(void) {
    generic *i = Int(5);
    generic *add = Int(10);
    printGeneric(i);
    printGeneric(add);
    addGeneric(i, add);
    printGeneric(i);
    return 0;
}