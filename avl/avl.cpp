#include <stdio.h>
#include <stdlib.h>

struct Node {
    int value;
    int height;
    int bf;
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
    newNode->bf = 0;
    newNode->right = newNode->left = NULL;

    return newNode;
}

Node *updateNode(Node *root){
    root->height = computeNewHegight(root);
    root->bf = getBalanceFactor(root);

    return root;
}

Node *leftRotate(Node *root){
    Node *pivot = root->right;
    Node *temp = pivot->left;
    pivot->left = root;
    root->right = temp;
    // updateNode(pivot);
    updateNode(root);
    updateNode(pivot);

    return pivot;
}

Node *rightRotate(Node *root){
    Node *pivot = root->left;
    Node *temp = pivot->right;
    pivot->right = root;
    root->left = temp;
    // updateNode(pivot);
    updateNode(root);
    updateNode(pivot);

    return pivot;
}

Node *rotation(Node *root){
    if(root->bf < -1 && root->right->bf <= 0){
        return leftRotate(root);
    } else if(root->bf > 1 && root->left->bf >= 0){
        return rightRotate(root);
    } else if(root->bf > 1 && root->left->bf < 0){
        root->left = leftRotate(root->left);
        return rightRotate(root);
    } else if(root->bf < -1 && root->right->bf > 0){
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

Node *insertNode(Node *root, int value){
    if(!root){
        return createNode(value);
    } else if(value < root->value){
        root->left = insertNode(root->left, value);
    } else if(value > root->value){
        root->right = insertNode(root->right, value);
    }

    return rotation(updateNode(root));
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
            root->left = root->right = NULL;
            free(root);
            root = NULL;

            return candidateRoot;
        }

        Node *candidateRoot = inOrderPredecessor(root);
        root->value = candidateRoot->value;
        root->left = deleteNode(root->left, candidateRoot->value);
    }

    return rotation(updateNode(root));
}

void inOrder(Node *root) {
    if(root) {
        inOrder(root->left);
        printf("| %-3d | %4d   | %7d        |\n", root->value, root->height, root->bf);
        inOrder(root->right);
    }
}

int main(){
    Node *baseRoot = NULL;
    int toInsert[] = {10, 11, 12, 5, 3, 2, 8, 7, 4};

    for(int i = 0; i < 9; i++) {
        baseRoot = insertNode(baseRoot, toInsert[i]);
        printf("\nAdded %d to the tree.\n", toInsert[i]);
        printf("| %-3s | %-5s | %-14s |\n", "Key", "Height", "Balance Factor");
        inOrder(baseRoot); getchar();
    }

    for(int i = 0; i < 9; i++) {
        baseRoot = deleteNode(baseRoot, toInsert[i]);
        printf("\nRemoved %d from the tree.\n", toInsert[i]);
        printf("| %-3s | %-5s | %-14s |\n", "Key", "Height", "Balance Factor");
        inOrder(baseRoot); getchar();
    }

    return 0;
}