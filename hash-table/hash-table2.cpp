#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int MAX_ELEMENT = 10;
int COLLISION_COUNT = 0;

struct Node {
    char name[255];
    Node *next;
} *head[MAX_ELEMENT], *tail[MAX_ELEMENT];

Node *createNode(const char *name){
    Node *newNode = (Node *) malloc(sizeof(Node));
    strcpy(newNode->name, name);
    newNode->next = NULL;

    return newNode;
}

int hash(const char *str){
    int sum = 0;
    for (int i = 0; str[i] != '\0'; i++){
        sum += str[i] - 'a';
    }
    
    return sum % MAX_ELEMENT;
}

void insert(const char *str){
    int index = hash(str);
    Node *temp = createNode(str);
    if(!head[index]){
        head[index] = tail[index] = temp;
    } else {
        COLLISION_COUNT++;
        tail[index]->next = temp;
        tail[index] = temp;
    }
}

void view(){
    for (int i = 0; i < MAX_ELEMENT; i++){
        printf("Index %d : ", i);
        Node *curr = head[i];

        if(head[i]) { // if head exists
            Node *curr = head[i];

            while(curr) {
                printf("%s -> ", curr->name);
                curr = curr->next;
            }
        } 
        puts("NULL");
    }
}

int main() {
  insert("carrick");
  insert("bryan");
  insert("nicholas");
  insert("leonardo");
  insert("romario");
  insert("kevin");
  insert("dodi");
  insert("masmas");
  insert("leody");
  insert("jollybee");
  insert("it division");
  insert("saya senang socs");
  insert("zoom meetings");
  insert("cecep");
  view();
  printf("%d\n", COLLISION_COUNT);

  return 0;
}