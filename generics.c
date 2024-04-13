#include <stdlib.h>
#include <stdio.h>

typedef struct string {
    char *val;
    size_t length;
} string;

typedef enum Datatype {
    Int,
    Float,
    Char,
    String,
} Datatype;

typedef union generic {
    int i;
    float f;
    double d;
    string s;
} generic;

generic * newGenericInt(int value) {
    generic *v = malloc(sizeof(generic));
    v->i = value;
    return v;
}

int genericGetInt(generic *gen) {
    return gen->i;
}

typedef struct object {
    Datatype type;
    generic *data;
} object;

object * newInt(int value) {
    generic *data = newGenericInt(value);
    object *obj = malloc(sizeof(object));
    obj->data = data;
    obj->type = Int;
    return obj;
}

object * objectAdd(object *first, object *second) {
    object *newObj = malloc(sizeof(object));
    if (first->type == Int && second->type == Int) {
        newObj = newInt(genericGetInt(first->data) + genericGetInt(second->data));
    }
    return newObj;
}

object * objectSub(object *first, object *second) {
    object *newObj = malloc(sizeof(object));
    if (first->type == Int && second->type == Int) {
        newObj = newInt(genericGetInt(first->data) - genericGetInt(second->data));
    }
    return newObj;
}

void printObject(object *obj) {
    printf("object {\n");
    switch (obj->type) {
        case Int:
            printf("\tdata: %d\n", obj->data->i);
            break;
        default:
            printf("\tdata: Invalid\n");
            break;
    }
    printf("\ttype: Int\n");
    printf("}\n");
}

int main(void) {
    object *a = newInt(10);
    object *b = newInt(10);
    printObject(a);
    printObject(b);
    
    object *c = objectAdd(a, b);
    printObject(c);

    c = objectSub(c, newInt(15));
    printObject(c);
    return 0;
}