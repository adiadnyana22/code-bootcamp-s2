#include <stdio.h>
#include <stdlib.h>

struct friendList {
    char username[25];
    friendList *next, *prev;
};

struct friendInbox {
    char username[25];
    friendInbox *next, *prev;
};

struct friendReq {
    char username[25];
    friendReq *next, *prev;
};

struct userList {
    char username[25];
    char password[25];
    friendList *head, *tail;
    friendInbox *head, *tail;
    friendReq *head, *tail;
};