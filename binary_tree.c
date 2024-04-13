#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct node {
    int data;
    struct node *left;
    struct node *right;
} node;

node * newNode(int data) {
    node *n = malloc(sizeof(node));
    n->data = data;
    n->left = NULL;
    n->right = NULL;
    return n;
}

void freeNode(node *n) {
    if (n->left != NULL) {
        freeNode(n->left);
    }
    if (n->right != NULL) {
        freeNode(n->right);
    }
    free(n);
}

void nodeAddLeft(node *root, int leftValue) {
    node *left = newNode(leftValue);
    root->left = left;
}

void nodeAddRight(node *root, int rightValue) {
    node *right = newNode(rightValue);
    root->right = right;
}

void nodeAdd(node *parent, node *newNode) {
    if (newNode->data < parent->data) {
        if (parent->left == NULL) {
            parent->left = newNode;
        } else {
            nodeAdd(parent->left, newNode);
        }
    }
    if (newNode->data >= parent->data) {
        if (parent->right == NULL) {
            parent->right = newNode;
        } else {
            nodeAdd(parent->right, newNode);
        }
    }
}

bool nodeContains(node *node, int search) {
    if (node->data == search) {
        return true;
    }
    if (node->left != NULL && search < node->data) {
        return nodeContains(node->left, search);
    }
    if (node->right != NULL && search >= node->data) {
        return nodeContains(node->right, search);
    }
    return false;
}

typedef struct tree {
    node *root;
} tree;

tree * newTree(void) {
    tree *t = malloc(sizeof(tree));
    t->root = NULL;
    return t;
}

void freeTree(tree *t) {
    free(t->root);
    free(t);
}

void treeAdd(tree *t, node *newNode) {
    if (t->root == NULL) {
        t->root = newNode;
        return;
    }
    nodeAdd(t->root, newNode);
}

bool treeContains(tree *t, int search) {
    if (t->root == NULL) {
        return false;
    }
    return nodeContains(t->root, search);
}

int main(void) {
    tree *root = newTree();

    treeAdd(root, newNode(5));
    treeAdd(root, newNode(3));
    treeAdd(root, newNode(4));
    treeAdd(root, newNode(2));
    treeAdd(root, newNode(8));
    treeAdd(root, newNode(7));
    treeAdd(root, newNode(9));
    treeAdd(root, newNode(6));

    for (int i = 0; i < 10; i++) {
        printf("The tree contains %d: %d\n", i, treeContains(root, i));
    }

    freeTree(root);
    return 0;
}