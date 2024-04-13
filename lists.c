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

void listInsert(list *l, int value, size_t index) {
    listNode *newNode = newListNode(value);
    if (index == 0) {
        newNode->next = l->root;
        l->root = newNode;
    } else {
        listNode *temp = l->root;
        for (size_t i = 0; i < index - 1; i++) {
            temp = temp->next;
        }
        newNode->next = temp->next;
        temp->next = newNode;
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

void listRemove(list *l, size_t index) {
    listNode *temp = l->root;
    if (index == 0) {
        listNode *newRoot = temp->next;
        temp->next = NULL;
        freeListNode(temp);
        l->root = newRoot;
    } else {
        for (size_t i = 1; i < index; i++) {
            temp = temp->next;
        }
        listNode *remove = temp->next;
        listNode *next = remove->next;
        remove->next = NULL;
        temp->next = next;
        freeListNode(remove);
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

    listInsert(root, 7, 1);
    listPrint(root);
    listInsert(root, 10, 0);
    listPrint(root);
    listInsert(root, 9, 4);
    listPrint(root);

    listRemove(root, 0);
    listPrint(root);

    listRemove(root, 1);
    listPrint(root);

    freeList(root);
    return 0;
}