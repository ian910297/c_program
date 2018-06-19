#pragma once
#define STRING_LENGTH 50

typedef struct __SINGLY_NODE {
    int value;
    struct __SINGLY_NODE *next;
} SINGLY_NODE;

typedef struct __SINGLY_LIST {
    SINGLY_NODE* head;
} SINGLY_LIST;

typedef struct __TREE_NODE {
    char data[STRING_LENGTH];
    struct __TREE_NODE *left;
    struct __TREE_NODE *right;
} TREE_NODE;

typedef struct __HASH_NODE {
    int times;
    char data[STRING_LENGTH];
    struct __HASH_NODE *next;
} HASH_NODE;

