#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "LibQueue.h"

void *safeMalloc(int n) {    
    void *a = malloc(n);
    if (a == NULL) {
        fprintf(stderr, "Fatal error: safeMalloc(%d) failed.\n", n);
        exit(EXIT_FAILURE);
    }
    return a;
}

int readNumber() {
  int i = 0;
  char line[12];
  assert( line != NULL );
  char c = getchar();
  while ( c != ' ' && c != '\n' ) {
    line[i] = c;
    i++;
    c = getchar();
  }
  line[i] = '\0';
  int num = atoi(line);
  return num;
}

Queue newQueue (int s) {
  Queue q;
  q.array = safeMalloc(s*sizeof(int));
  assert(q.array != NULL);
  q.back = 0;
  q.front = 0;
  q.size = s;
  return q;
}

void magicMirror (Queue *q, int N) {
  int vac = q->size - q->back + q->front, rest = N - q->back;
  int num = ( vac < rest ) ? vac : rest;
  // printf("Mirror Num: %d \n",num);
  for (int i = 0; i < num; i++) {
    int price = readNumber();
    enqueue(price, q);
    // printf("%d ",price);
  }
  // printf("\n");
}

long int dynamicSkip (Queue *q, int h, int c) {
  int qf = q->front, qs = q->size, pos = 0;
  long int s = sumQueue(q, qf, h + c), temp = sumQueue(q, qf + h, c), newSum = s;
  //printf("No Skip: %d\nSkip 1: %d\n",s, temp);
  s = (s <= temp)? s : temp;
  for (int i = 0; i < h + c - 1; i++) {
    temp = temp + q->array[(qf + i) % qs] - q->array[(qf + h + i) % qs] + q->array[(qf + h + c + i) % qs];
    newSum += q->array[(qf + h + c + i) % qs];
    if ( temp < s ) { s = temp; pos = i + 1; }
    if ( newSum < s ) { s = newSum; pos = i + 1; }
    //printf("Skip %d: %d \n", qf + i+2 ,temp);
  }
  dequeue(q, h + c + pos);
  //printf("Optimal Skip: %d, Pos: %d  \n",s, pos + qf+1);
  return s;
}

long int sumQueue (Queue *q, int pos, int num) {
  int s = 0;
  for (int i = 0; i < num; i++) { s += q->array[ (pos + i) % q->size ]; }
  return s;
}

long int bruteSkip (Queue *q, int qf, int h, int c) {
  int num = q->back - qf, qs = q->size;
  long int s = sumQueue(q, qf, num), temp;
  if (num < h) { return s ; }
  if (num < 2 * h + c) {
    temp = sumQueue(q, qf + h, num - h);
    s = (s <= temp)? s : temp;
    for (int i = 0; i < num - h; i++) {
      temp = temp + q->array[(qf + i) % qs] - q->array[(qf + h + i) % qs];
      s = (s <= temp)? s : temp;
    }
    return s;
  }
  temp = sumQueue(q, qf + h, c);
  int newf = qf + h + c, noSkip = sumQueue(q, qf, h);
  int newSum = temp + bruteSkip(q, newf, h, c);
  newSum = (noSkip < 0) ? newSum + noSkip : newSum;
  s = (s <= newSum)? s : newSum;
  for (int i = 0; i < num - h - c; i++) {
    temp = temp + q->array[(qf + i) % qs] - q->array[(qf + h + i) % qs] + q->array[(qf + h + c + i) % qs];
    noSkip = noSkip + q->array[(qf + h + i) % qs] - q->array[(qf + i) % qs];
    newSum = (noSkip < 0) ? temp + noSkip : temp;
    newSum += bruteSkip(q, newf + i + 1, h, c);
    
    s = (s < newSum)? s : newSum;
  }
  // printf("Brute Force: %d, new front: %d\n",s, newf);
  return s;
}

void enqueue (int item, Queue *qp) {
  qp->array[qp->back % qp->size] = item; qp->back ++;
  if ( qp->back == qp->front ) {
    doubleQueueSize(qp);
  }
}

void dequeue (Queue *qp, int num) {
  if (isEmptyQueue(*qp)) { queueEmptyError(); }
  //for (int i = 0; i < num; i++) { printf("%d ",qp->array[(qp->front+i)%qp->size]); }
  qp->front += num;
  //printf("\n");
}

void freeQueue (Queue q) {
  free(q.array);
}



int isEmptyQueue (Queue q) {
  return (q.back == q.front);
}

void queueEmptyError() {
  printf("queue empty\n");
  abort();
}

void doubleQueueSize (Queue *qp) {
  int i;
  int oldSize = qp->size;
  qp->size = 2 * oldSize;
  qp->array = realloc(qp->array, qp->size * sizeof(int));
  assert(qp->array != NULL);
  for (i=0; i < qp->back ; i++) { /* eliminate the split configuration */
    qp->array[oldSize + i] = qp->array[i];
  }
  qp->back = qp->back + oldSize;  /* update qp->back */
}
