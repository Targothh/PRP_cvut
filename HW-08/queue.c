#include "queue.h"

queue_t* create_queue(int capacity){
    queue_t *temp =  (queue_t *) malloc(sizeof(queue_t));
    temp -> size = capacity;
    temp -> element = (void **) malloc(capacity * sizeof(void *));
    temp -> end = 0;
    temp -> start = 0;
    temp -> current_size = 0;
    return temp;
}

void delete_queue(queue_t *queue){
    free(queue -> element);
    free(queue);
}

bool push_to_queue(queue_t *queue, void *data){
    if (queue -> current_size >= queue -> size){
        void **new_element = (void **) malloc((queue -> size * 2) * sizeof(void *));
        for (int i = 0; i < queue -> current_size; i++){
            new_element[i] = queue -> element[(queue -> start + i) % queue->size];
        }
        queue -> size = queue -> size * 2;
        queue -> start = 0;
        queue -> end = queue -> current_size; // -1 kvuli poli
        free(queue -> element);
        queue -> element = new_element;
    }
    queue -> element[queue -> end] = data;
    queue -> end = (queue -> end + 1) % queue -> size;
    queue -> current_size = queue -> current_size + 1;
    return 1;
}

void* pop_from_queue(queue_t *queue){
    if(queue -> current_size == 0){
        return NULL;
    }
    if(queue -> current_size < (queue -> size /3)){
        void **new_element = (void **) malloc((queue -> size/3) * sizeof(void *));
        for (int i = 0; i < queue -> current_size; i++){
            new_element[i] = queue -> element[(queue -> start + i) % queue->size];
        }
        queue -> size = queue -> size / 3;
        queue -> start = 0;
        queue -> end = queue -> current_size; // -1 kvuli poli
        free(queue -> element);
        queue -> element = new_element;
    }
    void *ret = queue -> element[queue -> start];
    queue -> start = (queue -> start + 1) % queue -> size;
    queue -> current_size = queue -> current_size - 1;
    //printf("%d",queue -> size);
    return ret;
}

void* get_from_queue(queue_t *queue, int idx){
    if(idx < 0){
        return NULL;
    }
    if(idx >= queue-> current_size){
		return NULL;
    }
    int index = (queue -> start + idx) % queue -> size;
    void *ret = queue -> element[index];
    return ret;
}

int get_queue_size(queue_t *queue){
    return queue -> current_size;
}
