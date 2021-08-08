#include "locked_queue.h"
#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/time.h>
#include <errno.h>

void q_kill(l_queue* q) {
    pthread_mutex_lock(&q->mutex);
    pthread_cond_broadcast(&q->avail);
    q->kill = true;
    pthread_mutex_unlock(&q->mutex);
}

void q_ready(l_queue* q) {
    pthread_mutex_lock(&q->mutex);
    q->ready = true;
    pthread_mutex_unlock(&q->mutex);
}

bool q_is_dead(l_queue* q) {
    pthread_mutex_lock(&q->mutex);
    bool val = q->kill;
    pthread_mutex_unlock(&q->mutex);
    return val;
}

bool q_is_empty(l_queue* q) {
    pthread_mutex_lock(&q->mutex);
    bool ret = (q->size <= 0);
    pthread_mutex_unlock(&q->mutex);
    return ret; 
}

int q_size(l_queue* q) {
    pthread_mutex_lock(&q->mutex);
    bool ret = q->size;
    pthread_mutex_unlock(&q->mutex);
    return ret; 
}

l_queue* q_queue_alloc() {
    l_queue* q = malloc(sizeof(l_queue));
    q->head = NULL;
    q->tail = NULL;
    if (pthread_mutex_init(&q->mutex, NULL)) {
        printf("locked queue failed to create mutex\n");
        abort();
    }
    if (pthread_cond_init(&q->avail, NULL)) {
        printf("locked queue failed to create condition variable\n");
        abort();
    }
    q->size = 0;
    q->kill = false;
    q->ready = false;
    return q; 
}

node* q_node_alloc(node* next_node, void* datav) {
    node* node = malloc(sizeof(node));
    node->next = next_node;
    //printf("setting node data to %p\n", datav);
    node->data = datav;
    //printf("node data set to %p\n", node->data);
    return node;
}

void q_enqueue(l_queue* q, void* data) {
    pthread_mutex_lock(&q->mutex); 
    node* tmp = q_node_alloc(NULL, data);
    if (q->head == NULL) {
        q->head = tmp;
    }
    if (q->tail != NULL) {
        q->tail->next = tmp;
    }
    q->tail = tmp;
    q->size++;
    pthread_cond_signal(&q->avail);
    pthread_mutex_unlock(&q->mutex);
}

int q_dequeue(l_queue* q, void** output) {
    pthread_mutex_lock(&q->mutex);
    while (q->size <= 0) {
        //printf("waiting for elements on queue\n");
        if (q->kill == true) {
            printf("kill signal recieved\n");
            pthread_mutex_unlock(&q->mutex);
            return -1;
        }

        /* set time for wait timeout
        gettimeofday(&q->tv, NULL);
        q->ts.tv_sec = q->tv.tv_sec+5;
        q->ts.tv_nsec = (q->tv.tv_usec+1000UL*10)*1000UL;
        */

        //printf("waiting on avail\n");
        pthread_cond_wait(&q->avail, &q->mutex);
        /*
        if (pthread_cond_timedwait(&q->avail, &q->mutex, &q->ts) == ETIMEDOUT) {
            continue;
        }
        //printf("returned from wait\n");
        */
    }
    node* front = q->head;
    assert(front != NULL);
    // move head to next item in list
    q->head = front->next;
    if (q->head == NULL) {
        // list is now empty set tail to NULL too
        q->tail = NULL;
    }
    q->size--;
    pthread_mutex_unlock(&q->mutex);
    *output = front->data;
    q_free_node(front);
    return 0;
}

void q_free_node(node* n) {
    free(n);
}

typedef void (*finalizer)(void*);
void q_free_queue(l_queue* q, finalizer fn) {
    if(q_is_empty(q)) {
        pthread_mutex_destroy(&q->mutex);
        pthread_cond_destroy(&q->avail);
        free(q);
        return;
    }
    void* pnt;
    if (q_dequeue(q, &pnt) == -1) {
        printf ("error occured removing head\n");
        abort();
    }
    // Definite Memory leak need to provide finalizer for data
    if (fn != NULL) {fn(pnt);}
    q_free_queue(q, fn);
}