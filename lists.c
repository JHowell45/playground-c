#include <stdlib.h>
#include <stdio.h>

typedef struct listNode {
    int data;
    struct listNode *next;
} listNode;

listNode * newListNode(int data) {
    listNode *node = malloc(sizeof(listNode));
    node->data = data;
    node->next = NULL;
    return node;
}

void freeListNode(listNode *node) {
    if (node->next != NULL) {
        freeListNode(node->next);
    }
    free(node);
}

void listNodePrint(listNode *node) {
    printf("(%d)", node->data);
    listNode *temp = node->next;
    while (temp != NULL) {
        printf("->(%d)", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void listNodePush(listNode *node, int value) {
    if (node->next == NULL) {
        listNode *newNode = newListNode(value);
        node->next = newNode;
    } else {
        listNodePush(node->next, value);
    }
}

void listNodePop(listNode *node) {
    listNode *current = node;
    while (current->next != NULL && current->next->next != NULL) {
        current = current->next;
    }
    current->next = NULL;
}

typedef struct list {
    listNode *root;
    size_t length;
} list;

list * newList(void) {
    list *root = malloc(sizeof(list));
    root->root = NULL;
    root->length = 0;
    return root;
}

void freeList(list *l) {
    freeListNode(l->root);
    free(l);
}

void listPush(list *l, int value) {
    if (l->root == NULL) {
        l->root = newListNode(value);
    } else {
        listNodePush(l->root, value);
    }
    l->length++;
}

void listPop(list *l) {
    if (l->length == 0 && l->root == NULL) {
        return;
    }
    else if (l->length == 1 && l->root->next == NULL) {
        l->root = NULL;
    } else {
        listNodePop(l->root);
    }
    l->length--;
}

size_t listLength(list *l) {
    return l->length;
}

void listPrint(list *l) {
    printf("List {\n");
    printf("\tRoot: ");
    if (l->root == NULL) {
        printf("NULL\n");
    } else {
        listNodePrint(l->root);
    }
    printf("\tLength: %zu\n", l->length);
    printf("}\n");
}

int main(void) {
    list *root = newList();
    for (size_t i = 0; i <= 5; i++) {
        listPush(root, i);
        listPrint(root);
    }
    for (size_t i = 0; i < 3; i++) {
        listPop(root);
        listPrint(root);
    }
    freeList(root);
    return 0;
}