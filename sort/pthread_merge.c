#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <pthread.h>

#define DATASET_SIZE 5

typedef struct __SET {
    int *data;
    int size;
} SET;

void* PDivide(void* input);
void merge(SET *left, SET *right);
void Show(int *cur, int size);

int main() {
    srand(time(NULL));

    SET *dataset;
    dataset = malloc(sizeof(SET));
    dataset->data = malloc(sizeof(int)*DATASET_SIZE);
    dataset->size = DATASET_SIZE;

    for(int i=0; i<DATASET_SIZE; i++) {
        dataset->data[i] = rand();
    }

    printf("Init\n");
    Show(dataset->data, DATASET_SIZE);

    pthread_t root;
    pthread_create(&root, NULL, PDivide, dataset);
    pthread_join(root, NULL);
    
    printf("Sorted\n");
    Show(dataset->data, DATASET_SIZE);
    
    
    free(dataset->data);
    free(dataset);

    return 0;
}

void merge(SET *left, SET *right) {
    int size = left->size + right->size;
    int *new = malloc(sizeof(int) * size);
    int left_index;
    int right_index;
    left_index = right_index = 0;
    
    for(int i=0; i<size; i++) {
        //printf("(left, right) = (%d, %d)\n", left.data[left_index], right.data[right_index]);
        if(left_index == left->size) {
            new[i] = right->data[right_index++];
        } else if(right_index == right->size) {
            new[i] = left->data[left_index++];
        } else if(left->data[left_index] < right->data[right_index]) {
            new[i] = left->data[left_index++];
        } else if(left->data[left_index] >= right->data[right_index]){
            new[i] = right->data[right_index++];
        }
    }

    memcpy(left->data, new, sizeof(int)*size);
    free(new);
}

void* PDivide(void* input) {
    SET* parent = (SET*)input;
    int half = parent->size / 2;
    if(half==0) {
        pthread_exit(NULL);
    }

    SET *left, *right;
    left = malloc(sizeof(SET));
    right = malloc(sizeof(SET));
    left->data = parent->data;
    left->size = half;

    right->data = parent->data + half;
    right->size = parent->size - half;

    pthread_t t_left, t_right;
    pthread_create(&t_left, NULL, (void*)PDivide, left);
    pthread_create(&t_right, NULL, (void*)PDivide, right);

    pthread_join(t_left, NULL);
    pthread_join(t_right, NULL);

    merge(left, right);

    free(left);
    free(right);
    pthread_exit(NULL);
}

void Show(int *cur, int size) {
    for(int i=0; i<size; i++) {
        printf("[%d]: %d\n", i, cur[i]);
    }
}

