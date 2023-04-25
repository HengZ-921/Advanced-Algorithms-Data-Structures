#ifndef HEAP_H
#define HEAP_H

/* The strategy for this challenge is to use heap to build a priority queue of time used,
 * the main function startProduction is a while loop, keep subtracting number of produced laptops
 * from the request number. Each time of subtraction, the factory another period of the factory
 * will be added to the corresponding element in the cumulative time priority queue,
 * and this new time will be sort to the proper position in the priority queue.
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#define N 11

typedef long int lint;

typedef struct Heap {
  lint *qAr;
  lint front;
} Heap;

void *safeMalloc(lint n);
lint readNumber();
char *readID();
Heap makeHeap(lint Length);

void enqueue(char *id, lint lv, Heap *hp, char *idAr);
void swap ( int a, int b, char *idAr, lint *qAr);
void upheap(Heap *hp, char *idAr, lint fr);
void downheap(Heap *hp, lint Length, lint num, char *idAr);
void freeHeap(Heap hp);

void initList(Heap *hp, lint Length, char *idAr);
void modifyList(Heap *hp, lint visit, lint total, char *idAr);

lint partition(lint Length, char *idAr, lint *qAr);
void quickSort(lint Length, char *idAr, lint *qAr);

#endif