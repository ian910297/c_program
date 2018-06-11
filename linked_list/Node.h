#pragma once

typedef struct __SINGLY_NODE {
    int value;
    struct __SINGLY_NODE *next;
} SINGLY_NODE;

typedef struct __SINGLY_LIST {
    SINGLY_NODE* head;
} SINGLY_LIST;

