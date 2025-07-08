#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct BST_Node_t {
    int key;
    struct BST_Node_t *left, *right;
} BSTNode;

typedef struct BST_t {
    struct BST_Node_t *root;
    size_t size;
} BST;

// Utility function
BSTNode *u_createNode(int key) {
    BSTNode *newNode = malloc(sizeof(BSTNode));
    if (newNode) {
        newNode->key = key;
        newNode->left = newNode->right = NULL;

        return newNode;
    }
    return NULL;
}

BSTNode *u_search(BSTNode *root, int key) {
    while (root != NULL) {
        if (key < root->key) {
            root = root->left;
        } else if (key > root->key) {
            root = root->right;
        } else {
            return root;
        }
    }
    return root;
}

BSTNode *u_insert(BSTNode *root, int key) {
    if (root == NULL) {
        return u_createNode(key);
    }

    if (key < root->key) {
        root->left = u_insert(root->left, key);
    } else if (key > root->key) {
        root->right = u_insert(root->right, key);
    }

    return root;
}

BSTNode *u_findMinNode(BSTNode *root) {
    BSTNode *currNode = root;
    while (currNode && currNode->left != NULL) {
        currNode = currNode->left;
    }
    return currNode;
}

BSTNode *u_remove(BSTNode *root, int key) {
    if (root == NULL) 
        return root;

    if (key < root->key) {
        root->left = u_remove(root->left, key);
    } else if (key > root->key) {
        root->right = u_remove(root->right, key);
    } else {
        if (root->left == NULL) {
            BSTNode *rightChild = root->right;
            free(root);
            return rightChild;
        } else if (root->right == NULL) {
            BSTNode *leftChild = root->left;
            free(root);
            return leftChild;
        }

        BSTNode *temp = u_findMinNode(root->right);
        root->key = temp->key;
        root->right = u_remove(root->right, temp->key);
    }
    return root;
}

void u_inorder(BSTNode *root) {
    if (root) {
        u_inorder(root->left);
        printf("%d ", root->key);
        u_inorder(root->right);
    }
}

void u_postorder(BSTNode *root) {
    if (root) {
        u_postorder(root->left);
        u_postorder(root->right);
        printf("%d ", root->key);
    }
}

void u_preorder(BSTNode *root) {
    if (root) {
        printf("%d ", root->key);
        u_preorder(root->left);
        u_preorder(root->right);
    }
}

void u_destroy(BSTNode *root) {
    if (root) {
        u_destroy(root->left);
        u_destroy(root->right);
        free(root);
    }
}

// Primary Function
void init(BST *tree) {
    tree->root = NULL;
    tree->size = 0;
}

bool isEmpty(BST *tree) {
    return (tree->root == NULL);
}

bool find(BST *tree, int key) {
    BSTNode *temp = u_search(tree->root, key);
    if (temp == NULL) {
        return false;
    }

    if (temp->key == key) {
        return true;
    } else {
        return false;
    }
}

void insertNode(BST *tree, int key) {
    if (!find(tree, key)) {
        tree->root = u_insert(tree->root, key);
        tree->size++;
    }
}

void removeNode(BST *tree, int key) {
    if (find(tree, key)) {
        tree->root = u_remove(tree->root, key);
        tree->size--;
    }
}

void inorder(BST *tree) {
    u_inorder(tree->root);
}

void postorder(BST *tree) {
    u_postorder(tree->root);
}

void preorder(BST *tree) {
    u_preorder(tree->root);
}

void destroy(BST *tree) {
    u_destroy(tree->root);
    tree->root = NULL;
    tree->size = 0;
}

int main() {
    BST tree;
    init(&tree);

    insertNode(&tree, 6);
    insertNode(&tree, 1);
    insertNode(&tree, 8);
    insertNode(&tree, 12);
    insertNode(&tree, 1);
    insertNode(&tree, 3);
    insertNode(&tree, 7);

    inorder(&tree);
    puts("");

    removeNode(&tree, 8);
    removeNode(&tree, 6);

    inorder(&tree);
    puts("");

    destroy(&tree);
    return 0;
}