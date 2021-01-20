#include <stdio.h>
#include <stdlib.h>

int MAX_DEPTH = 0;
// int max[MAX_DEPTH] = 0;

struct Node {
    int key;
    int goldProduce;
    int depth;
    Node *left, *right;
};

Node *createNode(int key, int goldProduce, int depth){
    Node *newNode = (Node *) malloc(sizeof(Node));
    newNode->key = key;
    newNode->goldProduce = goldProduce;
    newNode->depth = depth;
    newNode->left = newNode->right = NULL;

    return newNode;
}

Node *insertNode(Node *root, int key, int goldProduce, int depth){
    if(!root){
        return createNode(key, goldProduce, depth);
    } else if(key < root->key){
        root->left = insertNode(root->left, key, goldProduce, ++depth);
    } else if(key > root->key){
        root->right = insertNode(root->right, key, goldProduce, ++depth);
    }
    if(depth > MAX_DEPTH){
        MAX_DEPTH = depth;
    }

    return root;
}

Node *inOrderPredecessor(Node *root){
    Node *curr = root->left;
    while (curr && curr->right){
        curr = curr->right;
    }
    
    return curr;
}

Node *deleteNode(Node *root, int key){
    if(!root){
        return root;
    } else if(key < root->key){
        root->left = deleteNode(root->left, key);
    } else if(key > root->key){
        root->right = deleteNode(root->right, key);
    } else {
        if(!root->left || !root->right){
            Node *candidateRoot = (root->left) ? root->left : root->right;
            free(root);
            root = NULL;

            return candidateRoot;
        }

        Node *candidateRoot = inOrderPredecessor(root);
        root->key = candidateRoot->key;
        root->left = deleteNode(root->left, candidateRoot->key);
    }

    return root;
}

bool searchNode(Node *root, int key) {
  if(root) {
    if(root->key == key) {
      return true;
    } else if(key < root->key) {
      return searchNode(root->left, key); 
    } else if(key > root->key) {
      return searchNode(root->right, key);
    }
  }

  return false;
}

void inOrder(Node *root) {
    if(root) {
        inOrder(root->left);
        printf("Cave %d\t( depth %d ), total gold production: %d\n", root->key, root->depth, root->goldProduce);
        inOrder(root->right);
    }
}

int calculateReport(Node *root, int *max){
    if(root) {
        max[(root->depth)-1] += root->goldProduce;
        calculateReport(root->left, max);
        calculateReport(root->right, max);
    }
    // for(int i = 0; i < MAX_DEPTH; i++){
    //     printf("Total gold production for depth %d is %d\n", i+1, max[i]);
    // }

    // return max;
}

void inOrderDepth(Node *root) {
    if(root) {
        inOrderDepth(root->left);
        inOrderDepth(root->right);
    }
}

Node* deleteAll(Node* root) {
    if (!root) {
        return NULL;
    }
    else if (root) {
        if (!root->left && !root->right) {
            root = NULL;
            free(root);
        } else if (root->left) {
            deleteAll(root->left);
        } else if (root->right) {
            deleteAll(root->right);
        }
    }

    return root;
}

int main(){
    Node *baseRoot = NULL;

    int flag = 1;
    while(flag == 1){
        // system("clear||cls");
        puts("Hov Mining Simulator");
        puts("====================");
        puts("[1] Insert Mining Data");
        puts("[2] Display All Cave Data");
        puts("[3] Display Mining Reports");
        puts("[4] Exit");
        printf(">> ");
        int menu;
        scanf("%d", &menu);
        if(menu == 1){
            int index;
            printf("Input cave index [1-999]     : ");
            scanf("%d", &index);
            int gold;
            printf("Input gold production [1-100]: ");
            scanf("%d", &gold);
            baseRoot = insertNode(baseRoot, index, gold, 1);
        } else if(menu == 2){
            inOrder(baseRoot);
        } else if(menu == 3){
            int max[MAX_DEPTH];
            for (int i = 0; i < MAX_DEPTH; i++){
                max[i] = 0;
            }
            calculateReport(baseRoot, max);
            for(int i = 0; i < MAX_DEPTH; i++){
                printf("Total gold production for depth %d is %d\n", i+1, max[i]);
            }
        } else if(menu == 4){
            puts("All data has been removed from memory.");
            puts("Thank you for playing, see you again...");
            deleteAll(baseRoot);
            flag = 0;
        }
    }

    return 0;
}