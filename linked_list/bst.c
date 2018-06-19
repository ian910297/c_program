#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Node.h"

TREE_NODE* Init();
void Load();
void Insert();
void Search();
void FreeDFS();
void ShowDFS();
void bfs();

int main(int argc, char *argv[]) {
    char *filename = argv[1];
    TREE_NODE *root = Init();

    printf("Load start\n");
    Load(root, filename);

    ShowDFS(root);

    printf("Free start\n");
    FreeDFS(root);
    printf("Free end\n");

    return 0;
}

TREE_NODE* Init() {
    TREE_NODE *root = malloc(sizeof(TREE_NODE));
    root->data[0] = '\0';

    return root;
}

void Load(TREE_NODE *root, char *filename) {
    FILE *fp;
    char data[STRING_LENGTH];
    fp = fopen(filename, "r");

    while(fscanf(fp, "%s", data)!=EOF) {
        Insert(root, data);
    }

    fclose(fp);
}

void Insert(TREE_NODE *root, char data[STRING_LENGTH]) {
    // First node
    if(root->data[0]=='\0') {
        strcpy(root->data, data);
        return;
    }

    TREE_NODE *cur, *parent;
    cur = root;
    int cmp;

    while(cur!=NULL) {
        parent = cur;
        cmp = strcmp(cur->data, data);

        if(cmp<0) {
            cur = cur->left;
        } else if(cmp>0) {
            cur = cur->right;
        }
    }

    if(cmp==0) {
        return;
    }

    TREE_NODE *new = malloc(sizeof(TREE_NODE));
    strcpy(new->data, data);
    new->left = new->right = NULL;

    if(cmp<0) {
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

