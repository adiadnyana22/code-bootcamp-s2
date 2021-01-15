#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "model.h"

userList *createUser(const char *username, const char *password){
    userList *newNode = (userList *) malloc(sizeof(userList));
    strcpy(newNode->username, username);
    strcpy(newNode->password, password);
    newNode->headFriendInbox = newNode->tailFriendInbox = NULL;
    newNode->headFriendReq = newNode->tailFriendReq = NULL;
    newNode->headFriendList = newNode->tailFriendList = NULL;
    newNode->headRecycleBin = newNode->tailRecycleBin = NULL;
    newNode->next = newNode->prev = NULL;

    return newNode;
}

void pushUser(const char *username, const char *password){ // pushTail (Queue)
    userList *temp = createUser(username, password);
    if(!headUser){
        headUser = tailUser = temp;
    } else {
        temp->prev = tailUser;
        tailUser->next = temp;
        tailUser = temp;
    }
}

friendReq *createFriendReq(const char *username){
    friendReq *newNode = (friendReq *) malloc(sizeof(friendReq));
    strcpy(newNode->username, username);
    newNode->next = newNode->prev = NULL;

    return newNode;
}

void pushFriendReq(userList *user, const char *username){ // pushTail (Queue)
    friendReq *temp = createFriendReq(username);
    if(user->headFriendReq == NULL){
        user->headFriendReq = user->tailFriendReq = temp;
    } else {
        temp->prev = user->tailFriendReq;
        user->tailFriendReq->next = temp;
        user->tailFriendReq = temp;
    }
}

void popHeadFriendReq(userList *user){
    if (!user->headFriendReq){
        return ;
    } else if(user->headFriendReq == user->tailFriendReq){
        free(user->headFriendReq);
        user->headFriendReq = NULL;
    } else {
        friendReq *candidateHead = user->headFriendReq->next;
        candidateHead->prev = NULL;
        user->headFriendReq->next = NULL;
        free(user->headFriendReq);
        user->headFriendReq = candidateHead;
    }
}

void popTailFriendReq(userList *user){
    if (!user->headFriendReq){
        return ;
    } else if(user->headFriendReq == user->tailFriendReq){
        free(user->headFriendReq);
        user->headFriendReq = NULL;
    } else {
        friendReq *candidateTail = user->tailFriendReq->prev;
        candidateTail->next = NULL;
        user->tailFriendReq->prev = NULL;
        free(user->tailFriendReq);
        user->tailFriendReq = candidateTail;
    }
}

void popFriendReq(userList *user, const char *username){
    if (!user->headFriendReq){
        return;
    } else if(strcmp(user->headFriendReq->username, username) == 0){
        popHeadFriendReq(user);
    } else if(strcmp(user->tailFriendReq->username, username) == 0){
        popTailFriendReq(user);
    } else {
        friendReq *curr = user->headFriendReq;
        while(curr && strcmp(curr->username, username) != 0){
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

friendInbox *createFriendInbox(const char *username){
    friendInbox *newNode = (friendInbox *) malloc(sizeof(friendInbox));
    strcpy(newNode->username, username);
    newNode->next = newNode->prev = NULL;

    return newNode;
}

void pushFriendInbox(userList *user, const char *username){ // pushTail (Queue)
    friendInbox *temp = createFriendInbox(username);
    if(!user->headFriendInbox){
        user->headFriendInbox = user->tailFriendInbox = temp;
    } else {
        temp->prev = user->tailFriendInbox;
        user->tailFriendInbox->next = temp;
        user->tailFriendInbox = temp;
    }
}

void popHeadFriendInbox(userList *user){
    if (!user->headFriendInbox){
        return ;
    } else if(user->headFriendInbox == user->tailFriendInbox){
        free(user->headFriendInbox);
        user->headFriendInbox = NULL;
    } else {
        friendInbox *candidateHead = user->headFriendInbox->next;
        candidateHead->prev = NULL;
        user->headFriendInbox->next = NULL;
        free(user->headFriendInbox);
        user->headFriendInbox = candidateHead;
    }
}

void popTailFriendInbox(userList *user){
    if (!user->headFriendInbox){
        return ;
    } else if(user->headFriendInbox == user->tailFriendInbox){
        free(user->headFriendInbox);
        user->headFriendInbox = NULL;
    } else {
        friendInbox *candidateTail = user->tailFriendInbox->prev;
        candidateTail->next = NULL;
        user->tailFriendInbox->prev = NULL;
        free(user->tailFriendInbox);
        user->tailFriendInbox = candidateTail;
    }
}

void popFriendInbox(userList *user, const char *username){
    if (!user->headFriendInbox){
        return;
    } else if(strcmp(user->headFriendInbox->username, username) == 0){
        popHeadFriendInbox(user);
    } else if(strcmp(user->tailFriendInbox->username, username) == 0){
        popTailFriendInbox(user);
    } else {
        friendInbox *curr = user->headFriendInbox;
        while(curr && strcmp(curr->username, username) != 0){
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

friendList *createFriendList(const char *username){
    friendList *newNode = (friendList *) malloc(sizeof(friendList));
    strcpy(newNode->username, username);
    newNode->next = newNode->prev = NULL;

    return newNode;
}

void pushFriendList(userList *user, const char *username){ // pushTail (Queue)
    friendList *temp = createFriendList(username);
    if(!user->headFriendList){
        user->headFriendList = user->tailFriendList = temp;
    } else {
        temp->prev = user->tailFriendList;
        user->tailFriendList->next = temp;
        user->tailFriendList = temp;
    }
}

void popHeadFriendList(userList *user){
    if (!user->headFriendList){
        return ;
    } else if(user->headFriendList == user->tailFriendList){
        free(user->headFriendList);
        user->headFriendList = NULL;
    } else {
        friendList *candidateHead = user->headFriendList->next;
        candidateHead->prev = NULL;
        user->headFriendList->next = NULL;
        free(user->headFriendList);
        user->headFriendList = candidateHead;
    }
}

void popTailFriendList(userList *user){
    if (!user->headFriendList){
        return ;
    } else if(user->headFriendList == user->tailFriendList){
        free(user->headFriendList);
        user->headFriendList = NULL;
    } else {
        friendList *candidateTail = user->tailFriendList->prev;
        candidateTail->next = NULL;
        user->tailFriendList->prev = NULL;
        free(user->tailFriendList);
        user->tailFriendList = candidateTail;
    }
}

void popFriendList(userList *user, const char *username){
    if (!user->headFriendList){
        return;
    } else if(strcmp(user->headFriendList->username, username) == 0){
        popHeadFriendList(user);
    } else if(strcmp(user->tailFriendList->username, username) == 0){
        popTailFriendList(user);
    } else {
        friendList *curr = user->headFriendList;
        while(curr && strcmp(curr->username, username) != 0){
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

void addFriend(userList *user, const char *username){
    userList *curr = headUser;
    while(curr && strcmp(curr->username, username) != 0){
        curr = curr->next;
    }
    // printf("%s\n", curr->username);
    pushFriendInbox(user, username);
    pushFriendReq(curr, user->username);
}

void acceptFriend(userList *user, const char *username){
    userList *curr = headUser;
    while(curr && strcmp(curr->username, username) != 0){
        curr = curr->next;
    }
    pushFriendList(user, username);
    popFriendInbox(user, username);
    pushFriendList(curr, user->username);
    popFriendReq(curr, user->username);
}

void removeFriend(userList *user, const char *username){
    userList *curr = headUser;
    while(curr && strcmp(curr->username, username) != 0){
        curr = curr->next;
    }
    // printf("%s\n", curr->username);
    popFriendList(user, username);
    popFriendList(curr, user->username);
}

int main(){
    pushUser("adi", "adiadi");
    pushUser("han", "hanhan");
    pushUser("andru", "andruadnru");
    userList *curr = headUser;
    addFriend(curr, "han");
    userList *testSearch = headUser;
    while (testSearch && strcmp(testSearch->username, "han") != 0){
        testSearch = testSearch->next;
    }
    acceptFriend(testSearch, "adi");
    printf("%s\n", testSearch->headFriendList->username);
    printf("%s\n", curr->headFriendList->username);
    removeFriend(testSearch, "adi");
    printf("%s\n", testSearch->headFriendList->username);
    
    return 0;
}