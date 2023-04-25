/* The queue implementation is adapted from ADS. */

#ifndef LIBQUEUE_H
#define LIBQUEUE_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

typedef struct Queue {
  int *array;
  int back;
  int front;
  int size;
} Queue;

void *safeMalloc(int n);
int readNumber();

void magicMirror (Queue *q, int N);
long int sumQueue (Queue *q, int pos, int num);
long int dynamicSkip (Queue *q, int h, int c);
long int bruteSkip (Queue *q, int qf, int h, int c);

Queue newQueue(int s);
void enqueue(int item, Queue *qp);
void dequeue(Queue *qp, int num);
void freeQueue(Queue q);

int isEmptyQueue(Queue q);
void queueEmptyError();
void doubleQueueSize(Queue *qp);



#endif
