#include "locked_queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>

l_queue* q;
pthread_t thread1; 
pthread_t thread2;


void* add_elements(void* blank);
void* remove_elements(void* blank);

int main(int argc, char const *argv[])
{
    q = q_queue_alloc();
    printf("testing basic functionality\n");
    printf("result of isempty test: %d\n", q_is_empty(q));
    printf("testing enqueue\n");
    int* pnt = malloc(sizeof(int));
    *pnt = 1;
    printf("adding pointer %p to queue\n", pnt);
    q_enqueue(q, pnt);
    printf("value of 1 should be added to queue\n");
    printf("checking - empty status: %d\nchecking - size: %d\n", q_is_empty(q), q_size(q));
    printf("testing dequeue\n");
    int* ret;
    printf("value of pointer before fill %p\n", ret);
    printf("dequeue status returned as: %d\n", q_dequeue(q, (void**) &ret));
    printf("returned pointer %p\n", ret);
    printf("value of %d was pulled from the queue\n", *ret);
    printf("checking - empty status: %d\nchecking - size: %d\n", q_is_empty(q), q_size(q));
    free(ret);
    pthread_create(&thread2, NULL, &remove_elements, NULL);
    pthread_create(&thread1, NULL, &add_elements, NULL);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    q_free_queue(q, free);
    return 0;
}

void* add_elements(void* blank) {
    for (int i = 0; i < 100; i++) {
        int* pnt = malloc(sizeof(int));
        *pnt = i;
        printf("adding %d to queue\n", *pnt);
        q_enqueue(q, pnt);
    }
    q_kill(q);
    return NULL;
}


void* remove_elements(void* blank) {
    for (int j = 0; j < 150; j++) {
        int* ret;
        if (q_dequeue(q, (void**) &ret) == -1) {
            printf("nothing left to dequeue\n");
            return NULL;
        };
        printf("ret = %d \n", *ret);
        free(ret);
    }
    return NULL;
}