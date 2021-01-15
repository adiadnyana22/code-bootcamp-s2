#include <stdio.h>
#include <string.h>

const int MAX_ELEMENT = 5;
const int MAX_LENGTH = 255;
char HASHTABLES[MAX_ELEMENT][MAX_LENGTH];

int hash(const char *str){ //ascii sum hash function
    int sum = 0;
    for (int i = 0; str[i] != '\0'; i++){
        sum += str[i] - '0';
    }

    return sum % MAX_ELEMENT;
}

void linearProbing(const char *str, int index){
    for (int i = (index+1) % MAX_ELEMENT; i != index; i = (i+1) % MAX_ELEMENT){
        if(!HASHTABLES[i][0]){
            strcpy(HASHTABLES[i], str);
            return;
        }
    }
    
    puts("TABLE IS FULL");
}

void insert(const char *str){
    int index = hash(str);
    if(!HASHTABLES[index][0]){
        strcpy(HASHTABLES[index], str);
    } else {
        linearProbing(str, index);
    }
}

void view(){
    puts("HASHTABLE");
    for (int i = 0; i < MAX_ELEMENT; i++){
        printf("Index %d : %s\n", i, HASHTABLES[i]);
    }
}

int main(){
    insert("valdo");
    insert("vincent jonathan");
    insert("cecep");
    insert("ahmad");
    insert("kepin");
    insert("budi");
    view();
}