#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "model.h"

userList *createUser(const char *username, const char *password){
    userList *newNode = (userList *) malloc(sizeof(userList));
    newNode = NULL;
    strcpy(newNode->username, username);
    strcpy(newNode->password, password);
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

friendReq *createFiendReq(userList *user, const char *username){
    friendReq *newNode = (friendReq *) malloc(sizeof(friendReq));
    strcpy(newNode->username, username);
    newNode->next = newNode->prev = NULL;

    return newNode;
}

void pushFriendReq(userList *user, const char *username){ // pushTail (Queue)
    friendReq *temp = createFiendReq(user, username);
    if(!user->headFriendReq){
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
    } else if(username == user->headFriendReq->username){
        popHeadFriendReq(user);
    } else if(username == user->tailFriendReq->username){
        popTailFriendReq(user);
    } else {
        friendReq *curr = user->headFriendReq;
        while(curr && curr->username != username){
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

friendInbox *createFiendInbox(userList *user, const char *username){
    friendInbox *newNode = (friendInbox *) malloc(sizeof(friendInbox));
    strcpy(newNode->username, username);
    newNode->next = newNode->prev = NULL;

    return newNode;
}

void pushFriendInbox(userList *user, const char *username){ // pushTail (Queue)
    friendInbox *temp = createFiendInbox(user, username);
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
    } else if(username == user->headFriendInbox->username){
        popHeadFriendInbox(user);
    } else if(username == user->tailFriendInbox->username){
        popTailFriendInbox(user);
    } else {
        friendInbox *curr = user->headFriendInbox;
        while(curr && curr->username != username){
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

friendList *createFiendList(userList *user, const char *username){
    friendList *newNode = (friendList *) malloc(sizeof(friendList));
    strcpy(newNode->username, username);
    newNode->next = newNode->prev = NULL;

    return newNode;
}

void pushFriendList(userList *user, const char *username){ // pushTail (Queue)
    friendList *temp = createFiendList(user, username);
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
    } else if(username == user->headFriendList->username){
        popHeadFriendList(user);
    } else if(username == user->tailFriendList->username){
        popTailFriendList(user);
    } else {
        friendList *curr = user->headFriendList;
        while(curr && curr->username != username){
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
    while(curr && curr->username != username){
        curr = curr->next;
    }
    pushFriendInbox(user, username);
    pushFriendReq(curr, user->username);
}

void acceptFriend(userList *user, const char *username){
    userList *curr = headUser;
    while(curr && curr->username != username){
        curr = curr->next;
    }
    pushFriendList(user, username);
    popFriendInbox(user, username);
    pushFriendList(curr, user->username);
    popFriendReq(curr, user->username);
}

int main(){
    return 0;
}