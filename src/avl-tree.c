#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct AVLNode_t {
    int data;
    struct AVLNode_t *left, *right;
    int height;
} AVLNode;

typedef struct AVL_t {
    AVLNode *root;
    unsigned int size;
} AVL;

// Helper function
int _max(int num1, int num2) {
    return (num1 > num2 ? num1 : num2);
}

// Util function
int _getHeight(AVLNode* node){
    if(node==NULL)
        return 0; 
    return node->height;
}

int _getBalanceFactor(AVLNode* node){
    if(node==NULL)
        return 0;
    return _getHeight(node->left)-_getHeight(node->right);
}

AVLNode* _avl_createNode(int value) {
    AVLNode *newNode = (AVLNode*) malloc(sizeof(AVLNode));
    newNode->data = value;
    newNode->height=1;
    newNode->left = newNode->right = NULL;
    return newNode;
}

AVLNode* _search(AVLNode *root, int value) {
    while (root != NULL) {
        if (value < root->data)
            root = root->left;
        else if (value > root->data)
            root = root->right;
        else
            return root;
    }
    return root;
}

AVLNode* _rightRotate(AVLNode* pivotNode){

    AVLNode* newParrent=pivotNode->left;
    pivotNode->left=newParrent->right;
    newParrent->right=pivotNode;

    pivotNode->height=_max(_getHeight(pivotNode->left),
                    _getHeight(pivotNode->right))+1;
    newParrent->height=_max(_getHeight(newParrent->left),
                    _getHeight(newParrent->right))+1;
    
    return newParrent;
}

AVLNode* _leftCaseRotate(AVLNode* node){
    return _rightRotate(node);
}

AVLNode* _leftRotate(AVLNode* pivotNode){

    AVLNode* newParrent=pivotNode->right;
    pivotNode->right=newParrent->left;
    newParrent->left=pivotNode;

    pivotNode->height=_max(_getHeight(pivotNode->left),
                    _getHeight(pivotNode->right))+1;
    newParrent->height=_max(_getHeight(newParrent->left),
                    _getHeight(newParrent->right))+1;
    
    return newParrent;
}

AVLNode* _rightCaseRotate(AVLNode* node){
    return _leftRotate(node);
}

AVLNode* _leftRightCaseRotate(AVLNode* node){
    node->left=_leftRotate(node->left);
    return _rightRotate(node);
}

AVLNode* _rightLeftCaseRotate(AVLNode* node){
    node->right=_rightRotate(node->right);
    return _leftRotate(node);
}

AVLNode* _insert_AVL(AVL *avl,AVLNode* node,int value){
    
    if(node==NULL)
        return _avl_createNode(value);
    if(value < node->data)
        node->left = _insert_AVL(avl,node->left,value);
    else if(value > node->data)
        node->right = _insert_AVL(avl,node->right,value);
    
    node->height= 1 + _max(_getHeight(node->left),_getHeight(node->right)); 

    int balanceFactor=_getBalanceFactor(node);
    
    if(balanceFactor > 1 && value < node->left->data)
        return _leftCaseRotate(node);
    if(balanceFactor > 1 && value > node->left->data)
        return _leftRightCaseRotate(node);
    if(balanceFactor < -1 && value > node->right->data)
        return _rightCaseRotate(node);
    if(balanceFactor < -1 && value < node->right->data)
        return _rightLeftCaseRotate(node);
    
    return node;
}

AVLNode* _findMinNode(AVLNode *node) {
    AVLNode *currNode = node;
    while (currNode && currNode->left != NULL)
        currNode = currNode->left;
    return currNode;
}

AVLNode* _remove_AVL(AVLNode* node,int value){
    if(node==NULL)
        return node;
    if(value > node->data)
        node->right=_remove_AVL(node->right,value);
    else if(value < node->data)
        node->left=_remove_AVL(node->left,value);
    else{
        AVLNode *temp;
        if((node->left==NULL)||(node->right==NULL)){
            temp=NULL;
            if(node->left==NULL) temp=node->right;  
            else if(node->right==NULL) temp=node->left;
            
            if(temp==NULL){
                temp=node;
                node=NULL;
            }
            else
                *node=*temp;   
            
            free(temp);
        }
        else{
            temp = _findMinNode(node->right);
            node->data=temp->data;
            node->right=_remove_AVL(node->right,temp->data);
        }    
    }

    if(node==NULL) return node;
    
    node->height=_max(_getHeight(node->left),_getHeight(node->right))+1;

    int balanceFactor= _getBalanceFactor(node);
    
    if(balanceFactor>1 && _getBalanceFactor(node->left)>=0) 
        return _leftCaseRotate(node);

    if(balanceFactor>1 && _getBalanceFactor(node->left)<0) 
        return _leftRightCaseRotate(node);

    if(balanceFactor<-1 && _getBalanceFactor(node->right)<=0) 
        return _rightCaseRotate(node);

    if(balanceFactor<-1 && _getBalanceFactor(node->right)>0) 
        return _rightLeftCaseRotate(node);
    
    return node;
}

void u_inorder(AVLNode *root) {
    if (root) {
        u_inorder(root->left);
        printf("%d ", root->data);
        u_inorder(root->right);
    }
}

void u_postorder(AVLNode *root) {
    if (root) {
        u_postorder(root->left);
        u_postorder(root->right);
        printf("%d ", root->data);
    }
}

void u_preorder(AVLNode *root) {
    if (root) {
        printf("%d ", root->data);
        u_preorder(root->left);
        u_preorder(root->right);
    }
}

// Main function
void avl_init(AVL *avl) {
    avl->root = NULL;
    avl->size = 0;
}

bool avl_find(AVL *avl, int value) {
    AVLNode *temp = _search(avl->root, value);
    if (temp == NULL)
        return false;
    
    if (temp->data == value)
        return true;
    else
        return false;
}

void avl_insert(AVL *avl,int value){
    if(!avl_find(avl,value)){
        avl->root = _insert_AVL(avl,avl->root,value);
        avl->size++;
    }
}

void avl_remove(AVL *avl,int value) {
    if(avl_find(avl,value)) {
        avl->root=_remove_AVL(avl->root,value);
        avl->size--;
    }
}

void inorder(AVL *tree) {
    u_inorder(tree->root);
}

void postorder(AVL *tree) {
    u_postorder(tree->root);
}

void preorder(AVL *tree) {
    u_preorder(tree->root);
}

int main() { 
    AVL myAvl;
    avl_init(&myAvl);
    avl_insert(&myAvl,1);
    avl_insert(&myAvl,2);
    avl_insert(&myAvl,3);
    avl_insert(&myAvl,4);
	avl_insert(&myAvl,5);
	avl_insert(&myAvl,7);
	avl_insert(&myAvl,99);
	avl_insert(&myAvl,12);
	avl_insert(&myAvl,31);

	avl_remove(&myAvl,1);
	avl_remove(&myAvl,99);
	avl_remove(&myAvl,4);
	avl_remove(&myAvl,12);
	avl_remove(&myAvl,31);

    preorder(&myAvl);
    puts("");

    return 0; 
}