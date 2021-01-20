#include <stdio.h>
#include <stdlib.h>

struct Node {
    int value;
    int height;
    Node *left, *right;
};

int max(int a, int b){
    return (a > b) ? a : b;
}

int getHeight(Node *root){
    return (root) ? root->height : 0;
}

int getBalanceFactor(Node *root){
    return (root) ? getHeight(root->left) - getHeight(root->right) : 0;
}

int computeNewHegight(Node *root){
    return max(getHeight(root->left), getHeight(root->right)) + 1;
}

Node *createNode(int value){
    Node *newNode = (Node *) malloc(sizeof(Node));
    newNode->value = value;
    newNode->height = 1;
    newNode->right = newNode->left = NULL;

    return newNode;
}

Node *insertNode(Node *root, int value){
    if(!root){
        return createNode(value);
    } else if(value < root->value){
        root->left = insertNode(root->left, value);
    } else if(value > root->value){
        root->right = insertNode(root->right, value);
    }

    return rotation(root);
}

Node *inOrderPredecessor(Node *root){
    Node *curr = root->left;
    while (curr && curr->right){
        curr = curr->right;
    }
    
    return curr;
}

Node *deleteNode(Node *root, int value){
    if(!root){
        return root;
    } else if(value < root->value){
        root->left = deleteNode(root->left, value);
    } else if(value > root->value){
        root->right = deleteNode(root->right, value);
    } else {
        if(!root->left || !root->right){
            Node *candidateRoot = (root->left) ? root->left : root->right;
            free(root);
            root = NULL;

            return candidateRoot;
        }

        Node *candidateRoot = inOrderPredecessor(root);
        root->value = candidateRoot->value;
        root->left = deleteNode(root->left, candidateRoot->value);
    }

    return (root) ? rotation(root) : root;
}

int main(){
    Node *baseNode = NULL;

    return 0;
}