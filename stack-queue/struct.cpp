#include <stdio.h>
#include <stdlib.h>

struct Node {
    int value;
    Node *prev, *next;
};

Node *top;
Node *first, *last;

Node *createNode(int value){
    Node *newNode = (Node *) malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = newNode->prev = NULL;

    return newNode;
}

void pushStack(int value){
    Node *temp = createNode(value);
    if(!top){
        top = temp;
    } else {
        top->prev = temp;
        temp->next = top;
        top = temp;
    }
}

void removeStack(){
    if(!top){
        return;
    } else if(!top->next){
        free(top);
        top = NULL;
    } else {
        Node *candidateTop = top->next;
        top->next = candidateTop->prev = NULL;
        free(top);
        top = candidateTop;
    }
}

void pushQueue(int value){
    Node *temp = createNode(value);
    if(!first){
        first = last = temp;
    } else {
        last->next = temp;
        temp->prev = last;
        last = temp;
    }
}

void removeQueue(){
    if(!first){
        return;
    } else if(first == last){
        free(first);
        first = NULL;
    } else {
        Node *candidateFirst = first->next;
        first->next = candidateFirst->prev = NULL;
        free(first);
        first = candidateFirst;
    }
}

void printStack() {
  Node *curr = top;

  puts("Stack: ");
  while(curr) {
    printf("%d\n", curr->value);
    curr = curr->next; // traverse down
  }
  puts("NULL");
}

void printQueue() {
  Node *curr = first;

  printf("Queue: ");
  while(curr) {
    printf("%d -> ", curr->value);
    curr = curr->next; // traverse right
  }
  puts("NULL");
}

void visualizeStack(int N, int values[]) {
  for(int i = 0; i < N; i++) {
    pushStack(values[i]);
    printf("Inserted %d to the top of the stack.\n", values[i]);
    printStack();
    getchar();
  }

  for(int i = 0; i < N; i++) {
    removeStack();
    puts("Removed the top of the stack.");
    printStack();
    getchar();
  }
}

void visualizeQueue(int N, int values[]) {
  for(int i = 0; i < N; i++) {
    pushQueue(values[i]);
    printf("Inserted %d to the queue.\n", values[i]);
    printQueue();
    getchar();
  }

  for(int i = 0; i < N; i++) {
    removeQueue();
    puts("Removed the first element from the queue.");
    printQueue();
    getchar();
  }
}

int main(){
    int N = 8;
    int values[] = {10, 9, 13, 12, 5, 11, 8, 15};
    // visualizeStack(N, values);
    // visualizeQueue(N, values);

    return 0;
}