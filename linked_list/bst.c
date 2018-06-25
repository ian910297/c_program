#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Node.h"

void Load();
void Insert();
void Search();
void FreeDFS();
void ShowDFS();
void bfs();

int main(int argc, char *argv[]) {
    char *filename = argv[1];
    TREE_NODE *root = NULL;
    printf("The pointer of root address: %p\n", &root);

    printf("Load start\n");
    Load(&root, filename);
    //ShowDFS(root);

    printf("Free start\n");
    FreeDFS(root);
    printf("Free end\n");

    return 0;
}

void Load(TREE_NODE **root, char *filename) {
    FILE *fp;
    char data[STRING_LENGTH];
    fp = fopen(filename, "r");

    printf("The pointer of pointer of address: %p\n", &root);

    while(fscanf(fp, "%s", data)!=EOF) {
        //printf("root value's address: %p\n", *root);
        //printf("The pointer of root address: %p\n", &*root);
        Insert(&*root, data);
    }

    fclose(fp);
}

void Insert(TREE_NODE **root, char data[STRING_LENGTH]) {
    TREE_NODE *cur, *parent = NULL;
    cur = *root;
    int cmp;

    //printf("cur value's address: %p\n", cur);

    while(cur!=NULL) {
        parent = cur;
        cmp = strcmp(cur->data, data);

        if(cmp<0) {
            cur = cur->left;
        } else {
            cur = cur->right;
        }
    }

    TREE_NODE *new = malloc(sizeof(TREE_NODE));
    strcpy(new->data, data);
    new->left = new->right = NULL;

    if(parent==NULL) {// First node
        printf("First Insert\n");
        *root = new;
    } else if(cmp<0) {
        parent->left = new;
    } else {
        parent->right = new;
    }
}

void ShowDFS(TREE_NODE *cur) {
    if(cur==NULL) {
        return;
    }
    
    printf("(left)\n");
    ShowDFS(cur->left);
    printf("%s\n", cur->data);
    
    printf("(right)\n");
    ShowDFS(cur->right);
}

void FreeDFS(TREE_NODE *cur) {
    if(cur==NULL) {
        return;
    }

    FreeDFS(cur->left);
    FreeDFS(cur->right);
    free(cur);
}

