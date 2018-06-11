#include <stdio.h>
#include <stdlib.h>
#include "Node.h"

SINGLY_NODE* Create(SINGLY_NODE *head, int value);
SINGLY_NODE* Insert(SINGLY_NODE *node, int value);
void DeletePro(SINGLY_LIST *list, SINGLY_NODE *target);
void Show(SINGLY_NODE *head);

int main(int argc, char *argv[]) {
    
    SINGLY_NODE *head=NULL;

    head = Create(head, 12345);
    Show(head);

    free(head);

    return 0;
}

SINGLY_NODE* Create(SINGLY_NODE *head, int value) {
    SINGLY_NODE *cur = head;

    for( ; value>0; value/=10) {
        cur = Insert(cur, value%10);
    }

    return cur;
}

SINGLY_NODE* Insert(SINGLY_NODE *node, int value) {
    SINGLY_NODE *new;
    new = malloc(sizeof(SINGLY_NODE));
    new->value = value;
    new->next = node;

    return new;
}

void DeletePro(SINGLY_LIST *list, SINGLY_NODE *target) {
    SINGLY_NODE** indirect = &list->head;

    while(*indirect != target)
        indirect = &(*indirect)->next;

    *indirect = target->next;
}

void Show(SINGLY_NODE *head) {
    int i;
    SINGLY_NODE *cur = head;

    for(i=0; cur; i++, cur=cur->next) {
        printf("[%d]: %d\n", i, cur->value);
    }
}

