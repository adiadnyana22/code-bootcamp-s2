#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Node {
    char name[255];
    int score;
    Node *next;
} *head, *tail;

Node *createNode(const char *name, int score){
    Node *newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->name, name);
    newNode->score = score;
    newNode->next = NULL;

    return newNode;
}

void pushHead(const char *name, int score){
    Node *temp = createNode(name, score);
    if(!head){
        head = tail = temp;
    } else {
        temp->next = head;
        head = temp;
    }
}

void pushTail(const char *name, int score){
    Node *temp = createNode(name, score);
    if(!head){
        head = tail = temp;
    } else {
        tail->next = temp;
        tail = temp;
    }
}

void popHead(){
    if (!head){
        return;
    } else if(head == tail){
        free(head);
        head = tail = NULL;
    } else {
        Node *temp = head->next;
        head->next = NULL;
        free(head);
        head = temp;
    }
    
}

void popTail(){
    if (!head){
        return;
    } else if(head == tail){
        free(head);
        head = tail = NULL;
    } else {
        Node *temp = head;
        while(temp->next != tail){
            temp = temp->next;
        }
        tail->next = NULL;
        free(tail);
        tail = temp;
    }
}

void printList(){
    Node *curr = head;

    while(curr){
        printf("%s %d\n", curr->name, curr->score);
        curr = curr->next;
    }
}

int main() {
    pushHead("Adi", 100);
    pushTail("Yoyo", 85);
    pushTail("Nico", 90);
    printList();

    // printf("%s %d\n", head->name, head->score);

    return 0;
}