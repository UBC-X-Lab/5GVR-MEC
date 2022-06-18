#ifndef LOCKED_QUEUE_H
#define LOCKED_QUEUE_H

#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct queue_node {
    struct queue_node* next;
    struct queue_node* prev;
    void* data;
} node;

typedef struct locked_queue {
    pthread_mutex_t mutex;
    pthread_cond_t avail;
    bool kill;
    bool ready;
    node* head;
    node* tail;
    int size;
    char* PORT;
    struct timespec ts;
    struct timeval tv;
} l_queue;

// sets ready to true (mutex safe)
void q_ready(l_queue* q);

// sets kill to true (mutex safe)
void q_kill(l_queue* q);

// returns true if the locked_queue is dead
bool q_is_dead(l_queue* q);

// allocates empty queue
l_queue* q_queue_alloc();

// allocates node with passed data and pntr to node passed as next
node* q_node_alloc(node* next_node, void* datav);

// destroys the queue calling finalizer on every element contained. Should only be called after all other interaction with queue is complete
void q_free_queue(l_queue* q, void (*finalizer)(void*));

// frees node
void q_free_node(node* n);

// places new node on queue at tail with data passed
void q_enqueue(l_queue* q, void* data);

// pops node from head and stores data in output passed, takes care of deallocation of node
int q_dequeue(l_queue* q, void** output);

// return true if queue is empty
bool q_is_empty(l_queue* q);

// return the size of queue
int q_size(l_queue *q);

#endif