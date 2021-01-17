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

void cancelFriendReq(userList *user, const char *username){
    userList *curr = headUser;
    while(curr && strcmp(curr->username, username) != 0){
        curr = curr->next;
    }
    popFriendInbox(user, username);
    popFriendInbox(curr, user->username);
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

void printFriendToAdd(userList *user){
    userList *curr = headUser;
    int count = 1;
    while(curr){
        int flag = 1;
        if(strcmp(curr->username, user->username) == 0){
            flag = 0;
        }
        friendList *currList = user->headFriendList;
        while(currList){
            if(strcmp(currList->username, curr->username) == 0){
                flag = 0;
                break;
            }
            currList = currList->next;
        }
        friendReq *currReq = user->headFriendReq;
        while(currReq){
            if(strcmp(currReq->username, curr->username) == 0){
                flag = 0;
                break;
            }
            currReq = currReq->next;
        }
        friendInbox *currInbox = user->headFriendInbox;
        while(currInbox){
            if(strcmp(currInbox->username, curr->username) == 0){
                flag = 0;
                break;
            }
            currInbox = currInbox->next;
        }
        if(flag == 1){
            printf("%d. %s\n", count++, curr->username);
        }
        curr = curr->next;
    }
}

void printUser(){
    int count = 1;
    userList *curr = headUser;
    while (curr){
        printf("%d. %s\n", count++, curr->username);
        curr = curr->next;
    }
}

void printFriendList(userList *user){
    int count = 1;
    friendList *curr = user->headFriendList;
    while (curr){
        printf("%d. %s\n", count++, curr->username);
        curr = curr->next;
    }
}

void printFriendReq(userList *user){
    int count = 1;
    friendReq *curr = user->headFriendReq;
    while (curr){
        printf("%d. %s\n", count++, curr->username);
        curr = curr->next;
    }
}

void printFriendInbox(userList *user){
    int count = 1;
    friendInbox *curr = user->headFriendInbox;
    while (curr){
        printf("%d. %s\n", count++, curr->username);
        curr = curr->next;
    }
}

bool validateUsernameRegis(const char *username){
    userList *curr = headUser;
    while(curr){
        if(strcmp(curr->username, username) == 0){
            return false;
        }
        curr = curr->next;
    }

    return true;
}

userList *validateUsernameLogIn(const char *username, const char *password){
    userList *curr = headUser;
    while(curr){
        if(strcmp(curr->username, username) == 0 && strcmp(curr->password, password) == 0){
            return curr;
        }
        curr = curr->next;
    }

    return false;
}

note *createNote(const char *title, const char *content, const char *category){
    note *newNote = (note *) malloc(sizeof(note));
    strcpy(newNote->title, title);
    strcpy(newNote->content, content);
    strcpy(newNote->category, category);
    newNote->next = newNote->prev = NULL;

    return newNote;
}

void pushNote(userList *user, const char *title, const char *content, const char *category){
    note *temp = createNote(title, content, category);
    if(!user->headNote){
        user->headNote = user->tailNote = temp;
    } else {
        temp->prev = user->tailNote;
        user->tailNote->next = temp;
        user->tailNote = temp;
    }
}

void popHeadNote(userList *user){
    if (!user->headNote){
        return ;
    } else if(user->headNote == user->tailNote){
        free(user->headNote);
        user->headNote = NULL;
    } else {
        note *candidateHead = user->headNote->next;
        candidateHead->prev = NULL;
        user->headNote->next = NULL;
        free(user->headNote);
        user->headNote = candidateHead;
    }
}

void popTailNote(userList *user){
    if (!user->headNote){
        return ;
    } else if(user->headNote == user->tailNote){
        free(user->headNote);
        user->headNote = NULL;
    } else {
        note *candidateTail = user->tailNote->prev;
        candidateTail->next = NULL;
        user->tailNote->prev = NULL;
        free(user->tailNote);
        user->tailNote = candidateTail;
    }
}

void popNote(userList *user, const char *title){
    if (!user->headNote){
        return;
    } else if(strcmp(user->headNote->title, title) == 0){
        popHeadNote(user);
    } else if(strcmp(user->tailNote->title, title) == 0){
        popTailNote(user);
    } else {
        note *curr = user->headNote;
        while(curr && strcmp(curr->title, title) != 0){
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

void editNote(userList *user, const char *title, const char *newTitle, const char *newContent, const char *newCategory){
    note *curr = user->headNote;
    while(curr && strcmp(curr->title, title) != 0){
        curr = curr->next;
    }
    strcpy(curr->title, newTitle);
    strcpy(curr->content, newContent);
    strcpy(curr->category, newCategory);
}

void printNote(userList *user){
    int count = 1;
    note *curr = user->headNote;
    while(curr){
        printf("%d. %s\n", count++, curr->title);
        curr = curr->next;
    }
}

bool validateNoteHeader(userList *user, const char *title){
    note *curr = user->headNote;
    while(curr){
        if(strcmp(curr->title, title) == 0){
            return false;
        }
        curr = curr->next;
    }

    return true;
}

publicDashboard *createNote(const char *username, const char *title, const char *content, const char *category, bool privateOrPublic, const char *prvFriend1, const char *prvFriend2, const char *prvFriend3){
    publicDashboard *newNote = (publicDashboard *) malloc(sizeof(publicDashboard));
    strcpy(newNote->username, username);
    strcpy(newNote->title, title);
    strcpy(newNote->content, content);
    strcpy(newNote->category, category);
    newNote->like = 0;
    newNote->privateOrPublic = privateOrPublic;
    strcpy(newNote->privateFriend[0], prvFriend1);
    strcpy(newNote->privateFriend[1], prvFriend2);
    strcpy(newNote->privateFriend[2], prvFriend3);
    newNote->headComment = newNote->tailComment = NULL;
    newNote->next = newNote->prev = NULL;

    return newNote;
}

int main(){
    int globalFlag = 1;
    while(globalFlag == 1){
        printf("Oo====================================oO\n");
        printf("\t      STUDY NETWORK\n");
        printf("Oo====================================oO\n");

        printf("[All User]\nNo.\tUsername\n");
        printUser();
        printf("----------------------------------------\n");
        printf("[1] Register\n[2] Login\n[3] Exit\n");
        printf("----------------------------------------\n");
        printf("Press 0 and enter to abort an operation\n");
        printf("----------------------------------------\n");
        printf(">> ");
        int menu;
        scanf("%d", &menu);
        printf("----------------------------------------\n");
        if(menu == 1){
            char username[25], password[25];
            printf("Please type in your username [lowercase || 1..24]: ");
            scanf("%s", username);
            printf("Please type in your password [lowercase || 1..24]: ");
            scanf("%s", password);
            if(validateUsernameRegis(username)){
                pushUser(username, password);
                printf("-- Registration Successfull --\n");
            } else {
                printf("Username already in use\n");
            }
        } else if(menu == 2){
            char username[25], password[25];
            printf("Username: ");
            scanf("%s", username);
            printf("Password: ");
            scanf("%s", password);
            userList *curr = validateUsernameLogIn(username, password);
            if(curr){
                printf("--Login Successfull--\n");
                int flagLogin = 1;
                while(flagLogin == 1){
                    printf("Oo====================================oO\n");
                    printf("Welcome, %s\n", curr->username);
                    printf("Oo====================================oO\n");
                    printf("Logged in: %s\n", curr->username);
                    printf("----------------------------------------\n\n");
                    printf("[All friends of %s\n", curr->username);//user
                    printf("No.\t Username\n");
                    printFriendList(curr);
                    printf("----------------------------------------\n");
                    printf("\t >>MENU<< \t\n");
                    printf("----------------------------------------\n");
                    printf("[1] Add Friend\n");
                    printf("[2] Remove Friend\n");
                    printf("[3] View Inbox\n");
                    printf("[4] View Sent Request\n");
                    printf("[5] Add,Edit,Announce,Delete Note\n");
                    printf("[6] Log Out\n");
                    printf("----------------------------------------\n");
                    printf(">> ");
                    int menuLogin;
                    scanf("%d", &menuLogin);
                    printf("----------------------------------------\n");
                    if(menuLogin == 1){
                        printf("[ All Users You Can Add ]\n"); //input nama
                        printf("No. \t Username\n");
                        printFriendToAdd(curr);
                        printf("Which user do you want to add?\n");
                        printf(">> ");
                        char addUsername[25];
                        scanf("%s", addUsername);
                        addFriend(curr, addUsername);
                        printf("--Your request has been sent to %s --\n", addUsername);
                    } else if(menuLogin == 2){
                        printf("[All Friend of  %s]\n", curr->username); //nama user
                        printf("No. \t Username\n");
                        printFriendList(curr);
                        printf("Which user d you want to remove?\n");
                        printf(">> ");
                        char removeUsername[25];
                        scanf("%s", removeUsername);
                        removeFriend(curr, removeUsername);
                        printf("--You are no longer friends with %s --\n", removeUsername);
                    } else if(menuLogin == 3){
                        printf("[All Friend Inbox of %s]\n", curr->username); //input nama
                        printf("No. \t Username\n");
                        printFriendInbox(curr);
                        printf("Which user do you want to cancel friend request?\n");
                        printf(">> ");
                        char cancelUsername[25];
                        scanf("%s", cancelUsername);
                        cancelFriendReq(curr, cancelUsername);
                        printf("--You canceled the friend request to %s--\n", cancelUsername);
                    } else if(menuLogin == 4){
                        printf("[All Friend Request of %s]\n", curr->username); //input nama
                        printf("No. \t Username\n");
                        printFriendReq(curr);
                        printf("Which user do you want to accepted?\n");
                        printf(">> ");
                        char accUsername[25];
                        scanf("%s", accUsername);
                        acceptFriend(curr, accUsername);
                        printf("--You accepted the request from %s--\n", accUsername);
                    } else if(menuLogin == 5){
                        printf("[1] Add Note\n");
                        printf("[2] Edit Note\n");
                        printf("[3] Announce Note\n");
                        printf("[4] Delete Note\n");
                        printf("----------------------------------------\n");
                        printf(">> ");
                        int menuNote;
                        scanf("%d", &menuNote);
                        printf("----------------------------------------\n");
                        if(menuNote == 1){
                            char titleNote[25], contentNote[255], categoryNote[25];
                            printf("Please type in title note [lowercase || 1..24]: ");
                            scanf("%s", titleNote);
                            printf("Please type in content note [lowercase || 1..224]: ");
                            scanf("%s", contentNote);
                            printf("----------------------------------------\n");
                            printf("[1] Backlog\n");
                            printf("[2] InProgress\n");
                            printf("[3] PeerReview\n");
                            printf("[4] InTest\n");
                            printf("[5] Done\n");
                            printf("[6] Blocked\n");
                            printf("Which category do you choose?\n");
                            printf(">> ");
                            scanf("%s", categoryNote);
                            if(validateNoteHeader(curr , titleNote)){
                                pushNote(curr, titleNote, contentNote, categoryNote);
                                printf("--Your note added successfully--\n");
                            } else {
                                printf("Note title is already in use\n");
                            }
                        } else if(menuNote == 2){
                            printf("[All Note of %s]\n", curr->username); //input nama
                            printf("No. \t Title\n");
                            printNote(curr);
                            printf("Which note do you want to edit?\n");
                            printf(">> ");
                            char oldTitle[25];
                            scanf("%s", oldTitle);
                            printf("----------------------------------------\n");
                            char titleNote[25], contentNote[255], categoryNote[25];
                            printf("Please type in new title note [lowercase || 1..24]: ");
                            scanf("%s", titleNote);
                            printf("Please type in new content note [lowercase || 1..224]: ");
                            scanf("%s", contentNote);
                            printf("----------------------------------------\n");
                            printf("[1] Backlog\n");
                            printf("[2] InProgress\n");
                            printf("[3] PeerReview\n");
                            printf("[4] InTest\n");
                            printf("[5] Done\n");
                            printf("[6] Blocked\n");
                            printf("Which category do you choose?\n");
                            printf(">> ");
                            scanf("%s", categoryNote);
                            editNote(curr, oldTitle, titleNote, contentNote, categoryNote);
                            printf("--Your note edited successfully--\n");
                        } else if(menuNote == 3){
                            printf("[All Note of %s]\n", curr->username); //input nama
                            printf("No. \t Title\n");
                            printNote(curr);
                            printf("Which note do you want to announce?\n");
                            printf(">> ");
                            char annTitle[25];
                            scanf("%s", annTitle);

                        } else if(menuNote == 4){
                            printf("[All Note of %s]\n", curr->username); //input nama
                            printf("No. \t Title\n");
                            printNote(curr);
                            printf("Which note do you want to delete?\n");
                            printf(">> ");
                            char rmvTitle[25];
                            scanf("%s", rmvTitle);
                            popNote(curr, rmvTitle);
                            printf("--Your note deleted successfully--\n");
                        }
                    } else if(menuLogin == 6){
                        curr = NULL;
                        flagLogin = 0;
                        break;
                    }
                }
            } else {
                printf("Wrong username or password\n");
            }
        } else if(menu == 3){
            printf("Thank You\n");
            globalFlag = 0;
            break;
        }
    }
    
    return 0;
}