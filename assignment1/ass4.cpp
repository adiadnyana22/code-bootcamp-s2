#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Node {
    int score;
    Node *next;
} *head, *tail;

Node *createNode(int score){
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->score = score;
    newNode->next = NULL;

    return newNode;
}

void pushHead(int score){
    Node *temp = createNode(score);
    if(!head){
        head = tail = temp;
    } else {
        temp->next = head;
        head = temp;
    }
}

void pushTail(int score){
    Node *temp = createNode(score);
    if(!head){
        head = tail = temp;
    } else {
        tail->next = temp;
        tail = temp;
    }
}

void pushMid(int value) {
    Node* temp = createNode(value);
    if (!head) {
        head = tail = temp;
    }
    else if (head->score < value) {
        pushHead(value);
    }
    else if (tail->score >= value) {
        pushTail(value);
    }
    else {
        Node* curr = head;
        while (curr->next && curr->next->score > value) {
            curr = curr->next;
        }
        temp->next = curr->next;
        curr->next = temp;
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
        tail->next = NULL;
    }
}

void popMid(Node *before, Node *here){
    before->next = here->next;
    here->next = NULL;
    free(here);
}

void printList(){
    Node *curr = head;

    while(curr){
        printf("%d\n", curr->score);
        curr = curr->next;
    }
}

void pop(int value) {
    if (!head) {
        return;
    }
    else if (value == head->score) {
        popHead();
    }
    else if (value == tail->score) {
        popTail();
    }
    else {
        Node* temp = head;
        while (temp->next && temp->next->score != value) {
            temp = temp->next;
        }
        if (!temp->next) {
            return;
        }
        Node* temp2 = temp->next;
        if (temp->next->next) {
            temp->next = temp->next->next;
            temp->next->next = NULL;
            free(temp->next->next);
        }
        else {
            temp->next = NULL;
            free(temp->next);
        }
        free(temp2);
    }
}

void delet() {
    if (!head) {
        return;
    }
    Node* temp = head;
    while (temp) {
        if (!temp->next) {
            return;
        }
        Node* temp2 = temp->next;
        while (temp2) {
            if (temp->score == temp2->score) {
                // pop(temp2->score);
                popMid(temp, temp2);
            }
            temp2 = temp2->next;
        }
        temp = temp->next;
    }
}

void deleteall() {
    Node* temp = head;
    if (!head) {
        return;
    }
    delet();
    while (temp) {
        temp = temp->next;
        delet();
    }
}

int main() {
    pushTail(100);
    pushTail(99);
    pushTail(99);
    pushTail(98);
    pushTail(97);
    pushTail(96);
    pushTail(95);
    pushTail(95);
    pushTail(95);
    pushTail(94);
    // pushTail(94);

    // Node *curr = head;
    // while (curr){
    //     if(curr->score == curr->next->score){
    //         if(curr->next == tail){
    //             popTail();
    //             break;
    //         } else {
    //             pop(curr->score);
    //         }
    //     }

        // curr = curr->next;
        // if (curr->score == curr->next->score) { 
            /* The sequence of steps is important*/       
            // temp = curr->next->next;
            // free(curr->next); 
            // curr->next = temp; 
            // pop(curr->score);
        // } else { 
        //     curr = curr->next; 
        // } 
    //     curr = curr->next;
    // }
    // popTail();

    deleteall();
    
    printList();

    return 0;
}