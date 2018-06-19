#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define DATASET_SIZE 5

typedef struct __SET {
    int *data;
    int size;
} SET;

void divide(SET parent);
void merge(SET left, SET right);
void Show(int *cur, int size);

int main() {
    srand(time(NULL));

    SET dataset;
    dataset.data = malloc(sizeof(int)*DATASET_SIZE);
    dataset.size = DATASET_SIZE;

    for(int i=0; i<DATASET_SIZE; i++) {
        dataset.data[i] = rand();
    }

    Show(dataset.data, DATASET_SIZE);

    divide(dataset);
    
    Show(dataset.data, DATASET_SIZE);
    

    free(dataset.data);
    return 0;
}

void divide(SET parent) {
    int half = parent.size / 2;
    if(half==0) {
        return;
    }

    SET left, right;
    left.data = parent.data;
    left.size = half;

    right.data = parent.data + half;
    right.size = parent.size - half;

    divide(left);
    divide(right);
    
    //printf("(parent size, left size, right size) = (%d, %d, %d)\n", parent.size, left.size, right.size);
    //Show(left.data, left.size);
    //Show(right.data, right.size);
    
    merge(left, right);
}

void merge(SET left, SET right) {
    int size = left.size + right.size;
    int *new = malloc(sizeof(int) * size);
    int left_index;
    int right_index;
    left_index = right_index = 0;
    
    for(int i=0; i<size; i++) {
        //printf("(left, right) = (%d, %d)\n", left.data[left_index], right.data[right_index]);
        if(left_index == left.size) {
            new[i] = right.data[right_index++];
        } else if(right_index == right.size) {
            new[i] = left.data[left_index++];
        } else if(left.data[left_index] < right.data[right_index]) {
            new[i] = left.data[left_index++];
        } else if(left.data[left_index] >= right.data[right_index]){
            new[i] = right.data[right_index++];
        }
    }

    memcpy(left.data, new, sizeof(int)*size);
    free(new);
}

void Show(int *cur, int size) {
    for(int i=0; i<size; i++) {
        printf("[%d]: %d\n", i, cur[i]);
    }
}

