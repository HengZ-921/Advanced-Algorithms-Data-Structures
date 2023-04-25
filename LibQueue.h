/* based on queueTypeAndFunctions.c by Gerard Renardel, 31 January 2018 */

#ifndef LIBQUEUE_H
#define LIBQUEUE_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

typedef struct Queue {
  short *array;
  short back;
  short front;
  short size;
} Queue;

Queue newQueue(short s);
short isEmptyQueue(Queue q);
void queueEmptyError();
void doubleQueueSize(Queue *qp);
void enqueue(short item, Queue *qp);
short dequeue(Queue *qp);
void freeQueue(Queue q);

#endif
