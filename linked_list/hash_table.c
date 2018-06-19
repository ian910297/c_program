#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "Node.h"
#define TABLE_SIZE 100000
#define djb2

HASH_NODE** Init();
void Load();
void Insert();
void Show();
void Free();

// "unsigned long" equals to "unsigned long int".
unsigned long Hash(unsigned char *str);

int main(int argv, char *argc[]) {
    char *dictionary;
    dictionary = argc[1];
    printf("Dictionary: %s\n", dictionary);

    printf("Init start\n");
    HASH_NODE **table = Init();
    printf("Init end\n");


    printf("Load start\n");
    Load(table, dictionary);
    printf("Load end\n");

    printf("Free memory start\n");
    Free(table);
    printf("Free memory end\n");

    return 0;
}

HASH_NODE** Init() {
    int i;
    HASH_NODE **table = malloc(sizeof(HASH_NODE*) * TABLE_SIZE);

    for(i=0; i<TABLE_SIZE; i++) {
        table[i] = malloc(sizeof(HASH_NODE));
        table[i]->times = 0;
        table[i]->data[0] = '\0';
        table[i]->next = NULL;
    }

    return table;
}

void Load(HASH_NODE **table, char *dictionary) {
    FILE *fp;
    char data[STRING_LENGTH];
    fp = fopen(dictionary, "r");
    while(fscanf(fp, "%s", data)!=EOF) {
        unsigned long hash_index = Hash(data);
        Insert(table[hash_index], data);
    }
    fclose(fp);
}

void Insert(HASH_NODE *cur, char *data) {
    while(cur->next!=NULL) {
        if(strcmp(cur->data, data)==0) {
            return;
        }
        cur = cur->next;
    }

    HASH_NODE *new = malloc(sizeof(HASH_NODE));
    new->times = 0;
    strcpy(cur->data, data);
    new->next = NULL;

    cur->next = new;
}

void Free(HASH_NODE **table) {
    HASH_NODE *cur, *prev;
    for(int i=0; i<TABLE_SIZE; i++) {
        //printf("[%d]\n", i);
        cur = prev = table[i];
        while(cur->next!=NULL) {
            cur = cur->next;
            free(prev);
            prev = cur;
        }
        free(cur);
    }
    free(table);
}

void Show(HASH_NODE **table) {
    HASH_NODE *cur;
    for(int i=0; i<TABLE_SIZE; i++) {
        cur = table[i];
        printf("[%d]: ", i);
        while(cur->next!=NULL) {
            printf("%s->", cur->data);
            cur = cur->next;
        }
        printf("%s\n", cur->data);
    }
}

#ifdef djb2
unsigned long Hash(unsigned char *str) {
    unsigned long hash = 5381;
    int c;

    while(c=*str++) {
        // hash * 33 + c
        hash = ((hash<<5) + hash) + c;
    }

    return hash % TABLE_SIZE;
}
#endif

