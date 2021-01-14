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

struct commentNotes {
    char username[25];
    char comment[255];
    commentNotes *next, *prev;
};

struct recycleBin {
    char content[255];
    int category;
    int like;
    int privateOrPublic;
    recycleBin *next, *prev;
};

struct userList {
    char username[25];
    char password[25];
    friendList *head, *tail;
    friendInbox *head, *tail;
    friendReq *head, *tail;
    userList *next, *prev;
} *headUser, *tailUser;

struct note {
    char username[25];
    char content[255];
    int category;
    int like;
    int privateOrPublic;
    commentNotes *head, *tail;
    note *next, *prev;
} *headNote, *taillNote;