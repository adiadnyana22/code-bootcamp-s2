#include <stdio.h>
#include <stdlib.h>

struct Node {
    int value;
    Node *next, *prev;
} *head, *tail;

Node *createNode(int value){
    Node *newNode = (Node *) malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = newNode->prev = NULL;

    return newNode;
}

void pushHead(int value){
    Node *temp = createNode(value);
    if (!head){
        head = tail = temp;
    } else {
        head->prev = temp;
        head->next = head;
        head = temp;
    }
    // head->next = NULL;
    // head->prev = NULL;
}

void pushTail(int value){
    Node *temp = createNode(value);
    if (!head){
        head = tail = temp;
    } else {
        tail->next = temp;
        temp->prev = tail;
        tail = temp;
    }   
}

void popHead(){
    if (!head){
        return ;
    } else if(head == tail){
        free(head);
        head = NULL;
    } else {
        Node *candidateHead = head->next;
        candidateHead->prev = NULL;
        head->next = NULL;
        free(head);
        head = candidateHead;
    }
}

void popTail(){
    if (!head){
        return ;
    } else if(head == tail){
        free(head);
        head = NULL;
    } else {
        Node *candidateTail = tail->prev;
        candidateTail->next = NULL;
        tail->prev = NULL;
        free(tail);
        tail = candidateTail;
    }
}

void pushMid(int value){
    if (!head){
        Node *temp = createNode(value);
        head = tail = temp;
    } else if(value < head->value){
        pushHead(value);
    } else if(value > tail->value){
        pushTail(value);
    } else {
        Node *curr = head;
        while(curr->value < value){
            curr = curr->next;
        }
        Node *temp = createNode(value);
        temp->next = curr;
        temp->prev = curr->prev;
        curr->prev->next = temp;
        curr->prev = temp;
    }
}

void popMid(int value){
    if (!head){
        return;
    } else if(value == head->value){
        popHead();
    } else if(value == tail->value){
        popTail();
    } else {
        Node *curr = head;
        while(curr && curr->value != value){
            curr = curr->next;
        }
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
        curr->prev = NULL;
        curr->next = NULL;
        free(curr);
        curr = NULL;
    }
}

void printList(){
    Node *curr = head;

    while(curr){
        printf("%d\n", curr->value);
        curr = curr->next;
    }
}

int main(){


    return 0;
}